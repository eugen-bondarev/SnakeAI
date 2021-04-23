#include "cell.h"

bool Cell::operator==(const Cell& other) const
{
    return x == other.x && y == other.y;
}