
#ifndef _OSG_TRACKBALL_H_
#define _OSG_TRACKBALL_H_


#include <OSGBaseTypes.h>
#include <OSGVector.h>
#include <OSGQuaternion.h>

OSG_BEGIN_NAMESPACE

class OSGTrackball
{
  public:

    enum OSGMode
    {
        OSGCamera = 0x01,
        OSGObject = 0x02
    };
		
    enum OSGTranslationMode
    {
        OSGFixedX,
        OSGFixedY,
        OSGFixedZ,        

        OSGFree
    };
		
  public:
    const char *getClassname(void) { return "OSGTrackball"; }

	OSGTrackball(OSGReal32 rSize = 1.0);
	~OSGTrackball(void);

    void setSum(OSGBool bVal);

    void updateRotation(OSGReal32 rLastX,    OSGReal32 rLastY, 
                        OSGReal32 rCurrentX, OSGReal32 rCurrentY);
    void updatePosition(OSGReal32 rLastX,    OSGReal32 rLastY, 
                        OSGReal32 rCurrentX, OSGReal32 rCurrentY);
    void updatePositionNeg(OSGReal32 rLastX,    OSGReal32 rLastY, 
                           OSGReal32 rCurrentX, OSGReal32 rCurrentY);


    void setAutoPositionIncrement(OSGReal32 rVal);
    void setAutoPosition(OSGBool bVal);
    void setAutoPositionNeg(OSGBool bVal);
	
    void setMode(OSGMode gMode);
	void setTranslationMode(OSGTranslationMode gMode);
    void setTranslationScale(OSGReal32 rTranslationScale);


    void reset(void);

    void setStartPosition(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ, 
                          OSGBool bUpdate = false);
    void setStartPosition(OSGVec3f &gStartPos, OSGBool bUpdate = false);

    OSGVec3f &getPosition(void);

    void setStartRotation(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ, OSGReal32 rW, 
                          OSGBool bUpdate = false);
    void setStartRotation(OSGQuaternion &gStartRot, OSGBool bUpdate = false);

    OSGQuaternion &getRotation(void);		

		
	void setSize( OSGReal32 s );
	OSGReal32 getSize() const;

		
  private:

    OSGBool   _bSum;
    OSGBool   _bAutoPosition;

    OSGMode _gMode;
	OSGTranslationMode _gTransMode;
	
    OSGReal32 _rAutoPositionStep;
    OSGReal32 _rAutoPositionIncrement;

    OSGReal32 _rTrackballSize;
	OSGReal32 _rTranslationScale;
	
    OSGQuaternion _qVal;
    OSGVec3f    _pVal;

    OSGQuaternion _qValStart;
    OSGVec3f    _pValStart;

	OSGTrackball(const OSGTrackball &org);
	void operator =(const OSGTrackball &org);

  protected:


    float projectToSphere(OSGReal32 rRadius, OSGReal32 rX, OSGReal32 rY);

};

OSG_END_NAMESPACE

#endif







