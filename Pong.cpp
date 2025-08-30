#include <raylib.h>

int player_movement(int playerX, int speed, int screenWidth, int playerWidth);

int main(int argc, char* argv[])
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    int ballX = screenWidth / 2;
    int ballY = screenHeight / 2;

    int width = 150;
    int height = 20;
    int speed = 5;
    int playerX = screenWidth / 2 - (width / 2);

    int npcPosX = screenWidth / 2 - (width / 2);
    bool isGoingLeft = false;
    bool isGoingRight = true;


    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        // player movement
        playerX =  player_movement(playerX, speed, screenWidth, width);

        //NPC movement
        if (npcPosX >= (screenWidth - width))
        {
            isGoingLeft = true;
            isGoingRight = false;
        }

        if (isGoingLeft)
        {
            npcPosX -= speed;

            if (npcPosX <= 0)
            {
                isGoingLeft = false;
                isGoingRight = true;
            }
        }

        if (isGoingRight)
        {
            npcPosX += speed;
        }


        //drawing
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(ballX, ballY, 20,WHITE);

        //player
        DrawRectangle(playerX, screenHeight - height - 10, width, height,WHITE);

        //Npc
        DrawRectangle(npcPosX, height - 10, width, height,WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

int player_movement(int playerX, int speed, int screenWidth, int playerWidth)
{
    if (IsKeyDown(KEY_LEFT))
    {
        if (playerX <= 0)
        {
            playerX += 0;
        }
        else
        {
            playerX -= speed;
        }
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        if (playerX >= screenWidth - playerWidth)
        {
            playerX += 0;
        }
        else
        {
            playerX += speed;
        }
    }

    return playerX;
}
