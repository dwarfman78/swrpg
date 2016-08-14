//
// Created by Fabien on 16/01/2016.
//

#include "Imports.hpp"
#include "Components.hpp"

#ifndef SWRPG_MOVESYSTEM_HPP
#define SWRPG_MOVESYSTEM_HPP
class MoveSystem : public entityx::System<MoveSystem>,public entityx::Receiver<MoveSystem>
{
public:
    MoveSystem()
    {

    }
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);

    void receive(const Collision& collision);

    void configure(entityx::EventManager &event_manager);

private:

    sf::FloatRect mIntersectRec;
    bool mCollision;
    sf::Vector2f mFrom;
};
#endif //SWRPG_MOVESYSTEM_HPP
