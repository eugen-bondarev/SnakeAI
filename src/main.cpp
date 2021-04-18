#include "window/window.h"

#include "snake_ai.h"

int main()
{
    Window window;
    
    InitRandomEngine();

    SnakeAI snakeAi(window);
    
    while (!window.ShouldClose())
    {
        window.BeginFrame();
            snakeAi.Update();        
        window.EndFrame();
    }

    return 0;
}