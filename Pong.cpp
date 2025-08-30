#include <raylib.h>

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    float radius;

    Ball(float x, float y, int speed_x, int speed_y, float radius)
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
    float x, y;
    int speed_x;
    float width, height;

    Paddle(float x, float y, int speed_x, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->width = width;
        this->height = height;
    }

    void Draw()
    {
        DrawRectangle(x, y, width, height,WHITE);
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

class PaddleNPC
{
public:
    float x, y;
    int speed_x;
    float width, height;

    PaddleNPC(float x, float y, int speed_x, float width, float height)
    {
        this->x = x;
        this->y = y;
        this->speed_x = speed_x;
        this->width = width;
        this->height = height;
    }

    void Draw()
    {
        DrawRectangle(x, y, width, height,WHITE);
    }

    void Update(int ball_X, int radius)
    {
        if (x + width / 2 > ball_X + radius)
        {
            x -= speed_x;
        }
        if (x + width / 2 < ball_X + radius)
        {
            x += speed_x;
        }
    }
};

int main(int argc, char* argv[])
{
    const int screenWidth = 1000;
    const int screenHeight = 800;

    float width = 150;
    float height = 20;
    int speed = 5;

    Ball ball(screenWidth / 2.0, screenHeight / 2.0, speed, speed, 20);

    Paddle player(screenWidth / 2 - (width / 2), screenHeight - height - 10, speed, width, height);

    PaddleNPC paddle_npc(screenWidth / 2 - (width / 2), height, speed, width, height);

    InitWindow(screenWidth, screenHeight, "Pong");

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();

        // updating
        ball.updatePos();

        player.updatePos();

        paddle_npc.Update(ball.x, ball.radius);

        // Collision detection
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,
                                    Rectangle{player.x, player.y, player.width, player.height}))
        {
            ball.speed_y *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{
                                        paddle_npc.x, paddle_npc.y, paddle_npc.width, paddle_npc.height
                                    }))
        {
            ball.speed_y *= -1;
        }

        //drawing
        ClearBackground(BLACK);

        //ball 
        ball.draw();

        //player
        player.Draw();

        //Npc
        paddle_npc.Draw();
        // DrawRectangle(npcPosX, height - 10, width, height,WHITE);

        //Line separation
        DrawLine(0, screenHeight / 2, screenWidth, screenHeight / 2,WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
