/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef _OSG_TRACKBALL_H_
#define _OSG_TRACKBALL_H_

#include "OSGWindowBase.h"
#include <OSGBaseTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>

OSG_BEGIN_NAMESPACE

class OSG_WINDOW_DLLMAPPING Trackball
{
  public:

    enum Mode
    {
        OSGCamera = 0x01,
        OSGObject = 0x02
    };
		
    enum TranslationMode
    {
        OSGFixedX,
        OSGFixedY,
        OSGFixedZ,        

        OSGFree
    };
		
  public:
    const char *getClassname(void) { return "Trackball"; }

	Trackball(Real32 rSize = 1.0);
	~Trackball(void);

    void setSum(Bool bVal);

    void updateRotation(Real32 rLastX,    Real32 rLastY, 
                        Real32 rCurrentX, Real32 rCurrentY);
    void updatePosition(Real32 rLastX,    Real32 rLastY, 
                        Real32 rCurrentX, Real32 rCurrentY);
    void updatePositionNeg(Real32 rLastX,    Real32 rLastY, 
                           Real32 rCurrentX, Real32 rCurrentY);


    void setAutoPositionIncrement(Real32 rVal);
    void setAutoPosition(Bool bVal);
    void setAutoPositionNeg(Bool bVal);
	
    void setMode(Mode gMode);
	void setTranslationMode(TranslationMode gMode);
    void setTranslationScale(Real32 rTranslationScale);


    void reset(void);

    void setStartPosition(Real32 rX, Real32 rY, Real32 rZ, 
                          Bool bUpdate = false);
    void setStartPosition(Vec3f &gStartPos, Bool bUpdate = false);

    Vec3f &getPosition(void);

    void setStartRotation(Real32 rX, Real32 rY, Real32 rZ, Real32 rW, 
                          Bool bUpdate = false);
    void setStartRotation(Quaternion &gStartRot, Bool bUpdate = false);

    Quaternion &getRotation(void);		

		
	void setSize( Real32 s );
	Real32 getSize() const;

		
  private:

    Bool   _bSum;
    Bool   _bAutoPosition;

    Mode _gMode;
	TranslationMode _gTransMode;
	
    Real32 _rAutoPositionStep;
    Real32 _rAutoPositionIncrement;

    Real32 _rTrackballSize;
	Real32 _rTranslationScale;
	
    Quaternion _qVal;
    Vec3f    _pVal;

    Quaternion _qValStart;
    Vec3f    _pValStart;

	Trackball(const Trackball &org);
	void operator =(const Trackball &org);

  protected:


    float projectToSphere(Real32 rRadius, Real32 rX, Real32 rY);

};

OSG_END_NAMESPACE

#endif







