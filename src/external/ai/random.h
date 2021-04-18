#pragma once

#include <random>

#include "types.h"

namespace util {

// Just in case somebody doesn't do that..
inline static void InitRandomEngine()
{
    srand(time(0));
}

inline static float GenRandomFloat(float bottom = 0.0f, float top = 1.0f)
{
    return bottom + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (top - bottom));
}

// Default values are 0 and 2 for bottom and top respectively, since this function (in its mathematical sense) has domain [a; b)
inline static int GenRandomInt(int bottom = 0, int top = 2)
{
    return static_cast<int>(GenRandomFloat(static_cast<float>(bottom), static_cast<float>(top)));
}

inline static constexpr float BIAS_BOTTOM   = -1.0f;
inline static constexpr float BIAS_TOP      =  1.0f;
inline static constexpr float WEIGHT_BOTTOM = -1.0f;
inline static constexpr float WEIGHT_TOP    =  1.0f;

inline static value_t GenRandomWeight()
{
    return util::GenRandomFloat(WEIGHT_BOTTOM, WEIGHT_TOP);
}

inline static value_t GenRandomBias()
{
    return util::GenRandomFloat(BIAS_BOTTOM, BIAS_TOP);
}

}