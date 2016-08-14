//
// Created by Fabien on 17/01/2016.
//

#include "Imports.hpp"
#include "Components.hpp"

#ifndef SWRPG_ANIMATIONSYSTEM_HPP
#define SWRPG_ANIMATIONSYSTEM_HPP
class AnimationSystem : public entityx::System<AnimationSystem>
{
public:
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
};
#endif //SWRPG_ANIMATIONSYSTEM_HPP
