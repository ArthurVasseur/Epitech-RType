/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Lobby
*/

#include "Lobby.hpp"


namespace System
{

    Lobby::Lobby(Registry &r, World &world)
    {
        auto text = world.addEntity();
        Component::Transform transform(Component::Vector2Df(800.f,0.f), 0, Component::Vector2Df(1.f,1.f));
        auto &tt = r.emplaceComponent<Component::Transform>(text, transform);
        auto txt = Component::ui::Text ("./assets/pixelated.ttf","Lobby", Component::ui::Color (255,255,255), 75);
        auto &textcmpnt = r.emplaceComponent<Component::ui::Text>(text, txt);
        auto rectYellow = world.addEntity();
        Component::Transform transform2 (Component::Vector2Df(400.f,200.f), 0, Component::Vector2Df(4.f,4.f));
        auto &tt2 = r.emplaceComponent<Component::Transform>(rectYellow, transform2);
        auto rectY = Component::Sprite("./assets/RectangleY.png");
        auto &rectYellowCmpnt = r.emplaceComponent<Component::Sprite>(rectYellow, rectY);
        auto text10 = world.addEntity();
        Component::Transform transform10(Component::Vector2Df(300.f,185.f), 0, Component::Vector2Df(1.f,1.f));
        auto &tt10 = r.emplaceComponent<Component::Transform>(text10, transform10);
        auto txt10 = Component::ui::Text ("./assets/pixelated.ttf","Player1", Component::ui::Color (255,255,255), 30);
        auto &textcmpnt10 = r.emplaceComponent<Component::ui::Text>(text10, txt10);
        auto rectRed = world.addEntity();
        Component::Transform transform3 (Component::Vector2Df(400.f,250.f), 0, Component::Vector2Df(4.f,4.f));
        auto &tt3 = r.emplaceComponent<Component::Transform>(rectRed, transform3);
        auto rectR = Component::Sprite("./assets/RectangleR.png");
        auto &rectRedCmpnt = r.emplaceComponent<Component::Sprite>(rectRed, rectR);
        auto text11 = world.addEntity();
        Component::Transform transform11(Component::Vector2Df(300.f,235.f), 0, Component::Vector2Df(1.f,1.f));
        auto &tt11 = r.emplaceComponent<Component::Transform>(text11, transform11);
        auto txt11 = Component::ui::Text ("./assets/pixelated.ttf","Player2", Component::ui::Color (255,255,255), 30);
        auto &textcmpnt11 = r.emplaceComponent<Component::ui::Text>(text11, txt11);
        auto rectGreen = world.addEntity();
        Component::Transform transform4 (Component::Vector2Df(400.f,300.f), 0, Component::Vector2Df(4.f,4.f));
        auto &tt4 = r.emplaceComponent<Component::Transform>(rectGreen, transform4);
        auto rectG = Component::Sprite("./assets/RectangleG.png");
        auto &rectGreenCmpnt = r.emplaceComponent<Component::Sprite>(rectGreen, rectG);
        auto text12 = world.addEntity();
        Component::Transform transform12(Component::Vector2Df(300.f,285.f), 0, Component::Vector2Df(1.f,1.f));
        auto &tt12 = r.emplaceComponent<Component::Transform>(text12, transform12);
        auto txt12 = Component::ui::Text ("./assets/pixelated.ttf","Player3", Component::ui::Color (255,255,255), 30);
        auto &textcmpnt12 = r.emplaceComponent<Component::ui::Text>(text12, txt12);
        auto rectPurple = world.addEntity();
        Component::Transform transform5 (Component::Vector2Df(400.f,350.f), 0, Component::Vector2Df(4.f,4.f));
        auto &tt5 = r.emplaceComponent<Component::Transform>(rectPurple, transform5);
        auto rectP = Component::Sprite("./assets/RectanglePurple.png");
        auto &rectPurpleCmpnt = r.emplaceComponent<Component::Sprite>(rectPurple, rectP);
        auto text13 = world.addEntity();
        Component::Transform transform13(Component::Vector2Df(300.f,200.f), 0, Component::Vector2Df(1.f,1.f));
        auto &tt13 = r.emplaceComponent<Component::Transform>(text13, transform13);
        auto txt13 = Component::ui::Text ("./assets/pixelated.ttf","Player4", Component::ui::Color (255,255,255), 30);
        auto &textcmpnt13 = r.emplaceComponent<Component::ui::Text>(text13, txt13);
    }

    Lobby::~Lobby()
    {
    }

    void Lobby::update(float deltaTime, Registry &r)
    {
        auto &texts = r.getComponents<Component::ui::Text>();
        
    }

    void Lobby::stepUpdate(float deltaTime, Registry &r)
    {

    }

}