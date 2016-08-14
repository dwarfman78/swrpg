//
// Created by Fabien on 24/01/2016.
//

#include "Imports.hpp"
#include "Config.hpp"
#include "Components.hpp"

#ifndef SWRPG_COLLISIONSYSTEM_HPP
#define SWRPG_COLLISIONSYSTEM_HPP
class CollisionSystem : public entityx::System<CollisionSystem>
{
public:
    CollisionSystem(sf::RenderTarget& pTarget,tmx::MapLoader& pLoader);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
private:
    tmx::MapLoader& mLoader;
    sf::RenderTarget& mTarget;
};
#endif //SWRPG_COLLISIONSYSTEM_HPP
