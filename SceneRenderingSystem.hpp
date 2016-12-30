//
// Created by Fabien on 11/01/2016.
//

#ifndef SWRPG_SCENERENDERINGSYSTEM_HPP
#define SWRPG_SCENERENDERINGSYSTEM_HPP

#include "Imports.hpp"
#include "Config.hpp"
#include "Components.hpp"

class SceneRenderingSystem : public entityx::System<SceneRenderingSystem>
{
public:
    SceneRenderingSystem(sf::RenderTarget &target,tmx::MapLoader& loader) : mTarget(target), mLoader(loader)
    {

    }

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);

private:
    sf::RenderTarget &mTarget;
    tmx::MapLoader& mLoader;
};

#endif //SWRPG_SCENERENDERINGSYSTEM_HPP
