/* --------------------------------------------------------------- *\

  file  : OSGAVCodec.cpp
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



/* --------------------------------------------------------------- *\
  includes
\* --------------------------------------------------------------- */


#include <string>
#include <exception>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "OSGAVCodec.h"


/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */
class AVCodecException : public std::exception
{
  public:

    AVCodecException(const char *error)
      throw() : s("AVCodecEncoder error: ") { s += error; }
    ~AVCodecException() throw() {}

    virtual const char* what(void) const throw()
      { return s.c_str(); }

  private:

    string s;
}; // class AVVideoException


/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */
AVCodecEncoder::AVCodecEncoder(const char* filename, 
    const unsigned int& width, const unsigned int& height,
    const unsigned int& bitrate, const unsigned int& fps, 
    const CodecID& codecid, const bool& flip ) :

    _format_ctx(0),
    _format_out(0),
    _stream(0),
    _yuvframe(0),
    _rgbframe(0),
    _video_outbuf(0),
    _video_outbuf_size(0),
    _frame_count(0),
    _video_pts(0),
    _flip_before_encode(flip)
{

  // init avcodec && avformat
  avcodec_register_all();
  av_register_all();


//
// find a good output-format
//

  // check for ffv1 -> experimental
  if ( codecid == CODEC_ID_FFV1 )
  {
    printf(" >>> CODEC_ID_FFV1 <<< \n");
    _format_out= guess_format("avi", NULL, NULL);
    _format_out->video_codec= codecid;
    _format_out->audio_codec= CODEC_ID_NONE;
  }

  // check search output formats for given codecid */
  if ( codecid != CODEC_ID_NONE && !_format_out )
  {
    printf(" >>> search for codec <<< \n");
    extern AVOutputFormat* first_oformat;
    for(AVOutputFormat* f= first_oformat; !f; f= f->next )
    {
      if ( f->video_codec == codecid )
      {
        _format_out= f;
        break;
      }
    }
  }

  // auto detect the output format from the name
  if ( !_format_out )
  {
    printf(" >>> guess codec via filename <<< \n");
    _format_out = guess_format(NULL, filename, NULL);
  }

  // fallback
  if (!_format_out)
  {
    printf("Could not deduce output format from file extension: using MPEG.\n");
    _format_out = guess_format("mpeg", NULL, NULL);
  }

  if (!_format_out)
    throw AVCodecException("couldnt find suitable output format\n");


//
// allocate the context for the output
//

  _format_ctx= (AVFormatContext*)av_mallocz(sizeof(AVFormatContext));
  if (!_format_ctx)
    throw AVCodecException("memory error while allformat_ctxating formatcontext\n");

  _format_ctx->oformat= _format_out;
  snprintf(_format_ctx->filename, sizeof(_format_ctx->filename), "%s", filename);

//
// create the resulting stream
//
  if (_format_out->video_codec != CODEC_ID_NONE)
  {
    _stream= av_new_stream(_format_ctx, 0);
    if (!_stream)
      throw AVCodecException("couldnt allformat_ctx stream\n");

    AVCodecContext* c= &_stream->codec;
    c->codec_id= _format_out->video_codec;
    c->codec_type= CODEC_TYPE_VIDEO;

    switch ( c->codec_id)
    {
      case CODEC_ID_FFV1:
        c->strict_std_compliance= -1;
        c->codec_tag= ('F' | ('F' << 8) | ('V' << 16) | ('1' << 24));
        break;

      case CODEC_ID_HUFFYUV:
        c->strict_std_compliance= -1;
        break;
    };

    c->bit_rate= bitrate * 1000;
    c->width= width;
    c->height= height;
    c->frame_rate= fps;
    c->frame_rate_base= 1;
    c->gop_size = 12;
  }

  /* set the output parameters (must be done even if no
     parameters). */
  if (av_set_parameters(_format_ctx, NULL) < 0)
    throw AVCodecException("invalid output format parameters\n");


  // setup all buffers and structures
  if (_stream)
    initCodec();

  dump_format(_format_ctx, 0, filename, 1);

  /* open the output file, if needed */
  if (!(_format_out->flags & AVFMT_NOFILE))
  {
    if (url_fopen(&_format_ctx->pb, filename, URL_WRONLY) < 0)
      throw AVCodecException((std::string("couldnt open") + std::string(filename) + std::string("\n")).c_str());
  }

  /* write the stream header, if any */
  av_write_header(_format_ctx);
}

AVCodecEncoder::~AVCodecEncoder()
{
  av_write_trailer(_format_ctx);

  if (!(_format_out->flags & AVFMT_NOFILE)) {
    url_fclose(&_format_ctx->pb);
  }
  
  /* close each codec */
  avcodec_close(&_stream->codec);
  av_free(_yuvframe->data[0]);
  av_free(_yuvframe);
  av_free(_rgbframe);
  av_free(_video_outbuf);

  /* free the streams */
  for(int i = 0; i < _format_ctx->nb_streams; i++) {
      av_freep(&_format_ctx->streams[i]);
  }

  av_free(_format_ctx);
}

