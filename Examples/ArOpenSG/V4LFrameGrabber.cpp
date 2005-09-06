

#include "V4LFrameGrabber.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <linux/types.h>

// Hardcode all the parameters

static const char *cam_device = "/dev/video0";
static const int nframes = 2;



V4LFrameGrabber::V4LFrameGrabber()
{
    dev = open (cam_device, O_RDWR);
    
    if(dev < 0)
    {
        fprintf(stderr, 
            "V4LFrameGrabber::V4LFrameGrabber: Error opening camera "
            "device %s: %d!\n", cam_device, dev);
        exit(1);
    }
    
    struct video_capability cap;

    if(ioctl(dev, VIDIOCGCAP, &cap) == -1) 
    {
        fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                "Getting camera caps failed!");
        exit(1);        
    }
    
    width = cap.maxwidth;
    height = cap.maxheight;
    
    if((cap.type & VID_TYPE_CAPTURE) != 1) 
    {
        use_read = true;
    }
    else
    {
        use_read = false;
    }

    struct video_window win;
    if(ioctl(dev, VIDIOCGWIN, &win) == -1) 
    {
        fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                "Getting win info failed!");
        exit(1);        
    }
    
    win.width = width;
    win.height = height;
    
    win.x = 0;
    win.y = 0;
    win.chromakey = 0;
    win.flags = 0;

    if(ioctl(dev, VIDIOCSWIN, &win) == -1) 
    {
        fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                "Setting win info failed!");
        exit(1);        
    }
    
    printf("V4LFrameGrabber::V4LFrameGrabber: Camera opened for (%dx%d) image"
           " using %s\n", width, height, use_read ? "read" : "mmap");
    
    struct video_picture pic;
    if(ioctl(dev, VIDIOCGPICT, &pic) == -1) 
    {
        fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                "Getting pic info failed!");
        exit(1);        
    }
    
    bpp = pic.depth / 8;
    
    if(use_read)
    {
        buffer = new unsigned char [ width * height * bpp * nframes ];
    }
    else
    {
        if(ioctl(dev, VIDIOCGMBUF, &vmbuf) == -1) 
        {
            fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                    "Getting buffer info failed!\n");
            exit(1);        
        }
    
        // Initialize mmap area
        
        buffer = (unsigned char *) mmap( 0, vmbuf.size, PROT_READ | PROT_WRITE, MAP_SHARED, dev, 0 );
        
        if(buffer == NULL)
        {
            fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                    "mmap failed!");
            exit(1);                   
        }
        
        act_frame = 0;
        vmmap.width = width;
        vmmap.height = height;
        vmmap.format = pic.palette;
        
        for(int i = 0; i < vmbuf.frames; ++i)
        {
            vmmap.frame = i;
            
            if(ioctl(dev, VIDIOCMCAPTURE, &vmmap) == -1) 
            {
                fprintf(stderr, "V4LFrameGrabber::V4LFrameGrabber: "
                        "Error initiating frame %d!\n", i);
                exit(1);        
            }
        }
        
    }
}

V4LFrameGrabber::~V4LFrameGrabber()
{
    close(dev);
    delete [] buffer;
}

void V4LFrameGrabber::grabFrame(void)
{
    if(use_read)
    {
        read(dev, buffer, width * height * bpp);
    }
    else
    {
        int res = -1;
        int frame = act_frame;
        
        while(res == -1)
        {
            res = ioctl (dev, VIDIOCSYNC, &frame);
            if(res < 0 && errno == EINTR)
                continue;
            
            if(res < 0)
            {
                fprintf(stderr, "V4LFrameGrabber::grabFrame: "
                    "error syncing frame!\n");
                exit(1);                   
            }
        }
        
        vmmap.frame = frame;
        if(ioctl(dev, VIDIOCMCAPTURE, &vmmap) == -1) 
        {
            fprintf(stderr, "V4LFrameGrabber::grabFrame: "
                    "Error capturing frame!\n");
            exit(1);        
        }
        
        act_frame = (act_frame + 1) % vmbuf.frames;
        
    }
}

unsigned char *V4LFrameGrabber::getFrame(void) const
{
    if(use_read)
    {
        return buffer;
    }
    else
    {
        return buffer + vmbuf.offsets[act_frame]; 
    } 
}

long V4LFrameGrabber::getFrameBufferLength(void) const
{
    return width * height * bpp;
}

int V4LFrameGrabber::getWidth(void) const
{
    return width;
}

int V4LFrameGrabber::getHeight(void) const
{
    return height;    
}

bool V4LFrameGrabber::isTopDown(void) const
{
    return true;    
}

