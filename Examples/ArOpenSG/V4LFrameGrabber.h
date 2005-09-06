
#ifndef _V4L_FRAME_GRABBER_H
#define _V4L_FRAME_GRABBER_H

#include <stdlib.h>
#include <linux/videodev.h>

/* Note that this is an ASAP (as simple as possible) implementation
of frame grabbing using V4L. Good enough for a simple example, but definitely 
not for production use!
*/

class V4LFrameGrabber
{
	private:
        
        int dev;
        int width, height;
        unsigned char *buffer;
        bool use_read;
        int bpp;
        struct video_mbuf vmbuf;
        struct video_mmap vmmap;
        int act_frame;
        
	public:
		V4LFrameGrabber();

		~V4LFrameGrabber();
        
		void grabFrame(void);
		unsigned char *getFrame(void) const;
		long getFrameBufferLength(void) const;
		int getWidth(void) const;
		int getHeight(void) const;
        bool isTopDown(void) const;
};
 
#endif
