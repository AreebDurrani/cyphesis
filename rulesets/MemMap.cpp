#include <Atlas/Message/Object.h>
#include <Atlas/Objects/Operation/Login.h>
#include <Atlas/Objects/Operation/Look.h>

using Atlas::Objects::Operation::Look;

#include "Thing.h"
#include "MemMap.h"
#include <modules/Location.h>

static int debug_map = 0;

void MemMap::script_hook(const string & method, Thing * object)
{
    if (script_object != NULL) {
        ThingObject * obj = newThingObject(NULL);
        obj->m_thing = object;
        PyObject_CallMethod(script_object, (char *)(method.c_str()), "(O)",obj);
        Py_DECREF(obj);
    }
}

list<Thing *> MemMap::find_by_type(const string & what)
{
    list<Thing *> res;
    fdict_t::const_iterator I;
    for(I = things.begin(); I != things.end(); I++) {
        Thing * item = (Thing *)I->second;
        debug_map && cout << "F" << what << ":" << item->type << ":" << item->fullid << endl << flush;
        if (item->type == what) {
            res.push_back((Thing*)I->second);
        }
    }
    return res;
}

list<Thing *> MemMap::find_by_location(const Location & loc, double radius)
{
    list<Thing *> res;
    fdict_t::const_iterator I;
    for(I = things.begin(); I != things.end(); I++) {
        const Location & oloc = I->second->location;
        if (!loc || !oloc) {
            continue;
        }
        if ((oloc.parent->fullid == loc.parent->fullid) &&
            (loc.coords.distance(oloc.coords) < radius)) {
            res.push_back((Thing*)I->second);
        }
    }
    return res;
}
