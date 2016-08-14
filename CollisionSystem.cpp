//
// Created by Fabien on 24/01/2016.
//

#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(sf::RenderTarget& ptarget, tmx::MapLoader& pLoader) : mLoader(pLoader), mTarget(ptarget)
{
}
void CollisionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{

    const sf::IntRect &viewport = mTarget.getViewport(mTarget.getDefaultView());

    mLoader.UpdateQuadTree(sf::FloatRect(viewport));

    es.each<Drawable,Playable,Movable>([this,&events](entityx::Entity entity, Drawable& drawable, Playable& playable, Movable& movable) {

        sf::Vector2f &pos = drawable.vectorPos;

        sf::FloatRect playerRec = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};

        for(auto& object : mLoader.QueryQuadTree(playerRec))
        {
            if(object->GetName()!="playerStart")
            {
                sf::FloatRect intersecRec;

                const sf::FloatRect &objRec = object->GetAABB();

                if(objRec.intersects(playerRec, intersecRec))
                {
                    events.emit<Collision>(playerRec, objRec, intersecRec,movable.vectorMov);
                }
            }

        }
    });
}