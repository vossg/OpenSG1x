
#ifndef _OSGSTATEELEMINFO_H_
#define _OSGSTATEELEMINFO_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>

#include <string>

OSG_BEGIN_NAMESPACE

class StateElemInfo
{
    /*==========================  PUBLIC  =================================*/
  public:
    enum StateElemAccessE
    {
        PublicAccess    = 0,
        ProtectedAccess = 1
    };

    enum StateElemOrderE
    {
        Unordered = 0,
        Ordered   = 1
    };

    /*---------------------------------------------------------------------*/
    /*! \name                       Constructors                           */
    /*! \{                                                                 */

    StateElemInfo(const std::string      &name         = "", 
                  const std::string      &type         = "ActorBase",
                  const std::string      &typeHeader   = "",
                  const std::string      &defaultValue = "",
                        StateElemAccessE  access       = PublicAccess,
                        StateElemOrderE   order        = Unordered    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get & Set                             */
    /*! \{                                                                 */

    void               setName        (const std::string &name        );
    const std::string &getName        (void                           ) const;

    void               setType        (const std::string &type        );
    const std::string &getType        (void                           ) const;

    void               setTypeHeader  (const std::string &typeHeader  );
    const std::string &getTypeHeader  (void                           ) const;
                  
    void               setDefaultValue(const std::string &defaultValue);
    const std::string &getDefaultValue(void                           ) const;

    void               setAccess      (StateElemAccessE   access      );
    void               setAccess      (const std::string &access      );
    StateElemAccessE   getAccess      (void                           ) const;

    void               setOrder       (StateElemOrderE    order       );
    void               setOrder       (const std::string &order       );
    StateElemOrderE    getOrder       (void                           ) const;

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    bool mapAccessName(const std::string &access, StateElemAccessE &outVar);
    bool mapOrderName (const std::string &order,  StateElemOrderE  &outVar);

    std::string      _name;
    std::string      _type;
    std::string      _typeHeader;
    std::string      _defaultValue;
    StateElemAccessE _access;
    StateElemOrderE  _order;
};

OSG_END_NAMESPACE

#include "OSGStateElemInfo.inl"

#define OSGSTATEELEMINFO_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSTATEELEMINFO_H_ */
