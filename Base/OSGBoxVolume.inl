/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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


#ifndef _OSGBOXVOLUME_INL_
#define _OSGBOXVOLUME_INL_

#include "OSGConfig.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class BoxVolume;
Bool operator ==(const BoxVolume &b1, const BoxVolume &b2);
Bool operator !=(const BoxVolume &b1, const BoxVolume &b2);
ostream& operator<< (ostream & os, const BoxVolume &obj);
#endif

/*! Default constructor - leaves box totally empty
*/

inline
BoxVolume::BoxVolume() : Volume() {;}

inline
BoxVolume::BoxVolume ( float xmin, float ymin, float zmin,
                       float xmax, float ymax, float zmax) 
	: Volume(), _min(xmin, ymin, zmin), _max(xmax, ymax, zmax) 
{ setEmpty(false); }

inline
BoxVolume::BoxVolume(const Pnt3f &min, const Pnt3f &max)
		: Volume(), _min(min), _max(max) 
{ setEmpty(false); }

inline
BoxVolume::BoxVolume(const BoxVolume &obj)
		: Volume(obj), _min(obj._min), _max(obj._max) {;}

inline
BoxVolume::~BoxVolume() {;}

inline
const Pnt3f &BoxVolume::getMin() const 
{ 
	return _min; 
}

inline
const Pnt3f &BoxVolume::getMax() const 
{ 
	return _max; 
}

inline
void BoxVolume::setBounds(float w, float h, float d)
{
    _min.setValues(-w / 2.0, -h / 2.0, -d / 2.0);
    _max.setValues( w / 2.0,  h / 2.0,  d / 2.0);

		Volume::setValid(true);
		Volume::setEmpty(false);
		Volume::setInfinite(false);
}

inline
void BoxVolume::setBounds(float xmin, float ymin, float zmin,
                        float xmax, float ymax, float zmax)
{
    _min.setValues(xmin, ymin, zmin);
    _max.setValues(xmax, ymax, zmax);

		Volume::setValid(true);
		Volume::setEmpty(false);
		Volume::setInfinite(false);
}

inline
void BoxVolume::setBounds(const Pnt3f &min, const Pnt3f &max)
{ 
	_min = min; _max = max; 
			
	Volume::setValid(true);
	Volume::setEmpty(false);
	Volume::setInfinite(false);
}


inline
void BoxVolume::getBounds(float &xmin, float &ymin, float &zmin,
                        float &xmax, float &ymax, float &zmax ) const
{ 
	_min.getSeparateValues(xmin, ymin, zmin); 
	_max.getSeparateValues(xmax, ymax, zmax); 
}

inline
void BoxVolume::getBounds(Pnt3f &min, Pnt3f &max) const
{ 
	min = _min; 
	max = _max; 
}
    
inline
void BoxVolume::getOrigin(float &originX, float &originY, float &originZ) const
{ 
	originX = _min[0]; 
	originY = _min[1]; 
	originZ = _min[2]; 
}

inline
void BoxVolume::getSize(float &sizeX, float &sizeY, float &sizeZ) const
{
    sizeX = _max[0] - _min[0];
    sizeY = _max[1] - _min[1]; 
    sizeZ = _max[2] - _min[2]; 
}

inline
void BoxVolume::getSize(Vec3f &vec) const
{ 
	vec.setValues(_max[0] - _min[0], _max[1] - _min[1], _max[2] - _min[2]); 
}

inline
void BoxVolume::extendBy(const Volume &volume)
{
	osg::extend(*this,volume);
}

inline
void BoxVolume::extendBy(const BoxVolume &volume)
{
	osg::extend(*this,volume);
}

inline
Bool BoxVolume::intersect (const Volume &volume) const
{
	return osg::intersect(*this,volume);
}

inline
Bool BoxVolume::intersect(const BoxVolume &volume) const
{
	return osg::intersect(*this,volume);
}

inline
Bool operator != (const BoxVolume &b1, const BoxVolume &b2)
{ 
	return !(b1 == b2); 
}

OSG_END_NAMESPACE

#endif // BOX_CLASS_DECLARATION
