#ifndef _AV_HPP_
#define _AV_HPP_

/* --------------------------------------------------------------- *\

  file  : av.hpp
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

#include <ffmpeg/avformat.h>

/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */

class AVVideoEncoder
{
  public:

    AVVideoEncoder(const char* filename, int width, int height,
        int bitrate= 900, int fps= 25, bool flip= true);
    ~AVVideoEncoder();

    int width() const { return c->width; };
    int height() const { return c->height; };

    unsigned char* rgb() { return rgbframe->data[0]; };
    void setRgb(unsigned char* rgb);
    void setBitrate(int bitrate);
    AVCodecContext*   getCodecContext() { return c; }

    void write_video_frame();

  private:

    AVFrame* alloc_picture(int pix_fmt, int width, int height);
    void open_video();

  private:

    AVFormatContext*  oc;
    AVCodecContext*   c;
    AVStream*         video_st;
    AVOutputFormat*   fmt;

    AVFrame*          yuvframe;
    AVFrame*          rgbframe;

    unsigned char*    video_outbuf;
    unsigned int      video_outbuf_size;
    unsigned int      frame_count;
    double            video_pts;

    bool              flip_before_encode;

}; // class AVVideoEncoder

/* --------------------------------------------------------------- *\
\* --------------------------------------------------------------- */

#endif // _AV_HPP_


