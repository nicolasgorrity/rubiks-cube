#include <iostream>
#include <vector>

#include "cube_state.hpp"


namespace rubiks {

    CubeState_::CubeState_()
            : facesCorners_(), facesEdges_() {
        resetBlocks();
    }

    bool CubeState_::isSorted() const {
        for (const Edge& edge: edges_) {
            if (!edge.isWellPlaced()) return false;
        }
        for (const Corner& corner: corners_) {
            if (!corner.isWellPlaced()) return false;
        }
        return true;
    }

    const EdgePtrArray_<CubeState_::EDGES_PER_FACE>& CubeState_::getFaceEdges(const Color &faceColor) const {
        return facesEdges_.at(faceColor);
    }

    const CornerPtrArray_<CubeState_::CORNERS_PER_FACE>& CubeState_::getFaceCorners(const Color& faceColor) const {
        return facesCorners_.at(faceColor);
    }

    void CubeState_::resetBlocks() {
        Color anyFrontColor = Color::RED;
        Color anyTopColor = Color::BLUE;
        Color backColor = ColorFinder::getOpposite(anyFrontColor);
        Color bottomColor = ColorFinder::getOpposite(anyTopColor);
        Color rightColor = ColorFinder::getFromFrontAndTop(anyFrontColor, anyTopColor, FacePose::RIGHT);
        Color leftColor = ColorFinder::getOpposite(rightColor);

        std::array<Color, NB_FACES - 2> lateralOrderedColors = {anyTopColor, rightColor, bottomColor, leftColor};

        std::map<Color, unsigned short> edge_ptr_counters = {
                {anyFrontColor, 0},
                {anyTopColor,   0},
                {backColor,     0},
                {bottomColor,   0},
                {rightColor,    0},
                {leftColor,     0},
        };
        std::map<Color, unsigned short> corner_ptr_counters(edge_ptr_counters);

        // Initialize corners and front & back edges
        unsigned short edgeCpt = 0;
        unsigned short cornerCpt = 0;
        for (const Color& frontalColor: {anyFrontColor, backColor}) {
            for (unsigned short i = 0; i < NB_FACES - 2; ++i) {
                const Color& adjacentColor1 = lateralOrderedColors[i];
                const Color& adjacentColor2 = lateralOrderedColors[(i + 1) % (NB_FACES - 2)];
                // Initialize edge colors
                unsigned short& frontColorEdgeCnt = edge_ptr_counters[frontalColor];
                unsigned short& adjacentColor1EdgeCnt = edge_ptr_counters[adjacentColor1];
                initializeEdge(edgeCpt++, {frontalColor, adjacentColor1},
                        {frontColorEdgeCnt++, adjacentColor1EdgeCnt++});
                // Initialize corner colors
                unsigned short& frontColorCornerCnt = corner_ptr_counters[frontalColor];
                unsigned short& adjacentColor1CornerCnt = corner_ptr_counters[adjacentColor1];
                unsigned short& adjacentColor2CornerCnt = corner_ptr_counters[adjacentColor2];
                initializeCorner(cornerCpt++, {frontalColor, adjacentColor1, adjacentColor2},
                        {frontColorCornerCnt++, adjacentColor1CornerCnt++, adjacentColor2CornerCnt++});
            }
        }

        // Initialize middle edges
        for (unsigned short i = 0; i < NB_FACES - 2; ++i) {
            const Color& adjacentColor1 = lateralOrderedColors[i];
            const Color& adjacentColor2 = lateralOrderedColors[(i + 1) % (NB_FACES - 2)];
            unsigned short& adjacentColor1EdgeCnt = edge_ptr_counters[adjacentColor1];
            unsigned short& adjacentColor2EdgeCnt = edge_ptr_counters[adjacentColor2];
            initializeEdge(edgeCpt++, {adjacentColor1, adjacentColor2},
                    {adjacentColor1EdgeCnt++, adjacentColor2EdgeCnt++});
        }

    }

