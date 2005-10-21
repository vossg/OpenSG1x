#include <OSGGLUT.h>
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGGLUTWindow.h>
#include <OSGSimpleSceneManager.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGImage.h>
#include <OSGImageScaler.h>

OSG_USING_NAMESPACE

int main(int argc, char **argv)
{
    // OSG init
    osgInit(argc,argv);

    if(argc == 1)
    {
        printf("%s srcImg dstImg width height depth b|l|g|h|B|L filterWidth\n",argv[0]);
        return 0;
    }

    ImagePtr pImageSrc = Image::create();
    ImagePtr pImageDst = Image::create();
    if( argc > 1 )
    {
        pImageSrc->read(argv[1]);
    }
    else
    {
        pImageSrc->set( Image::OSG_RGBA_PF, 256, 256, 1, 9, 1, 0 );
    }
    UInt32 width = pImageSrc->getWidth();
    UInt32 height = pImageSrc->getHeight();
    UInt32 depth = pImageSrc->getDepth();
    printf("Src: %dx%dx%d Sides: %d Frames %d\n",
           width,height,depth,pImageSrc->getSideCount(),pImageSrc->getFrameCount());
    if( argc > 3 )
        width = atoi(argv[3]);
    if( argc > 4 )
        height = atoi(argv[4]);
    if( argc > 5 )
        depth = atoi(argv[5]);
    printf("Dst: %dx%dx%d Sides: %d Frames %d\n",
           width,height,depth,pImageSrc->getSideCount(),pImageSrc->getFrameCount());

    ImageGenericFilter *filter = NULL;
    if(argc > 6)
    {
        switch(argv[6][0])
        {
            case 'b': filter = new ImageBoxFilter(); break;
            case 'l': filter = new ImageLinearFilter(); break;
            case 'g': filter = new ImageGaussianFilter(); break;
            case 'h': filter = new ImageHammingFilter; break;
            case 'B': filter = new ImageBlackmanFilter; break;
            case 'L': filter = new ImageLanczos3Filter; break;
        }
    }
    if(!filter)
    {
        filter = new ImageLinearFilter();
    }
    if(argc > 7)
    {
        float filterWidth;
        sscanf(argv[7],"%f", &filterWidth);
        filter->setWidth(filterWidth);
    }

    ImageScaler::scale(pImageSrc,pImageDst,width,height,depth,*filter);


    if( argc > 2 )
    {
        pImageDst->write(argv[2]);
    }
    return 0;
}

