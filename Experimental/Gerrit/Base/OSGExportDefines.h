/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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


#if (defined(WIN32) && defined(__ICL)) || defined (darwin)

#define OSG_EXTERN_EXPORT

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



#define OSG_EXPORT_TYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                      \
    template                                                                 \
        const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                  \
    template                                                                 \
        const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_EXPORT_GETTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                   \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1>::getType    (void) const;
#define OSG_EXPORT_GETTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)               \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1, T2>::getType(void) const;

#define OSG_EXPORT_GETCLASSTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)              \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1>::getClassType    (void);
#define OSG_EXPORT_GETCLASSTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)          \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1, T2>::getClassType(void);

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
    OSG_EXPORT_TYPE_DEF1        (CLASSNAME, T1, DLLMAPPING)                  \
    OSG_EXPORT_GETTYPE_DEF1     (CLASSNAME, T1, DLLMAPPING)                  \
    OSG_EXPORT_GETCLASSTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)


#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
    OSG_EXPORT_TYPE_DEF2        (CLASSNAME, T1, T2, DLLMAPPING)              \
    OSG_EXPORT_GETTYPE_DEF2     (CLASSNAME, T1, T2, DLLMAPPING)              \
    OSG_EXPORT_GETCLASSTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)



#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template                                                          \
        FieldContainerType CLASSNAME<T1>::_type;

/*
#define OSG_FC_EXPORT_DESC_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template                                                          \
        FieldDescription   *CLASSNAME<T1>::_desc[];
*/

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    extern template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    extern template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

//  OSG_FC_EXPORT_DESC_DECL   (CLASSNAME, T1, DLLMAPPING)                    

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     



#define OSG_FC_EXPORT_TYPE_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template                                                                 \
        FieldContainerType CLASSNAME<T1>::_type;

/*
#define OSG_FC_EXPORT_DESC_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template                                                                 \
        FieldDescription  *CLASSNAME<T1>::_desc[];
*/

#define OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)                 \
    template DLLMAPPING                                                      \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    template DLLMAPPING                                                      \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    template DLLMAPPING                                                      \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    template DLLMAPPING                                                      \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

//  OSG_FC_EXPORT_DESC_DEF   (CLASSNAME, T1, DLLMAPPING)                     

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)     


#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)     

#elif defined(WIN32) && !defined(BCC)

#define OSG_EXTERN_EXPORT extern

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    extern template class DLLMAPPING CLASSNAME<T1, T2>;

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
           template class DLLMAPPING CLASSNAME<T1>;

#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
           template class DLLMAPPING CLASSNAME<T1, T2>;





#define OSG_FC_EXPORT_CLASS_DECL(CLASSNAME, T1, DLLMAPPING)                  \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_CLASS_DECL (CLASSNAME, T1, DLLMAPPING)

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_CLASS_DECL       (CLASSNAME, T1, DLLMAPPING)



#define OSG_FC_EXPORT_CLASS_DEF(CLASSNAME, T1, DLLMAPPING)                   \
           template class DLLMAPPING CLASSNAME<T1>;

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_CLASS_DEF (CLASSNAME, T1, DLLMAPPING)

#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_CLASS_DEF       (CLASSNAME, T1, DLLMAPPING)


#elif defined (WIN32) && defined(BCC)

#define OSG_EXTERN_EXPORT

#define OSG_EXPORT_TYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                     \
    explicit template                                                        \
        const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                 \
           template                                                          \
        const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_EXPORT_GETTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                  \
           template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1>::getType    (void) const;
#define OSG_EXPORT_GETTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)              \
           template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1, T2>::getType(void) const;

#define OSG_EXPORT_GETCLASSTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)             \
           template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1>::getClassType(void);
#define OSG_EXPORT_GETCLASSTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)         \
           template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1, T2>::getClassType(void);

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    OSG_EXPORT_GETTYPE_DECL1     (CLASSNAME, T1, DLLMAPPING)                 \
    OSG_EXPORT_TYPE_DECL1        (CLASSNAME, T1, DLLMAPPING)                 \
    OSG_EXPORT_GETCLASSTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    OSG_EXPORT_TYPE_DECL2        (CLASSNAME, T1, T2, DLLMAPPING)             \
    OSG_EXPORT_GETTYPE_DECL2     (CLASSNAME, T1, T2, DLLMAPPING)             \
    OSG_EXPORT_GETCLASSTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)



#define OSG_EXPORT_TYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                      \
    template                                                                 \
        const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                  \
    template                                                                 \
        const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_EXPORT_GETTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                   \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1>::getType    (void) const;
#define OSG_EXPORT_GETTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)               \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1, T2>::getType(void) const;