    void CubeState_::initializeEdge(unsigned short blockIdx, std::array<Color, 2> &&colors,
                                    std::array<unsigned short, 2>&& ptrIdxList) {
        if (blockIdx >= edges_.size()) {
            std::cerr << "[CubeState_] WARNING: Attempt to initialize edge at index " << blockIdx
                      << "which is not in the CubeState_::edges_ boundaries [0, " << edges_.size() << "]"
                      << std::endl << "[CubeState_] Ignoring edge initialization" << std::endl;
            return;
        }

        for (const std::size_t ptrIdx: ptrIdxList) {
            if (ptrIdx >= facesEdges_.size()) {
                std::cerr << "[CubeState_] WARNING: Attempt to initialize edge pointer at index " << ptrIdx
                          << "which is not in CubeState_::facesEdges_ boundaries [0, " << facesEdges_.size() << "]"
                          << std::endl << "[CubeState_] Ignoring edge pointer initialization" << std::endl;
                return;
            }
        }

        if (std::find(colors.begin(), colors.end(), Color::UNDEFINED) != colors.end()) {
            std::cerr << "[CubeState_] WARNING: Attempt to initialize an edge with the Color "
                      << "\"Color::UNDEFINED\" which is not supported in CubeState_ colors."
                      << std::endl << "[CubeState_] Ignoring edge pointer initialization" << std::endl;
            return;
        }

        // Initialize edge colors
        Edge* edgePtr = edges_.data() + blockIdx;
        edgePtr->initColorsPlaces(std::forward<std::array<Color, 2>>(colors));

        // Associate this edge pointer to both related cube faces (distinguished by their center color)
        for (std::size_t i=0; i<2; ++i) {
            facesEdges_[colors[i]][ptrIdxList[i]] = edges_.data() + blockIdx;
        }
    }

    void CubeState_::initializeCorner(unsigned short blockIdx, std::array<Color, 3> &&colors,
                                      std::array<unsigned short, 3>&& ptrIdxList) {
        if (blockIdx >= corners_.size()) {
            std::cerr << "[CubeState_] WARNING: Attempt to initialize corner at index " << blockIdx
                      << "which is not in the CubeState_::corners_ boundaries [0, " << corners_.size() << "]"
                      << std::endl << "[CubeState_] Ignoring corner initialization" << std::endl;
            return;
        }

        for (const std::size_t ptrIdx: ptrIdxList) {
            if (ptrIdx >= facesCorners_.size()) {
                std::cerr << "[CubeState_] WARNING: Attempt to initialize corner pointer at index " << ptrIdx
                          << "which is not in CubeState_::facesCorners_ boundaries [0, " << facesCorners_.size() << "]"
                          << std::endl << "[CubeState_] Ignoring corner pointer initialization" << std::endl;
                return;
            }
        }

        if (std::find(colors.begin(), colors.end(), Color::UNDEFINED) != colors.end()) {
            std::cerr << "[CubeState_] WARNING: Attempt to initialize a corner with the Color "
                      << "\"Color::UNDEFINED\" which is not supported in CubeState_ colors."
                      << std::endl << "[CubeState_] Ignoring corner pointer initialization" << std::endl;
            return;
        }

        // Initialize corner colors
        Corner* cornerPtr = corners_.data() + blockIdx;
        cornerPtr->initColorsPlaces(std::forward<std::array<Color, 3>>(colors));

        // Associate this corner pointer to both related cube faces (distinguished by their center color)
        for (std::size_t i=0; i<3; ++i) {
            facesCorners_[colors[i]][ptrIdxList[i]] = corners_.data() + blockIdx;
        }
    }

