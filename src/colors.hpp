#pragma once

#include <algorithm>
#include <ostream>
#include <string>
#include <vector>


namespace rubiks {

    enum class Color : unsigned short {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        ORANGE,
        WHITE,
        UNDEFINED
    };

    using HashColor = char;
    using HashColorArray = std::string;

    HashColor hashColor(const Color& color);

    template <class Iterator>
    HashColorArray hashColors(const Iterator& first, const Iterator& last) {
        HashColorArray hashValue;
        for (auto it = first; it != last; ++it) {
            hashValue += hashColor(*it);
        }
        std::sort(hashValue.begin(), hashValue.end());
        return hashValue;
    }

    template <class Iterable>
    HashColorArray hashColors(const Iterable& array) {
        return hashColors(array.begin(), array.end());
    }

    std::ostream &operator<<(std::ostream &os, const Color &color);

}