// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#ifndef ROUTING_H
#define ROUTING_H

#include "OOG_Thing.h"

class Routing : public OOGThing {
  protected:
    dict_t objects;
  public:

    Routing() { }
    virtual ~Routing();

    BaseEntity * addObject(BaseEntity * obj) {
        objects[obj->fullid]=obj;
        return obj;
    }

    void delObject(BaseEntity * obj) {
        objects.erase(obj->fullid);
        delete obj;
    }

    BaseEntity * getObject(const string & fid) const {
        return Routing::objects[fid];
    }

    BaseEntity * findObject(const string & fid) const {
        return Routing::objects[fid];
    }
};

#endif // ROUTING_H
