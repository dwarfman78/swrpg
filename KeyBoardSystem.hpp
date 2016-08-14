//
// Created by Fabien on 11/01/2016.
//

#ifndef SWRPG_KEYBOARDSYSTEM_H
#define SWRPG_KEYBOARDSYSTEM_H

#include "Imports.hpp"
#include "Components.hpp"

class KeyBoardSystem : public entityx::System<KeyBoardSystem>, public entityx::Receiver<KeyBoardSystem>
{
public:
    KeyBoardSystem(sf::RenderWindow &target) : mTarget(target)
    {
        mChai.add(chaiscript::base_class<sf::Window, sf::RenderWindow>());
        mChai.add(chaiscript::var(&mTarget), "window");
        mChai.add(chaiscript::fun(&sf::Window::close), "close");
    }

    void configure(entityx::EventManager &event_manager);

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);

    void receive(const sf::Event &event);

private:
    sf::RenderWindow &mTarget;
    chaiscript::ChaiScript mChai;

    std::string convertToValue(const sf::Event &event);
    std::string getRealTimeKey();
};

#endif //SWRPG_KEYBOARDSYSTEM_H
