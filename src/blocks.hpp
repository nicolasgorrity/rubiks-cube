#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <utility>

#include "colors.hpp"


namespace rubiks {

    /**
     * @class Block<nbFaces>
     * @brief Block of a Cube
     * @tparam nbFaces number of faces on the block
     */
    template<std::size_t nbFaces>
    class Block {
    public:
        /**
         * @brief Builds a non-initialized block
         */
        Block() = default;

        /**
         * @brief Builds a block with given colors, mapping them to the corresponding cube face
         * @param colors block colors
         */
        explicit Block(std::array<Color, nbFaces>&& colors);

        /**
         * @brief Builds a block with given block colors mapped to the given cube faces colors
         * @param blockFacesColors colors of the block faces
         * @param cubeFacesColors colors of the cube faces to be mapped to the block faces
         */
        Block(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors);

        ~Block() = default;

        /**
         * @brief determines if all the colors of the block are placed on the cube faces with matching colors
         * @return true if the block is correctly placed, false otherwise
         */
        bool isWellPlaced() const;

        /**
         * @brief Initializes a block with given colors, mapping them to the corresponding cube face
         * @param colors block colors
         */
        void initColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors);

        /**
         * @brief initializes a block with given block colors mapped to the given cube faces colors
         * @param blockFacesColors colors of the block faces
         * @param cubeFacesColors colors of the cube faces to be mapped to the block faces
         */
        void initColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors);

        /**
         * @brief Maps the given cube face color to the given block face color
         * @param color block face color
         * @param faceColor cube face color
         * @param doHash whether to re-compute the hash value of the block after this operation (defaults to true)
         */
        void setColorPlace(const Color& color, const Color& faceColor, bool doHash=true);

        /**
         * @brief Maps the given cube faces color to the given block faces colors, then recomputes the block' hash value
         * @param color block faces colors
         * @param faceColor cube faces colors
         */
        void setColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors);

        const std::map<Color, Color>& blockColors() const;
        const HashColorArray& hashValue() const;

    private:
        /**
         * @brief Computes the internal hash value of the block
         */
        void hash();

        std::map<Color, Color> blockColors_;
        HashColorArray hashValue_;
    };

    template<std::size_t nbFaces>
    Block<nbFaces>::Block(std::array<Color, nbFaces> &&colors) {
        initColorPlaces(colors);
    }

    template<std::size_t nbFaces>
    Block<nbFaces>::Block(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors)
            : blockColors_() {
        initColorsPlaces(blockFacesColors, cubeFacesColors);
    }

    template<std::size_t nbFaces>
    void Block<nbFaces>::initColorsPlaces(std::array<Color, nbFaces> &&blockFacesColors) {
        initColorsPlaces(std::forward<std::array<Color, nbFaces>>(blockFacesColors),
                         std::forward<std::array<Color, nbFaces>>(blockFacesColors));
    }

    template<std::size_t nbFaces>
    void Block<nbFaces>::initColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors,
                                          std::array<Color, nbFaces>&& cubeFacesColors) {
        for (std::size_t i=0; i<nbFaces; ++i) {
            blockColors_[blockFacesColors[i]] = cubeFacesColors[i];
        }
        hash();
    }

    template<std::size_t nbFaces>
    void Block<nbFaces>::setColorPlace(const Color &color, const Color &faceColor, bool doHash) {
        blockColors_.at(color) = faceColor;
        if (doHash) hash();
    }

    template<std::size_t nbFaces>
    void Block<nbFaces>::setColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors,
                                         std::array<Color, nbFaces>&& cubeFacesColors) {
        for (std::size_t i=0; i<nbFaces; ++i) {
            setColorPlace(blockFacesColors[i], cubeFacesColors[i], false);
        }
        hash();
    }

    template<std::size_t nbFaces>
    void Block<nbFaces>::hash() {
        hashValue_ = "";

        for (const auto& blockColor : blockColors_) {
            hashValue_ += hashColor(blockColor.first);
        }

        std::sort(hashValue_.begin(), hashValue_.end());
    }

    template<std::size_t nbFaces>
    const HashColorArray& Block<nbFaces>::hashValue() const {
        return hashValue_;
    }

    template<std::size_t nbFaces>
    const std::map<Color, Color>& Block<nbFaces>::blockColors() const {
        return blockColors_;
    }

    template<std::size_t nbFaces>
    bool Block<nbFaces>::isWellPlaced() const {
        for (const auto& blockFace: blockColors_) {
            if (blockFace.first != blockFace.second) return false;
        }
        return true;
    }

    class Corner : public Block<3> {};

    class Edge : public Block<2> {};

}