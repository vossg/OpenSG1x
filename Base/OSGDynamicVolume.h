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

#ifndef OSGDYNAMICVOLUME_CLASS_DECLARATION
#define OSGDYNAMICVOLUME_CLASS_DECLARATION

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include <OSGVolume.h>

/* 3D base volume.
 *
 *
 * @author jbehr, Wed Feb 16 20:04:15 2000
 */

OSG_BEGIN_NAMESPACE

class OSG_DLLEXPORT DynamicVolume {
		
public:

	enum Type { BOX_VOLUME, SPHERE_VOLUME, CYLINDER_VOLUME };    

private:

	Type _type;

	UChar8 _volumeMem [36];


protected:

public:

  /** Default Constructor */
  DynamicVolume (Type type = BOX_VOLUME );

  /** Copy Constructor */
    DynamicVolume (const DynamicVolume &obj);

  /** Destructor */
  virtual ~DynamicVolume (void) {;}

	/** */
	Volume & getVolume (void) const { return *((OSG::Volume*)(_volumeMem)); }

	/** */
	DynamicVolume::Type getType (void) const { return _type; }

	/** */
	void setVolumeType (Type type);

	/** */
	void morphToType (Type type);

	/** */
	DynamicVolume & operator = (const DynamicVolume &source);

};

ostream &operator <<(ostream &outStream,
                     const DynamicVolume &vol);

typedef DynamicVolume* DynamicVolumeP;

OSG_END_NAMESPACE

#endif // OSGDYNAMICVOLUME_CLASS_DECLARATION
