#pragma once

#include <array>
#include <random>


namespace rubiks {

    /**
     * @class RandomGenerator<T, N>
     * @brief Draws random samples from an input array with a uniform distribution
     * @tparam T type of samples to draw
     * @tparam N size of input array to draw from
     */
    template <typename T, std::size_t N>
    class RandomGenerator {
    public:
        RandomGenerator() = delete;

        /**
         * @brief RandomGenerator constructor
         * @param list array containing the population to draw samples from
         */
        explicit RandomGenerator(std::array<T, N>&& list);

        /**
         * @brief RandomGenerator destructor
         */
        ~RandomGenerator() = default;

        /**
         * @brief draw a sample from the population
         * @details return a copy of a sample drawn randomly from the population with a uniform distribution
         * @param list array containing the population to draw samples from
         */
        T draw();

    private:
        std::random_device randomDevice_;  /*!< uniformly-distributed integer random number generator */
        std::mt19937 generator_;           /*!< pseudo-random number generator seeded by randomDevice_ */

        std::uniform_int_distribution<std::size_t> distribution_;  /*!< uniform distribution for the population */
        std::array<T, N> list_;                                    /*!< population to draw samples from */
    };

    template <typename T, std::size_t N>
    RandomGenerator<T, N>::RandomGenerator(std::array<T, N>&& list):
            generator_(randomDevice_()),
            list_(std::move(list)),
            distribution_(0, list_.size() - 1) {}

    template <typename T, std::size_t N>
    T RandomGenerator<T, N>::draw() {
        return list_.at(distribution_(generator_));
    }

}