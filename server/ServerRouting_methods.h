// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#ifndef SERVER_ROUTING_METHODS_H
#define SERVER_ROUTING_METHODS_H

#include "ServerRouting.h"
#include "WorldRouter.h"

inline int ServerRouting::idle() {
    return world.idle();
}

inline BaseEntity * ServerRouting::addObject(BaseEntity * obj) {
    obj = Routing::addObject(obj);
    idDict[obj->fullid] = obj;
    return obj;
}


#endif // SERVER_ROUTING_METHODS_H
