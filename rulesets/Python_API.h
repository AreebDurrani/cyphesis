#ifndef PYTHON_API_H
#define PYTHON_API_H

#include <Atlas/Message/Object.h>
#include <Atlas/Objects/Operation/RootOperation.h>
#include <Atlas/Objects/Operation/Login.h>
#include <Atlas/Objects/Operation/Create.h>
#include <Atlas/Objects/Operation/Look.h>
#include <Atlas/Objects/Operation/Talk.h>
#include <Atlas/Objects/Operation/Move.h>
#include <Atlas/Objects/Operation/Set.h>

using Atlas::Message::Object;
using Atlas::Objects::Operation::RootOperation;
//using Atlas::Objects::Operation::Login;
//using Atlas::Objects::Operation::Create;
//using Atlas::Objects::Operation::Move;
//using Atlas::Objects::Operation::Set;

class Thing;
class MemMap;
class Location;
class WorldTime;
class WorldRouter;

typedef std::list<RootOperation *> oplist;

#include <physics/Vector3D.h>

typedef struct {
    PyObject_HEAD
    PyObject	* Object_attr;	/* Attributes dictionary */
    Object	* m_obj;
} AtlasObject;

typedef struct {
    PyObject_HEAD
    PyObject	* Thing_attr;	/* Attributes dictionary */
    Thing	* m_thing;
} ThingObject;

typedef struct {
    PyObject_HEAD
    PyObject	* Map_attr;	/* Attributes dictionary */
    MemMap	* m_map;
} MapObject;

typedef struct {
    PyObject_HEAD
    PyObject	* Location_attr;	/* Attributes dictionary */
    Location	* location;
} LocationObject;

typedef struct {
    PyObject_HEAD
    PyObject	* Vector3D_attr;	/* Attributes dictionary */
    Vector3D	coords;
} Vector3DObject;

typedef struct {
    PyObject_HEAD
    PyObject	* WorldTime_attr;	/* Attributes dictionary */
    WorldTime	* time;
} WorldTimeObject;

typedef struct {
    PyObject_HEAD
    PyObject	* World_attr;	/* Attributes dictionary */
    WorldRouter	* world;
} WorldObject;

#define ATLAS_OPERATION(_name) typedef struct { \
    PyObject_HEAD \
    PyObject	* Operation_attr; \
    _name	* operation; \
    Thing	* from; \
    Thing	* to; \
} _name ## Object;

typedef struct {
    PyObject_HEAD
    PyObject	* Oplist_attr;	/* Attributes dictionary */
    oplist	* ops;
} OplistObject;

typedef struct {
    PyObject_HEAD
} FunctionObject;

typedef struct {
    PyObject_HEAD
    PyObject	* Optime_attr;	/* Attributes dictionary */
    RootOperation	* operation;
} OptimeObject;

#define ATLAS_OPERATION_METHODS(_name) \
PyMethodDef _name ## _methods[] = { \
    {"SetSerialno",	(PyCFunction)Operation_SetSerialno,	METH_VARARGS}, \
    {"SetRefno",	(PyCFunction)Operation_SetRefno,	METH_VARARGS}, \
    {"SetFrom",		(PyCFunction)Operation_SetFrom,		METH_VARARGS}, \
    {"SetTo",		(PyCFunction)Operation_SetTo,		METH_VARARGS}, \
    {"SetSeconds",	(PyCFunction)Operation_SetSeconds,	METH_VARARGS}, \
    {"SetFutureSeconds",(PyCFunction)Operation_SetFutureSeconds,METH_VARARGS}, \
    {"SetTimeString",	(PyCFunction)Operation_SetTimeString,	METH_VARARGS}, \
    {"SetArgs",		(PyCFunction)Operation_SetArgs,		METH_VARARGS}, \
    {"GetSerialno",	(PyCFunction)Operation_GetSerialno,	METH_VARARGS}, \
    {"GetRefno",	(PyCFunction)Operation_GetRefno,	METH_VARARGS}, \
    {"GetFrom",		(PyCFunction)Operation_GetFrom,		METH_VARARGS}, \
    {"GetTo",		(PyCFunction)Operation_GetTo,		METH_VARARGS}, \
    {"GetSeconds",	(PyCFunction)Operation_GetSeconds,	METH_VARARGS}, \
    {"GetFutureSeconds",(PyCFunction)Operation_GetFutureSeconds,METH_VARARGS}, \
    {"GetTimeString",	(PyCFunction)Operation_GetTimeString,	METH_VARARGS}, \
    {"GetArgs",		(PyCFunction)Operation_GetArgs,		METH_VARARGS}, \
    {"get_name",	(PyCFunction)Operation_get_name,	METH_VARARGS}, \
{NULL,		NULL} \
};

#define ATLAS_OPERATION_TYPE(_name) \
PyTypeObject _name ## _Type = { \
	PyObject_HEAD_INIT(&PyType_Type) \
	0,					/*ob_size*/ \
	"Operation",				/*tp_name*/ \
	sizeof(RootOperationObject),		/*tp_basicsize*/ \
	0,					/*tp_itemsize*/ \
	/* methods */ \
	(destructor)Operation_dealloc,		/*tp_dealloc*/ \
	0,					/*tp_print*/ \
	(getattrfunc)Operation_getattr,		/*tp_getattr*/ \
	(setattrfunc)Operation_setattr,		/*tp_setattr*/ \
	0,					/*tp_compare*/ \
	0,					/*tp_repr*/ \
	&Operation_num,				/*tp_as_number*/ \
	&Operation_seq,				/*tp_as_sequence*/ \
	0,					/*tp_as_mapping*/ \
	0,					/*tp_hash*/ \
};
	
ATLAS_OPERATION(RootOperation)

#include "Py_Object.h"
#include "Py_Thing.h"
#include "Py_Map.h"
#include "Py_Location.h"
#include "Py_Vector3D.h"
#include "Py_WorldTime.h"
#include "Py_World.h"
#include "Py_Operation.h"
#include "Py_Oplist.h"
#include "Py_Optime.h"

void Create_PyThing(Thing * thing, const string & package, const string & type);

#endif /* PYTHON_API_H */
