/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//-------------------------------
// 	Includes 					 			    
//-------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGSGIImageFileType.h"

#ifdef OSG_SGI_STL
//#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<int>::max()
#endif
#else
#include <limits.h>
#endif

OSG_USING_NAMESPACE


/* the basic reader functions */

/* I found these on the net a long time ago. They didn't contain any copyright
   notice and I couldn't find out where I found them.
   If you wrote them please let us know (info@opensg.org) so that we can either
   credit you or remove them if you have a problem with us using them.
   Thanks
            Dirk
*/

static void
rgbatorgba(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *a,
unsigned char *l,int n) 
{
    while(n--) 
    {
	l[0] = r[0];
	l[1] = g[0];
	l[2] = b[0];
	l[3] = a[0];
        l += 4; r++; g++; b++; a++;
    }
}

static void
bwtobw(unsigned char *b,unsigned char *l,int n) 
{
    memcpy( l, b, n );
}

static void
latola(unsigned char *b, unsigned char *a,unsigned char *l,int n) 
{
    while(n--) 
    {
	l[0] = *b;
	l[1] = *a;
	l += 2; b++; a++;
    }
}

static void
rgbtorgb(unsigned char *r,unsigned char *g,unsigned char *b,unsigned char *l,
    int n) 
{
    while(n--) 
    {
	l[0] = r[0];
	l[1] = g[0];
	l[2] = b[0];
	l += 3; r++; g++; b++;
    }
}

typedef struct _ImageRec 
{
    unsigned short imagic;
    unsigned short type;
    unsigned short dim;
    unsigned short xsize, ysize, zsize;
    unsigned int min, max;
    unsigned int wasteBytes;
    char name[80];
    unsigned long colorMap;
    FILE *file;
    unsigned char *tmp, *tmpR, *tmpG, *tmpB;
    unsigned long rleEnd;
    unsigned int *rowStart;
    int *rowSize;
} ImageRec;

static void
ConvertShort(unsigned short *array, long length) 
{
    unsigned b1, b2;
    unsigned char *ptr;

    ptr = (unsigned char *)array;
    while (length--) 
    {
	b1 = *ptr++;
	b2 = *ptr++;
	*array++ = (b1 << 8) | (b2);
    }
}

static void
ConvertLong(unsigned *array, long length) 
{
    unsigned long b1, b2, b3, b4;
    unsigned char *ptr;

    ptr = (unsigned char *)array;
    while (length--) 
    {
	b1 = *ptr++;
	b2 = *ptr++;
	b3 = *ptr++;
	b4 = *ptr++;
	*array++ = (b1 << 24) | (b2 << 16) | (b3 << 8) | (b4);
    }
}

static ImageRec *ImageOpen(const char *fileName)
{
    union 
    {
	int testWord;
	char testByte[4];
    } endianTest;
    ImageRec *image;
    int swapFlag;
    int x;

    endianTest.testWord = 1;
    if (endianTest.testByte[0] == 1) 
    {
	swapFlag = 1;
    } 
    else 
    {
	swapFlag = 0;
    }

    image = (ImageRec *)malloc(sizeof(ImageRec));
    if (image == NULL) 
    {
	fprintf(stderr, "Out of memory!\n");
	exit(1);
    }
    if ((image->file = fopen(fileName, "rb")) == NULL) 
    {
	perror(fileName);
	exit(1);
    }

    fread(image, 1, 12, image->file);

    if (swapFlag) 
    {
	ConvertShort(&image->imagic, 6);
    }

    image->tmp = (unsigned char *)malloc(image->xsize*256);
    image->tmpR = (unsigned char *)malloc(image->xsize*256);
    image->tmpG = (unsigned char *)malloc(image->xsize*256);
    image->tmpB = (unsigned char *)malloc(image->xsize*256);
    if (image->tmp == NULL || image->tmpR == NULL || image->tmpG == NULL ||
	image->tmpB == NULL) 
    {
	fprintf(stderr, "Out of memory!\n");
	exit(1);
    }

    if ((image->type & 0xFF00) == 0x0100) 
    {
	x = image->ysize * image->zsize * sizeof(unsigned);
	image->rowStart = (unsigned *)malloc(x);
	image->rowSize = (int *)malloc(x);
	if (image->rowStart == NULL || image->rowSize == NULL) 
	{
	    fprintf(stderr, "Out of memory!\n");
	    exit(1);
	}
	image->rleEnd = 512 + (2 * x);
	fseek(image->file, 512, SEEK_SET);
	fread(image->rowStart, 1, x, image->file);
	fread(image->rowSize, 1, x, image->file);
	if (swapFlag) 
	{
	    ConvertLong(image->rowStart, x/sizeof(unsigned));
	    ConvertLong((unsigned *)image->rowSize, x/sizeof(int));
	}
    }
    return image;
}

static void
ImageClose(ImageRec *image) 
{
    fclose(image->file);
    free(image->tmp);
    free(image->tmpR);
    free(image->tmpG);
    free(image->tmpB);
    free(image);
}

