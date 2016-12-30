//
// Created by Fabien on 30/12/2016.
//
#include "DialogSystem.hpp"

void DialogSystem::configure(entityx::EventManager &event_manager) {event_manager.subscribe<DialogEvent>(*this); }
void DialogSystem::receive(const DialogEvent &collision)
{
    mShowDialog = true;
    mDialogText.setString(collision.mDialog);
}

void DialogSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    if(mShowDialog)
    {
        mTarget.draw(mDialog);
        mTarget.draw(mDialogText);
    }

}


