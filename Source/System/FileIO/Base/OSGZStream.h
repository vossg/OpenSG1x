/*
zipstream Library License:
--------------------------

The zlib/libpng License Copyright (c) 2003 Jonathan de Halleux.

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution

Author: Jonathan de Halleux, dehalleux@pelikhan.com, 2003

Altered by: Andreas Zieringer 2003
            made it platform independent, gzip conform, fixed gzip footer)
*/

#ifndef _OSGZSTREAM_H_
#define _OSGZSTREAM_H_

#undef OSG_ZSTREAM_SUPPORTED
// The zlib is only linked into the OSGSystem lib when png support is enabled.
// We should link it into the BaseLib and move this header file to Base and
// define something like OSG_WITH_ZLIB via a new configure option --with-zlib=...
// This platforms are not tested yet __hpux __sun
#if defined(OSG_WITH_PNG) && (defined(__hpux) || defined(__sgi) || defined(WIN32) || (defined(__linux) && __GNUC__ == 3))
#define OSG_ZSTREAM_SUPPORTED
#endif

#ifdef OSG_ZSTREAM_SUPPORTED

#include <vector>
#include <string>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <zlib.h>

#ifdef WIN32 /* Window 95 & Windows NT */
#  define OS_CODE  0x0b
#endif
#if defined(MACOS) || defined(TARGET_OS_MAC)
#  define OS_CODE  0x07
#endif
#ifndef OS_CODE
#  define OS_CODE  0x03  /* assume Unix */
#endif

#ifdef OSG_WIN32_CL
#pragma warning(disable : 4355)
#endif

OSG_BEGIN_NAMESPACE

namespace detail
{
	const int gz_magic[2] = {0x1f, 0x8b}; /* gzip magic header */

	/* gzip flag byte */
	const int gz_ascii_flag =  0x01; /* bit 0 set: file probably ascii text */
	const int gz_head_crc    = 0x02; /* bit 1 set: header CRC present */
	const int gz_extra_field = 0x04; /* bit 2 set: extra field present */
	const int gz_orig_name  =  0x08; /* bit 3 set: original file name present */
	const int gz_comment    =  0x10; /* bit 4 set: file comment present */
	const int gz_reserved   =  0xE0; /* bits 5..7: reserved */	
}

/// default gzip buffer size,
/// change this to suite your needs
const size_t zstream_default_buffer_size = 4096;

/// Compression strategy, see zlib doc.
enum EStrategy
{
	StrategyFiltered = 1,
	StrategyHuffmanOnly = 2,
	DefaultStrategy = 0
};

/** \brief A stream decorator that takes raw input and zips it to a ostream.

The class wraps up the inflate method of the zlib library 1.1.4 http://www.gzip.org/zlib/
*/
template <class charT,
          class traits = std::char_traits<charT> >
class basic_zip_streambuf : public std::basic_streambuf<charT, traits>
{
public:
	typedef std::basic_ostream<charT, traits>& ostream_reference;
	typedef unsigned char byte_type;
    typedef char          char_type;
	typedef byte_type* byte_buffer_type;
	typedef std::vector<byte_type> byte_vector_type;
	typedef std::vector<char_type> char_vector_type;
    typedef int int_type;
    typedef basic_zip_streambuf Self;
    typedef std::basic_streambuf<charT, traits> Inherited;

    /** Construct a zip stream
     * More info on the following parameters can be found in the zlib documentation.
     */
	/// returns a reference to the output stream
	ostream_reference get_ostream(void) const
    {
        return _ostream;
    }
	/// returns the latest zlib error status
	int get_zerr(void) const
    {
        return _err;
    }
	/// returns the crc of the input data compressed so far.
	unsigned long get_crc(void) const
    {
        return _crc;
    }
	/// returns the size (bytes) of the input data compressed so far.
	unsigned long get_in_size(void) const
    {
        return _zip_stream.total_in;
    }
	/// returns the size (bytes) of the compressed data so far.
	long get_out_size(void) const
    {
        return _zip_stream.total_out;
    }

