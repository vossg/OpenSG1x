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

#include "OSGActorEditViewCtl_qt.h"
#include "OSGActorDescReader.h"
#include "OSGActorDescWriter.h"
#include "OSGActorCodeWriter.h"

#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlistbox.h>

#include <fstream>

OSG_USING_NAMESPACE

/*------------------------------------------------------------------------*/
/*    Constructors                                                        */

ActorEditViewCtl::ActorEditViewCtl(QWidget *pParent, const char   *name,
                                   bool     modal,         WFlags  fl   )
    : Inherited      (pParent, name, modal, fl  ),
      _actorDesc     (                          ),
      _iActiveSEIndex(-1                        )
{
    updateActorView   ();
    updateSEList      ();
    updateActiveSEView();
}

/*------------------------------------------------------------------------*/
/*    Destructor                                                          */

ActorEditViewCtl::~ActorEditViewCtl(void)
{
}

/*------------------------------------------------------------------------*/
/*    Actor Desc Access                                                   */

const ActorDesc &
ActorEditViewCtl::getActorDesc(void) const
{
    return _actorDesc;
}

ActorDesc &
ActorEditViewCtl::getActorDesc(void)
{
    return _actorDesc;
}

/*------------------------------------------------------------------------*/
/*    Load / Save / Write                                                 */

void
ActorEditViewCtl::loadActorDesc(const std::string &inFileName)
{
    std::ifstream inStream(inFileName.c_str());

    if(!inStream)
    {
        QMessageBox::critical(this, "Error opening description file",
                              "An error occured while opening the file.",
                              QMessageBox::Ok, QMessageBox::NoButton,
                              QMessageBox::NoButton                        );

        return;
    }

    ActorDescReader::the().readDesc(inStream, &_actorDesc);

    _actorDesc.dump();

    updateActorView   ();
    updateSEList      ();
    updateActiveSEView();
}

void
ActorEditViewCtl::saveActorDesc(const std::string &outFileName)
{
    std::ofstream outStream(outFileName.c_str());

    if(!outStream)
    {
        QMessageBox::critical(this, "Error opening description file",
                              "An error occured while opening the file.",
                              QMessageBox::Ok, QMessageBox::NoButton,
                              QMessageBox::NoButton                        );

        return;
    }

    ActorDescWriter::the().writeDesc(outStream, &_actorDesc);
}

void
ActorEditViewCtl::writeActorBaseCode(const std::string &outDecFileName,
                                     const std::string &outImpFileName,
                                     const std::string &outInlFileName )
{
    std::ofstream outStreamDec(outDecFileName.c_str());
    std::ofstream outStreamImp(outImpFileName.c_str());
    std::ofstream outStreamInl(outInlFileName.c_str());

    if((!outStreamDec) || (!outStreamImp) || (!outStreamInl))
    {
        QMessageBox::critical(this, "Error opening base code files",
                              "An error occured while opening the code files",
                              QMessageBox::Ok, QMessageBox::NoButton,
                              QMessageBox::NoButton                          );

        return;
    }

    ActorCodeWriter::the().writeBaseCodeDec(outStreamDec, &_actorDesc);
    ActorCodeWriter::the().writeBaseCodeImp(outStreamImp, &_actorDesc);
    ActorCodeWriter::the().writeBaseCodeInl(outStreamInl, &_actorDesc);

    //ActorCodeWriter::the().writeBaseCodeDec(std::cout, &_actorDesc);
    //ActorCodeWriter::the().writeBaseCodeImp(std::cout, &_actorDesc);
    //ActorCodeWriter::the().writeBaseCodeInl(std::cout, &_actorDesc);
}

void
ActorEditViewCtl::writeActorCode(const std::string &outDecFileName,
                                 const std::string &outImpFileName,
                                 const std::string &outInlFileName )
{
    std::ofstream outStreamDec(outDecFileName.c_str());
    std::ofstream outStreamImp(outImpFileName.c_str());
    std::ofstream outStreamInl(outInlFileName.c_str());

    if((!outStreamDec) || (!outStreamImp) || (!outStreamInl))
    {
        QMessageBox::critical(this, "Error opening code files",
                              "An error occured while opening the code files",
                              QMessageBox::Ok, QMessageBox::NoButton,
                              QMessageBox::NoButton                          );

        return;
    }

    ActorCodeWriter::the().writeCodeDec(outStreamDec, &_actorDesc);
    ActorCodeWriter::the().writeCodeImp(outStreamImp, &_actorDesc);
    ActorCodeWriter::the().writeCodeInl(outStreamInl, &_actorDesc);
}

/*------------------------------------------------------------------------*/
/*    Protected Slots                                                     */

void
ActorEditViewCtl::aboutButtonClicked(void)
{
    QMessageBox::about(this, "About", "OpenSG Actor Description File Editor");
}

