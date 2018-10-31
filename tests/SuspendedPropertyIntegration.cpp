// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2014 Erik Ogenvik
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
#ifdef NDEBUG
#undef NDEBUG
#endif
#ifndef DEBUG
#define DEBUG
#endif

#include "TestBase.h"
#include "TestWorld.h"

#include "rules/simulation/Entity.h"
#include "rules/SuspendedProperty.h"

#include "rules/BaseWorld.h"
#include "common/TypeNode.h"
#include "common/operations/Tick.h"
#include "common/custom.h"
#include "common/PropertyManager.h"

#include <Atlas/Objects/Operation.h>


#include <functional>

std::function<void(Operation)> worldMessageCallback;
std::function<void(bool)> worldSetSuspendedCallback;

using Atlas::Objects::Operation::Tick;


class TestEntity : public Entity {
public:
	std::function<void()> tickCallback;

	explicit TestEntity(const std::string & id, long intId) : Entity(id, intId)
	{

	}
    virtual void TickOperation(const Operation &, OpVector &)
    {
    	tickCallback();
    }

};

class TestPropertyManager : public PropertyManager
{
  public:
    virtual PropertyBase * addProperty(const std::string & name,
                                       int type);
};

PropertyBase * TestPropertyManager::addProperty(const std::string & name,
                                                int type)
{
    return new SuspendedProperty();
}

class SuspendedPropertyintegration : public Cyphesis::TestBase
{
  private:
	Ref<TestEntity> world_entity;

	TestWorld* world;


  public:
    SuspendedPropertyintegration();

    void setup();
    void teardown();

    void test_suspending_entity_should_prevent_ticks();
    void test_suspending_world_should_suspend_the_whole_baseworld();
};

SuspendedPropertyintegration::SuspendedPropertyintegration()
{
	new TestPropertyManager();

	ADD_TEST(SuspendedPropertyintegration::test_suspending_entity_should_prevent_ticks);
    ADD_TEST(SuspendedPropertyintegration::test_suspending_world_should_suspend_the_whole_baseworld);
}

void SuspendedPropertyintegration::setup()
{
    TestWorld::extension.messageFn = [](const Operation & op, LocatedEntity & ent){
        worldMessageCallback(op);
    };
	world_entity = new TestEntity("0", 0);
	world = new TestWorld(world_entity);
}

void SuspendedPropertyintegration::teardown()
{
	delete world;
	//skip deleting entity
}

void SuspendedPropertyintegration::test_suspending_entity_should_prevent_ticks()
{
	TestEntity * entity = new TestEntity("1", 1);

	bool tick_called = false;

	auto callback = [&]{
		tick_called = true;
	};
	entity->tickCallback = callback;

	Tick tick;
	OpVector res;

	//First make sure TickOperation is called when there's no "suspended" property.
	entity->operation(tick, res);
	ASSERT_TRUE(tick_called);

	tick_called = false;
	//Now make sure it's not called when the suspended property is set
	entity->setAttr("suspended", 1);
	entity->operation(tick, res);
	ASSERT_TRUE(!tick_called);

	//And then test resuming it
	//The previous op should now be resent
	bool got_message = false;
	worldMessageCallback = [&](Operation op){
		got_message = true;
	};
	entity->setAttr("suspended", 0);
	ASSERT_TRUE(got_message);
	entity->operation(tick, res);
	ASSERT_TRUE(tick_called);
}

void SuspendedPropertyintegration::test_suspending_world_should_suspend_the_whole_baseworld()
{
	bool is_suspended = false;
	worldSetSuspendedCallback = [&](bool suspended){
		is_suspended = suspended;
	};
	ASSERT_TRUE(!is_suspended);
	world_entity->setAttr("suspended", 1);
	ASSERT_TRUE(is_suspended);
	world_entity->setAttr("suspended", 0);
	ASSERT_TRUE(!is_suspended);
}

int main()
{

	Atlas::Objects::Operation::TICK_NO = 100000;
	SuspendedPropertyintegration t;

    return t.run();
}



// stubs

//#include "Property_stub_impl.h"
#include "stubs/rulesets/stubLocation.h"
#include "stubs/common/stubProperty.h"
#include "stubs/common/stubPropertyManager.h"
#include "stubs/common/stubRouter.h"
#include "stubs/rulesets/stubDomainProperty.h"
#include "stubs/rulesets/stubIdProperty.h"
#include "stubs/rulesets/stubContainsProperty.h"


long integerId(const std::string & id)
{
    long intId = strtol(id.c_str(), 0, 10);
    if (intId == 0 && id != "0") {
        intId = -1L;
    }

    return intId;
}

#ifndef STUB_BaseWorld_getEntity
#define STUB_BaseWorld_getEntity
Ref<LocatedEntity> BaseWorld::getEntity(const std::string & id) const
{
    return getEntity(integerId(id));
}

Ref<LocatedEntity> BaseWorld::getEntity(long id) const
{
    auto I = m_eobjects.find(id);
    if (I != m_eobjects.end()) {
        assert(I->second);
        return I->second;
    } else {
        return nullptr;
    }
}
#endif //STUB_BaseWorld_getEntity

#ifndef STUB_BaseWorld_setIsSuspended
#define STUB_BaseWorld_setIsSuspended
void BaseWorld::setIsSuspended(bool suspended)
{
    worldSetSuspendedCallback(suspended);
}
#endif //STUB_BaseWorld_setIsSuspended


#include "stubs/rulesets/stubBaseWorld.h"




void log(LogLevel lvl, const std::string & msg)
{
}
