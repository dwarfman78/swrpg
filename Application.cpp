//
// Created by Fabien on 24/01/2016.
//

#include "Application.hpp"
#include "CollisionSystem.hpp"
#include "ActionSystem.hpp"

Application::Application() : mWindow(sf::VideoMode(1024, 768), "SWRPG"), mLoader("maps")
{
    mScript.add(
            chaiscript::bootstrap::standard_library::map_type<std::map<std::string, std::string> >("ConfigMap"));
    mScript.add(chaiscript::var(&mConfig), "application");
    mScript.eval_file(CONFIG_FILE);

    systems.add<KeyBoardSystem>(mWindow);
    systems.add<SceneRenderingSystem>(mWindow,mLoader);
    systems.add<MoveSystem>();
    systems.add<AnimationSystem>();
    systems.add<CollisionSystem>(mWindow,mLoader);
    systems.add<ActionSystem>(mLoader);
    systems.configure();

    mLoader.Load("test.tmx");

    mTileset.loadFromFile("maps/tileset.png");


    entityx::Entity player = entities.create();

    for (auto &layer : mLoader.GetLayers())
    {
        if (layer.name == "logic")
        {
            for(auto& object : layer.objects)
            {
                if(object.GetName() == "playerStart")
                {
                    player.assign<Drawable>(object.GetPosition());
                    player.assign<Movable>(sf::Vector2f(0,0));
                    player.assign<Animable>(constructPlayerAnimations(),constructPlayerStates(),"standdown");
                    player.assign<Playable>();
                }
            }
        }
    }
}

sf::RenderStates Application::constructPlayerStates()
{
    sf::RenderStates retour;

    retour.texture = &mTileset;

    return retour;
}

std::map< std::string, std::unique_ptr<Animation> > Application::constructPlayerAnimations()
{
    std::map< std::string, std::unique_ptr<Animation> > retour;

    std::vector<sf::FloatRect> standDownRects = {{992,768,32,32}};
    std::vector<sf::FloatRect> standLeftRects = {{64,1024,32,32}};
    std::vector<sf::FloatRect> standRightRects = {{160,1024,32,32}};
    std::vector<sf::FloatRect> standUpRects = {{256,1024,32,32}};

    std::vector<sf::FloatRect> runDownRects = {{0,1024,32,32},{32,1024,32,32}};

    std::vector<sf::FloatRect> runUpRects = {{288,1024,32,32},{320,1024,32,32}};

    std::vector<sf::FloatRect> runLeftRects = {{96,1024,32,32},{128,1024,32,32}};

    std::vector<sf::FloatRect> runRightRects = {{192,1024,32,32},{224,1024,32,32}};

    std::unique_ptr<Animation> standdown (new Animation(1,standDownRects));
    std::unique_ptr<Animation> standup (new Animation(1,standUpRects));
    std::unique_ptr<Animation> standleft (new Animation(1,standLeftRects));
    std::unique_ptr<Animation> standright (new Animation(1,standRightRects));

    std::unique_ptr<Animation> runDown (new Animation(500,runDownRects));

    std::unique_ptr<Animation> runUp (new Animation(500,runUpRects));

    std::unique_ptr<Animation> runLeft (new Animation(500,runLeftRects));

    std::unique_ptr<Animation> runRight (new Animation(500,runRightRects));

    retour["standdown"] = std::move(standdown);

    retour["standleft"] = std::move(standleft);

    retour["standright"] = std::move(standright);

    retour["standup"] = std::move(standup);

    retour["rundown"] = std::move(runDown);

    retour["runup"] = std::move(runUp);

    retour["runleft"] = std::move(runLeft);

    retour["runright"] = std::move(runRight);

    return std::move(retour);
}

void Application::start()
{

    sf::Int64 myNextTick = mClock.getElapsedTime().asMicroseconds();
    unsigned int loops = 0;
    sf::Int64 windowSize = 1000000 / std::stoi(mConfig["MAXFPS"]);

    double lDt;
    double rDt;

    // run the program as long as the window is open
    while (mWindow.isOpen())
    {
        loops = 0;
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            events.emit<sf::Event>(event);
        }


        // clear the window with black color
        mWindow.clear(sf::Color::Black);

        while (mClock.getElapsedTime().asMicroseconds() >= myNextTick && loops < 5)
        {
            myNextTick += windowSize;

            loops++;

            sf::Int32 currTime = mClock.getElapsedTime().asMilliseconds();

            double diffTime = currTime - lDt;

            systems.update<KeyBoardSystem>(diffTime);
            systems.update<AnimationSystem>(diffTime);
            systems.update<MoveSystem>(diffTime);
            systems.update<CollisionSystem>(diffTime);
            systems.update<ActionSystem>(diffTime);

            lDt = currTime;

        }

        double interpolation = (double) (mClock.getElapsedTime().asMicroseconds() + windowSize - myNextTick) / windowSize;
        systems.update<MoveSystem>(interpolation);
        systems.update<SceneRenderingSystem>(interpolation);

        // end the current frame
        mWindow.display();

    }
}