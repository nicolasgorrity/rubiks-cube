#pragma once

#include "blocks.hpp"
#include "colors.hpp"


namespace rubiks {

    template<typename IndexingType, class ElementType, std::size_t N>
    class EnumArray_ : public std::array<ElementType, N> {
    public:
        ElementType &operator[](IndexingType index) {
            return std::array<ElementType, N>::operator[]((std::size_t) index);
        }

        const ElementType &operator[](IndexingType index) const {
            return std::array<ElementType, N>::operator[]((std::size_t) index);
        }

        ElementType &at(IndexingType index) {
            return std::array<ElementType, N>::at((std::size_t) index);
        }

        const ElementType &at(IndexingType index) const {
            return std::array<ElementType, N>::at((std::size_t) index);
        }
    };

    /**
     * @brief Alias for an array of Corner*
     */
    template<std::size_t length>
    using CornerPtrArray_ = std::array<Corner*, length>;

    /**
     * @brief Alias for an array of Edge*
     */
    template<std::size_t length>
    using EdgePtrArray_ = std::array<Edge*, length>;

}