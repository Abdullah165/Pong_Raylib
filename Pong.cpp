#include <raylib.h>

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    Ball(float x, float y, int speed_x, int speed_y, int radius)
    {
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->speed_y = speed_y;
        this->radius = radius;
    }

    void updatePos()
    {
        x += speed_x;
        y += speed_y;

        if (x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1;
        }
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
    }

    void draw()
    {
        DrawCircle(x, y, radius,WHITE);
    }
};

class Paddle
{
    public:
    int x, y;
    int speed_x;
    int width, height;

    Paddle(int x, int y, int speed_x, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->width = width;
        this->height = height;
    }

    void Draw()
    {
        DrawRectangle(x, y , width, height,WHITE);
    }

    void updatePos()
    {
        if (IsKeyDown(KEY_LEFT))
        {
            if (this->x <= 0)
            {
                this->x += 0;
            }
            else
            {
                this->x -= speed_x;
            }
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            if (this->x >= GetScreenWidth() - width)
            {
                this->x += 0;
            }
            else
            {
                this->x += speed_x;
            }
        }

    }
};

int main(int argc, char* argv[])
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    int width = 150;
    int height = 20;
    int speed = 5;
    int playerX = screenWidth / 2 - (width / 2);

    int npcPosX = screenWidth / 2 - (width / 2);
    bool isGoingLeft = false;
    bool isGoingRight = true;


    Ball ball(screenWidth / 2.0, screenHeight / 2.0, speed, speed, 20);

    Paddle paddle(screenWidth / 2 - (width / 2), screenHeight - height - 10,speed,width,height);

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
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

        ball.updatePos();

        paddle.updatePos();

        ClearBackground(BLACK);

        //ball 
        ball.draw();

        //player
        paddle.Draw();

        //Npc
        DrawRectangle(npcPosX, height - 10, width, height,WHITE);

        //Line separation
        DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2,WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}