#pragma once

#include <array>
#include <ostream>

#include "random.hpp"


namespace rubiks {

    /**
     * @enum Rotation
     * @brief Type of rotation
     */
    enum class Rotation : bool {
        CLOCKWISE,
        ANTICLOCKWISE
    };

    /**
     * @brief Returns all possible values of Rotation.
     * @details Returns an array of all possible values of a Rotation.
     * @return Array of Rotations
     */
    std::array<Rotation, 2> _getAllRotations();

    /**
     * @brief Prints a Rotation value in the ostream.
     * @details Adds a string representation of the input Rotation value to the ostream object.
     * @param os Output stream in which to print the Rotation value
     * @param rotation Element to print
     * @return Reference to the modified os stream
     */
    std::ostream &operator<<(std::ostream &os, const Rotation &rotation);

    /**
     * @brief Alias for a RandomGenerator of Rotations
     */
    using RandomRotationGenerator_ = RandomGenerator<Rotation, 2>;

}