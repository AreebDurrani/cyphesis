// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#include <Atlas/Message/Object.h>
#include <Atlas/Objects/Root.h>
#include <Atlas/Objects/Operation/Login.h>
#include <Atlas/Objects/Operation/Create.h>
#include <Atlas/Objects/Operation/Move.h>
#include <Atlas/Objects/Operation/Set.h>
#include <Atlas/Objects/Operation/Sight.h>
#include <Atlas/Objects/Operation/Sound.h>
#include <Atlas/Objects/Operation/Touch.h>
#include <Atlas/Objects/Operation/Look.h>
#include <Atlas/Objects/Operation/Error.h>

#include "BaseEntity.h"

#include <common/debug.h>
#include <common/op_switch.h>

static const bool debug_flag = false;

using Atlas::Message::Object;

BaseEntity::BaseEntity() : seq(0), inGame(false)
{
}

BaseEntity::~BaseEntity()
{
}

void BaseEntity::destroy()
{
}

Object BaseEntity::asObject() const
{
    debug( cout << "BaseEntity::asObject" << endl << flush;);
    Object::MapType map;
    map["objtype"] = "object";
    Object obj(map);
    addToObject(obj);
    return(obj);
}


void BaseEntity::addToObject(Object & obj) const
{
    debug( cout << "BaseEntity::addToObject" << endl << flush;);
    Object::MapType & omap = obj.AsMap();
    if (fullid.size() != 0) {
        omap["id"] = fullid;
    }
    omap["seq"] = seq;
#if 0
    Object::ListType contlist;
    list_t::const_iterator I;
    for(I = contains.begin(); I != contains.end(); I++) {
        contlist.push_back(Object((*I)->fullid));
    }
    if (contlist.size() != 0) {
        omap["contains"] = Object(contlist);
    }
#endif
}

oplist BaseEntity::externalMessage(const RootOperation & op)
{
    return message(op);
}

oplist BaseEntity::message(const RootOperation & op)
{
    debug( cout << "BaseEntity::message" << endl << flush;);
    return operation(op);
}

oplist BaseEntity::Operation(const Look & op)
{
    debug( cout << "look op got all the way to here" << endl << flush;);
    Sight * s = new Sight( Sight::Instantiate());
    Object::ListType args(1,asObject());
    s->SetArgs(args);
    s->SetTo(op.GetFrom());

    // Set refno?
    return oplist(1,s);
}

oplist BaseEntity::operation(const RootOperation & op)
{
    debug( cout << "BaseEntity::operation" << endl << flush;);
    return callOperation(op);
}

oplist BaseEntity::externalOperation(const RootOperation & op)
{
    return operation(op);
}

oplist BaseEntity::Operation(const Login & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Logout & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Chop & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Combine & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Create & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Cut & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Delete & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Divide & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Eat & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Fire & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Get & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Info & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Move & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Nourish & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Set & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Sight & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Sound & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Talk & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Touch & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Tick & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Load & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Save & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Setup & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Appearance & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const Disappearance & op) { oplist res; return(res); }
oplist BaseEntity::Operation(const RootOperation & op) { oplist res; return(res); }

void BaseEntity::setRefno(const oplist& ret, const RootOperation & ref_op) const
{
    for(oplist::const_iterator I = ret.begin(); I != ret.end(); I++) {
        setRefnoOp(*I, ref_op);
    }
}

op_no_t BaseEntity::opEnumerate(const RootOperation & op) const
{
    const Atlas::Message::Object::ListType & parents = op.GetParents();
    if (parents.size() != 1) {
        cerr << "This is a weird operation." << endl << flush;
    }
    if (!parents.begin()->IsString()) {
        cerr << "This op has invalid parent.\n" << endl << flush;
    }
    const string & parent = parents.begin()->AsString();
    if ("login" == parent)  { return(OP_LOGIN); }
    if ("chop" == parent)  { return(OP_CHOP); }
    if ("combine" == parent)  { return(OP_COMBINE); }
    if ("create" == parent)  { return(OP_CREATE); }
    if ("cut" == parent)  { return(OP_CUT); }
    if ("delete" == parent)  { return(OP_DELETE); }
    if ("divide" == parent)  { return(OP_DIVIDE); }
    if ("eat" == parent)  { return(OP_EAT); }
    if ("fire" == parent)  { return(OP_FIRE); }
    if ("get" == parent)  { return(OP_GET); }
    if ("info" == parent)  { return(OP_INFO); }
    if ("move" == parent)  { return(OP_MOVE); }
    if ("nourish" == parent)  { return(OP_NOURISH); }
    if ("set" == parent)  { return(OP_SET); }
    if ("sight" == parent)  { return(OP_SIGHT); }
    if ("sound" == parent)  { return(OP_SOUND); }
    if ("talk" == parent)  { return(OP_TALK); }
    if ("touch" == parent)  { return(OP_TOUCH); }
    if ("tick" == parent)  { return(OP_TICK); }
    if ("look" == parent)  { return(OP_LOOK); }
    if ("load" == parent)  { return(OP_LOAD); }
    if ("save" == parent)  { return(OP_SAVE); }
    if ("setup" == parent)  { return(OP_SETUP); }
    if ("appearance" == parent)  { return(OP_APPEARANCE); }
    if ("disappearance" == parent)  { return(OP_DISAPPEARANCE); }
    if ("error" == parent)  { return(OP_ERROR); }
    return (OP_INVALID);
}

oplist BaseEntity::callOperation(const RootOperation & op)
{
    const op_no_t op_no = opEnumerate(op);
    OP_SWITCH(op, op_no,)
}

oplist BaseEntity::error(const RootOperation& op, const char* errstring) const
{
    Error * e = new Error(Error::Instantiate());

    cerr << "ERROR generated by " << fullid << " with message:" << endl;
    cerr << " [" << errstring << "]" << endl << flush;
    Atlas::Message::Object::ListType args;
    Atlas::Message::Object::MapType errmsg;
    errmsg["message"] = Object(errstring);
    args.push_back(Object(errmsg));
    args.push_back(op.AsObject());

    e->SetArgs(args);
    e->SetRefno(op.GetSerialno());

    return oplist(1,e);
}

