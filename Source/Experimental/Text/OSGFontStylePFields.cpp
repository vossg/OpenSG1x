
#define OSG_COMPILEFONTSTYLEINST


#include <OSGFontStylePFields.h>

#include <OSGSFieldTypeScanTypeDef.inl>
#include <OSGMFieldTypeScanTypeDef.inl>

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<FontStyleP>::_type("FontStyleP", NULL ); 

OSG_DLLEXPORT_SFIELD_DEF1_ST(FontStyleP, OSG_SYSTEMLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1_ST(FontStyleP, OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

OSG_USING_NAMESPACE

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGFONTSTYLEFIELDS_HEADER_CVSID;
//    static Char8 cvsid_inl       [] = OSGFONTSTYLEFIELDS_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFONTSTYLEFIELDS_HEADER_CVSID;
}


