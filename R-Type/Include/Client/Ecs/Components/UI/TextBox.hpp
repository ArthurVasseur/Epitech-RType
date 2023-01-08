/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** TextBox
*/

#ifndef TEXTBOX_HPP_
#define TEXTBOX_HPP_

#include "Rectangle.hpp"
namespace Component
{
    namespace ui
    {
        struct TextBox
        {
            TextBox(const Rectangle &rec) : hasFocus(false),  rectangle(rec)  {}
            bool hasFocus;
            Rectangle rectangle;
        };
    }
}
#endif /* !TEXTBOX_HPP_ */
