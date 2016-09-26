#ifndef SWRPG_ACTIONSYSTEM_HPP
#define SWRPG_ACTIONSYSTEM_HPP

#include "Imports.hpp"
#include "Components.hpp"
#include "Config.hpp"

class ActionSystem : public entityx::System<ActionSystem>,public entityx::Receiver<ActionSystem>
{
public:
    ActionSystem(tmx::MapLoader& pLoader);
    void configure(entityx::EventManager &event_manager);
    void receive(const Collision &collision);
    void receive(const EndCollision &collision);
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
private:
    tmx::MapLoader& mLoader;
    bool mCollision;
    tmx::MapObject* mObject;
    chaiscript::ChaiScript mChai;

    void say(const std::string& something) const;
    bool mActionPending;
    entityx::EventManager* mEventManager;
};

#endif