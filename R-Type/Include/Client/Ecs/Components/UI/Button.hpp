/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <functional>
#include "IInteractable.hpp"

namespace Component
{
    namespace ui
    {
        enum State
        {
            NONE,
            OVERED,
            CLICKED
        };

        class Button : public IInteractable
        {
        public:
            Button(std::function<void(void)> onPointerClicked, std::function<void(void)> onPointerReleased,
                   std::function<void(void)> onPointerOver) : _currentState(NONE), _lastState(NONE), _onPointerClicked(onPointerClicked),
                                                              _onPointerReleased(onPointerReleased), _onPointerOver(onPointerOver) {}

            ~Button() override = default;

            void onPointerClicked() override
            {
                _onPointerClicked();
            }

            void onPointerReleased() override
            {
                _onPointerReleased();
            }

            void onPointerOver() override
            {
                _onPointerOver();
            }

            void setState(State state)
            {
                _currentState = state;
            }

            State getState() const
            {
                return _currentState;
            }

            State getLastState() const
            {
                return (_lastState);
            }

            void setLastState(State state) { _lastState = state; }

        protected:
        private:
            State _currentState;
            State _lastState;
            std::function<void(void)> _onPointerClicked;
            std::function<void(void)> _onPointerReleased;
            std::function<void(void)> _onPointerOver;
        };
    }
}
#endif /* !BUTTON_HPP_ */
