#pragma once

#include "pch.h"

#include "cell.h"
#include "field.h"

class Apple : public Cell
{
public:
    inline static const ImVec4 DEFAULT_COLOR = ImVec4(0.8f, 0.4f, 0.0f, 1.0f);

    Apple();

    void Draw(Field& field) const;
};