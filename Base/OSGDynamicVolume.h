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

class OSGDynamicVolume {
		
public:

	enum Type { BOX_VOLUME, SPHERE_VOLUME, CYLINDER_VOLUME };    

private:

	Type _type;

	OSGUChar8 _volumeMem [36];


protected:

public:

  /** Default Constructor */
  OSGDynamicVolume (Type type = BOX_VOLUME );

  /** Copy Constructor */
    OSGDynamicVolume (const OSGDynamicVolume &obj);

  /** Destructor */
  virtual ~OSGDynamicVolume (void) {;}

	/** */
	OSGVolume & getVolume (void) const { return *((OSG::OSGVolume*)(_volumeMem)); }

	/** */
	OSGDynamicVolume::Type getType (void) const { return _type; }

	/** */
	void setVolumeType (Type type);

	/** */
	void morphToType (Type type);

	/** */
	OSGDynamicVolume & operator = (const OSGDynamicVolume &source);

};

ostream &operator <<(ostream &outStream,
                     const OSGDynamicVolume &vol);

typedef OSGDynamicVolume* OSGDynamicVolumeP;

OSG_END_NAMESPACE

#endif // OSGDYNAMICVOLUME_CLASS_DECLARATION
