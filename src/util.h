#pragma once

#include <random>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

inline static void InitRandomEngine()
{
    srand(time(0));
}

// The range is [a; b)
template <typename T>
inline static T GenRandomNumber(T a = 0.0f, T b = 2.0f)
{
    return static_cast<T>((static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) * (b - a) + a);
}