//
// Created by Fabien on 11/01/2016.
//
#include "KeyBoardSystem.hpp"

void KeyBoardSystem::configure(entityx::EventManager &event_manager)
{
    event_manager.subscribe<sf::Event>(*this);
    mChai.add(chaiscript::fun(&Movable::vectorMov),"vectorMov");
    mChai.add(chaiscript::fun(&sf::Vector2f::x),"x");
    mChai.add(chaiscript::fun(&sf::Vector2f::y),"y");
    mChai.add(chaiscript::fun(&Animable::current),"current");


}

void KeyBoardSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    mChai.add(chaiscript::var(getRealTimeKey()), "key");

    es.each<Drawable,Movable, Animable, Playable>([this](entityx::Entity entity, Drawable& drawable, Movable& movable, Animable& animable, Playable & player){
        this->mChai.add(chaiscript::var(&movable), "playerDirection");
        this->mChai.add(chaiscript::var(&animable), "playerAnimation");

        this->mChai.eval_file("scripts/realtime-keyboard.chai");
    });


}

void KeyBoardSystem::receive(const sf::Event &event)
{
    if (event.type == sf::Event::Closed)
        mTarget.close();

    if (event.type == sf::Event::KeyPressed)
    {
        mChai.add(chaiscript::var(convertToValue(event)), "eventValue");

        try
        {
            mChai.eval_file("scripts/keyboard.chai");
        }
        catch (std::exception &e)
        {
            std::cout << e.what();
        }
    }
}

std::string KeyBoardSystem::convertToValue(const sf::Event &event)
{
    std::string retour = "";

    if (event.key.code == sf::Keyboard::Escape)
    {
        retour = "escape";
    }

    return retour;
}

std::string KeyBoardSystem::getRealTimeKey()
{
    std::string retour = "";

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        retour = "up";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        retour = "down";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        retour = "left";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        retour = "right";
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        retour = "space";
    }

    return retour;
}
