#pragma once

#include <utility>
#include <array>
#include <map>

#include "colors.hpp"
#include "color_finder.hpp"
#include "cube_state.hpp"
#include "positions.hpp"
#include "random.hpp"
#include "rotations.hpp"
#include "types.hpp"


namespace rubiks {

    class Cube {
    public:
        Cube();
        explicit Cube(unsigned int nbShuffle);
        explicit Cube(const Color& frontColor);
        Cube(const Color& frontColor, unsigned int nbShuffle);
        Cube(const Color& frontColor, const Color& topColor);
        Cube(const Color& frontColor, const Color& topColor, unsigned int nbShuffle);

        ~Cube() = default;

        bool isSorted() const;

        void shuffle(unsigned int nbShuffles = 20);
        void rotate(const Color& faceColor, const Rotation& rotation);
        void rotate(const FacePose& facePose, const Rotation& rotation);

        std::array<std::array<Color, 3>, 3> getFace(const FacePose& facePose) const;

        friend std::ostream &operator<<(std::ostream &os, const Cube &cube);

    private:
        Color frontColor_;
        Color topColor_;

        CubeState_ state_;

        RandomRotationGenerator_ rotationGenerator_;
        RandomCubeFaceGenerator_ faceGenerator_;

        void resetState();

    };

    std::ostream &operator<<(std::ostream &os, const Cube &cube);
    std::ostream &operator<<(std::ostream &os, const std::array<Color, 3> &row);
}