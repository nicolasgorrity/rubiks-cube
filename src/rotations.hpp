#pragma once

#include <array>
#include <ostream>

#include "random.hpp"


namespace rubiks {

    enum class Rotation : bool {
        CLOCKWISE,
        ANTICLOCKWISE
    };

    std::array<Rotation, 2> _getAllRotations();

    std::ostream &operator<<(std::ostream &os, const Rotation &rotation);

    using RandomRotationGenerator_ = RandomGenerator<Rotation, 2>;

}