/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** InputManager
*/

#ifndef INPUT_SYSTE_HPP_
#define INPUT_SYSTE_HPP_
#include <memory>

#include "ISystem.hpp"
#include "UdpClient.hpp"
#include "EventHandler.hpp"
#include "Registry.hpp"

namespace System
{
    class InputManager : public ISystem
    {
    public:
        InputManager(std::shared_ptr<EventHandler> handler, std::shared_ptr<Network::UDP::UdpClient> udpClient);
        ~InputManager();
        void update(float deltaTime, Registry &r);
        void stepUpdate(float deltaTime, Registry &r);

    protected:
    private:
        std::shared_ptr<Network::UDP::UdpClient> _udpClient;
    };
}
#endif /* !INPUT_SYSTE_HPP_ */
