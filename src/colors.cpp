#include "colors.hpp"


namespace rubiks {

    std::ostream &operator<<(std::ostream &os, const Color &color) {
        os << hashColor(color);
        return os;
    }

    char hashColor(const Color& color) {
        char result;

        switch (color) {
            case Color::RED:
                result = 'R';
                break;
            case Color::GREEN:
                result = 'G';
                break;
            case Color::BLUE:
                result = 'B';
                break;
            case Color::YELLOW:
                result = 'Y';
                break;
            case Color::ORANGE:
                result = 'O';
                break;
            case Color::WHITE:
                result = 'W';
                break;
            case Color::UNDEFINED:
                result = '?';
                break;
        }

        return result;
    }

}