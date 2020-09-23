#include "rotations.hpp"


namespace rubiks {

    std::ostream &operator<<(std::ostream &os, const Rotation &rotation) {
        switch (rotation) {
            case Rotation::CLOCKWISE:
                os << "Clockwise";
                break;
            case Rotation::ANTICLOCKWISE:
                os << "Anticlockwise";
                break;
        }
        return os;
    }

    std::array<Rotation, 2> _getAllRotations() {
        return {Rotation::CLOCKWISE, Rotation::ANTICLOCKWISE};
    }

}