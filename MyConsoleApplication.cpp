#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <Windows.h>

typedef struct entity
{
    char shape[7];
    int pos;
}ENTITY;

void clearCanvas(char* canvas, const int canvasSize)
{
    for (int i = 0; i < canvasSize; i++)
        canvas[i] = ' ';
    canvas[canvasSize] = '\0';
}

char* initCanvas(int canvasSize)
{
    char* canvas = (char*)malloc(sizeof(char) * (canvasSize + 1));
    return canvas;
}

void deinitCanvas(char* canvas)
{
    free(canvas);
}

void renderCanvas(const char* canvas)
{
    printf("%s\r", canvas);
}

void canvas_draw(char* canvas, char* entity, int entity_pos)
{
    for (int i = 0; i < strlen(entity); i++)
        canvas[entity_pos + i] = entity[i];
}

void player_draw(char* player, int player_pos, char* canvas)
{
    canvas_draw(canvas, player, player_pos);
}

void enemy_draw(char* enemy, int enemy_pos, char* canvas)
{
    canvas_draw(canvas, enemy, enemy_pos);
}

void bullet_draw(char* bullet, int bullet_pos, char* canvas)
{
    canvas_draw(canvas, bullet, bullet_pos);
}


int main()
{
    const int canvasSize = 106;
    char* canvas = initCanvas(canvasSize);

    ENTITY player = { "(^__^)", 10 };
    ENTITY enemy = { "(*__*)" , 50 };
    ENTITY bullet = { "->" , player.pos + strlen(player.shape) };

    canvas = initCanvas(canvasSize);    // malloc for canvas

    int loop_count = 0;

    while (true) {
        // Clear Canvas
        clearCanvas(canvas, canvasSize);

        // Draw player
        player_draw(player.shape, player.pos, canvas);
        // Draw enemy
        enemy_draw(enemy.shape, enemy.pos, canvas);

        if (loop_count >= 30) {
            // Draw bullet
            bullet_draw(bullet.shape, bullet.pos, canvas);
            bullet.pos++;

            // Remove bullet when enemy was hit
            if ((bullet.pos + strlen(bullet.shape) - 1) == enemy.pos)
            {
                strcpy(bullet.shape, "\0");
                strcpy(enemy.shape, "(T__T)");
            }
        }

        renderCanvas(canvas);
        Sleep(100);
        loop_count++;
    }

    deinitCanvas(canvas);

    return 0;
}