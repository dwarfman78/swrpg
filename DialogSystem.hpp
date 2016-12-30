//
// Created by Fabien on 30/12/2016.
//

#ifndef SWRPG_DIALOGSYSTEM_HPP
#define SWRPG_DIALOGSYSTEM_HPP
#include "Imports.hpp"
#include "Components.hpp"
class DialogSystem : public entityx::System<DialogSystem>, public entityx::Receiver<DialogSystem>
{
public:
    DialogSystem(sf::RenderTarget& pTarget):mTarget(pTarget),mDialog({1024,300}), mShowDialog(false)
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
    void receive(const DialogEvent& dialogEvent);

    void configure(entityx::EventManager &event_manager);

    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt);
private:
    sf::RenderTarget& mTarget;
    sf::RectangleShape mDialog;
    sf::Text mDialogText;
    sf::Font mDialogFont;
    bool mShowDialog;
};
#endif //SWRPG_DIALOGSYSTEM_HPP_HPP
