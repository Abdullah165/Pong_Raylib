#include <raylib.h>

int main(int argc, char* argv[])
{
    InitWindow(800, 600, "Pong");

    while (WindowShouldClose() == false)
    {
        // events

        //drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
