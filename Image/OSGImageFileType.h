#ifndef OSGIMAGEFILETYPE_CLASS_DECLARATION
#define OSGIMAGEFILETYPE_CLASS_DECLARATION

#include <list>

#include <OSGBaseTypes.h>
#include <OSGString.h>
#include <OSGImage.h>

OSG_BEGIN_NAMESPACE

/** .
*
*
* @author jbehr, Tue Apr 11 15:32:43 2000
*/


class OSGImageFileType {

private:

  /**  */
  list<OSGString> _suffixList;

	/**  */
	OSGInt16 _majorMagic;

	/**  */
	OSGInt16 _minorMagic;

protected:

  /** Default Constructor */
  OSGImageFileType ( const char * suffixArray[], OSGUInt16 suffixByteCount, 
										 OSGInt16 majorMagic, OSGInt16 minorMagic );

  /** Copy Constructor */
  OSGImageFileType (const OSGImageFileType &obj);

public:

  /** Destructor */
  virtual ~OSGImageFileType (void);

  /** get method for attribute majorMagic, -1 => no major magic code */
  virtual OSGInt16 getMajorMagic (void) { return _majorMagic; }

  /** get method for attribute minorMagic, -1 => no minor magic code */
  virtual OSGInt16 getMinorMagic (void) { return _minorMagic; }

	/** get mathod for the type name */
	virtual const char *getName (void) = 0;

  /** get method for attribute suffixList */
  virtual list<OSGString> & suffixList (void) { return _suffixList; }

  /** fill the given image with the content of the file 'fileName' */
  virtual bool read (OSGImage &image, const char *fileName ) = 0;

  /** write the given image to 'fileName' */
  virtual bool write (const OSGImage &image, const char *fileName ) = 0;

	/** print debug info to cerr */
	void print(void);

};

typedef OSGImageFileType* OSGImageFileTypeP;

OSG_END_NAMESPACE

#endif // OSGIMAGEFILETYPE_CLASS_DECLARATION
