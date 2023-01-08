/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Render
*/

#include "Render.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "SfmlRenderer.hpp"
#include "Collider.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "TextBox.hpp"

namespace System
{
    Render::Render(std::shared_ptr<EventHandler> handler)
    {
        _rendererLibrary = std::make_unique<renderer::SfmlRenderer>(handler);
    }

    void Render::update(float deltaTime, Registry &r)
    {
        _rendererLibrary->handleInputs(deltaTime, r);
        _rendererLibrary->clear();
        try
        {
            auto transforms = r.getComponents<Component::Transform>();

            for (std::size_t entity = 0; entity < transforms.size(); entity++)
            {
                try
                {
                    bool hasSprite = r.hasComponent<Component::Sprite>(entity);
                    bool hasTransform = r.hasComponent<Component::Transform>(entity);
                    bool hasText = r.hasComponent<Component::ui::Text>(entity);
                    bool hasRectangle = r.hasComponent<Component::Rectangle>(entity);
                    bool hasButton = r.hasComponent<Component::ui::Button>(entity);
                    bool hasTextBox = r.hasComponent<Component::ui::TextBox>(entity);
                    if (!hasTransform)
                        continue;
                    auto &transform = r.getComponent<Component::Transform>(entity);
                    if (hasSprite)
                        _rendererLibrary->drawSprite(r.getComponent<Component::Sprite>(entity), transform);
                    if (hasRectangle && hasButton)
                        handleButton(r, entity);
                    if (hasText)
                        handleText(r, entity);
                    if (hasText && hasTextBox)
                        handleTextBox(r, entity);
                }
                catch (...)
                {
                }
            }
        }
        catch (const std::exception &e)
        {
        }
        _rendererLibrary->display();
    }

    void Render::handleButton(Registry &r, Entity entity)
    {
        auto &rectangle = r.getComponent<Component::Rectangle>(entity);
        auto &transform = r.getComponent<Component::Transform>(entity);
        auto &btn = r.getComponent<Component::ui::Button>(entity);
        //_rendererLibrary->drawShape(transform._position, rectangle._size);
        float pointerX = _rendererLibrary->getPointerX();
        float pointerY = _rendererLibrary->getPointerY();
        bool isColliding = Component::Collider::checkCollision(transform._position, rectangle, {pointerX, pointerY}, {1, 1});
        bool mousePressed = _rendererLibrary->isMouseButtonPressed(Input::Mouse::LeftButton);
        if (isColliding && mousePressed)
        {
            if (btn.getLastState() != Component::ui::CLICKED)
            {
                btn.setState(Component::ui::State::NONE);
                btn.onPointerClicked();
            }
            btn.setLastState(Component::ui::CLICKED);
        }
        else if (isColliding)
        {
            btn.setState(Component::ui::NONE);
            if (btn.getLastState() != Component::ui::OVERED && btn.getLastState() != Component::ui::CLICKED)
                btn.onPointerOver();
            if (btn.getLastState() == Component::ui::CLICKED && !mousePressed)
                btn.onPointerReleased();
            btn.setLastState(Component::ui::OVERED);
        }
        else
        {
            btn.setLastState(Component::ui::NONE);
        }
    }

    void Render::handleText(Registry &r, Entity entity)
    {
        auto &text = r.getComponent<Component::ui::Text>(entity);
        auto &transform = r.getComponent<Component::Transform>(entity);

        _rendererLibrary->drawText(text, transform);
    }

    void Render::handleTextBox(Registry &r, Entity entity)
    {
        auto &textBox = r.getComponent<Component::ui::TextBox>(entity);
        auto &text = r.getComponent<Component::ui::Text>(entity);
        auto &transform = r.getComponent<Component::Transform>(entity);

        float pointerX = _rendererLibrary->getPointerX();
        float pointerY = _rendererLibrary->getPointerY();
        bool isColliding = Component::Collider::checkCollision(transform._position, textBox.rectangle, {pointerX, pointerY}, {1, 1});
        bool mousePressed = _rendererLibrary->isMouseButtonPressed(Input::Mouse::LeftButton);
        if (mousePressed && isColliding)
            textBox.hasFocus = true;
        else if (mousePressed && !isColliding)
            textBox.hasFocus = false;
        if (textBox.hasFocus)
        {
            char c = 0;
            while (_rendererLibrary->pollCharTyped(c))
            {
                if (c == '\b' && !text._text.empty())
                    text._text.pop_back();
                else if (c != '\b')
                    text._text += c;
            }
        }
        else
        {
            char c = 0;
            while (_rendererLibrary->pollCharTyped(c))
            {
            }
        }
    }
}