static void
ImageGetRow(ImageRec *image, unsigned char *buf, int y, int z) 
{
    unsigned char *iPtr, *oPtr, pixel;
    int count;

    if ((image->type & 0xFF00) == 0x0100) 
    {
	fseek(image->file, image->rowStart[y+z*image->ysize], SEEK_SET);
	fread(image->tmp, 1, (unsigned int)image->rowSize[y+z*image->ysize],
	      image->file);

	iPtr = image->tmp;
	oPtr = buf;
	while (1) 
	{
	    pixel = *iPtr++;
	    count = (int)(pixel & 0x7F);
	    if (!count) 
	    {
		return;
	    }
	    if (pixel & 0x80) 
	    {
		while (count--) 
		{
		    *oPtr++ = *iPtr++;
		}
	    } 
	    else 
	    {
		pixel = *iPtr++;
		while (count--) 
		{
		    *oPtr++ = pixel;
		}
	    }
	}
    } 
    else 
    {
	fseek(image->file, 512+(y*image->xsize)+(z*image->xsize*image->ysize),
	      SEEK_SET);
	fread(buf, 1, image->xsize, image->file);
    }
}

/*****************************
 *   Types
 *****************************/
 
// Static Class Varible implementations: 
static const char *suffixArray[] = 
{
	"rgb", "rgba", "sgi", "bw"
};

SGIImageFileType SGIImageFileType::_the ( suffixArray,
					  sizeof(suffixArray) );


/*****************************
 *	  Classvariables
 *****************************/


/********************************
 *	  Class methodes
 *******************************/


/*******************************
*public
*******************************/

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: read the image from the given file
//SeeAlso:
//s:
//
//------------------------------
Bool SGIImageFileType::read (Image &image, const char *fileName )
{
 
    ImageRec *img = ImageOpen(fileName);
    
    if(!img)
	return false;

    unsigned char *rbuf = (unsigned char *)malloc(img->xsize*
    	    	    	    	    	    	    sizeof(unsigned char));
    unsigned char *gbuf = (unsigned char *)malloc(img->xsize*
    	    	    	    	    	    	    sizeof(unsigned char));
    unsigned char *bbuf = (unsigned char *)malloc(img->xsize*
    	    	    	    	    	    	    sizeof(unsigned char));
    unsigned char *abuf = (unsigned char *)malloc(img->xsize*
    	    	    	    	    	    	    sizeof(unsigned char));
 
    unsigned char *lptr; // pointer to beginning of line in image data
    int y;
    
    switch ( img->zsize )
    {
    case 1: image.set( Image::OSG_L_PF, img->xsize, img->ysize );
    	    lptr = image.getData();
	    for(y=0; y<img->ysize; y++) 
	    {
		ImageGetRow(img,rbuf,y,0);
		bwtobw(rbuf,lptr,img->xsize);
		lptr += img->xsize;
	    }
	    break;
    case 2: image.set( Image::OSG_LA_PF, img->xsize, img->ysize );
    	    lptr = image.getData();
	    for(y=0; y<img->ysize; y++) 
	    {
		ImageGetRow(img,rbuf,y,0);
		ImageGetRow(img,abuf,y,1);
		latola(rbuf,abuf,lptr,img->xsize);
		lptr += img->xsize*img->zsize;
	    }
	    break;
    case 3: image.set( Image::OSG_RGB_PF, img->xsize, img->ysize );
    	    lptr = image.getData();
	    for(y=0; y<img->ysize; y++) 
	    {
		ImageGetRow(img,rbuf,y,0);
		ImageGetRow(img,gbuf,y,1);
		ImageGetRow(img,bbuf,y,2);
		rgbtorgb(rbuf,gbuf,bbuf,lptr,img->xsize);
		lptr += img->xsize*img->zsize;
	    }
	    break;
    case 4: image.set( Image::OSG_RGBA_PF, img->xsize, img->ysize );
    	    lptr = image.getData();
	    for(y=0; y<img->ysize; y++) 
	    {
		ImageGetRow(img,rbuf,y,0);
		ImageGetRow(img,gbuf,y,1);
		ImageGetRow(img,bbuf,y,2);
		ImageGetRow(img,abuf,y,3);
		rgbatorgba(rbuf,gbuf,bbuf,abuf,lptr,img->xsize);
		lptr += img->xsize*img->zsize;
	    }
	    break;
    default:FWARNING(( "SGIImageFileType::read: unknown zsize %d!", 
    	    	img->zsize));
    	    return false;
    }

    ImageClose(img);
    free(rbuf);
    free(gbuf);
    free(bbuf);
    free(abuf);

    return true;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: write the image to the given file
//SeeAlso:
//s:
//
//------------------------------
Bool SGIImageFileType::write (const Image &image, const char *fileName )
{	
    return false;
}

/******************************
*protected
******************************/


/******************************
*private	
******************************/


/***************************
*instance methodes 
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: SGIImageFileType
//----------------------------
//
//Parameters:
//p: const char *suffixArray[], UInit16 suffixByteCount
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------
SGIImageFileType::SGIImageFileType ( const char *suffixArray[], 
																					 UInt16 suffixByteCount )
	: ImageFileType ( suffixArray, suffixByteCount )
{
	return;
}

//----------------------------
// Function name: SGIImageFileType
//----------------------------
//
//Parameters:
//p: const SGIImageFileType &obj
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------
SGIImageFileType::SGIImageFileType (const SGIImageFileType &obj )
	: ImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~SGIImageFileType
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------
SGIImageFileType::~SGIImageFileType (void )
{
	return;
}

/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/



/****************************
*protected	
****************************/


/****************************
*private
****************************/


