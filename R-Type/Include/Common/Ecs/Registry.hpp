/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Registry
*/

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_
#include <unordered_map>
#include <typeindex>
#include <any>
#include <functional>
#include <iostream>
#include <unordered_set>
#include "SparseAarray.hpp"

using Entity = std::size_t;
class Registry
{
public:
    Registry() : _entityCount(0) {}
    template <class Component>
    SparseArray<Component> &registerComponent()
    {
        auto &any = _components[std::type_index(typeid(Component))];
        any = std::make_any<SparseArray<Component>>();
        auto lambda = [](Registry &r, const Entity &e)
        {
            auto &comp = r.getComponents<Component>();
            comp.remove_at(e);
        };
        _sparseArrayComponentEraser[std::type_index(typeid(Component))] = lambda;
        return std::any_cast<SparseArray<Component> &>(any);
    }

    template <class Component>
    SparseArray<Component> &getComponents()
    {
        auto array = _components.find(std::type_index(typeid(Component)));
        if (array == _components.end())
            throw std::runtime_error("Component array not found");
        return std::any_cast<SparseArray<Component> &>((*array).second);
    }

    template <class Component>
    const SparseArray<Component> &getComponents() const
    {
        const auto array = _components.find(std::type_index(typeid(Component)));
        if (array == _components.end())
            throw std::runtime_error("Component array not found");
        return std::any_cast<const SparseArray<Component> &>((*array).second);
    }

    Entity addEntity()
    {
        if (!_availableEntitiesId.empty())
        {
            Entity entity = _availableEntitiesId.back();
            _availableEntitiesId.pop_back();
            return entity;
        }
        return _entityCount++;
    }

    void removeEntity(Entity entity)
    {
        for (auto &componentEraser : _sparseArrayComponentEraser)
        {
            componentEraser.second(*this, entity);
        }
        _availableEntitiesId.push_back(entity);
    }

    template <typename Component>
    typename SparseArray<Component>::reference_type addComponent(Entity to, Component &&c)
    {
        auto &comp = _components[std::type_index(typeid(Component))];
        if (!comp.has_value())
        {
            auto &array = registerComponent<Component>();
            return array.insert_at(to, c);
        }
        else
        {
            auto &array = std::any_cast<SparseArray<Component> &>(comp);
            return array.insert_at(to, c);
        }
        throw std::runtime_error("Unable to add Component");
    }

    template <typename Component, typename... Args>
    typename SparseArray<Component>::reference_type emplaceComponent(Entity to, Args &&...p)
    {
        auto &comp = _components[std::type_index(typeid(Component))];
        if (!comp.has_value())
        {
            auto &array = registerComponent<Component>();
            return array.emplace_at(to, std::forward<Args>(p)...);
        }
        else
        {
            auto &array = std::any_cast<SparseArray<Component> &>(comp);
            return array.emplace_at(to, std::forward<Args>(p)...);
        }
        throw std::runtime_error("Unable to add Component");
    }

    template <typename Component>
    void removeComponent(Entity from)
    {
        auto &comp = _components[std::type_index(typeid(Component))];
        if (comp.has_value())
        {
            auto &array = std::any_cast<SparseArray<Component> &>(comp);
            array.remove_at(from);
            return;
        }
        throw std::runtime_error("Unable to remove Component");
    }

    template <typename Component>
    bool hasComponent(Entity from)
    {
        try
        {
            const auto &array = getComponents<Component>();
            if (array[from])
            {
                return (true);
            }
        }
        catch (const std::exception &e)
        {
            return (false);
        }
        return (false);
    }

    template <typename Component>
    Component &getComponent(Entity from)
    {
        if (!hasComponent<Component>(from))
            throw std::runtime_error("Component not found");
        auto &array = getComponents<Component>();
        return static_cast<Component &>(array[from].value());
    }

    void clear()
    {
        _components.clear();
        _sparseArrayComponentEraser.clear();
        _availableEntitiesId.clear();
        _entityCount = 0;
    }

private:
    std::unordered_map<std::type_index, std::any> _components;
    std::unordered_map<std::type_index, std::function<void(Registry &, const Entity &)>> _sparseArrayComponentEraser;
    std::vector<Entity> _availableEntitiesId;
    std::size_t _entityCount;
};

#endif /* !REGISTRY_HPP_ */
