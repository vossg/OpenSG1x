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

OSG_BEGIN_NAMESPACE



/*! increase indent by _step
 *
 */
inline void Indenter::operator++(int)
{
    _indent += _step;
}


/*! increase indent by _step
 *
 */
inline void Indenter::operator++()
{
    _indent += _step;
}


/*! decrease indent by _step
 *
 */
inline void Indenter::operator--(int)
{
    _indent -= _step;
}


/*! decrease indent by _step
 *
 */
inline void Indenter::operator--()
{
    _indent -= _step;
}


/*! get _indent
 *
 */
inline UInt32 Indenter::getIndent(void) const
{
    return _indent;
}


/*! get _step
 *
 */
inline UInt32 Indenter::getStep(void) const
{
    return _step;
}

/*! return a string of _indent many spaces
 *
 */

inline std::string Indenter::str(void) const
{
    std::string indStr;

    for(UInt32 i=0; i<_indent; i++)
    {
        indStr.append(" ");
    }
    return indStr;
}



/*! set _indent
 *
 */
inline void Indenter::setIndent(UInt32 indent)
{
    _indent = indent;
}


/*! set _step
 *
 */
inline void Indenter::setStep(UInt32 step)
{
    _step = step;
}


/*! write _indent spaces to stream
 *
 */
inline std::ostream& operator << (std::ostream& stream, const Indenter& indent)
{
    for(UInt32 i=0; i<indent.getIndent(); i++)
    {
        stream << ' ';
    }
    return stream;
}

OSG_END_NAMESPACE

#define OSGINDENTER_INLINE_CVSID "@(#)$Id: template.inl,v 1.2 2001/10/15 03:10:24 vossg Exp $"

