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

#ifndef _OSGQATTACHMENTMAPEDITOR_QT_H_
#define _OSGQATTACHMENTMAPEDITOR_QT_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGWindowQTDef.h>
#include <OSGQAbstractValueEditor_qt.h>
#include <OSGAttachment.h>

#include <vector>

class QLabel;
class QGridLayout;

OSG_BEGIN_NAMESPACE
    
class QFieldContainerPtrEditor;

class OSG_WINDOWQTLIB_DLLMAPPING QAttachmentMapEditor 
    : public QAbstractValueEditor
{
    Q_OBJECT
        
  public:
    static QAbstractValueEditor *create(QWidget *pParent, const char *name);

             QAttachmentMapEditor(QWidget *pParent, const char *name);
    virtual ~QAttachmentMapEditor(void                              );
        
    inline void getValue(      AttachmentMap &attMap) const;
    inline void setValue(const AttachmentMap &attMap);

    inline const QFieldContainerPtrEditor *getEditor(UInt32 index) const;
    inline       QFieldContainerPtrEditor *getEditor(UInt32 index); 

  public slots:
    virtual void setLabelsVisible(bool bLabels  );
    virtual void setReadOnly     (bool bReadOnly);

    virtual void readField      (FieldContainerPtr pFC,          
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex,
                                 UInt32            uiAspect     );
    virtual void readField      (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );

    virtual void writeField     (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );

    virtual void addFieldElem   (FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );
    virtual void removeFieldElem(FieldContainerPtr pFC,
                                 UInt32            uiFieldId,
                                 UInt32            uiValueIndex );
    
 protected slots:
    virtual void slotValueChanged  (QAbstractValueEditor *pSender                 );
    virtual void slotGenericRequest(QAbstractValueEditor *pSender, QString request);

  private:
    typedef QAbstractValueEditor Inherited;
      
    /*!\brief prohibit default function (move to 'public' if needed) */
    QAttachmentMapEditor (const QAttachmentMapEditor &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator= (const QAttachmentMapEditor &source);
  
    void createChildWidgets(void);
    void layoutChildWidgets(void);
    void initSelf          (void);
      
    void updateDisplay     (const AttachmentMap &attMap);
    void updateData        (      AttachmentMap &attMap) const;
    
    std::vector<QLabel                   *>  _indexLabels;
    std::vector<QLabel                   *>  _groupLabels;
    std::vector<QFieldContainerPtrEditor *>  _attachmentEditors;
    
    QGridLayout                             *_pGrid;
};

OSG_END_NAMESPACE

#include "OSGQAttachmentMapEditor_qt.inl"

#define OSGQATTACHMENTMAPEDITORQT_HEADER_CVSID "@(#)$Id: OSGQAttachmentMapEditor_qt.h,v 1.1 2004/12/20 11:09:52 neumannc Exp $"

#endif /* _OSGQATTACHMENTMAPEDITOR_QT_H_ */
