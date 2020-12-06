#pragma once

#include <algorithm>
#include <ostream>
#include <string>
#include <vector>


namespace rubiks {

    /**
     * @enum Color
     * @brief Color of a cube face
     */
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

    /**
     * @brief Hashes a color.
     * @details Computes the hash value of the input color.
     * @param color Color to hash
     * @return Hash value of input color
     */
    HashColor hashColor(const Color& color);

    /**
     * @brief Hashes an ensemble of colors.
     * @details Computes the hash value of each color and sorts the resulting list.
     * @param first Iterator pointing to the first element of the iterable
     * @param last Iterator pointing to the <i>past-the-end</i> element of the iterable
     * @return Hash value of input colors
     */
    template <class Iterator>
    HashColorArray hashColors(const Iterator& first, const Iterator& last) {
        HashColorArray hashValue;
        for (auto it = first; it != last; ++it) {
            hashValue += hashColor(*it);
        }
        std::sort(hashValue.begin(), hashValue.end());
        return hashValue;
    }

    /**
     * @brief Hashes an ensemble of colors.
     * @details Computes the hash value of each color and sorts the resulting list.
     * @param array Iterable of colors
     * @return Hash value of input colors
     */
    template <class Iterable>
    HashColorArray hashColors(const Iterable& array) {
        return hashColors(array.begin(), array.end());
    }

    /**
     * @brief Prints a Color value in the ostream.
     * @details Adds a string representation of the input Color value to the ostream object.
     * @param os Output stream in which to print the Color value
     * @param color Element to print
     * @return Reference to the modified os stream
     */
    std::ostream &operator<<(std::ostream &os, const Color &color);

}