//
// Created by Fabien on 10/09/2016.
//

#include "ActionSystem.hpp"

ActionSystem::ActionSystem(tmx::MapLoader& pLoader):mLoader(pLoader),mCollision(false),mObject(nullptr)
{

}

void ActionSystem::configure(entityx::EventManager &event_manager) {
    event_manager.subscribe<Collision>(*this);
    event_manager.subscribe<EndCollision>(*this);
}

void ActionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
// tester l'état du clavier

    if (mCollision && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(mObject!= nullptr)
        {
            std::cout << "ACTION : " << mObject->GetPropertyString("action") << std::endl;
        }
    }
}

void ActionSystem::receive(const Collision &collision) {
    switch (collision.mType) {
        case Collision::CollisionType::FAR :
            std::cout << "far collision detected" << std::endl;
            mObject = collision.mObject;
            mCollision = true;
            break;
        default:
            break;
    }
}

void ActionSystem::receive(const EndCollision &collision)
{
    std::cout << "far collision ended" << std::endl;
    mCollision = false;
    mObject = nullptr;
}

