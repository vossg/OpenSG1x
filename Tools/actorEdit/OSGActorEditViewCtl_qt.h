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

#ifndef _OSGACTOREDITVIEWCTL_QT_H_
#define _OSGACTOREDITVIEWCTL_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGActorEditView_qt.uic.h"
#include "OSGActorDesc.h"

#include <string>

OSG_USING_NAMESPACE

class ActorEditViewCtl : public ActorEditView
{
    Q_OBJECT

    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    ActorEditViewCtl(QWidget *pParent = 0,     const char *name = 0,
                     bool     modal   = FALSE, WFlags      fl   = 0 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    virtual ~ActorEditViewCtl(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Actor Desc Access                                         */
    /*! \{                                                                 */

    const ActorDesc &getActorDesc(void                 ) const;
          ActorDesc &getActorDesc(void                 );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Load / Save / Write                                       */
    /*! \{                                                                 */

    void loadActorDesc     (const std::string &inFileName     );
    void saveActorDesc     (const std::string &outFileName    );

    void writeActorBaseCode(const std::string &outDecFileName,
                            const std::string &outImpFileName,
                            const std::string &outInlFileName );
    void writeActorCode    (const std::string &outDecFileName,
                            const std::string &outImpFileName,
                            const std::string &outInlFileName );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected slots:
    /*---------------------------------------------------------------------*/
    /*! \name    Protected Slots                                           */
    /*! \{                                                                 */

    virtual void aboutButtonClicked             (void           );
    virtual void actorNameChanged               (const QString &);
    virtual void enterFunctorStoreChanged       (const QString &);
    virtual void exitButtonClicked              (void           );
    virtual void leaveFunctorStoreChanged       (const QString &);
    virtual void libraryNameChanged             (const QString &);
    virtual void loadButtonClicked              (void           );
    virtual void newButtonClicked               (void           );
    virtual void seHighlightChanged             (int            );
    virtual void parentNameChanged              (const QString &);
    virtual void parentSystemComponentChanged   (bool           );
    virtual void saveAsButtonClicked            (void           );
    virtual void saveButtonClicked              (void           );
    virtual void seAccessChanged                (const QString &);
    virtual void seDefaultValueChanged          (const QString &);
    virtual void seDeleteButtonClicked          (void           );
    virtual void seDownButtonClicked            (void           );
    virtual void seHeaderChanged                (const QString &);
    virtual void seHierarchicalChanged          (bool           );
    virtual void seNameChanged                  (const QString &);
    virtual void seNewButtonClicked             (void           );
    virtual void seTypeChanged                  (const QString &);
    virtual void seUpButtonClicked              (void           );
    virtual void useLocalIncludesChanged        (bool           );
    virtual void systemComponentChanged         (bool           );
    virtual void writeActorBaseCodeButtonClicked(void           );
    virtual void writeActorCodeButtonClicked    (void           );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    typedef ActorEditView Inherited;

    std::string buildSEListEntry(ActorDesc::StateElemListIt itSE);

    void updateActorView    (void);
    void updateSEList       (void);
    void updateActiveSEEntry(void);
    void updateActiveSEView (void);

    ActorDesc _actorDesc;
    Int32     _iActiveSEIndex;
};

//#include "OSGActorEditViewCtl_qt.inl"

#define OSGACTOREDITVIEWCTLQT_HEADER_CVSID "@(#)$Id: OSGActorEditViewCtl_qt.h,v 1.1 2004/04/20 13:06:50 neumannc Exp $"

#endif /* _OSGACTOREDITVIEWCTL_QT_H_ */
