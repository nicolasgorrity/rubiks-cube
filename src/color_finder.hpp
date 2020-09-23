#pragma once

#include <utility>
#include <map>

#include "colors.hpp"
#include "positions.hpp"

namespace rubiks {

    class ColorFinder {
        friend class CubeState_;
        static const unsigned short NB_FACES = 6;

        using One2OneColorMap_ = std::map<Color, Color>;
        using Two2OneColorMap_ = std::map<std::pair<Color, Color>, Color>;

    public:
        static Color defaultTopColorFromFront(const Color& frontColor);
        static Color getFromFrontAndTop(const Color &frontColor, const Color &topColor, const FacePose& facePose);
        static Color getOpposite(const Color &color);

    private:
        ColorFinder() = default;

        static const One2OneColorMap_ oppositeMap_;
        static const Two2OneColorMap_ rightFromFrontAndTopMap_;

        static One2OneColorMap_ initializeOppositeMap() noexcept;
        static Two2OneColorMap_ initializeRightFromFrontAndTopMap() noexcept;

    };

}
