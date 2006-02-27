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

#ifndef _OSGCHANGELIST_H_
#define _OSGCHANGELIST_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGChangeList.h
    \ingroup GrpSystemMultithreading
 */
#endif

#include <vector>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGMemoryObject.h>

OSG_BEGIN_NAMESPACE

class Thread;
class Field;
class FieldContainerPtr;

/*! \ingroup GrpSystemMultithreading
 */

class OSG_SYSTEMLIB_DLLMAPPING ChangeList : public MemoryObject
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum Mode
    {
        Private,
        Public
    };

//    typedef pair<FieldContainerPtr, BitVector>  ChangeEntry;

    typedef std::pair<UInt32, BitVector>             ChangeEntry;     
    typedef FieldContainerPtr                        RefEntry;    
    typedef UInt32                                   IdRefEntry;

    typedef std::vector<ChangeEntry>::size_type      changed_size_type;
    typedef std::vector<ChangeEntry>::const_iterator changed_const_iterator;

//    typedef vector<RefEntry>::size_type       refd_size_type;
//    typedef vector<RefEntry>::const_iterator  refd_const_iterator;

    typedef std::vector<IdRefEntry>::size_type       refd_size_type;
    typedef std::vector<IdRefEntry>::const_iterator  refd_const_iterator;

    typedef std::vector<IdRefEntry>::size_type       idrefd_size_type;
    typedef std::vector<IdRefEntry>::const_iterator  idrefd_const_iterator;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ChangeList(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ChangeList(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    changed_size_type      sizeChanged   (void);

    changed_const_iterator beginChanged  (void) const;
    changed_const_iterator endChanged    (void) const;
    
    refd_size_type         sizeAddRefd   (void);

    refd_const_iterator    beginAddRefd  (void) const;
    refd_const_iterator    endAddRefd    (void) const;

    refd_size_type         sizeSubRefd   (void);

    refd_const_iterator    beginSubRefd  (void) const;
    refd_const_iterator    endSubRefd    (void) const;

    idrefd_const_iterator  beginCreated  (void) const;
    idrefd_const_iterator  endCreated    (void) const;

    idrefd_size_type       sizeCreated   (void) const;

    idrefd_const_iterator  beginDestroyed(void) const;
    idrefd_const_iterator  endDestroyed  (void) const;

    idrefd_size_type       sizeDestroyed (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Add                                     */
    /*! \{                                                                 */

    void addChanged  (const FieldContainerPtr &pFieldContainer, 
                            BitVector          bvWhichField   );
    void addAddRefd  (const FieldContainerPtr &pFieldContainer);
    void addSubRefd  (const FieldContainerPtr &pFieldContainer);

    void addCreated  (const UInt32 uiContainerId);
    void addDestroyed(const UInt32 uiContainerId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Helper                                   */
    /*! \{                                                                 */
    
           void clearAll           (      void                     );
           void swap               (      ChangeList &list         );
           bool merge              (const ChangeList &list         );
           bool empty              (                               ) const;

           void setAspect          (      UInt32 uiAspectId        );

           void setReadOnly        (      bool bReadOnly           );
    static void setReadWriteDefault(      bool bReadWrite = true   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Apply                                   */
    /*! \{                                                                 */

#ifndef OSG_DISABLE_DEPRECATED
    void applyTo       (UInt32 uiAspectId);
    void applyToCurrent(void);
#endif

    void apply        (void);
    void applyAndClear(void);

#if defined(OSG_FIXED_MFIELDSYNC)
    void applySubRefs(void);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    void dump(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef MemoryObject Inherited;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class Thread;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

           bool              _bReadOnly;
    static bool              _bReadWriteDefault;

    UInt32                   _uiAspectId;
    Mode                     _listMode;

    std::vector<ChangeEntry> _vChangedFieldContainers;

//    vector<RefEntry>  _vAddRefdFieldContainers;
//    vector<RefEntry>  _vSubRefdFieldContainers;

    std::vector<IdRefEntry>  _vAddRefdFieldContainers;
    std::vector<IdRefEntry>  _vSubRefdFieldContainers;
    
    std::vector<IdRefEntry>  _vCreatedFieldContainers;
    std::vector<IdRefEntry>  _vDestroyedFieldContainers;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    /*!\brief prohibit default function (move to 'public' if needed) */
    ChangeList(const ChangeList &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ChangeList &source);
};

OSG_END_NAMESPACE

#define OSGCHANGELIST_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGCHANGELIST_H_ */
