//
// Created by Fabien on 17/01/2016.
//

#include "AnimationSystem.hpp"

void AnimationSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Animable>([dt](entityx::Entity entity, Animable& animable) {

        Animation* currentAnimation = animable.animations[animable.current].get();

        if(currentAnimation != nullptr)
        {
            currentAnimation->displayTime += dt;

            if(currentAnimation->displayTime > currentAnimation->frameTime)
            {
                currentAnimation->displayTime = 0;

                currentAnimation->current++;

                if(currentAnimation->current == currentAnimation->animationRects.end())
                {
                    currentAnimation->current = currentAnimation->animationRects.begin();
                }

            }
        }

    });
}

