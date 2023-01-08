/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-vincent.darnige
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <string>

namespace Component
{
    namespace ui
    {
        struct Color
        {
        public:
            Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

            Color(int r, int g, int b) : r(r), g(g), b(b), a(255) {}
            int r;
            int g;
            int b;
            int a;
        };

        struct Text
        {
        public:
            enum Style
            {
                REGULAR = 0,
                BOLD = 1,
                ITALIC = 2,
                UNDERLINED = 4,
                STRIKETHROUGH = 8
            };

            Text(const std::string &font, const std::string &text, const Color &color, int size) : _font(font), _text(text), _color(color), _size(size), _style(REGULAR) {}

            Text(const std::string &font, const std::string &text, const Color &color, int size, Style style) : _font(font), _text(text), _color(color), _size(size), _style(style) {}

            ~Text() {}
            std::string _font;
            std::string _text;
            Color _color;
            int _size;
            Style _style;
        };
    }
}
#endif /* !TEXT_HPP_ */