AVFrame* AVCodecEncoder::allocFrame(int pix_format_out, int width, int height)
{
    AVFrame*        picture;
    unsigned char*  picture_buf;
    int             size;

    picture= avcodec_alloc_frame();
    if (!picture) return NULL;
    size= avpicture_get_size(pix_format_out, width, height);
    picture_buf= (unsigned char*)av_malloc(size);

    if (!picture_buf)
    {
      av_free(picture);
      return NULL;
    }

    avpicture_fill((AVPicture*)picture, picture_buf, pix_format_out, width, height);
    return picture;
}

void AVCodecEncoder::initCodec()
{
  AVCodec *codec;
  AVCodecContext* c= &_stream->codec;

  /* find the video encoder */
  if (c->codec_id == CODEC_ID_FFV1)
  {
    codec= &ffv1_encoder;
  }
  else
    codec= avcodec_find_encoder(c->codec_id);

  if (!codec)
    throw AVCodecException("couldnt find codec\n");

  /* open the codec */
  if (avcodec_open(c, codec) < 0)
    throw AVCodecException("couldnt open codec\n");

  _video_outbuf= NULL;
  if (!(_format_ctx->oformat->flags & AVFMT_RAWPICTURE))
  {
    _video_outbuf_size= 200000;
    _video_outbuf= (unsigned char*)av_malloc(_video_outbuf_size);
  }

  /* allformat_ctxate the encoded raw picture */
  _yuvframe= allocFrame(c->pix_fmt, c->width, c->height);
  if (!_yuvframe)
    throw AVCodecException("couldnt allformat_ctxate yuv-picture\n");

  _rgbframe= avcodec_alloc_frame();
  if (!_rgbframe)
    throw AVCodecException("coudlnt allformat_ctxate rgb-picture\n");

  return;
}


void AVCodecEncoder::writeFrame()
{

  // calculate time
  if (_stream)
    _video_pts = (double)_stream->pts.val * _format_ctx->pts_num / _format_ctx->pts_den;
  else
    _video_pts = 0.0;

  if (!_stream) return;

  // convert rgb to yuv420
  img_convert( (AVPicture*)(_yuvframe), _stream->codec.pix_fmt,
               (AVPicture*)(_rgbframe), PIX_FMT_RGB24,
                _stream->codec.width, _stream->codec.height);

  // flip yuv-buffer horizontal -> opengl has other order
  // why not the rgb-buffer? yuv has smaller size
  //
  // TODO: check pix_format_out and do the right thing, its not
  // alway yuf420 ...
  if ( _flip_before_encode )
  {
    unsigned char* s;
    unsigned char* d;

    static unsigned char  b[24000];

    for (s= _yuvframe->data[0], d= _yuvframe->data[1]-_yuvframe->linesize[0];
        s < d; s+= _yuvframe->linesize[0], d-= _yuvframe->linesize[0])
    {
       memcpy(b, s, _yuvframe->linesize[0]);
       memcpy(s, d, _yuvframe->linesize[0]);
       memcpy(d, b, _yuvframe->linesize[0]);
    }

    for (s= _yuvframe->data[1], d= _yuvframe->data[2]-_yuvframe->linesize[2];
         s < d; s+= _yuvframe->linesize[1], d-= _yuvframe->linesize[1])
    {
       memcpy(b, s, _yuvframe->linesize[1]);
       memcpy(s, d, _yuvframe->linesize[1]);
       memcpy(d, b, _yuvframe->linesize[1]);
    }

    for (s= _yuvframe->data[2], d= _yuvframe->data[2]+(_yuvframe->data[2]-_yuvframe->data[1]-_yuvframe->linesize[2]);
         s < d; s+= _yuvframe->linesize[2], d-= _yuvframe->linesize[2])
    {
       memcpy(b, s, _yuvframe->linesize[2]);
       memcpy(s, d, _yuvframe->linesize[2]);
       memcpy(d, b, _yuvframe->linesize[2]);
    }

  }

  int out_size, ret;

  if (_format_ctx->oformat->flags & AVFMT_RAWPICTURE)
    ret= av_write_frame(_format_ctx, _stream->index, (unsigned char*)_yuvframe, sizeof(AVPicture));
  else
  {
    out_size= avcodec_encode_video(&_stream->codec, _video_outbuf, _video_outbuf_size, _yuvframe);
    ret= av_write_frame(_format_ctx, 0, _video_outbuf, out_size);
  }

  if (ret != 0)
    throw AVCodecException("error while writing frame\n");

  _frame_count++;

  return;
}

/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */
void AVCodecEncoder::setRgb(unsigned char* rgb)
{
  avpicture_fill((AVPicture*)_rgbframe, rgb, PIX_FMT_RGB24, width(), height());
  return;
}


void AVCodecEncoder::setBitrate(int bitrate)
{
  _stream->codec.bit_rate= bitrate * 1000;
  return;
}
/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */

