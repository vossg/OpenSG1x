
#include <stdio.h>

#include "OSGTrackball.h"

using namespace osg;

OSGTrackball::OSGTrackball(OSGReal32 rSize) :
    _bSum(false),
    _bAutoPosition(false),
    _gMode(OSGCamera),
	_gTransMode(OSGFixedZ),
    _rAutoPositionStep(1.),
    _rAutoPositionIncrement(1.),
    _rTrackballSize(rSize),
	_rTranslationScale(1.),
    _qVal(),
    _pVal(),
    _qValStart(),
    _pValStart()
{
}

OSGTrackball::~OSGTrackball(void)
{
}

void OSGTrackball::setSize( OSGReal32 s )
{
	_rTrackballSize = s;
}

OSGReal32 OSGTrackball::getSize() const
{
	return _rTrackballSize;
}

OSGReal32 OSGTrackball::projectToSphere(OSGReal32 rRadius, OSGReal32 rX, OSGReal32 rY)
{
    OSGReal32 d, t, z;

    d = sqrt(rX * rX + rY * rY);

    if (d < rRadius * 0.70710678118654752440f) 
    {    /* Inside sphere */
        z = sqrt(rRadius * rRadius - d * d);
    } 
    else 
    {           /* On hyperbola */
        t = rRadius / 1.41421356237309504880f;
        z = t * t / d;
    }

    return z;
}

void OSGTrackball::setSum(bool bVal)
{
    _bSum = bVal;
}

void OSGTrackball::updateRotation(OSGReal32 rLastX,    OSGReal32 rLastY, 
                                 OSGReal32 rCurrentX, OSGReal32 rCurrentY)
{
    OSGQuaternion qCurrVal;

    OSGVec3f gAxis; /* Axis of rotation */
    OSGReal32    rPhi;  /* how much to rotate about axis */
    OSGVec3f gP1;
    OSGVec3f gP2;
    OSGVec3f gDiff;
    OSGReal32    rTmp;

    if( (osgabs(rLastX - rCurrentX) > osgEps) ||
        (osgabs(rLastY - rCurrentY) > osgEps))
    {
        /*
         * First, figure out z-coordinates for projection of P1 and P2 to
         * deformed sphere
         */
        
        gP1.setValues(	rLastX,
						rLastY,
						 projectToSphere(_rTrackballSize, rLastX, rLastY));

        gP2.setValues(	rCurrentX,
						rCurrentY,
						projectToSphere(_rTrackballSize, rCurrentX, rCurrentY));
        
        /*
         *  Now, we want the cross product of P1 and P2
         */

        gAxis = gP2;
        gAxis.crossThis(gP1);

        /*
         *  Figure out how much to rotate around that axis.
         */

        gDiff = gP2;
        gDiff -= gP1;

        rTmp = gDiff.length() / (2.0f * _rTrackballSize);


        /*
         * Avoid problems with out-of-control values...
         */
        
        if(rTmp > 1.0) 
            rTmp = 1.0;

        if(rTmp < -1.0) 
            rTmp = -1.0;

        if(_gMode == OSGObject)
            rPhi = (OSGReal32) -2.0 * osgasin(rTmp);
        else
            rPhi = (OSGReal32)  2.0 * osgasin(rTmp);

    }

    if(_bSum == false)
    {
        _qVal.setValue(gAxis, osgrad2degree(rPhi));
    }
    else
    {
        qCurrVal.setValue(gAxis, osgrad2degree(rPhi));
        _qVal *= qCurrVal;
//        _qVal.multLeft(qCurrVal);
    }
}

void OSGTrackball::updatePosition(OSGReal32 rLastX,    OSGReal32 rLastY, 
                                 OSGReal32 rCurrentX, OSGReal32 rCurrentY)
{
    if(_gTransMode == OSGFree)
    {
        _pVal[0] += (rLastX - rCurrentX) * -_rTranslationScale;
        _pVal[1] += (rLastY - rCurrentY) * -_rTranslationScale;
    }	
}

void OSGTrackball::updatePositionNeg(OSGReal32 /*rLastX*/,    OSGReal32 rLastY, 
                                    OSGReal32 /*rCurrentX*/, OSGReal32 rCurrentY)
{
    if(_gTransMode == OSGFree)
    {
        _pVal[2] += (rLastY - rCurrentY) * -_rTranslationScale;
    }
}

void OSGTrackball::setAutoPositionIncrement(OSGReal32 rVal)
{
    _rAutoPositionIncrement = rVal;
}

void OSGTrackball::setAutoPosition(bool bVal)
{
    _bAutoPosition = bVal;
    _rAutoPositionStep = -_rAutoPositionIncrement;
}

void OSGTrackball::setAutoPositionNeg(bool bVal)
{
    _bAutoPosition = bVal;
    _rAutoPositionStep = _rAutoPositionIncrement;
}

void OSGTrackball::setMode(OSGMode gMode)
{
    _gMode = gMode;
}

void OSGTrackball::setTranslationMode(OSGTranslationMode gMode)
{
    _gTransMode = gMode;
}

void OSGTrackball::setTranslationScale(OSGReal32 rTranslationScale)
{
    _rTranslationScale = rTranslationScale;
}


void OSGTrackball::reset(void)
{
    _qVal = _qValStart;
    _pVal = _pValStart;
}

void OSGTrackball::setStartPosition(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ,
                                   bool bUpdate)
{
    _pValStart.setValues(rX, rY, rZ);
    
    if(bUpdate == true)
        _pVal = _pValStart;
}

void OSGTrackball::setStartPosition(OSGVec3f &gStartPos, bool bUpdate)
{
    _pValStart = gStartPos;
    
    if(bUpdate == true)
        _pVal = _pValStart;
}

OSGVec3f &OSGTrackball::getPosition(void)
{
	/*
    if(_bAutoPosition == true)
        _pVal[2] += _rAutoPositionStep;

    return _pVal;
	*/    
	if(_bAutoPosition == true)
    {
        switch(_gTransMode)
        {
            case OSGFixedX:
                _pVal[0] += _rAutoPositionStep;
                break;
                
            case OSGFixedY:
                _pVal[1] += _rAutoPositionStep;
                break;
                
            case OSGFixedZ:
                _pVal[2] += _rAutoPositionStep;
                break;
                
            default:
                break;
        }
    }

    return _pVal;
}

void OSGTrackball::setStartRotation(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ, OSGReal32 rW, 
                                  bool bUpdate)
{
    _qValStart.setValueAsAxis(rX, rY, rZ, rW);

    if(bUpdate == true)
        _qVal = _qValStart;
}

void OSGTrackball::setStartRotation(OSGQuaternion &gStartRot, bool bUpdate)
{
    _qValStart = gStartRot;

    if(bUpdate == true)
        _qVal = _qValStart;
}

OSGQuaternion &OSGTrackball::getRotation(void)
{
    return _qVal;
}




