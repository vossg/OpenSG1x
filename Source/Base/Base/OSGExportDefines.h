/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGEXPORTDEFINES_H_
#define _OSGEXPORTDEFINES_H_

#ifndef WIN32
#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
#else
#ifdef OSG_WIN32_ICL
#define OSG_EXPORT_TYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                     \
    extern template DLLMAPPING                                               \
        const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                 \
    extern template DLLMAPPING                                               \
        const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_EXPORT_GETTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                  \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1>::getType    (void) const;
#define OSG_EXPORT_GETTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)              \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1, T2>::getType(void) const;

#define OSG_EXPORT_GETCLASSTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)             \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1>::getClassType(void);
#define OSG_EXPORT_GETCLASSTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)         \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1, T2>::getClassType(void);

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    OSG_EXPORT_GETTYPE_DECL1     (CLASSNAME, T1, DLLMAPPING)                 \
    OSG_EXPORT_TYPE_DECL1        (CLASSNAME, T1, DLLMAPPING)                 \
    OSG_EXPORT_GETCLASSTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    OSG_EXPORT_TYPE_DECL2        (CLASSNAME, T1, T2, DLLMAPPING)             \
    OSG_EXPORT_GETTYPE_DECL2     (CLASSNAME, T1, T2, DLLMAPPING)             \
    OSG_EXPORT_GETCLASSTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
#else
#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    extern template class DLLMAPPING CLASSNAME<T1, T2>;
#endif
#endif

#ifndef WIN32
#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)
#else
#ifdef OSG_WIN32_ICL
#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template                                                          \
        FieldContainerType CLASSNAME<T1>::_type;

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    extern template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    extern template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     
#else
#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    extern template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    extern template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    extern template class DLLMAPPING CLASSNAME<T1>;
#endif
#endif

#ifdef WIN32
#ifdef OSG_WIN32_ICL
#define  OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)         \
template<>                                                       \
FieldContainerType CLASSNAME< T1 >::_type =                      \
    FieldContainerType(                                          \
        T1::getTypeName(),                                       \
        T1::getParentTypeName(),                                 \
        T1::getGroupName(),                                      \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,        \
        T1::getInitMethod(),                                     \
        T1::getDesc(),                                           \
        sizeof(FieldDescription *));                             \
                                                                 \
template DLLMAPPING                                              \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);         \
                                                                 \
template DLLMAPPING                                              \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);                    \
                                                                 \
template DLLMAPPING                                              \
FieldContainerType &CLASSNAME< T1 >::getType(void);              \
template DLLMAPPING                                              \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const


#define  OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        T1::getDesc(),                                         \
        sizeof(FieldDescription *));                           \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);       \
                                                               \
template DLLMAPPING                                            \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);                  \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getType(void);            \
template DLLMAPPING                                            \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const

#define  OSG_DYNFIELD_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        NULL,                                                  \
        0,                                                     \
        true);                                                 \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);       \
                                                               \
template DLLMAPPING                                            \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);                  \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getType(void);            \
template DLLMAPPING                                            \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const
#else
#define  OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)         \
template<>                                                       \
FieldContainerType CLASSNAME< T1 >::_type =                      \
    FieldContainerType(                                          \
        T1::getTypeName(),                                       \
        T1::getParentTypeName(),                                 \
        T1::getGroupName(),                                      \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,        \
        T1::getInitMethod(),                                     \
        T1::getDesc(),                                           \
        sizeof(FieldDescription *));                             \
template class DLLMAPPING CLASSNAME< T1 >

#define  OSG_DYNFIELD_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        NULL,                                                  \
        0,                                                     \
        true);                                                 \
template class DLLMAPPING CLASSNAME< T1 >
#endif
#else
#define  OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)         \
template<>                                                       \
FieldContainerType CLASSNAME< T1 >::_type =                      \
    FieldContainerType(                                          \
        T1::getTypeName(),                                       \
        T1::getParentTypeName(),                                 \
        T1::getGroupName(),                                      \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,        \
        T1::getInitMethod(),                                     \
        T1::getDesc(),                                           \
        sizeof(FieldDescription *))