    basic_zip_streambuf(ostream_reference ostream,
                        int level,
                        EStrategy strategy,
                        int window_size,
                        int memory_level,
                        size_t buffer_size) : 
		_ostream(ostream),
		_output_buffer(buffer_size, 0),
		_buffer(buffer_size, 0),
		_crc(0)
	{
		_zip_stream.zalloc = (alloc_func) 0;
		_zip_stream.zfree = (free_func) 0;

		_zip_stream.next_in = NULL;
		_zip_stream.avail_in = 0;
		_zip_stream.avail_out = 0;
		_zip_stream.next_out = NULL;

        if(level > 9)
            level = 9;
        
        if(memory_level > 9)
            memory_level = 9;
        
		_err=deflateInit2(&_zip_stream, level, Z_DEFLATED,
                          window_size, memory_level,
                          static_cast<int>(strategy));

		setp( &(_buffer[0]), &(_buffer[_buffer.size()-1]));
	}

	~basic_zip_streambuf(void)
	{
		flush();
		_ostream.flush();
		_err=deflateEnd(&_zip_stream);
	}

	int sync(void)
	{ 
		if(this->pptr() && this->pptr() > this->pbase()) 
		{
			/*int c =*/ overflow(EOF);

            // ACHTUNG wenn das drin ist hoert er nach dem ersten endl auf!
            /*
			if ( c == EOF)
				return -1;
            */
        }

        return 0;
	}

    
	int_type overflow(int_type c)
	{ 
        int w = static_cast<int>(this->pptr() - this->pbase());
        if (c != EOF)
        {
            *(this->pptr()) = c;
            ++w;
        }
        if (zip_to_stream(this->pbase(), w))
        {
             setp(this->pbase(), this->epptr() - 1);
             return c;
        }
        else
        {
            return EOF;
        }
	}

    /** flushes the zip buffer and output buffer.

	This method should be called at the end of the compression. Calling flush multiple times, will lower the
	compression ratio.
	*/
	std::streamsize flush(void)
	{
		std::streamsize written_byte_size = 0, total_written_byte_size = 0;

		size_t remainder = 0;

		// updating crc
		_crc = crc32(_crc,  _zip_stream.next_in,
                     _zip_stream.avail_in);		

		do
		{
			_err = deflate(&_zip_stream, Z_FINISH);
			if(_err == Z_OK || _err == Z_STREAM_END)
			{
				written_byte_size = static_cast<std::streamsize>(_output_buffer.size()) - _zip_stream.avail_out;
				total_written_byte_size += written_byte_size;
				// ouput buffer is full, dumping to ostream
				_ostream.write( (const char_type*) &(_output_buffer[0]), 
					static_cast<std::streamsize>(written_byte_size/sizeof(char_type)*sizeof(char)));
			
				// checking if some bytes were not written.
				if((remainder = written_byte_size%sizeof(char_type)) != 0)
				{
					// copy to the beginning of the stream
					memcpy(&(_output_buffer[0]), 
                           &(_output_buffer[written_byte_size-remainder]), remainder);
					
				}
				
				_zip_stream.avail_out = static_cast<uInt>(_output_buffer.size() - remainder);
				_zip_stream.next_out = &_output_buffer[remainder];
			}
		}
        while(_err == Z_OK);

		_ostream.flush();

		return total_written_byte_size;
	}
    

private:
    
	bool zip_to_stream(char_type *buffer, std::streamsize buffer_size)
	{	
		std::streamsize written_byte_size = 0, total_written_byte_size = 0;

		_zip_stream.next_in = (byte_buffer_type) buffer;
		_zip_stream.avail_in = static_cast<uInt>(buffer_size * sizeof(char_type));
		_zip_stream.avail_out = static_cast<uInt>(_output_buffer.size());
		_zip_stream.next_out = &_output_buffer[0];
		size_t remainder = 0;

		// updating crc
		_crc = crc32(_crc, _zip_stream.next_in,
                     _zip_stream.avail_in);		

		do
		{
			_err = deflate(&_zip_stream, 0);
	
			if (_err == Z_OK  || _err == Z_STREAM_END)
			{
				written_byte_size= static_cast<std::streamsize>(_output_buffer.size()) -
                                                                _zip_stream.avail_out;
				total_written_byte_size += written_byte_size;
				// ouput buffer is full, dumping to ostream

                _ostream.write((const char_type*) &_output_buffer[0], 
					static_cast<std::streamsize>(written_byte_size / sizeof(char_type)));
												
				// checking if some bytes were not written.
				if((remainder = written_byte_size % sizeof(char_type)) != 0)
				{
					// copy to the beginning of the stream
					memcpy(&_output_buffer[0], 
						   &_output_buffer[written_byte_size-remainder],
                           remainder);
				}
				
				_zip_stream.avail_out = static_cast<uInt>(_output_buffer.size()-remainder);
				_zip_stream.next_out = &_output_buffer[remainder];
			}
		} 
		while(_zip_stream.avail_in != 0 && _err == Z_OK);
	
		return _err == Z_OK;
	}
    
