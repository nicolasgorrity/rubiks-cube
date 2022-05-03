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

    /**
     * @class Cube
     * @brief encapsulates the cube object and functions
     */
    class Cube {
    public:
        /**
         * @brief creates a sorted cube using default color settings
         */
        Cube();

        /**
         * @brief creates a sorted cube and rotates it randomly the given number of times
         * @param nbShuffle number of times to shuffle the cube
         */
        explicit Cube(unsigned int nbShuffle);

        /**
         * @brief creates a cube with a custom front color
         * @param frontColor custom front color
         */
        explicit Cube(const Color& frontColor);

        /**
         * @brief creates a cube with a custom front color and rotates it randomly the given number of times
         * @param frontColor custom front color
         * @param nbShuffle number of times to shuffle the cube
         */
        Cube(const Color& frontColor, unsigned int nbShuffle);

        /**
         * @brief creates a cube with custom front and top colors
         * @param frontColor custom front color
         * @param topColor custom top color
         */
        Cube(const Color& frontColor, const Color& topColor);

        /**
         * @brief creates a cube with custom front and top colors and rotates it randomly the given number of times
         * @param frontColor custom front color
         * @param topColor custom top color
         * @param nbShuffle number of times to shuffle the cube
         */
        Cube(const Color& frontColor, const Color& topColor, unsigned int nbShuffle);

        ~Cube() = default;

        /**
         * @brief returns whether the cube is sorted
         * @return true if the cube is sorted, false otherwise
         */
        bool isSorted() const;

        /**
         * @brief randomly shuffles the cube the given number of times
         * @param nbShuffles number of times to shuffle the cube
         */
        void shuffle(unsigned int nbShuffles = 20);

        /**
         * @brief rotates the given face (chosen by the color of its middle block) in the given direction
         * @param faceColor face color to rotate
         * @param rotation rotation direction
         */
        void rotate(const Color& faceColor, const Rotation& rotation);

        /**
         * @brief rotates the given face (chosen by its pose) in the given direction
         * @param facePose face pose to rotate
         * @param rotation rotation direction
         */
        void rotate(const FacePose& facePose, const Rotation& rotation);

        std::array<std::array<Color, 3>, 3> getFace(const FacePose& facePose) const;

        friend std::ostream &operator<<(std::ostream &os, const Cube &cube);

    private:
        Color frontColor_;
        Color topColor_;

        CubeState_ state_;

        RandomRotationGenerator_ rotationGenerator_;
        RandomCubeFaceGenerator_ faceGenerator_;

        /**
         * @brief resets the cube to a sorted state
         */
        void resetState();

    };

    /**
     * @brief Prints a cube representation in the ostream.
     * @param os Output stream in which to print the Color value
     * @param cube Cube to print
     * @return Reference to the processed os stream
     */
    std::ostream &operator<<(std::ostream &os, const Cube &cube);

    /**
     * @brief Prints a representation of the row of a cube face in the ostream.
     * @param os Output stream in which to print the row
     * @param row Row to print
     * @return Reference to the processed os stream
     */
    std::ostream &operator<<(std::ostream &os, const std::array<Color, 3> &row);

}