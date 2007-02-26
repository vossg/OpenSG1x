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

#ifndef _OSGQGLManagedDesignerWidget_H_
#define _OSGQGLManagedDesignerWidget_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_WITH_QT

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGWindowQT4Def.h"

#include "OSGQ4GLManagedWidget_qt.h"

// The OSGQGLManagedDesignerWidget is not in the OpenSG namespace by purpose, 
// because Qt's designer doesn't handle namespaces correctly.
OSG_USING_NAMESPACE

/*! \brief Managed QT Designer Widget. See 
    \ref PageOSGQGLManagedDesignerWidget "OSGQGLManagedDesignerWidget" for a 
	     description. 

	The OSGQGLManagedDesignerWidget is a wrapper class for osg::OSGQGLWidget 
	to make	it usable within Qt's designer. The wrapper is necessary because
	the moc (meta object compiler) does not fully support the usage of C++
	namespaces. 
	
	This wrapper simply tranfers the OSGQGLManagedWidget from the osg to the 
	the standard namespace.
*/

class OSG_WINDOWQTLIB_DLLMAPPING OSGQGLManagedDesignerWidget 
	: public osg::OSGQGLManagedWidget
{

  Q_OBJECT
  
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    OSGQGLManagedDesignerWidget(      QWidget            *parent  = 0, 
                                const char               *name    = 0,
                                      SimpleSceneManager *manager = NULL);

    /*! \}                                                                 */

  private:

    typedef osg::OSGQGLManagedWidget Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGQGLManagedDesignerWidget(const OSGQGLManagedDesignerWidget &source);
    OSGQGLManagedDesignerWidget & 
	                 operator =(const OSGQGLManagedDesignerWidget &source);
};

typedef OSGQGLManagedDesignerWidget *OSGQGLManagedDesignerWidgetP;

//OSG_END_NAMESPACE

#define OSGQGLMANAGEDDESIGNERWIDGET_HEADER_CVSID "@(#)$Id: OSGQ4GLManagedDesignerWidget_qt.h,v 1.2 2007/02/26 13:37:38 yjung Exp $"

#endif /* OSG_WITH_QT */

#endif /* _OSGQGLManagedDesignerWidget_H_ */
