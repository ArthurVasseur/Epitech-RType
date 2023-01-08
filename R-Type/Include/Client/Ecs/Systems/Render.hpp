/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Render
*/

#ifndef RENDER_CPP_HPP_
#define RENDER_CPP_HPP_

#include <memory>
#include <functional>
#include "IRenderer.hpp"
#include "ISystem.hpp"
#include "EventHandler.hpp"

namespace System
{
    class Render : public ISystem
    {
    public:
        Render(std::shared_ptr<EventHandler> handler);

        ~Render() override = default;

        void update(float deltaTime, Registry &r) final;

        void stepUpdate(float deltaTime, Registry &r) final {}
        void getPointerX() const;
        void getPointerY() const;

    private:
        void handleButton(Registry &r, Entity entity);

        void handleText(Registry &r, Entity entity);
        void handleTextBox(Registry &r, Entity entity);

        std::unique_ptr<renderer::IRenderer> _rendererLibrary;
    };
}
#endif /* !RENDER_CPP_HPP_ */
