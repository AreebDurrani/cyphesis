# This file is distributed under the terms of the GNU General Public license.
# Copyright (C) 2018 Erik Ogenvik (See the file COPYING for details).

from atlas import *

import server


def strike(instance):
    # If there's a cooldown we need to mark the actor
    cooldown = getattr(instance.tool.props, "cooldown_" + instance.op.id)
    if cooldown and cooldown > 0.0:
        instance.tool.send_world(Operation('set', Entity(instance.tool.id, ready_at=server.world.get_time() + cooldown), to=instance.tool.id))

    # Send sight even if we miss
    instance.actor.send_world(Operation("sight", instance.op))

    # Unarmed strike only handles one target
    target = instance.get_arg("targets", 0)
    # Ignore pos
    if target:
        if instance.actor.can_reach(target):
            damage = 0
            damage_attr = getattr(instance.actor.props, "damage_" + instance.op.id)
            if damage_attr:
                damage = damage_attr
            hit_op = Operation('hit', Entity(damage=damage, hit_type=instance.op.id), to=target.entity)
            return (server.OPERATION_BLOCKED, hit_op, Operation('sight', hit_op))
        else:
            return (server.OPERATION_BLOCKED, instance.actor.client_error(instance.op, "Too far away"))
    else:
        return server.OPERATION_BLOCKED
