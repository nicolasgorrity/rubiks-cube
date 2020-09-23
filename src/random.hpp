#pragma once

#include <array>
#include <random>


namespace rubiks {

    template <typename T, std::size_t N>
    class RandomGenerator {
    public:
        explicit RandomGenerator(std::array<T, N>&& list);
        ~RandomGenerator() = default;

        T draw();

    private:
        std::random_device randomDevice_;
        std::mt19937 generator_;

        std::uniform_int_distribution<std::size_t> distribution_;
        std::array<T, N> list_;
    };

    template <typename T, std::size_t N>
    RandomGenerator<T, N>::RandomGenerator(std::array<T, N>&& list):
            randomDevice_(),
            generator_(randomDevice_()),
            list_(std::move(list)),
            distribution_(0, list_.size() - 1) {}

    template <typename T, std::size_t N>
    T RandomGenerator<T, N>::draw() {
        return list_.at(distribution_(generator_));
    }

}