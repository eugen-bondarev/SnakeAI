#pragma once

#include "pch.h"

#include "cell.h"

class Field
{
public:
    Field();

    inline static constexpr int SIZE = 32;
    using Row = std::array<RenderableCell, Field::SIZE>;

    void Clear();

    Row& operator[](int i);

private:
    std::array<Row, Field::SIZE> data;

};