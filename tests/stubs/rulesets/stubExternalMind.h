// AUTOGENERATED file, created by the tool generate_stub.py, don't edit!
// If you want to add your own functionality, instead edit the stubExternalMind_custom.h file.

#include "rulesets/ExternalMind.h"
#include "stubExternalMind_custom.h"

#ifndef STUB_RULESETS_EXTERNALMIND_H
#define STUB_RULESETS_EXTERNALMIND_H

#ifndef STUB_ExternalMind_deleteEntity
//#define STUB_ExternalMind_deleteEntity
  void ExternalMind::deleteEntity(const std::string & id, bool forceDelete)
  {
    
  }
#endif //STUB_ExternalMind_deleteEntity

#ifndef STUB_ExternalMind_purgeEntity
//#define STUB_ExternalMind_purgeEntity
  void ExternalMind::purgeEntity(const LocatedEntity & ent, bool forceDelete )
  {
    
  }
#endif //STUB_ExternalMind_purgeEntity

#ifndef STUB_ExternalMind_ExternalMind
//#define STUB_ExternalMind_ExternalMind
   ExternalMind::ExternalMind(LocatedEntity &)
    : Router(LocatedEntity)
  {
    
  }
#endif //STUB_ExternalMind_ExternalMind

#ifndef STUB_ExternalMind_ExternalMind_DTOR
//#define STUB_ExternalMind_ExternalMind_DTOR
   ExternalMind::~ExternalMind()
  {
    
  }
#endif //STUB_ExternalMind_ExternalMind_DTOR

#ifndef STUB_ExternalMind_externalOperation
//#define STUB_ExternalMind_externalOperation
  void ExternalMind::externalOperation(const Operation & op, Link &)
  {
    
  }
#endif //STUB_ExternalMind_externalOperation

#ifndef STUB_ExternalMind_operation
//#define STUB_ExternalMind_operation
  void ExternalMind::operation(const Operation &, OpVector &)
  {
    
  }
#endif //STUB_ExternalMind_operation

#ifndef STUB_ExternalMind_connectionId
//#define STUB_ExternalMind_connectionId
  const std::string& ExternalMind::connectionId()
  {
    return "";
  }
#endif //STUB_ExternalMind_connectionId

#ifndef STUB_ExternalMind_linkUp
//#define STUB_ExternalMind_linkUp
  void ExternalMind::linkUp(Link * c)
  {
    
  }
#endif //STUB_ExternalMind_linkUp


#endif