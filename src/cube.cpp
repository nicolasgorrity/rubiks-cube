#include <iostream>
#include "cube.hpp"


namespace rubiks {

    Cube::Cube()
            : Cube(0) {}

    Cube::Cube(unsigned int nbShuffle)
            : Cube(Color::RED, nbShuffle) {}

    Cube::Cube(const Color &frontColor)
            : Cube(frontColor, ColorFinder::defaultTopColorFromFront(frontColor)) {}

    Cube::Cube(const Color &frontColor, unsigned int nbShuffle)
            : Cube(frontColor, ColorFinder::defaultTopColorFromFront(frontColor), nbShuffle) {}

    Cube::Cube(const Color &frontColor, const Color &topColor)
            : Cube(frontColor, topColor, 0) {}

    Cube::Cube(const Color &frontColor, const Color &topColor, unsigned int nbShuffle):
            frontColor_(frontColor),
            topColor_(topColor),
            state_(),
            rotationGenerator_(_getAllRotations()),
            faceGenerator_(_getAllFacePoses()) {
        resetState();
        if (topColor_ == ColorFinder::getOpposite(frontColor_)) {
            topColor_ = ColorFinder::defaultTopColorFromFront(frontColor_);
            std::cerr << "[Cube] ERROR: tried to create a cube with front color " << frontColor_
                      << " and top color " << topColor << " whereas those colors must be opposite" << std::endl
                      << "[Cube] Using default top color " << topColor_ << " instead" << std::endl;
        }
        if (nbShuffle) shuffle(nbShuffle);
    }

    bool Cube::isSorted() const {
        return state_.isSorted();
    }

    void Cube::resetState() {
        state_.resetBlocks();
    }

    void Cube::shuffle(unsigned int nbShuffles) {
        for (unsigned int i=0; i<nbShuffles; ++i) {
            // Pick a random face
            FacePose facePose = faceGenerator_.draw();
            // Pick a random rotation direction
            Rotation rotation = rotationGenerator_.draw();
            // Rotate
            rotate(facePose, rotation);
        }
    }

    void Cube::rotate(const FacePose &facePose, const Rotation &rotation) {
        const Color rotatingFaceColor = ColorFinder::getFromFrontAndTop(frontColor_, topColor_, facePose);
        rotate(rotatingFaceColor, rotation);
    }

    void Cube::rotate(const Color &faceColor, const Rotation &rotation) {
        if (faceColor == Color::UNDEFINED)
            return;
        std::cout << "Rotating face of color " << faceColor << " " << rotation << std::endl;
        state_.rotateFace(faceColor, rotation);
    }

