/* --------------------------------------------------------------- *\

  file  : av.cpp
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
class AVVideoException : public std::exception
{
  public:

    AVVideoException(const char *error)
      throw() : s("AVVideoEncoder error: ") { s += error; }
    ~AVVideoException() throw() {}

    virtual const char* what(void) const throw() { return s.c_str(); }

  private:

    string s;
}; // class AVVideoException


/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */
AVVideoEncoder::AVVideoEncoder(const char* filename, int width, int height,
   int bitrate, int fps, bool flip) :
    oc(0),
    c(0),
    video_st(0),
    fmt(0),
    yuvframe(0),
    rgbframe(0),
    video_outbuf(0),
    video_outbuf_size(0),
    frame_count(0),
    video_pts(0),
    flip_before_encode(flip)
{
  av_register_all();

  /* auto detect the output format from the name. default is
     mpeg. */
  fmt = guess_format(NULL, filename, NULL);
  if (!fmt) {
    printf("Could not deduce output format from file extension: using MPEG.\n");
    fmt = guess_format("mpeg", NULL, NULL);
  }
  if (!fmt)
    throw AVVideoException("couldnt find suitable output format\n");

  /* allocate the output media context */
  oc= (AVFormatContext*)av_mallocz(sizeof(AVFormatContext));
  if (!oc)
    throw AVVideoException("memory error while allocating formatcontext\n");

  oc->oformat= fmt;
  snprintf(oc->filename, sizeof(oc->filename), "%s", filename);

  /* add the audio and video streams using the default format codecs
     and initialize the codecs */
  if (fmt->video_codec != CODEC_ID_NONE)
  {
    video_st= av_new_stream(oc, 0);
    if (!video_st)
      throw AVVideoException("couldnt alloc stream\n");

    c= &video_st->codec;
    c->codec_id= fmt->video_codec;
    c->codec_type= CODEC_TYPE_VIDEO;

    c->bit_rate= bitrate * 1000;
    c->width= width;
    c->height= height;
    c->frame_rate= fps;
    c->frame_rate_base= 1;
    c->gop_size = 12;
  }

  /* set the output parameters (must be done even if no
     parameters). */
  if (av_set_parameters(oc, NULL) < 0)
    throw AVVideoException("invalid output format parameters\n");

  dump_format(oc, 0, filename, 1);

  /* now that all the parameters are set, we can open the audio and
     video codecs and allocate the necessary encode buffers */
  if (video_st) open_video();

  /* open the output file, if needed */
  if (!(fmt->flags & AVFMT_NOFILE))
  {
    if (url_fopen(&oc->pb, filename, URL_WRONLY) < 0)
      throw AVVideoException((std::string("couldnt open") + std::string(filename) + std::string("\n")).c_str());
  }

  /* write the stream header, if any */
  av_write_header(oc);
}

AVVideoEncoder::~AVVideoEncoder()
{
  av_write_trailer(oc);

  /* close each codec */
  avcodec_close(&video_st->codec);
  av_free(yuvframe->data[0]);
  av_free(yuvframe);
  av_free(rgbframe);
  av_free(video_outbuf);

  /* free the streams */
  for(int i = 0; i < oc->nb_streams; i++) {
      av_freep(&oc->streams[i]);
  }

  if (!(fmt->flags & AVFMT_NOFILE)) {
    url_fclose(&oc->pb);
  }

  av_free(oc);
}

AVFrame* AVVideoEncoder::alloc_picture(int pix_fmt, int width, int height)
{
    AVFrame*        picture;
    unsigned char*  picture_buf;
    int             size;

    picture= avcodec_alloc_frame();
    if (!picture) return NULL;
    size= avpicture_get_size(pix_fmt, width, height);
    picture_buf= (unsigned char*)av_malloc(size);

    if (!picture_buf)
    {
      av_free(picture);
      return NULL;
    }

    avpicture_fill((AVPicture*)picture, picture_buf, pix_fmt, width, height);
    return picture;
}

