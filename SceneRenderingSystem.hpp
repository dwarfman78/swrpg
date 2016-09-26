//
// Created by Fabien on 11/01/2016.
//

#ifndef SWRPG_SCENERENDERINGSYSTEM_HPP
#define SWRPG_SCENERENDERINGSYSTEM_HPP

#include "Imports.hpp"
#include "Config.hpp"
#include "Components.hpp"

class SceneRenderingSystem : public entityx::System<SceneRenderingSystem>,public entityx::Receiver<SceneRenderingSystem>
{
public:
    SceneRenderingSystem(sf::RenderTarget &target,tmx::MapLoader& loader) : mTarget(target), mLoader(loader), mDialog({1024,300}), mShowDialog(false)
    {
        mDialogFont.loadFromFile("font.ttf");
        mDialog.setPosition({0,768-300});
        mDialog.setFillColor({0,0,0,128});
        const sf::Vector2f &position = mDialog.getPosition();

        mDialogText.setPosition(position.x, position.y);
        mDialogText.setFont(mDialogFont);
        mDialogText.setCharacterSize(40);
        mDialogText.setFillColor({255,255,255,255});
    }

    void configure(entityx::EventManager &event_manager);

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);

    void receive(const DialogEvent &collision);

private:
    sf::RenderTarget &mTarget;
    tmx::MapLoader& mLoader;
    sf::RectangleShape mDialog;
    sf::Text mDialogText;
    sf::Font mDialogFont;
    bool mShowDialog;
};

#endif //SWRPG_SCENERENDERINGSYSTEM_HPP
