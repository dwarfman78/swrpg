//
// Created by Fabien on 11/01/2016.
//

#ifndef SWRPG_APPLICATION_HPP_HPP
#define SWRPG_APPLICATION_HPP_HPP

#include "Imports.hpp"
#include "Config.hpp"
#include "KeyBoardSystem.hpp"
#include "SceneRenderingSystem.hpp"
#include "MoveSystem.hpp"
#include "AnimationSystem.hpp"

class Application : public entityx::EntityX
{
public:

    Application();

    sf::RenderStates constructPlayerStates();

    std::map< std::string, std::unique_ptr<Animation> > constructPlayerAnimations();

    void start();

private:
    std::map<std::string, std::string> mConfig;
    sf::RenderWindow mWindow;
    chaiscript::ChaiScript mScript;
    tmx::MapLoader mLoader;
    sf::Clock mClock;
    sf::Texture mTileset;

};

#endif //SWRPG_APPLICATION_HPP_HPP
