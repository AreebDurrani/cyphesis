// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#include <Atlas/Message/Object.h>
#include <Atlas/Objects/Root.h>
#include <Atlas/Objects/Operation/Login.h>
#include <Atlas/Objects/Operation/Create.h>

#include "Player.h"

using Atlas::Message::Object;

Player::Player(Connection* conn, const string& username, const string& passwd) :
               Account(conn, username, passwd)
{
    type = "player";
}

Player::~Player() { }

oplist Player::characterError(const Create& op,const Object::MapType& ent) const
{
    Object::MapType::const_iterator I = ent.find("name");
    if ((I == ent.end()) || !I->second.IsString()) {
        return error(op, "Object to be created has no name");
    }

    if (!I->second.AsString().compare("admin", 0, 5)) {
        return error(op, "Object to be created cannot start with admin");
    }

    const string& type= ent.find("parents")->second.AsList().front().AsString();
    
    if ((type!="character") && (type!="farmer") && (type!="smith")) {
        return error(op, "Object of that type cannot be created by this account");
    }
    return oplist();
}