#define OSG_EXPORT_GETCLASSTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)              \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1>::getClassType    (void);
#define OSG_EXPORT_GETCLASSTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)          \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1, T2>::getClassType(void);

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
    OSG_EXPORT_TYPE_DEF1        (CLASSNAME, T1, DLLMAPPING)                  \
    OSG_EXPORT_GETTYPE_DEF1     (CLASSNAME, T1, DLLMAPPING)                  \
    OSG_EXPORT_GETCLASSTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)


#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
    OSG_EXPORT_TYPE_DEF2        (CLASSNAME, T1, T2, DLLMAPPING)              \
    OSG_EXPORT_GETTYPE_DEF2     (CLASSNAME, T1, T2, DLLMAPPING)              \
    OSG_EXPORT_GETCLASSTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)



#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
           template                                                          \
        FieldContainerType CLASSNAME<T1>::_type;

/*
#define OSG_FC_EXPORT_DESC_DECL(CLASSNAME, T1, DLLMAPPING)                   \
           template                                                          \
        FieldDescription  *CLASSNAME<T1>::_desc[];
*/

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
           template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
           template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
           template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
           template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

//  OSG_FC_EXPORT_DESC_DECL   (CLASSNAME, T1, DLLMAPPING)                    

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     



#define OSG_FC_EXPORT_TYPE_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template                                                                 \
        FieldContainerType CLASSNAME<T1>::_type;

/*
#define OSG_FC_EXPORT_DESC_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template                                                                 \
        FieldDescription  *CLASSNAME<T1>::_desc[];
*/

#define OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)                 \
    template DLLMAPPING                                                      \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    template DLLMAPPING                                                      \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    template DLLMAPPING                                                      \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    template DLLMAPPING                                                      \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

//  OSG_FC_EXPORT_DESC_DEF   (CLASSNAME, T1, DLLMAPPING)                     

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)     


#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)     

#elif defined (__hpux)

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)
#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING) 

#define OSG_EXPORT_TYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                      \
    template const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                  \
    template const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
    OSG_EXPORT_TYPE_DEF1        (CLASSNAME, T1, DLLMAPPING)                  \

#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
    OSG_EXPORT_TYPE_DEF2        (CLASSNAME, T1, T2, DLLMAPPING)              \

#elif defined (__linux) || defined(__sun) || defined(__hpux)

#if 0

#define OSG_EXTERN_EXPORT

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    extern template class DLLMAPPING CLASSNAME<T1, T2>;

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
           template class DLLMAPPING CLASSNAME<T1>;

#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
           template class DLLMAPPING CLASSNAME<T1, T2>;





#define OSG_FC_EXPORT_CLASS_DECL(CLASSNAME, T1, DLLMAPPING)                  \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_CLASS_DECL (CLASSNAME, T1, DLLMAPPING)

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_CLASS_DECL       (CLASSNAME, T1, DLLMAPPING)



#define OSG_FC_EXPORT_CLASS_DEF(CLASSNAME, T1, DLLMAPPING)                   \
           template class DLLMAPPING CLASSNAME<T1>;

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_CLASS_DEF (CLASSNAME, T1, DLLMAPPING)

#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_CLASS_DEF       (CLASSNAME, T1, DLLMAPPING)

#endif

#if 1
#define OSG_EXTERN_EXPORT

#define OSG_EXPORT_TYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                     \
    extern template const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                 \
    extern template const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    OSG_EXPORT_TYPE_DECL1        (CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    OSG_EXPORT_TYPE_DECL2        (CLASSNAME, T1, T2, DLLMAPPING)             \


#define OSG_EXPORT_TYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                      \
    template const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                  \
    template const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
    OSG_EXPORT_TYPE_DEF1        (CLASSNAME, T1, DLLMAPPING)                  \

#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
    OSG_EXPORT_TYPE_DEF2        (CLASSNAME, T1, T2, DLLMAPPING)              \



#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template FieldContainerType CLASSNAME<T1>::_type;

/*
#define OSG_FC_EXPORT_DESC_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template FieldDescription  *CLASSNAME<T1>::_desc[];
*/

//  OSG_FC_EXPORT_DESC_DECL   (CLASSNAME, T1, DLLMAPPING)                    

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \



#define OSG_FC_EXPORT_TYPE_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template FieldContainerType CLASSNAME<T1>::_type;

/*
#define OSG_FC_EXPORT_DESC_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template FieldDescription  *CLASSNAME<T1>::_desc[];
*/

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \

#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)
#endif

#elif defined (__sgi)
#define OSG_EXTERN_EXPORT
#else
#error Could not determine system
#endif


#endif /* _OSGEXPORTDEFINES_H_ */
