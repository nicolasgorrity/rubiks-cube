#pragma once

#include "color_finder.hpp"
#include "rotations.hpp"
#include "types.hpp"


namespace rubiks {

    /**
     * @class CubeState_
     * @brief Encodes the state (configuration of all blocks) of a cube
     */
    class CubeState_ {

    public:

        static const unsigned short EDGES_PER_FACE = 4;
        static const unsigned short CORNERS_PER_FACE = 4;
        static const unsigned short NB_FACES = ColorFinder::NB_FACES;
        static const unsigned short TOTAL_EDGES = 12;
        static const unsigned short TOTAL_CORNERS = 8;

        CubeState_();
        ~CubeState_() = default;

        /**
         * @brief returns whether the cube is sorted (all blocks are the same color on each face) or not
         * @return True if the cube is sorted, False otherwise
         */
        bool isSorted() const;

        /**
         * @brief retrieves the list of edges that are adjacent to a face
         * @param faceColor color of the face (middle block)
         * @return list of the adjacent edges
         */
        const EdgePtrArray_<EDGES_PER_FACE>& getFaceEdges(const Color& faceColor) const;

        /**
         * @brief retrieves the list of corners that are adjacent to a face
         * @param faceColor color of the face (middle block)
         * @return list of the adjacent corners
         */
        const CornerPtrArray_<CORNERS_PER_FACE>& getFaceCorners(const Color& faceColor) const;

        /**
         * @brief Resets the cube to a sorted state
         */
        void resetBlocks();

        /**
         * @brief rotates given cube face in a given direction
         * @param color color of the face to rotate (designates the color of the middle block)
         * @param rotation rotation direction
         */
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