#define  OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        T1::getDesc(),                                         \
        sizeof(FieldDescription *))

#define  OSG_DYNFIELD_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        NULL,                                                  \
        0,                                                     \
        true)
#endif

#ifdef WIN32
#ifdef OSG_WIN32_ICL
#define  OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractGeoProperty< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0);                                                         \
                                                                    \
template DLLMAPPING                                                 \
FieldContainerType &AbstractGeoProperty< T1 >::getClassType(void);  \
                                                                    \
template DLLMAPPING                                                 \
UInt32 AbstractGeoProperty< T1 >::getClassTypeId(void);             \
                                                                    \
template DLLMAPPING                                                 \
FieldContainerType &AbstractGeoProperty< T1 >::getType(void);       \
template DLLMAPPING                                                 \
const FieldContainerType &AbstractGeoProperty< T1 >::getType(void) const


#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType GeoProperty< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &GeoProperty< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &GeoProperty< T1 >::getClassType(void);    \
                                                              \
template DLLMAPPING                                           \
UInt32 GeoProperty< T1 >::getClassTypeId(void);               \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &GeoProperty< T1 >::getType(void);         \
template DLLMAPPING                                           \
const FieldContainerType &GeoProperty< T1 >::getType(void) const
#else
#define  OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractGeoProperty< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0);                                                         \
                                                                    \
template class DLLMAPPING AbstractGeoProperty< T1 >

#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType GeoProperty< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &GeoProperty< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template class DLLMAPPING GeoProperty< T1 >
#endif
#else
#define  OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractGeoProperty< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0)

#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType GeoProperty< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &GeoProperty< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *))
#endif

#define OSG_DLLEXPORT_SFIELD_TYPE_DEF1(T1,     DLLMAPPING) \
template <>                                                \
const FieldType SField< T1, 0 >::_fieldType(               \
    SFieldTraits::getSName(),                              \
    SFieldTraits::getPName (),                             \
    SFieldTraits::getType(),                               \
    SField< T1, 0 >::create,                               \
    FieldType::SINGLE_FIELD)

#define OSG_DLLEXPORT_SFIELD_TYPE_DEF1_ST(T1,     DLLMAPPING) \
template <>                                                   \
const FieldType SField< T1, 0 >::_fieldType(                  \
    SFieldTraits::getSName(),                                 \
    SFieldTraits::getPName (),                                \
    SFieldTraits::getType(),                                  \
    SField< T1, 0 >::create,                                  \
    FieldType::SINGLE_FIELD,                                  \
    SFieldTraits::getScanAsTypeSF())

#define OSG_DLLEXPORT_SFIELD_TYPE_DEF2(T1, T2, DLLMAPPING) \
template <>                                                \
const FieldType SField< T1, T2 >::_fieldType(              \
    SFieldTraits::getSName(),                              \
    SFieldTraits::getPName (),                             \
    SFieldTraits::getType(),                               \
    SField< T1, T2 >::create,                              \
    FieldType::SINGLE_FIELD)

#define OSG_DLLEXPORT_MFIELD_TYPE_DEF1(T1,     DLLMAPPING) \
template <>                                                \
const FieldType MField< T1, 0 >::_fieldType(               \
    MFieldTraits::getMName(),                              \
    MFieldTraits::getPName (),                             \
    MFieldTraits::getType(),                               \
    MField< T1 >::create,                                  \
    FieldType::MULTI_FIELD)

#define OSG_DLLEXPORT_MFIELD_TYPE_DEF1_ST(T1,     DLLMAPPING) \
template <>                                                   \
const FieldType MField< T1, 0 >::_fieldType(                  \
    MFieldTraits::getMName(),                                 \
    MFieldTraits::getPName (),                                \
    MFieldTraits::getType(),                                  \
    MField< T1 >::create,                                     \
    FieldType::MULTI_FIELD,                                   \
    MFieldTraits::getScanAsTypeMF())

#define OSG_DLLEXPORT_MFIELD_TYPE_DEF2(T1, T2, DLLMAPPING) \
template <>                                                \
const FieldType MField< T1, T2 >::_fieldType(              \
    MFieldTraits::getMName(),                              \
    MFieldTraits::getPName (),                             \
    MFieldTraits::getType(),                               \
    MField< T1, T2 >::create,                              \
    FieldType::MULTI_FIELD)


