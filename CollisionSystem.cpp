//
// Created by Fabien on 24/01/2016.
//

#include "CollisionSystem.hpp"

CollisionSystem::CollisionSystem(sf::RenderTarget& ptarget, tmx::MapLoader& pLoader) : mLoader(pLoader), mTarget(ptarget), mFarCollisionLastTimeDetected(false)
{
}
void CollisionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{

    const sf::IntRect &viewport = mTarget.getViewport(mTarget.getDefaultView());

    mLoader.UpdateQuadTree(sf::FloatRect(viewport));

    es.each<Drawable,Playable,Movable>([this,&events](entityx::Entity entity, Drawable& drawable, Playable& playable, Movable& movable) {

        sf::Vector2f &pos = drawable.vectorPos;

        sf::Vector2f& oldMov = movable.lastVectorMov;

        sf::FloatRect playerRec = {pos.x, pos.y, TILE_SIZE, TILE_SIZE};

        sf::FloatRect farPlayerRec = {playerRec.left+oldMov.x*20, playerRec.top+oldMov.y*20, TILE_SIZE, TILE_SIZE};

        sf::FloatRect intersecRec;

        bool farCollisionDetected{false};

        for(auto& object : mLoader.QueryQuadTree(playerRec))
        {
            if(object->GetName()!="playerStart")
            {
                const sf::FloatRect &objRec = object->GetAABB();

                if(objRec.intersects(playerRec, intersecRec))
                {
                    events.emit<Collision>(Collision::CollisionType::DIRECT, object, playerRec, objRec, intersecRec,movable.vectorMov);
                }
                if(objRec.intersects(farPlayerRec,intersecRec))
                {
                    farCollisionDetected = true;
                    mFarCollisionLastTimeDetected = true;
                    events.emit<Collision>(Collision::CollisionType::FAR, object, farPlayerRec, objRec, intersecRec,movable.vectorMov);
                }
            }
        }

        if(!farCollisionDetected&&mFarCollisionLastTimeDetected)
        {
            mFarCollisionLastTimeDetected = false;
            events.emit<EndCollision>();
        }
    });
}