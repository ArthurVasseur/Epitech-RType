/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** IInteractable
*/

#ifndef IINTERACTABLE_HPP_
#define IINTERACTABLE_HPP_

class IInteractable
{
    public:
        virtual ~IInteractable() = default;
        virtual void onPointerClicked() = 0;
        virtual void onPointerReleased() = 0;
        virtual void onPointerOver() = 0;
};

#endif /* !IINTERACTABLE_HPP_ */
