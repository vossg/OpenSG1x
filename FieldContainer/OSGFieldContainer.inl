
// #include <new.h>

OSG_BEGIN_NAMESPACE

/*-------------------------- output -----------------------------------*/

/** \brief Write FC to the given stream
 */
template <class OSGBasePtrTypeT, class OSGFieldContainerTypeT> inline
ostream &operator <<(ostream                                          &os,
                     const OSGFCPtr<OSGBasePtrTypeT, OSGFieldContainerTypeT> &fc)
{
	if ( fc == OSGNullFC )
		os << hex << "OSGFCPtr 0x" << &fc << dec << ":OSGNullFC";
	else
		os << hex << "OSGFCPtr 0x" << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x" 
		   << hex << (int)fc._storeP << dec << ")";

	return os;
}



OSG_END_NAMESPACE
