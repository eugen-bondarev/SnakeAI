#include "apple.h"

#include "game_settings.h"

Apple::Apple() : Cell(rand() % FIELD_SIZE, rand() % FIELD_SIZE)
{

}

void Apple::Draw(Field& field) const
{
    field[x][y].state = RenderableCell::State::Apple;
}