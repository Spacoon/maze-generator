#pragma once
#include <random>

inline const int getRandomNumber(const int& min, const int& max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    return distribution(rng);
}