void
ActorEditViewCtl::actorNameChanged(const QString &actorName)
{
    _actorDesc.setActorName(actorName.ascii());
}

void
ActorEditViewCtl::enterFunctorStoreChanged(const QString &enterFunctorStore)
{
    _actorDesc.setEnterFunctorStore(enterFunctorStore.ascii());
}

void
ActorEditViewCtl::exitButtonClicked(void)
{
    ::exit(0);
}

void
ActorEditViewCtl::leaveFunctorStoreChanged(const QString &leaveFunctorStore)
{
    _actorDesc.setLeaveFunctorStore(leaveFunctorStore.ascii());
}

void
ActorEditViewCtl::libraryNameChanged(const QString &libraryName)
{
    _actorDesc.setLibraryName(libraryName.ascii());
}

void
ActorEditViewCtl::loadButtonClicked(void)
{
    QString fileName = QFileDialog::getOpenFileName(
                           QString::null, "Actor Description (*.acd)", this);

    if(fileName.isEmpty() == false)
    {
        loadActorDesc(fileName.ascii());
    }
}

void
ActorEditViewCtl::newButtonClicked(void)
{
    _actorDesc.clear();
    _iActiveSEIndex = -1;

    updateActorView   ();
    updateSEList      ();
    updateActiveSEView();
}

void
ActorEditViewCtl::seHighlightChanged(int index)
{
    if((0 <= index) && (index < _actorDesc.getStateElemList().size()))
    {
        _iActiveSEIndex = index;
    }
    else
    {
        _iActiveSEIndex = -1;
    }

    updateActiveSEView();
}

void
ActorEditViewCtl::parentNameChanged(const QString &parentName)
{
    _actorDesc.setParentName(parentName.ascii());
}

void
ActorEditViewCtl::parentSystemComponentChanged(bool parentSystemComponent)
{
    _actorDesc.setParentSystemComponent(parentSystemComponent);
}

void
ActorEditViewCtl::saveAsButtonClicked(void)
{
    QString fileName = QFileDialog::getSaveFileName(
                           QString::null, "Actor Description (*.acd)", this);

    if(fileName.isEmpty() == false)
    {
        saveActorDesc(fileName.ascii());
    }
}

void
ActorEditViewCtl::saveButtonClicked(void)
{
    std::string fileName = ActorDescWriter::the().getDescFileName(&_actorDesc);

    if(fileName.empty() == false)
    {
        saveActorDesc(fileName);
    }
}

void
ActorEditViewCtl::seAccessChanged(const QString &access)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        activeSE.setAccess(access.ascii());
    }

    updateActiveSEEntry();
}

void
ActorEditViewCtl::seDefaultValueChanged(const QString &defaultValue)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        activeSE.setDefaultValue(defaultValue.ascii());
    }
}

void
ActorEditViewCtl::seDeleteButtonClicked(void)
{
    Int32 numSE = _actorDesc.getStateElemList().size();

    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        _actorDesc.getStateElemList().erase(
            _actorDesc.getStateElemList().begin() + _iActiveSEIndex);

        if(numSE > 1)
        {
            _iActiveSEIndex = 0;
        }
        else
        {
            _iActiveSEIndex = -1;
        }

        updateSEList      ();
        updateActiveSEView();
    }
}

void
ActorEditViewCtl::seDownButtonClicked(void)
{
}

void
ActorEditViewCtl::seHeaderChanged(const QString &header)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        activeSE.setHeader(header.ascii());
    }
}

void
ActorEditViewCtl::seHierarchicalChanged(bool hierarchical)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        activeSE.setHierarchical(hierarchical);
    }
}

void
ActorEditViewCtl::seNameChanged(const QString &name)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        activeSE.setName(name.ascii());
    }

    updateActiveSEEntry();
}

void
ActorEditViewCtl::seNewButtonClicked(void)
{
    _actorDesc.getStateElemList().push_back(ActorStateElemDesc());
    _iActiveSEIndex = _actorDesc.getStateElemList().size() - 1;

    updateSEList      ();
    updateActiveSEView();
}


void
ActorEditViewCtl::seTypeChanged(const QString &type)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        activeSE.setType(type.ascii());
    }

    updateActiveSEEntry();
}

void
ActorEditViewCtl::seUpButtonClicked(void)
{
}

void
ActorEditViewCtl::useLocalIncludesChanged(bool useLocalIncludes)
{
    _actorDesc.setUseLocalIncludes(useLocalIncludes);
}

void
ActorEditViewCtl::systemComponentChanged(bool systemComponent)
{
    _actorDesc.setSystemComponent(systemComponent);
}