	ostream_reference   _ostream;
	z_stream            _zip_stream;
    int                 _err;
	byte_vector_type    _output_buffer;
	char_vector_type    _buffer;
	unsigned long       _crc;
};

/** \brief A stream decorator that takes compressed input and unzips it to a istream.

The class wraps up the deflate method of the zlib library 1.1.4 http://www.gzip.org/zlib/
*/
template <class charT,
          class traits = std::char_traits<charT> >
class basic_unzip_streambuf :
	public std::basic_streambuf<charT, traits>
{
public:
	typedef std::basic_istream<charT,traits>& istream_reference;
	typedef unsigned char byte_type;
    typedef char          char_type;
	typedef byte_type* byte_buffer_type;
	typedef std::vector<byte_type> byte_vector_type;
	typedef std::vector<char_type> char_vector_type;
    typedef int int_type;

     /** Construct a unzip stream
     * More info on the following parameters can be found in the zlib documentation.
     */
    basic_unzip_streambuf(istream_reference istream,
                          int window_size,
                          size_t read_buffer_size,
                          size_t input_buffer_size) :  
		_istream(istream),
		_input_buffer(input_buffer_size),
		_buffer(read_buffer_size),
		_crc(0)
	{
		// setting zalloc, zfree and opaque
		_zip_stream.zalloc = (alloc_func) 0;
		_zip_stream.zfree = (free_func) 0;

		_zip_stream.next_in = NULL;
		_zip_stream.avail_in = 0;
		_zip_stream.avail_out = 0;
		_zip_stream.next_out = NULL;

		_err = inflateInit2(&_zip_stream, window_size);
		
		this->setg(&_buffer[0] + 4,     // beginning of putback area
                   &_buffer[0] + 4,     // read position
                   &_buffer[0] + 4);    // end position    
	}

	~basic_unzip_streambuf(void)
	{
		inflateEnd(&_zip_stream);
	}

    int_type underflow(void) 
	{ 
		if(this->gptr() && ( this->gptr() < this->egptr()))
            return * reinterpret_cast<unsigned char *>(this->gptr());
     
        int n_putback = static_cast<int>(this->gptr() - this->eback());
        if(n_putback > 4)
            n_putback = 4;
       
        memcpy(&_buffer[0] + (4 - n_putback),
               this->gptr() - n_putback,
               n_putback * sizeof(char_type));
  
        int num = unzip_from_stream(&_buffer[0] + 4, 
		   static_cast<std::streamsize>((_buffer.size() - 4) * sizeof(char_type)));
        
        if(num <= 0) // ERROR or EOF
            return EOF;
    
        // reset buffer pointers
        this->setg(&_buffer[0] + (4 - n_putback),  // beginning of putback area
                   &_buffer[0] + 4,                // read position
                   &_buffer[0] + 4 + num);         // end of buffer
        
         // return next character
         return * reinterpret_cast<unsigned char *>(this->gptr());    
    }


	/// returns the compressed input istream
	istream_reference get_istream(void)
    {
        return _istream;
    }
	/// returns the zlib stream structure
	z_stream& get_zip_stream(void)
    {
        return _zip_stream;
    }
	/// returns the latest zlib error state
	int get_zerr(void) const
    {
        return _err;
    }
	/// returns the crc of the uncompressed data so far
	unsigned long get_crc(void) const
    {
        return _crc;
    }
	/// returns the number of uncompressed bytes
	long get_out_size(void) const
    {
        return _zip_stream.total_out;
    }
	/// returns the number of read compressed bytes
	long get_in_size(void) const
    {
        return _zip_stream.total_in;
    }

private:
	
	void put_back_from_zip_stream(void)
	{
		if(_zip_stream.avail_in == 0)
			return;

		_istream.clear(std::ios::goodbit);
		_istream.seekg(-intf(_zip_stream.avail_in),
                       std::ios_base::cur);

		_zip_stream.avail_in = 0;
	}
	
    std::streamsize unzip_from_stream(char_type* buffer, std::streamsize buffer_size)
	{
		_zip_stream.next_out = (byte_buffer_type) buffer;
		_zip_stream.avail_out = static_cast<uInt>(buffer_size * sizeof(char_type));
		size_t count = _zip_stream.avail_in;

		do
		{
			if(_zip_stream.avail_in == 0)
				count=fill_input_buffer();

			if(_zip_stream.avail_in)
			{
                _err = inflate(&_zip_stream,  Z_SYNC_FLUSH);
			}
		}
        while(_err==Z_OK && _zip_stream.avail_out != 0 && count != 0);

		// updating crc
		_crc = crc32(_crc, (byte_buffer_type) buffer,
                     buffer_size - _zip_stream.avail_out / sizeof(char_type));
        
		std::streamsize n_read = buffer_size - _zip_stream.avail_out / sizeof(char_type);
		
		// check if it is the end
		if (_err == Z_STREAM_END)
			put_back_from_zip_stream();				
		
		return n_read;
	}

    size_t fill_input_buffer(void)
	{
		_zip_stream.next_in = &_input_buffer[0];
		_istream.read((char_type*) &_input_buffer[0], 
			static_cast<std::streamsize>(_input_buffer.size() / sizeof(char_type)));
        
		return _zip_stream.avail_in = _istream.gcount()*sizeof(char_type);
	}

	istream_reference   _istream;
	z_stream            _zip_stream;
    int                 _err;
	byte_vector_type    _input_buffer;
	char_vector_type    _buffer;
	unsigned long       _crc;
};

