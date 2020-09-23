#pragma once

#include "color_finder.hpp"
#include "rotations.hpp"
#include "types.hpp"


namespace rubiks {

    class CubeState_ {

    public:

        static const unsigned short EDGES_PER_FACE = 4;
        static const unsigned short CORNERS_PER_FACE = 4;
        static const unsigned short NB_FACES = ColorFinder::NB_FACES;
        static const unsigned short TOTAL_EDGES = 12;
        static const unsigned short TOTAL_CORNERS = 8;

        CubeState_();
        ~CubeState_() = default;

        bool isSorted() const;

        const EdgePtrArray_<EDGES_PER_FACE>& getFaceEdges(const Color& faceColor) const;
        const CornerPtrArray_<CORNERS_PER_FACE>& getFaceCorners(const Color& faceColor) const;

        void resetBlocks();
        void rotateFace(const Color& color, const Rotation& rotation);

    private:
        EnumArray_<Color, CornerPtrArray_<CORNERS_PER_FACE>, NB_FACES> facesCorners_;
        EnumArray_<Color, EdgePtrArray_<EDGES_PER_FACE>, NB_FACES> facesEdges_;
        std::array<Edge, TOTAL_EDGES> edges_;
        std::array<Corner, TOTAL_CORNERS> corners_;


        void initializeEdge(unsigned short blockIdx, std::array<Color, 2>&& colors,
                            std::array<unsigned short, 2>&& ptrIdxList);

        void initializeCorner(unsigned short blockIdx, std::array<Color, 3>&& colors,
                              std::array<unsigned short, 3>&& ptrIdxList);

    };

}