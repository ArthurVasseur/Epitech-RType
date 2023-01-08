/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** SfmlRenderer
*/

#include <memory>
#include "SfmlRenderer.hpp"
// #include "Input.hpp"
#include "Text.hpp"

namespace renderer
{
    SfmlRenderer::SfmlRenderer(std::shared_ptr<EventHandler> eventHandler) : _window(sf::VideoMode(1280, 720), "ECS Engine"), _eventHandler(eventHandler)
    {
    }

    void SfmlRenderer::clear()
    {
        _window.clear();
    }

    void SfmlRenderer::display()
    {
        _window.display();
    }

    void SfmlRenderer::drawSprite(const Component::Sprite &sprite, const Component::Transform &transform)
    {
        auto it = _sprites.find(sprite._path);
        if (it != _sprites.end())
        {
            sf::Sprite newSprite;
            newSprite.setTexture(it->second);
            newSprite.setPosition(sf::Vector2f(transform._position.x, transform._position.y));
            newSprite.setScale(transform._scale.x, transform._scale.y);
            newSprite.setRotation(transform._rotation);
            _window.draw(newSprite);
            return;
        }
        sf::Texture texture;
        if (!texture.loadFromFile(sprite._path))
        {
            std::cerr << "Error load from file" << std::endl;
            return;
        }
        sf::Sprite newSprite;
        texture.setSmooth(true);
        newSprite.setTexture(texture);
        newSprite.setPosition(sf::Vector2f(transform._position.x, transform._position.y));
        newSprite.setRotation(transform._rotation);
        newSprite.setScale(transform._scale.x, transform._scale.y);
        _sprites.emplace(sprite._path, texture);
        _window.draw(newSprite);
    }

    void SfmlRenderer::drawText(const Component::ui::Text &text, const Component::Transform &transform)
    {
        auto it = _fonts.find(text._font);
        sf::Text txt;
        if (it != _fonts.end())
        {
            auto &color = text._color;
            txt.setFont(it->second);
            txt.setStyle((sf::Text::Style)text._style);
            txt.setString(text._text);
            txt.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
            txt.scale(transform._scale.x, transform._scale.y);
            txt.setCharacterSize(text._size);
            txt.setPosition(transform._position.x, transform._position.y);
            _window.draw(txt);
            return;
        }
        sf::Font font;
        if (!font.loadFromFile(text._font))
        {
            std::cerr << "Error load from file" << std::endl;
            return;
        }
        auto &color = text._color;
        txt.setFont(font);
        txt.setString(text._text);
        txt.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
        txt.scale(transform._scale.x, transform._scale.y);
        txt.setCharacterSize(text._size);
        txt.setPosition(transform._position.x, transform._position.y);
        _fonts.emplace(text._font, font);
        _window.draw(txt);
    }

    void SfmlRenderer::drawShape(const Component::Vector2Df &position, const Component::Vector2Df &size)
    {
        sf::RectangleShape rec(sf::Vector2f(size.x, size.y));
        rec.setPosition(sf::Vector2f(position.x, position.y));
        rec.setFillColor(sf::Color::Green);
        _window.draw(rec);
    }

    bool SfmlRenderer::pollCharTyped(char &c)
    {
        if (_textEntered.empty())
            return false;
        c = _textEntered.front();
        _textEntered.pop();
        return true;
    }

    void SfmlRenderer::handleInputs(float deltatime, Registry &r)
    {
        const auto &keys = _eventHandler->getKeys();
        auto callbacks = _eventHandler->getCallbacks();
        std::map<Input::Key, bool> inputs;
        for (auto k : keys)
        {
            inputs[k] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)k);
        }
        for (auto &callback : callbacks)
        {
            callback(inputs, deltatime, r);
        }
        sf::Event event;
        while (_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                _window.close();
                break;
            case sf::Event::TextEntered:
                _textEntered.push((char)event.text.unicode);
                break;
            default:
                break;
            }
        }
    }

    float SfmlRenderer::getPointerX() const
    {
        return (sf::Mouse::getPosition(_window).x);
    }

    float SfmlRenderer::getPointerY() const
    {
        return (sf::Mouse::getPosition(_window).y);
    }

    bool SfmlRenderer::isMouseButtonPressed(Input::Mouse m) const
    {
        if (m == Input::Mouse::LeftButton)
            return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if (m == Input::Mouse::RightButton)
            return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
        return (false);
    }
}