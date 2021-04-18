#include "field.h"

Field::Field()
{
    for (int x = 0; x < Field::SIZE; x++)
    {
        for (int y = 0; y < Field::SIZE; y++)
        {
            data[x][y].x = x;
            data[x][y].y = y;
        }
    }
}

void Field::Clear()
{
    for (auto& row : data)
    {
        for (auto& cell : row)
        {
            cell.state = RenderableCell::State::Empty;
        }
    }
}

Field::Row& Field::operator[](int i)
{
    return data[i];
}