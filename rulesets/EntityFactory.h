// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2000,2001 Alistair Riddoch

#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H

#include <string>
#include <map>

class Thing;
class ThingFactory;
class WorldRouter;

typedef std::map<std::string, ThingFactory *> fdict_t;

class EntityFactory {
    EntityFactory();
    static EntityFactory * m_instance;

    fdict_t factories;
  public:
    static EntityFactory * instance() {
        if (m_instance == NULL) {
            m_instance = new EntityFactory();
        }
        return m_instance;
    }
    void readRuleset(const string & file);
    Thing * newThing(const string &, const Atlas::Message::Object &, WorldRouter *);
};

#endif // ENTITY_FACTORY_H
