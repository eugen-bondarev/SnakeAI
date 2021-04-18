#pragma once

#include "pch.h"

#include "cell.h"
#include "field.h"

class Apple : public Cell
{
public:
    Apple();

    void Draw(Field& field) const;
};