    std::array<std::array<Color, 3>, 3> Cube::getFace(const FacePose &facePose) const {
        const Color frontFaceColor = ColorFinder::getFromFrontAndTop(frontColor_, topColor_, facePose);
        Color topFaceColor;
        switch (facePose) {
            case FacePose::FRONT:
            case FacePose::LEFT:
            case FacePose::RIGHT:
                topFaceColor = topColor_;
                break;
            case FacePose::BACK:
                topFaceColor = ColorFinder::getOpposite(topColor_);
                break;
            case FacePose::TOP:
                topFaceColor = ColorFinder::getOpposite(frontColor_);
                break;
            case FacePose::BOTTOM:
                topFaceColor = frontColor_;
                break;
        }

        const Color bottomFaceColor = ColorFinder::getOpposite(topFaceColor);
        const Color rightFaceColor = ColorFinder::getFromFrontAndTop(frontFaceColor, topFaceColor, FacePose::RIGHT);
        const Color leftFaceColor = ColorFinder::getOpposite(rightFaceColor);

        std::map<Color, Color*> edgesColorsMap;
        std::array<Color, CubeState_::EDGES_PER_FACE> edgesColors{};
        unsigned int edgeCpt = 0;
        for (const auto edgePtr: state_.getFaceEdges(frontFaceColor)) {
            for (const auto& blockFace: edgePtr->blockColors()) {
                if (blockFace.second == frontFaceColor) {
                    edgesColors[edgeCpt] = blockFace.first;
                }
                else {
                    edgesColorsMap[blockFace.second] = edgesColors.data() + edgeCpt;
                }
            }
            ++edgeCpt;
        }
        const Color topBlockColor = *edgesColorsMap[topFaceColor];
        const Color leftBlockColor = *edgesColorsMap[leftFaceColor];
        const Color rightBlockColor = *edgesColorsMap[rightFaceColor];
        const Color bottomBlockColor = *edgesColorsMap[bottomFaceColor];

        std::map<HashColorArray, Color> cornersColorsMap;
        std::array<Color, CubeState_::CORNERS_PER_FACE> cornersColors{};
        for (const auto cornerPtr: state_.getFaceCorners(frontFaceColor)) {
            std::array<Color, 2> otherColors{};
            unsigned int otherColorCpt = 0;
            Color colorOnThisFace = Color::UNDEFINED;
            for (const auto& blockFace: cornerPtr->blockColors()) {
                if (blockFace.second == frontFaceColor) {
                    colorOnThisFace = blockFace.first;
                }
                else {
                    otherColors[otherColorCpt++] = blockFace.second;
                }
            }
            const HashColorArray adjacentFacesHash = hashColors(otherColors.begin(), otherColors.end());
            cornersColorsMap[adjacentFacesHash] = colorOnThisFace;
        }
        std::array<Color, 2> topLeftFaceColors = {topFaceColor, leftFaceColor};
        const Color topLeftBlockColor = cornersColorsMap[hashColors(topLeftFaceColors)];
        std::array<Color, 2> topRightFaceColors = {topFaceColor, rightFaceColor};
        const Color topRightBlockColor = cornersColorsMap[hashColors(topRightFaceColors)];
        std::array<Color, 2> bottomLeftFaceColors = {bottomFaceColor, leftFaceColor};
        const Color bottomLeftBlockColor = cornersColorsMap[hashColors(bottomLeftFaceColors)];
        std::array<Color, 2> bottomRightFaceColors = {bottomFaceColor, rightFaceColor};
        const Color bottomRightBlockColor = cornersColorsMap[hashColors(bottomRightFaceColors)];

        return {
                std::array<Color, 3>{topLeftBlockColor, topBlockColor, topRightBlockColor},
                std::array<Color, 3>{leftBlockColor, frontFaceColor, rightBlockColor},
                std::array<Color, 3>{bottomLeftBlockColor, bottomBlockColor, bottomRightBlockColor}
        };
    }

    std::ostream &operator<<(std::ostream &os, const Cube &cube) {
        // Print top face
        for (const auto& row: cube.getFace(FacePose::TOP)) {
            os << "    " << row << std::endl;
        }
        os << std::endl;

        // Print left face, front face and right face next to each other
        const auto leftFace = cube.getFace(FacePose::LEFT);
        const auto frontFace = cube.getFace(FacePose::FRONT);
        const auto rightFace = cube.getFace(FacePose::RIGHT);
        for (unsigned int i=0; i<3; ++i) {
            os << leftFace[i] << ' ' << frontFace[i] << ' ' << rightFace[i] << std::endl;
        }
        os << std::endl;

        // Print bottom face
        for (const auto& row: cube.getFace(FacePose::BOTTOM)) {
            os << "    " << row << std::endl;
        }
        os << std::endl;

        // Print back face
        for (const auto& row: cube.getFace(FacePose::BACK)) {
            os << "    " << row << std::endl;
        }
        os << std::endl;

        os << "Cube is " << (cube.isSorted() ? "" : "not ") << "sorted" << std::endl;
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const std::array<Color, 3> &row) {
        for (const Color& color: row) {
            os << color;
        }
        return os;
    }

}