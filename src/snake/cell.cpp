#include "cell.h"

ImU32 RenderableCell::GetColor()
{
    static ImU32 empty = ImU32(ImColor(ImVec4(0.1f, 0.1f, 0.1f, 1.0f)));

    switch (state)
    {
        case RenderableCell::State::Empty:
            return empty;
        case RenderableCell::State::Snake:
            return ImU32(ImColor(ImVec4(0.0f, 0.8f, 0.0f, 1.0f)));
        case RenderableCell::State::Apple:
            return ImU32(ImColor(ImVec4(0.8f, 0.0f, 0.0f, 1.0f)));
    }

    return empty;
}