template <class charT,
          class traits = std::char_traits<charT> >
class basic_zip_ostream :
    private basic_zip_streambuf<charT, traits>,
    public std::basic_ostream<charT, traits>
{
public:
    
    typedef char char_type;
    typedef std::basic_ostream<charT, traits>& ostream_reference;

    explicit basic_zip_ostream(ostream_reference ostream,
                               bool is_gzip = false,
                               int level = Z_DEFAULT_COMPRESSION,
                               EStrategy strategy = DefaultStrategy,
                               int window_size = -15 /*windowBits is passed < 0 to suppress zlib header */,
                               int memory_level = 8,
                               size_t buffer_size = zstream_default_buffer_size) :
        basic_zip_streambuf<charT, traits>(ostream, level, strategy, window_size,
                                           memory_level, buffer_size),
        std::basic_ostream<charT, traits>(this),
        _is_gzip(is_gzip)
    {
		if(_is_gzip)
			add_header();
	}

	~basic_zip_ostream(void)
	{
		if(_is_gzip)
			add_footer();
	}

	/// returns true if it is a gzip
	bool is_gzip(void) const		{ return _is_gzip; }
	/// flush inner buffer and zipper buffer
	basic_zip_ostream<charT, traits>& zflush(void)
	{
		std::basic_ostream<charT, traits>::flush();
        basic_zip_streambuf<charT, traits>::flush();
        return *this;
	}

private:
    
	basic_zip_ostream<charT,traits>& add_header(void)
	{
	    char_type zero = 0;
	    
        this->get_ostream() << static_cast<char_type>(detail::gz_magic[0])
                            << static_cast<char_type>(detail::gz_magic[1])
                            << static_cast<char_type>(Z_DEFLATED)
                            << zero //flags
                            << zero<<zero<<zero<<zero // time
                            << zero //xflags
                            << static_cast<char_type>(OS_CODE);
        
        return *this;
	}
    
	basic_zip_ostream<charT,traits>& add_footer(void)
	{
        // Writes crc and length in LSB order to the stream.
        unsigned long crc = this->get_crc();
        for(int n=0;n<4;++n)
        {
            this->get_ostream().put((int)(crc & 0xff));
            crc >>= 8;
        }

        unsigned long length = this->get_in_size();
        for(int n=0;n<4;++n)
        {
            this->get_ostream().put((int)(length & 0xff));
            length >>= 8;
        }

		return *this;
	}
    
	bool _is_gzip;
};

template <class charT,
          class traits = std::char_traits<charT> >