void AVVideoEncoder::open_video()
{
  AVCodec *codec;

  c= &video_st->codec;

  /* find the video encoder */
  codec= avcodec_find_encoder(c->codec_id);
  if (!codec)
    throw AVVideoException("couldnt find codec\n");

  /* open the codec */
  if (avcodec_open(c, codec) < 0)
    throw AVVideoException("couldnt open codec\n");

  video_outbuf= NULL;
  if (!(oc->oformat->flags & AVFMT_RAWPICTURE))
  {
    /* allocate output buffer */
    /* XXX: API change will be done */
    video_outbuf_size= 200000;
    video_outbuf= (unsigned char*)av_malloc(video_outbuf_size);
  }

  /* allocate the encoded raw picture */
  yuvframe= alloc_picture(c->pix_fmt, c->width, c->height);
  if (!yuvframe)
    throw AVVideoException("couldnt allocate yuv-picture\n");

  rgbframe= avcodec_alloc_frame();
  if (!rgbframe)
    throw AVVideoException("coudlnt allocate rgb-picture\n");

  return;
}


void AVVideoEncoder::write_video_frame()
{
  if (video_st)
    video_pts = (double)video_st->pts.val * oc->pts_num / oc->pts_den;
  else
    video_pts = 0.0;

  if (!video_st) return;


  img_convert( (AVPicture*)(yuvframe), c->pix_fmt,
               (AVPicture*)(rgbframe), PIX_FMT_RGB24,
                c->width, c->height);

  // flip yuv-buffer horizontal -> opengl has other order
  // why not the rgb-buffer? yuv has smaller size
  //
  // TODO: check pix_fmt and do the right thing, its not
  // alway yuf420 ...
  if ( flip_before_encode )
  {
    unsigned char* s;
    unsigned char* d;

    static unsigned char  b[24000];

    for (s= yuvframe->data[0], d= yuvframe->data[1]-yuvframe->linesize[0];
        s < d; s+= yuvframe->linesize[0], d-= yuvframe->linesize[0])
    {
       memcpy(b, s, yuvframe->linesize[0]);
       memcpy(s, d, yuvframe->linesize[0]);
       memcpy(d, b, yuvframe->linesize[0]);
    }

    for (s= yuvframe->data[1], d= yuvframe->data[2]-yuvframe->linesize[2];
         s < d; s+= yuvframe->linesize[1], d-= yuvframe->linesize[1])
    {
       memcpy(b, s, yuvframe->linesize[1]);
       memcpy(s, d, yuvframe->linesize[1]);
       memcpy(d, b, yuvframe->linesize[1]);
    }

    for (s= yuvframe->data[2], d= yuvframe->data[2]+(yuvframe->data[2]-yuvframe->data[1]-yuvframe->linesize[2]);
         s < d; s+= yuvframe->linesize[2], d-= yuvframe->linesize[2])
    {
       memcpy(b, s, yuvframe->linesize[2]);
       memcpy(s, d, yuvframe->linesize[2]);
       memcpy(d, b, yuvframe->linesize[2]);
    }

  }

  int out_size, ret;

  if (oc->oformat->flags & AVFMT_RAWPICTURE) 
    ret= av_write_frame(oc, video_st->index, (unsigned char*)yuvframe, sizeof(AVPicture));
  else 
  {
    out_size= avcodec_encode_video(c, video_outbuf, video_outbuf_size, yuvframe);
    ret= av_write_frame(oc, video_st->index, video_outbuf, out_size);
  }

  if (ret != 0)
    throw AVVideoException("error while writing frame\n");

  frame_count++;

  return;
}

/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */
void AVVideoEncoder::setRgb(unsigned char* rgb)
{
  avpicture_fill((AVPicture*)rgbframe, rgb, PIX_FMT_RGB24, width(), height());
  return;
};


void AVVideoEncoder::setBitrate(int bitrate)
{
  c->bit_rate= bitrate * 1000;
  return;
};
/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */

