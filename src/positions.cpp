#include "positions.hpp"


namespace rubiks {

    std::array<FacePose, 6> _getAllFacePoses() {
        return {FacePose::FRONT, FacePose::TOP, FacePose::RIGHT,
                FacePose::LEFT, FacePose::BACK, FacePose::BOTTOM};
    }

    std::ostream &operator<<(std::ostream &os, const FacePose &facePose) {
        switch (facePose) {
            case FacePose::FRONT:
                os << "Front";
                break;
            case FacePose::BACK:
                os << "Back";
                break;
            case FacePose::RIGHT:
                os << "Right";
                break;
            case FacePose::LEFT:
                os << "Left";
                break;
            case FacePose::TOP:
                os << "Top";
                break;
            case FacePose::BOTTOM:
                os << "Bottom";
                break;
        }
        return os;
    }

}