void
ActorEditViewCtl::writeActorBaseCodeButtonClicked(void)
{
    std::string decFileName;
    std::string impFileName;
    std::string inlFileName;
    QString     dirName;

    if(_actorDesc.getActorName().empty() == true)
    {
        QMessageBox::warning(this, "No name given",
                             "Actor has no name. Enter a name, then try again");
        return;
    }

    dirName = QFileDialog::getExistingDirectory(
                  QString::null, this, "WriteBaseCodeDialog",
                  "Choose directory for base files"           );

    if(dirName.isEmpty() == true)
        return;
        
    dirName += "/";
    
    decFileName.clear (                                                      );
    decFileName.append(dirName.ascii()                                       );
    decFileName.append(ActorCodeWriter::the().getFilePrefix     (&_actorDesc));
    decFileName.append(ActorCodeWriter::the().getBaseDecFileName(&_actorDesc));

    impFileName.clear (                                                      );
    impFileName.append(dirName.ascii()                                       );
    impFileName.append(ActorCodeWriter::the().getFilePrefix     (&_actorDesc));
    impFileName.append(ActorCodeWriter::the().getBaseImpFileName(&_actorDesc));

    inlFileName.clear (                                                  );
    inlFileName.append(dirName.ascii()                                   );
    inlFileName.append(ActorCodeWriter::the().getFilePrefix     (&_actorDesc));
    inlFileName.append(ActorCodeWriter::the().getBaseInlFileName(&_actorDesc));

    writeActorBaseCode(decFileName, impFileName, inlFileName);
}

void
ActorEditViewCtl::writeActorCodeButtonClicked(void)
{
    std::string decFileName;
    std::string impFileName;
    std::string inlFileName;
    QString     dirName;

    if(_actorDesc.getActorName().empty() == true)
    {
        QMessageBox::warning(this, "No name given",
                             "Actor has no name. Enter a name, then try again");
        return;
    }

    dirName = QFileDialog::getExistingDirectory(
                  QString::null, this, "WriteCodeDialog",
                  "Choose directory for files"           );

    if(dirName.isEmpty() == true)
        return;
        
    dirName += "/";
    
    decFileName.clear (                                                  );
    decFileName.append(dirName.ascii()                                   );
    decFileName.append(ActorCodeWriter::the().getFilePrefix (&_actorDesc));
    decFileName.append(ActorCodeWriter::the().getDecFileName(&_actorDesc));

    impFileName.clear (                                                  );
    impFileName.append(dirName.ascii()                                   );
    impFileName.append(ActorCodeWriter::the().getFilePrefix (&_actorDesc));
    impFileName.append(ActorCodeWriter::the().getImpFileName(&_actorDesc));

    inlFileName.clear (                                                  );
    inlFileName.append(dirName.ascii()                                   );
    inlFileName.append(ActorCodeWriter::the().getFilePrefix (&_actorDesc));
    inlFileName.append(ActorCodeWriter::the().getInlFileName(&_actorDesc));

    writeActorCode(decFileName, impFileName, inlFileName);
}

std::string
ActorEditViewCtl::buildSEListEntry(ActorDesc::StateElemListIt itSE)
{
    std::string retValue("");

    retValue.append(itSE->getAccessStr().empty() ? "" : itSE->getAccessStr());
    retValue.append(": "                                                    );
    retValue.append(itSE->getType().empty()      ? "" : itSE->getType()     );
    retValue.append(" "                                                     );
    retValue.append(itSE->getName().empty()      ? "" : itSE->getName()     );

    return retValue;
}

void
ActorEditViewCtl::updateActorView(void)
{
    NameLineEdit                 ->setText       (
        _actorDesc.getActorName().c_str()        );
    ParentLineEdit               ->setText       (
        _actorDesc.getParentName().c_str()       );
    EnterFunctorStoreCombo       ->setCurrentItem(
        _actorDesc.getEnterFunctorStore()        );
    LeaveFunctorStoreCombo       ->setCurrentItem(
        _actorDesc.getLeaveFunctorStore()        );
    UseLocalIncludesCheckBox     ->setChecked    (
        _actorDesc.getUseLocalIncludes()         );
    SystemComponentCheckBox      ->setChecked    (
        _actorDesc.getSystemComponent()          );
    ParentSystemComponentCheckBox->setChecked    (
        _actorDesc.getParentSystemComponent()    );
    LibraryLineEdit              ->setText       (
        _actorDesc.getLibraryName().c_str()      );

    if(_actorDesc.getStateElemList().empty() == false)
    {
        SEFrame           ->setEnabled(true);
        SEDeletePushButton->setEnabled(true);
    }
    else
    {
        SEFrame           ->setEnabled(false);
        SEDeletePushButton->setEnabled(false);
    }
}

