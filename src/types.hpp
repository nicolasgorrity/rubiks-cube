#pragma once

#include "blocks.hpp"
#include "colors.hpp"


namespace rubiks {

    /**
     * @class EnumArray_
     * @brief Array that can be indexed using int-compatible enum types, so it can be interfaced as a hashmap.
     * @tparam IndexingType Type used as the key, it must be cast-compatible with std::size_t
     * @tparam ElementType Type used as the value
     * @tparam N Number of key-values pairs
     */
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
     * @tparam length size of the array
     */
    template<std::size_t length>
    using CornerPtrArray_ = std::array<Corner*, length>;

    /**
     * @brief Alias for an array of Edge*
     * @tparam length size of the array
     */
    template<std::size_t length>
    using EdgePtrArray_ = std::array<Edge*, length>;

}