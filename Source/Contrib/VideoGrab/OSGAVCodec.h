#ifndef _OSGAVCODEC_HPP_
#define _OSGAVCODEC_HPP_

/* --------------------------------------------------------------- *\

  file  : OSGAVCodec.hpp
  author: m. gumz
  mail  : gumz at cs.uni-magdeburg.de
  copyr : copyright (c) 2003 by m. gumz

  start : Mon 11 Aug 2003 02:05:50 CEST

  $Id$

\* --------------------------------------------------------------- */
/* --------------------------------------------------------------- *\

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public Licensse
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston,
  MA 02111-1307, USA.

\* --------------------------------------------------------------- */
/* --------------------------------------------------------------- *\

  about :

    c++ videoencoder for ffmpeg, based on output_example.c of
    ffmpeg

\* --------------------------------------------------------------- */


// hack for ffmpeg - c++ issue
#ifndef int64_t_C
#define int64_t_C(c)     (c ## LL)
#define uint64_t_C(c)    (c ## ULL)
#endif

#include <ffmpeg/config.h>
#include <ffmpeg/avformat.h>

/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */

class AVCodecEncoder
{
  public:

    /// \parameter filename - filename of the video
    /// \parameter width - width of the video
    /// \parameter height - height of the video
    /// \parameter bitrate - bitrate in kbyte / s
    /// \parameter fps - frames per second
    /// \parameter flip - flip the video verticale before encoding
    AVCodecEncoder(const char* filename,
        const unsigned int& width, 
        const unsigned int& height,
        const unsigned int& bitrate= 900, 
        const unsigned int& fps= 25,
        const CodecID& codecid= CODEC_ID_NONE,
        const bool& flip= true);

    ~AVCodecEncoder();

    int               width()   const { return _stream->codec.width; }
    int               height()  const { return _stream->codec.height; }
    unsigned char*    rgb()     const { return _rgbframe->data[0]; }
    AVCodecContext*   context() const { return &_stream->codec; }
    unsigned int      codecid() const { return _stream->codec.codec_id; }
    unsigned int      fps()     const { return _stream->codec.frame_rate; }
    bool              flip()    const { return _flip_before_encode; }
    unsigned int      bitrate() const { return _stream->codec.bit_rate; }
    
    void              setRgb(unsigned char* rgb);
    void              setBitrate(int bitrate);

    void              writeFrame();

  private:

    AVFrame*          allocFrame(int pix_fmt, int width, int height);
    void              initCodec();

  private:

    AVFormatContext*  _format_ctx;
    AVOutputFormat*   _format_out;
    AVStream*         _stream;

    AVFrame*          _yuvframe;
    AVFrame*          _rgbframe;

    unsigned char*    _video_outbuf;
    unsigned int      _video_outbuf_size;
    unsigned int      _frame_count;
    double            _video_pts;

    bool              _flip_before_encode;

}; // class AVVideoEncoder

/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */

#endif // _AV_HPP_