#if defined(OSG_WIN32_ICL)
#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  SField< T1, 0 >::_fieldType;                  \
template DLLMAPPING                                            \
const FieldType &SField< T1, 0 >::getClassType(void);          \
template DLLMAPPING                                            \
const FieldType &SField< T1, 0 >::getType(void) const

#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  SField< T1, T2 >::_fieldType;                 \
template DLLMAPPING                                            \
const FieldType &SField< T1, T2 >::getClassType(void);         \
template DLLMAPPING                                            \
const FieldType &SField< T1, T2 >::getType(void) const

#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  MField< T1, 0 >::_fieldType;                  \
template DLLMAPPING                                            \
const FieldType &MField< T1, 0 >::getClassType(void);          \
template DLLMAPPING                                            \
const FieldType &MField< T1, 0 >::getType(void) const

#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  MField< T1, T2 >::_fieldType;                 \
template DLLMAPPING                                            \
const FieldType &MField< T1, T2 >::getClassType(void);         \
template DLLMAPPING                                            \
const FieldType &MField< T1, T2 >::getType(void) const
#else
#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template class DLLMAPPING SField< T1, 0 >
#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template class DLLMAPPING MField< T1, 0 >                           
#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template class DLLMAPPING SField< T1, T2 >                          
#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template class DLLMAPPING MField< T1, T2 >
#endif

#ifdef WIN32
#define OSG_DLLEXPORT_SFIELD_DEF1(T1,     DLLMAPPING)         \
    OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_SFIELD_DEF1_ST(T1,     DLLMAPPING)      \
    OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_SFIELD_DEF2(T1, T2, DLLMAPPING)         \
    OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF1(T1,     DLLMAPPING)         \
    OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) 

#define OSG_DLLEXPORT_MFIELD_DEF1_ST(T1,     DLLMAPPING)      \
    OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) 

#define OSG_DLLEXPORT_MFIELD_DEF2(T1, T2, DLLMAPPING)         \
    OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING)


#define OSG_ABSTR_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,            \
                                        OSG_TMPL_PARAM,       \
                                        OSG_CLASS_PTR)        \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,                         \
                                  OSG_TMPL_PARAM,                    \
                                  OSG_CLASS_PTR)                     \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)

#define OSG_GEO_PROP_TYPE_TMPL_DEF(OSG_CLASS,                         \
                                   OSG_TMPL_PARAM,                    \
                                   OSG_CLASS_PTR)                     \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#else
#define OSG_DLLEXPORT_SFIELD_DEF1(T1,      DLLMAPPING)                \
    OSG_DLLEXPORT_SFIELD_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_SFIELD_DEF1_ST(T1,   DLLMAPPING)                \
    OSG_DLLEXPORT_SFIELD_TYPE_DEF1_ST(T1,  DLLMAPPING)

#define OSG_DLLEXPORT_SFIELD_DEF2(T1, T2,  DLLMAPPING)                \
    OSG_DLLEXPORT_SFIELD_TYPE_DEF2(T1, T2, DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF1(T1,      DLLMAPPING)                \
    OSG_DLLEXPORT_MFIELD_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF1_ST(T1,   DLLMAPPING)                \
    OSG_DLLEXPORT_MFIELD_TYPE_DEF1_ST(T1,  DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF2(T1, T2,  DLLMAPPING)                \
    OSG_DLLEXPORT_MFIELD_TYPE_DEF2(T1, T2, DLLMAPPING)


#define OSG_ABSTR_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,            \
                                        OSG_TMPL_PARAM,       \
                                        OSG_CLASS_PTR)

#define OSG_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,                         \
                                  OSG_TMPL_PARAM,                    \
                                  OSG_CLASS_PTR)

#define OSG_GEO_PROP_TYPE_TMPL_DEF(OSG_CLASS,                         \
                                   OSG_TMPL_PARAM,                    \
                                   OSG_CLASS_PTR)
#endif

#endif /* _OSGEXPORTDEFINES_H_ */
