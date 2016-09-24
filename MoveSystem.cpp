//
// Created by Fabien on 16/01/2016.
//

#include "MoveSystem.hpp"
void MoveSystem::configure(entityx::EventManager &event_manager)
{
    event_manager.subscribe<Collision>(*this);
}
void MoveSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Drawable,Movable>([this,dt](entityx::Entity entity, Drawable& drawable, Movable& movable) {

        if(mCollision)
        {
            mCollision = false;
            float offsetY, offsetX = 0;

            if(mFrom.y<0)
            {
                offsetY = mIntersectRec.height + 1;
            }
            if(mFrom.y>0)
            {
                offsetY = (mIntersectRec.height + 1) * -1;
            }
            if(mFrom.x<0)
            {
                offsetX = mIntersectRec.width + 1;
            }
            if(mFrom.x>0)
            {
                offsetX = (mIntersectRec.width + 1) * -1;
            }

            drawable.vectorPos.x += offsetX;
            drawable.vectorPos.y += offsetY;

        }
        else
        {
            sf::Vector2f vectormov = movable.vectorMov;

            drawable.vectorPos.x += vectormov.x * dt;
            drawable.vectorPos.y += vectormov.y * dt;

            if(vectormov.x != 0 || vectormov.y != 0) {
                movable.lastVectorMov = vectormov;
            }
        }



    });
}

void MoveSystem::receive(const Collision &collision)
{
    if(collision.mType == Collision::CollisionType::DIRECT)
    {
        mIntersectRec = collision.mIntersect;
        mCollision = true;
        mFrom = collision.mFrom;
    }
}
