//
// Created by Fabien on 17/01/2016.
//
#ifndef SWRPG_ANIMATIONSYSTEM_HPP
#define SWRPG_ANIMATIONSYSTEM_HPP

#include "Imports.hpp"
#include "Components.hpp"


class AnimationSystem : public entityx::System<AnimationSystem>
{
public:
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
};
#endif //SWRPG_ANIMATIONSYSTEM_HPP
