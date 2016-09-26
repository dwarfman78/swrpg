//
// Created by Fabien on 11/01/2016.
//
#include "SceneRenderingSystem.hpp"

void SceneRenderingSystem::receive(const DialogEvent &collision)
{
    mShowDialog = true;
    mDialogText.setString(collision.mDialog);
}
void SceneRenderingSystem::configure(entityx::EventManager &event_manager) {event_manager.subscribe<DialogEvent>(*this); }
void SceneRenderingSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    sf::View view = mTarget.getView();

    sf::FloatRect bounds;
    bounds.left = view.getCenter().x - (view.getSize().x / 2.f);
    bounds.top = view.getCenter().y - (view.getSize().y / 2.f);
    bounds.width = view.getSize().x;
    bounds.height = view.getSize().y;

    //add a tile border to prevent gaps appearing
    bounds.left -= static_cast<float>(TILE_SIZE);
    bounds.top -= static_cast<float>(TILE_SIZE);
    bounds.width += static_cast<float>(TILE_SIZE * 2);
    bounds.height += static_cast<float>(TILE_SIZE * 2);


    std::vector<tmx::MapLayer> &vector = mLoader.GetLayers();

    for (auto &layer : vector)
        layer.Cull(bounds);

    for (auto &layer : vector)
    {
        if (layer.name == "player")
        {

            es.each<Drawable,Animable,Playable>([this](entityx::Entity entity, Drawable& drawable,Animable& animable, Playable& playable) {
                sf::VertexArray quad(sf::Quads, 4);

                float abs = drawable.vectorPos.x;

                float ord = drawable.vectorPos.y;

                quad[0].position = sf::Vector2f(abs, ord);
                quad[1].position = sf::Vector2f(abs+TILE_SIZE, ord);
                quad[2].position = sf::Vector2f(abs+TILE_SIZE, ord+TILE_SIZE);
                quad[3].position = sf::Vector2f(abs, ord+TILE_SIZE);

                if(animable.current != "")
                {
                    Animation* animation = animable.animations[animable.current].get();

                    if(animation != nullptr)
                    {
                        sf::FloatRect currentRec = (*(animation->current));

                        quad[0].texCoords = sf::Vector2f(currentRec.left, currentRec.top);
                        quad[1].texCoords = sf::Vector2f(currentRec.left+currentRec.width, currentRec.top);
                        quad[2].texCoords = sf::Vector2f(currentRec.left+currentRec.width, currentRec.top+currentRec.height);
                        quad[3].texCoords = sf::Vector2f(currentRec.left, currentRec.top+currentRec.height);


                        this->mTarget.draw(quad,animable.states);
                    }

                }

            });
        }
        else
        {
            mTarget.draw(layer);
        }
    }

    if(mShowDialog)
    {
        mTarget.draw(mDialog);
        mTarget.draw(mDialogText);
    }


    //mLoader.Draw(mTarget, tmx::MapLayer::Debug);
}

