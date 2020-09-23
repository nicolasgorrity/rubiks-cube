#pragma once

#include <algorithm>
#include <map>
#include <string>
#include <utility>

#include "colors.hpp"

namespace rubiks {

    template<std::size_t nbFaces>
    class Block {
    public:
        Block() = default;
        explicit Block(std::array<Color, nbFaces>&& colors);
        Block(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors);
        ~Block() = default;

        bool isWellPlaced() const;

        void initColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors);
        void initColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors);
        void setColorPlace(const Color& color, const Color& faceColor, bool doHash=true);
        void setColorsPlaces(std::array<Color, nbFaces>&& blockFacesColors, std::array<Color, nbFaces>&& cubeFacesColors);

        const std::map<Color, Color>& blockColors() const;
        const HashColorArray& hashValue() const;

    private:
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