void
ActorEditViewCtl::updateSEList(void)
{
    ActorDesc::StateElemListIt itSE  = _actorDesc.beginStateElems();
    ActorDesc::StateElemListIt endSE = _actorDesc.endStateElems  ();

    StateElemListBox->clear();

    if(_actorDesc.getStateElemList().empty() == false)
    {
        SEFrame           ->setEnabled(true);
        SEDeletePushButton->setEnabled(true);
    }
    else
    {
        SEFrame           ->setEnabled(false);
        SEDeletePushButton->setEnabled(false);
    }

    StateElemListBox->blockSignals(true);

    for(; itSE != endSE; ++itSE)
    {
        StateElemListBox->insertItem(buildSEListEntry(itSE).c_str());
    }

    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        StateElemListBox->setSelected(_iActiveSEIndex, true);
    }

    StateElemListBox->blockSignals(false);
}

void
ActorEditViewCtl::updateActiveSEEntry(void)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        StateElemListBox->blockSignals(true );
        StateElemListBox->changeItem(
            buildSEListEntry(_actorDesc.beginStateElems() 
                             + _iActiveSEIndex           ).c_str(),
                             _iActiveSEIndex                       );
        StateElemListBox->blockSignals(false);
    }
}

void
ActorEditViewCtl::updateActiveSEView(void)
{
    if((0               <= _iActiveSEIndex                     ) &&
       (_iActiveSEIndex <  _actorDesc.getStateElemList().size())   )
    {
        ActorStateElemDesc &activeSE =
            _actorDesc.getStateElemList()[_iActiveSEIndex];

        SENameLineEdit        ->blockSignals  (true                        );
        SENameLineEdit        ->setText       (activeSE.getName().c_str()  );
        SENameLineEdit        ->blockSignals  (false                       );

        SETypeLineEdit        ->blockSignals  (true                        );
        SETypeLineEdit        ->setText       (activeSE.getType().c_str()  );
        SETypeLineEdit        ->blockSignals  (false                       );

        SEAccessCombo         ->blockSignals  (true                        );
        SEAccessCombo         ->setCurrentItem(activeSE.getAccess()        );
        SEAccessCombo         ->blockSignals  (false                       );

        SEHierarchicalCheckBox->blockSignals  (true                        );
        SEHierarchicalCheckBox->setChecked    (activeSE.getHierarchical()  );
        SEHierarchicalCheckBox->blockSignals  (false                       );

        SEHeaderLineEdit      ->blockSignals  (true                        );
        SEHeaderLineEdit      ->setText       (activeSE.getHeader().c_str());
        SEHeaderLineEdit      ->blockSignals  (false                       );

        SEDefaultValueLineEdit->blockSignals  (true                        );
        SEDefaultValueLineEdit->setText       (
                                    activeSE.getDefaultValue().c_str()     );
        SEDefaultValueLineEdit->blockSignals  (false                       );

        StateElemListBox->blockSignals(true );
        StateElemListBox->changeItem(
            buildSEListEntry(_actorDesc.beginStateElems()
                             + _iActiveSEIndex           ).c_str(),
                             _iActiveSEIndex                       );
        StateElemListBox->blockSignals(false);

        if(_iActiveSEIndex == 0)
        {
            SEUpPushButton->setEnabled(false);
        }
        else
        {
            SEUpPushButton->setEnabled(true);
        }

        if(_iActiveSEIndex + 1 == _actorDesc.getStateElemList().size())
        {
            SEDownPushButton->setEnabled(false);
        }
        else
        {
            SEDownPushButton->setEnabled(true);
        }
    }
    else
    {
        SENameLineEdit        ->blockSignals  (true );
        SENameLineEdit        ->setText       (""   );
        SENameLineEdit        ->blockSignals  (false);

        SETypeLineEdit        ->blockSignals  (true );
        SETypeLineEdit        ->setText       (""   );
        SETypeLineEdit        ->blockSignals  (false);

        SEAccessCombo         ->blockSignals  (true );
        SEAccessCombo         ->setCurrentItem(0    );
        SEAccessCombo         ->blockSignals  (false);

        SEHierarchicalCheckBox->blockSignals  (true );
        SEHierarchicalCheckBox->setChecked    (false);
        SEHierarchicalCheckBox->blockSignals  (false);

        SEHeaderLineEdit      ->blockSignals  (true );
        SEHeaderLineEdit      ->setText       (""   );
        SEHeaderLineEdit      ->blockSignals  (false);

        SEDefaultValueLineEdit->blockSignals  (true );
        SEDefaultValueLineEdit->setText       (""   );
        SEDefaultValueLineEdit->blockSignals  (false);
    }
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGActorEditViewCtl_qt.cpp,v 1.2 2005/05/24 23:11:01 dirk Exp $";
    static Char8 cvsid_hpp     [] = OSGACTOREDITVIEWCTLQT_HEADER_CVSID;
//    static Char8 cvsid_inl     [] = OSGACTOREDITVIEWCTLQT_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
