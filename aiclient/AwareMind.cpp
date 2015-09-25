/*
 Copyright (C) 2015 erik

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "AwareMind.h"
#include "AwarenessStore.h"
#include "AwarenessStoreProvider.h"
#include "SharedTerrain.h"

#include "navigation/Awareness.h"
#include "navigation/Steering.h"

#include "common/log.h"
#include "common/SystemTime.h"
#include "common/Tick.h"

#include <Atlas/Objects/RootEntity.h>
#include <Atlas/Objects/Operation.h>
#include <Atlas/Objects/Entity.h>

#include <wfmath/atlasconv.h>

AwareMind::AwareMind(const std::string &id, long intId, SharedTerrain& sharedTerrain, AwarenessStoreProvider& awarenessStoreProvider) :
        BaseMind(id, intId), mSharedTerrain(sharedTerrain), mAwarenessStoreProvider(awarenessStoreProvider), mSteering(new Steering(*this))
{
    m_map.setListener(this);
}

AwareMind::~AwareMind()
{
    delete mSteering;
}

void AwareMind::operation(const Operation & op, OpVector & res)
{
    BaseMind::operation(op, res);

    if (op->getClassNo() == Atlas::Objects::Operation::TICK_NO) {
        if (!op->getArgs().empty()) {
            auto arg = op->getArgs().front();
            if (arg->getName() == "move") {
                processMoveTick(op, res);
            }
        }
    }

}

void AwareMind::processMoveTick(const Operation & op, OpVector & res)
{
    double futureTick = 0.2;

    if (mAwareness) {
        auto remainingDirtyTiles = mAwareness->rebuildDirtyTile();
        if (remainingDirtyTiles > 0) {
            futureTick = 0;
        } else {
            if (mAwareness->needsPruning()) {
                mAwareness->pruneTiles();
            }
            if (mAwareness->needsPruning()) {
                futureTick = 0;
            }
        }
    }

    if (mSteering) {
        SystemTime time;
        time.update();
        SteeringResult result = mSteering->update(time.seconds() + (double)time.microseconds() / 1000000.0);
        if (result.direction.isValid()) {
            Atlas::Objects::Operation::Move move;
            Atlas::Objects::Entity::Anonymous what;
//            what->setLoc(m_entity->getLocation()->getId());
            what->setId(getId());
            what->setAttr("velocity", result.direction.toAtlas());
            if (result.destination.isValid()) {
                what->setAttr("pos", result.destination.toAtlas());
            }

            move->setFrom(getId());
            move->setArgs1(what);

            res.push_back(move);

        }
    }

    Atlas::Objects::Operation::Tick tick;
    Atlas::Objects::Root arg;
    arg->setName("move");
    tick->setArgs1(arg);
    tick->setFutureSeconds(futureTick);

    res.push_back(tick);
}

Steering& AwareMind::getSteering()
{
    return *mSteering;
}


void AwareMind::setType(const TypeNode * t)
{
    BaseMind::setType(t);
    log(INFO, "Creating store.");
    mAwarenessStore = &mAwarenessStoreProvider.getStore(getType());
}

void AwareMind::entityAdded(const MemEntity& entity)
{
    if (mAwareness) {
        log(INFO, "Adding entity.");
        //TODO: check if the entity is dynamic
        if (entity.m_location.m_loc == m_location.m_loc) {
            mAwareness->addEntity(*this, entity, false);
        }
    } else {
        if (this->m_location.m_loc && entity.getIntId() == this->m_location.m_loc->getIntId()) {
            log(INFO, "Creating awareness.");
            mAwareness = mAwarenessStore->requestAwareness(entity);
            mAwareness->addEntity(*this, *this, true);
        }
    }
}

void AwareMind::entityUpdated(const MemEntity& entity, const Atlas::Objects::Entity::RootEntity & ent, LocatedEntity* oldLocation)
{
    if (mAwareness) {
        if (ent->hasAttrFlag(Atlas::Objects::Entity::LOC_FLAG)) {
            if (oldLocation == entity.m_location.m_loc) {
                //Location wasn't changed
                if (entity.m_location.m_loc == this->m_location.m_loc) {
                    log(INFO, "Updated entity.");
                    mAwareness->updateEntityMovement(*this, entity);
                }
            } else {
                //Check if new location is the domain, and then add the entity
                if (entity.m_location.m_loc == this->m_location.m_loc) {
                    log(INFO, "Adding entity.");
                    mAwareness->addEntity(*this, entity, false);
                } else if (oldLocation == this->m_location.m_loc) {
                    log(INFO, "Removing entity.");
                    mAwareness->removeEntity(*this, entity);
                }
            }
        }
    } else {
        if (this->m_location.m_loc && entity.getIntId() == this->m_location.m_loc->getIntId()) {
            if (!mAwareness) {
                log(INFO, "Creating awareness.");
                mAwareness = mAwarenessStore->requestAwareness(entity);
                mAwareness->addEntity(*this, *this, true);
                mSteering->setAwareness(mAwareness.get());
            }
        }
    }
}

void AwareMind::entityDeleted(const MemEntity& entity)
{
    if (mAwareness) {
        log(INFO, "Removed entity.");
        mAwareness->removeEntity(*this, entity);
    }
}

void AwareMind::onContainered(const LocatedEntity * new_loc)
{
}