class basic_zip_istream :
    private basic_unzip_streambuf<charT, traits>,
    public std::basic_istream<charT, traits>
{
public:
    typedef std::basic_istream<charT, traits>& istream_reference;

    explicit basic_zip_istream(istream_reference istream,
                               int window_size = -15 /*windowBits is passed < 0 to suppress zlib header */,
                               size_t read_buffer_size = zstream_default_buffer_size,
                               size_t input_buffer_size = zstream_default_buffer_size) :
        basic_unzip_streambuf<charT, traits>(istream, window_size,
                                             read_buffer_size, input_buffer_size),
        std::basic_istream<charT, traits>(this),
        _is_gzip(false),
        _gzip_crc(0),
        _gzip_data_size(0)
	{
        if(this->get_zerr() == Z_OK)
            check_header();
	}

	/// returns true if it is a gzip file
	bool is_gzip(void) const
    {
        return _is_gzip;
    }
	
	
	/** return crc check result

    This must be called after the reading of compressed data is finished!
	This method compares it to the crc of the uncompressed data.

	\return true if crc check is succesful
	*/
	bool check_crc(void)
    {
        read_footer();
        return this->get_crc() == _gzip_crc;
    }
    
	/// return data size check
	bool check_data_size(void) const
    {
        return this->get_out_size() == _gzip_data_size;
    }

	/// return the crc value in the file
	long get_gzip_crc(void) const
    {
        return _gzip_crc;
    }
	/// return the data size in the file
	long get_gzip_data_size(void) const
    {
        return _gzip_data_size;
    }
    
protected:
    
	int check_header(void)
	{
	    int method; /* method byte */
	    int flags;  /* flags byte */
	    uInt len;
		int c;
		int err=0;
		z_stream &zip_stream = this->get_zip_stream();

	    /* Check the gzip magic header */
        for(len = 0; len < 2; len++) 
        {
			c = (int) this->get_istream().get();
			if (c != detail::gz_magic[len]) 
			{
			    if (len != 0) 
					this->get_istream().unget();
			    if (c!= EOF) 
			    {
					this->get_istream().unget();
			    }
		    
			    err = zip_stream.avail_in != 0 ? Z_OK : Z_STREAM_END;
			    _is_gzip = false;
			    return err;
			}
		}
    
		_is_gzip = true;
		method = (int)this->get_istream().get();
		flags = (int)this->get_istream().get();
		if (method != Z_DEFLATED || (flags & detail::gz_reserved) != 0) 
		{
			err = Z_DATA_ERROR;
			return err;
		}

	    /* Discard time, xflags and OS code: */
	    for (len = 0; len < 6; len++) 
			this->get_istream().get();
	
	    if ((flags & detail::gz_extra_field) != 0) 
	    { 
			/* skip the extra field */
			len  =  (uInt)this->get_istream().get();
			len += ((uInt)this->get_istream().get())<<8;
			/* len is garbage if EOF but the loop below will quit anyway */
			while (len-- != 0 && this->get_istream().get() != EOF) ;
	    }
	    if ((flags & detail::gz_orig_name) != 0) 
	    { 
			/* skip the original file name */
			while ((c = this->get_istream().get()) != 0 && c != EOF) ;
		}
	    if ((flags & detail::gz_comment) != 0) 
	    {   
			/* skip the .gz file comment */
			while ((c = this->get_istream().get()) != 0 && c != EOF) ;
		}
		if ((flags & detail::gz_head_crc) != 0) 
		{  /* skip the header crc */
			for (len = 0; len < 2; len++) 
				this->get_istream().get();
		}
		err = this->get_istream().eof() ? Z_DATA_ERROR : Z_OK;

		return err;
	}
    
    void read_footer(void)
	{		
		if(_is_gzip)
		{
            _gzip_crc = 0;
            for(int n=0;n<4;++n)
                _gzip_crc += ((((int) this->get_istream().get()) & 0xff) << (8*n));

            _gzip_data_size = 0;
            for(int n=0;n<4;++n)
                _gzip_data_size += ((((int) this->get_istream().get()) & 0xff) << (8*n));
		}
	}
    
	bool _is_gzip;
    long _gzip_crc;
	long _gzip_data_size;
};


/// A typedef for basic_zip_ostream<char>
typedef basic_zip_ostream<char> zip_ostream;
/// A typedef for basic_zip_ostream<wchar_t>
//typedef basic_zip_ostream<wchar_t> zip_wostream;
/// A typedef for basic_zip_istream<char>
typedef basic_zip_istream<char> zip_istream;
/// A typedef for basic_zip_istream<wchart>
//typedef basic_zip_istream<wchar_t> zip_wistream;

OSG_END_NAMESPACE

#ifdef OSG_WIN32_CL
#pragma warning(default : 4355)
#endif

#endif // OSG_ZSTREAM_SUPPORTED

#endif // _OSGZSTREAM_H_