    void CubeState_::rotateFace(const Color &faceColor, const Rotation& rotation) {
        if (faceColor == Color::UNDEFINED) {
            std::cerr << "[CubeState_] WARNING: Attempt to rotate a face of color "
                      << "\"Color::UNDEFINED\" which is not a face color of CubeState_."
                      << std::endl << "[CubeState_] Ignoring face rotation" << std::endl;
            return;
        }
        CornerPtrArray_<CORNERS_PER_FACE> cornersList = facesCorners_[faceColor];
        EdgePtrArray_<EDGES_PER_FACE> edgesList = facesEdges_[faceColor];

        // The relative positions to find successive colors changes according to the direction
        FacePose nextFacePose = FacePose::RIGHT;
        if (rotation == Rotation::ANTICLOCKWISE) nextFacePose = FacePose::LEFT;

        // Get the four adjacent colors given this front color
        Color topColor = ColorFinder::defaultTopColorFromFront(faceColor);
        Color nextAdjacentColor = ColorFinder::getFromFrontAndTop(faceColor, topColor, nextFacePose);
        Color bottomColor = ColorFinder::getOpposite(topColor);
        Color lastAdjacentColor = ColorFinder::getOpposite(nextAdjacentColor);

        // Maps to associate pointers with their previous and new faces
        std::map<Color, Edge*> oldEdgeFace, newEdgeFace;

        // Update edges faces colors locations
        for (Edge* edgePtr: edgesList) {
            for (const auto& edgeFace: edgePtr->blockColors()) {
                // Edge face located on front face remains on front face
                if (edgeFace.second != faceColor) {
                    // Store old cube face of this edge face
                    oldEdgeFace[edgeFace.second] = edgePtr;
                    // Compute the new cube face of this edge face and update it
                    Color newFaceColor = ColorFinder::getFromFrontAndTop(faceColor, edgeFace.second, nextFacePose);
                    edgePtr->setColorPlace(edgeFace.first, newFaceColor);
                    // Store this new cube face
                    newEdgeFace[newFaceColor] = edgePtr;
                }
            }
        }

        // Update faces arrays of Edges*
        for (const Color& adjacentFaceColor: {topColor, nextAdjacentColor, bottomColor, lastAdjacentColor}) {
            // Get edges of an adjacent face
            auto& faceEdges = facesEdges_[adjacentFaceColor];
            // Get pointer of the edge that moved onto another cube face
            Edge* edgeToReplace = oldEdgeFace[adjacentFaceColor];
            auto edgePtrIt = std::find(faceEdges.begin(), faceEdges.end(), edgeToReplace);
            if (edgePtrIt == faceEdges.end()) {
                std::cerr << "[CubeState_] ERROR: Did not find edge with pointer " << edgeToReplace
                          << " in array of Edge* of the cube face with color " << adjacentFaceColor << std::endl
                          << "[CubeState_] Aborting rotation, cube structure correctness may be affected" << std::endl;
                return;
            }
            // This pointer becomes the one of the edge that just moved onto this cube face
            *edgePtrIt = newEdgeFace[adjacentFaceColor];
        }

        // Maps to associate pointers with their previous and new faces
        std::map<Color, std::vector<Corner*>> oldCornerFace, newCornerFace;

        // Update corners faces colors locations
        for (Corner* cornerPtr: cornersList) {
            for (const auto& cornerFace: cornerPtr->blockColors()) {
                HashColorArray cornerHash = cornerPtr->hashValue();
                // Corner face located on front face remains on front face
                if (cornerFace.second != faceColor) {
                    // Store old cube face of this corner face as a potentially left face
                    oldCornerFace[cornerFace.second].push_back(cornerPtr);
                    // Compute the new cube face of this edge face and update it
                    Color newFaceColor = ColorFinder::getFromFrontAndTop(faceColor, cornerFace.second, nextFacePose);
                    cornerPtr->setColorPlace(cornerFace.first, newFaceColor);
                    // This corner leaves `oldFaceColor` face only if its new cube face is opposite to the other
                    // corner old face
                    newCornerFace[newFaceColor].push_back(cornerPtr);
                }
            }
        }

        // Update faces arrays of Corner*
        for (const Color &adjacentFaceColor: {topColor, nextAdjacentColor, bottomColor, lastAdjacentColor}) {
            // Get moving corners for this adjacent face
            std::vector<Corner*> &oldCorners = oldCornerFace[adjacentFaceColor];
            std::vector<Corner*> &newCorners = newCornerFace[adjacentFaceColor];
            // Search corners to replace for this face
            Corner *leavingCorner=nullptr, *arrivingCorner=nullptr, *commonCorner=nullptr;
            // The corner leaving the face is the one in oldCorners that is not in newCorners
            for (Corner *oldCorner: oldCorners) {
                if (std::find(newCorners.begin(), newCorners.end(), oldCorner) == newCorners.end()) {
                    leavingCorner = oldCorner;
                    break;
                }
                else commonCorner = oldCorner;
            }
            // The corner arriving in the face is the one in newCorners that is not in oldCorners
            for (Corner *newCorner: newCorners) {
                if (newCorner == commonCorner) continue;
                if (std::find(oldCorners.begin(), oldCorners.end(), newCorner) == oldCorners.end()) {
                    arrivingCorner = newCorner;
                    break;
                }
            }
            // Search leaving corner in this face corners list
            auto &faceCorners = facesCorners_[adjacentFaceColor];
            auto leavingCornerPtrIt = std::find(faceCorners.begin(), faceCorners.end(), leavingCorner);
            if (leavingCornerPtrIt == faceCorners.end()) {
                std::cerr << "[CubeState_] ERROR: Did not find corner with pointer " << leavingCorner
                          << " in array of Corner* of the cube face with color " << adjacentFaceColor << std::endl
                          << "[CubeState_] Aborting rotation, cube structure correctness may be affected" << std::endl;
                return;
            }
            // This pointer becomes the arriving corner
            *leavingCornerPtrIt = arrivingCorner;
        }
    }

}