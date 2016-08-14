//
// Created by Fabien on 15/01/2016.
//

#ifndef SWRPG_COMPONENTS_HPP
#define SWRPG_COMPONENTS_HPP

#include "Imports.hpp"
struct Drawable
{
    Drawable(sf::Vector2f vector):vectorPos(vector){}
    sf::Vector2f vectorPos;
};
struct Movable
{
    Movable(sf::Vector2f vector):vectorMov(vector){}
    sf::Vector2f vectorMov;
};
struct Playable
{
};
struct Animation{

    Animation(float pduration, std::vector<sf::FloatRect> rects) : duration(pduration), animationRects(std::move(rects)){current = animationRects.begin();displayTime=0;frameTime = duration / animationRects.size();}
    float duration;
    double frameTime;
    double displayTime;
    std::vector<sf::FloatRect> animationRects;
    std::vector<sf::FloatRect>::iterator current;

};
struct Animable
{
    Animable(std::map< std::string, std::unique_ptr<Animation> > panimations, sf::RenderStates pstates,std::string pcurrent = ""):animations(std::move(panimations)),states(pstates),current(pcurrent){}

    std::map< std::string, std::unique_ptr<Animation> > animations;

    std::string current;

    sf::RenderStates states;
};
struct Collision
{
    Collision(sf::FloatRect pA, sf::FloatRect pB, sf::FloatRect pIntersect, sf::Vector2f pFrom) : mA(pA), mB(pB), mIntersect(pIntersect), mFrom(pFrom)
    {

    }

    sf::FloatRect mA,mB,mIntersect;
    sf::Vector2f mFrom;
};
#endif //SWRPG_COMPONENTS_HPP
