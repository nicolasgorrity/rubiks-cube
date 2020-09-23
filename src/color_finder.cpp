#include "color_finder.hpp"

namespace rubiks {

    ColorFinder::One2OneColorMap_ ColorFinder::initializeOppositeMap() noexcept {
        return {
                {Color::RED,    Color::ORANGE},
                {Color::ORANGE, Color::RED},
                {Color::BLUE,   Color::GREEN},
                {Color::GREEN,  Color::BLUE},
                {Color::YELLOW, Color::WHITE},
                {Color::WHITE,  Color::YELLOW},
        };
    }
    const ColorFinder::One2OneColorMap_ ColorFinder::oppositeMap_ = ColorFinder::initializeOppositeMap();

    ColorFinder::Two2OneColorMap_ ColorFinder::initializeRightFromFrontAndTopMap() noexcept {
        ColorFinder::Two2OneColorMap_ map;
        // Given a front and top color, it remains only a binary constraint: which color is right and which is left
        Color front = Color::RED;
        Color top = Color::BLUE;
        Color right = Color::YELLOW;

        // From there, the rest of the cube's color layout can be deduced
        for (unsigned short i=0; i<6; ++i) {
            // Rotate the cube clockwise to vary the top face (second index)
            map[{front, top}] = right;
            map[{front, right}] = getOpposite(top);
            map[{front, getOpposite(top)}] = getOpposite(right);
            map[{front, getOpposite(right)}] = top;
            if (i != 2) {
                // Three first faces for i=0,1,2
                Color tmp = front;
                front = top;
                top = right;
                right = tmp;
            } else {
                // Three other faces for i=3,4,5
                Color tmp = top;
                top = getOpposite(right);
                right = getOpposite(tmp);
                front = getOpposite(front);
            }
        }

        return map;
    }
    const ColorFinder::Two2OneColorMap_ ColorFinder::rightFromFrontAndTopMap_ = ColorFinder::initializeRightFromFrontAndTopMap();

    Color ColorFinder::getOpposite(const Color &color) {
        if (oppositeMap_.find(color) != oppositeMap_.end()) {
            return oppositeMap_.at(color);
        }
        else return Color::UNDEFINED;
    }

    Color ColorFinder::getFromFrontAndTop(const Color &frontColor, const Color &topColor, const FacePose& facePose) {
        Color color = Color::UNDEFINED;

        switch(facePose) {
            case FacePose::FRONT:
                color = frontColor;
                break;
            case FacePose::BACK:
                color = getOpposite(frontColor);
                break;
            case FacePose::RIGHT:
                if (rightFromFrontAndTopMap_.find({frontColor, topColor}) != rightFromFrontAndTopMap_.end()) {
                    color = rightFromFrontAndTopMap_.at({frontColor, topColor});
                }
                break;
            case FacePose::LEFT:
                if (rightFromFrontAndTopMap_.find({frontColor, topColor}) != rightFromFrontAndTopMap_.end()) {
                    color = getOpposite(rightFromFrontAndTopMap_.at({frontColor, topColor}));
                }
                break;
            case FacePose::TOP:
                color = topColor;
                break;
            case FacePose::BOTTOM:
                color = getOpposite(topColor);
                break;
        }

        return color;
    }

    Color ColorFinder::defaultTopColorFromFront(const Color &frontColor) {
        Color color;

        switch (frontColor) {
            case Color::WHITE:
                color = Color::BLUE;
                break;
            case Color::YELLOW:
            case Color::BLUE:
            case Color::GREEN:
                color = Color::RED;
                break;
            case Color::RED:
                color = Color::WHITE;
                break;
            case Color::ORANGE:
                color = Color::GREEN;
                break;
            case Color::UNDEFINED:
                color = Color::UNDEFINED;
                break;
        }

        return color;
    }

}