#pragma once

#include <utility>
#include <map>

#include "colors.hpp"
#include "positions.hpp"


namespace rubiks {

    /**
     * @class ColorFinder
     * @brief Gathers static methods to help with colors logics
     */
    class ColorFinder {
        /**
         * @brief Access to private members granted to CubeState_ class
         * @relates CubeState_
         */
        friend class CubeState_;

        static const unsigned short NB_FACES = 6;  /*!< constant number of faces on a CubeState_ */

        /**
         * @brief alias for a map from a Color to another
         */
        using One2OneColorMap_ = std::map<Color, Color>;

        /**
         * @brief alias for a map from a pair of Colors to a Color
         */
        using Two2OneColorMap_ = std::map<std::pair<Color, Color>, Color>;

    public:
        ColorFinder() = delete;

        /**
         * @brief returns a default Color to be drawn on top of the input Color
         * @param frontColor Color on the front face of the CubeState_
         * @return default top Color
         */
        static Color defaultTopColorFromFront(const Color& frontColor);

        /**
         * @brief finds the Color on a given face of the CubeState_ given the front and top Colors
         * @param frontColor Color on the front of the CubeState_
         * @param topColor Color on the top of the CubeState_
         * @param facePose relative face location on which to find the output Color
         * @return Color located at the relative facePose position to the input front and top Colors
         */
        static Color getFromFrontAndTop(const Color &frontColor, const Color &topColor, const FacePose& facePose);

        /**
         * @brief finds the Color on the opposite face of the input Color
         * @param color Color from which to find the opposite
         * @return Color located at the opposite position to the input Color
         */
        static Color getOpposite(const Color &color);

    private:
        /**
         * @brief mapping of each Color to its opposite on a CubeState_
         */
        static const One2OneColorMap_ oppositeMap_;

        /**
         * @brief mapping of each pair of adjacent Colors to the Color on their right
         */
        static const Two2OneColorMap_ rightFromFrontAndTopMap_;

        /**
         * @brief initializes ColorFinder::oppositeMap_
         * @return value of ColorFinder::oppositeMap_
         */
        static One2OneColorMap_ initializeOppositeMap() noexcept;

        /**
         * @brief initializes ColorFinder::rightFromFrontAndTopMap_
         * @return value of ColorFinder::rightFromFrontAndTopMap_
         */
        static Two2OneColorMap_ initializeRightFromFrontAndTopMap() noexcept;

    };

}
