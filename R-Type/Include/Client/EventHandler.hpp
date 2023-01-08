/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** EventHandler
*/

#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_
#include <functional>
#include <map>
#include <vector>
#include "Input.hpp"
#include "Registry.hpp"

class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler() = default;
    void addInputHandler(std::function<void(std::map<Input::Key, bool> &, float deltatime, Registry &r)> callback) { _callbacks.push_back(callback); }
    void addKeyToHandle(Input::Key k) {_keys.push_back(k);}
    void addKeysToHandle(std::vector<Input::Key> keys)
    {
        for (auto k : keys)
            _keys.push_back(k);
    }
    const std::vector<Input::Key> &getKeys() const { return _keys; }
    std::vector<std::function<void(std::map<Input::Key, bool> &, float deltatime, Registry &r)>> getCallbacks() { return _callbacks; }

private:
    std::vector<std::function<void(std::map<Input::Key, bool> &, float deltatime, Registry &r)>> _callbacks;
    std::vector<Input::Key> _keys;
};

#endif /* !EVENTHANDLER_HPP_ */
