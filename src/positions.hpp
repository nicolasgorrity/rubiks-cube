#pragma once

#include <array>
#include <ostream>

#include "random.hpp"


namespace rubiks {

    /**
     * @enum FacePose
     * @brief The face location on the cube
     */
    enum class FacePose : unsigned short {
        FRONT,
        BACK,
        RIGHT,
        LEFT,
        TOP,
        BOTTOM
    };

    /**
     * @brief Returns all possible values of FacePose.
     * @details Returns an array of all possible values of a FacePose.
     * @return Array of FacePoses
     */
    std::array<FacePose, 6> _getAllFacePoses();

    /**
     * @brief Prints a FacePose value in the ostream.
     * @details Adds a string representation of the input FacePose value to the ostream object.
     * @param os Output stream in which to print the FacePose value
     * @param facePose Element to print
     * @return Reference to the modified os stream
     */
    std::ostream &operator<<(std::ostream &os, const FacePose &facePose);

    /**
     * @brief Alias for a RandomGenerator of FacePoses
     */
    using RandomCubeFaceGenerator_ = RandomGenerator<FacePose, 6>;

}