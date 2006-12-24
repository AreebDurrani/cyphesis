// Cyphesis Online RPG Server and AI Engine
// Copyright (C) 2000-2004 Alistair Riddoch
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

// $Id: BaseWorld.cpp,v 1.18 2006-12-24 14:42:06 alriddoch Exp $

#include "BaseWorld.h"

#include "id.h"
#include "log.h"
#include "debug.h"
#include "compose.hpp"

BaseWorld * BaseWorld::m_instance = 0;

/// \brief BaseWorld constructor.
///
/// Protected as BaseWorld is a base class.
/// This constructor registers the instance created as the singleton, and
/// in debug mode ensures that an instance has not already been created.
/// @param gw the top level in-game entity in the world.
BaseWorld::BaseWorld(Entity & gw) : m_gameWorld(gw)
{
    assert(m_instance == 0);
    m_instance = this;
}

/// \brief BaseWorld destructor.
///
/// Removes this instance from the singleton pointer. In debug mode ensures
/// that this instance is correctly installed as the singleton.
BaseWorld::~BaseWorld()
{
    assert(m_instance == this);
    m_instance = 0;
}

/// \brief Get an in-game Entity by its string ID.
///
/// @param id string ID of Entity to be retrieved.
/// @return pointer to Entity retrieved, or zero if it was not found.
Entity * BaseWorld::getEntity(const std::string & id) const
{
    long intId = integerId(id);

    EntityDict::const_iterator I = m_eobjects.find(intId);
    if (I != m_eobjects.end()) {
        assert(I->second != 0);
        return I->second;
    } else {
        return 0;
    }
}
