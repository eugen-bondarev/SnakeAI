#pragma once

#include "pch.h"

#include "cell.h"

#include "game_settings.h"

class Field
{
public:
    Field();
    
    using Row = std::array<RenderableCell, FIELD_SIZE>;

    void Clear();

    Row& operator[](int i);

private:
    std::array<Row, FIELD_SIZE> data;

};