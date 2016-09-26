//
// Created by Fabien on 10/09/2016.
//

#include "ActionSystem.hpp"

ActionSystem::ActionSystem(tmx::MapLoader& pLoader):mLoader(pLoader),mCollision(false),mObject(nullptr),mActionPending(false)
{

}

void ActionSystem::configure(entityx::EventManager &event_manager) {
    event_manager.subscribe<Collision>(*this);
    event_manager.subscribe<EndCollision>(*this);
    mChai.add(chaiscript::fun([this](const std::string& something){ say(something); }), "say");
    mEventManager = &event_manager;

}

void ActionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
// tester l'état du clavier

    if (mCollision)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if(!mActionPending) {
                mActionPending = true;
                if (mObject != nullptr) {
                    mChai.eval_file(mObject->GetPropertyString("action"));
                }
            }
        }
        else
        {
            mActionPending=false;
        }
    }
}

void ActionSystem::receive(const Collision &collision) {
    switch (collision.mType) {
        case Collision::CollisionType::FAR :
            mObject = collision.mObject;
            mCollision = true;
            break;
        default:
            break;
    }
}

void ActionSystem::receive(const EndCollision &collision)
{
    mCollision = false;
    mObject = nullptr;
}

void ActionSystem::say(const std::string &something) const {

    if(mEventManager!= nullptr) {
        mEventManager->emit<DialogEvent>(something);
    }

}

