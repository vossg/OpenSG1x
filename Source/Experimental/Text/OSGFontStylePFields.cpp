#define OSG_COMPILEFONTSTYLEINST


#include <OSGFontStylePFields.h>
#include <OSGSFieldTypeDef.inl>
#include <OSGMFieldTypeDef.inl>



OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<FontStyleP>::_type("FontStyleP", NULL ); 

OSG_DLLEXPORT_SFIELD_DEF1_ST(FontStyleP, OSG_WINDOWGLUTLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1_ST(FontStyleP, OSG_WINDOWGLUTLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */
#if 0

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCBaseTemplate_cpp.h,v 1.35 2002/09/16 18:39:11 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGFONTSTYLEFIELDS_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFONTSTYLEFIELDS_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFONTSTYLEFIELDS_HEADER_CVSID;
}

#endif

