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

void player_draw(ENTITY player, char* canvas)
{
    canvas_draw(canvas, player.shape, player.pos);
}
void enemy_draw(ENTITY enemy, char* canvas)
{
    canvas_draw(canvas, enemy.shape, enemy.pos);
}
void bullet_draw(ENTITY bullet, char* canvas)
{
    canvas_draw(canvas, bullet.shape, bullet.pos);
}

void bullet_update(ENTITY* bullet)
{
    bullet->pos++;
}
bool bullet_collide_check(ENTITY bullet, ENTITY target)
{
    if ((bullet.pos + strlen(bullet.shape)) == target.pos)
        return true;
    return false;
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
    bool gameover_flag = false;

    while (true) {
        // Clear Canvas
        clearCanvas(canvas, canvasSize);

        // Draw player
        player_draw(player, canvas);
        // Draw enemy
        enemy_draw(enemy, canvas);

        if (loop_count >= 30) {
            // Draw bullet
            bullet_draw(bullet, canvas);
            bullet_update(&bullet);


            // Remove bullet when enemy was hit
            if (bullet_collide_check(bullet, enemy))
            {
                strcpy(enemy.shape, "(T__T)");
                strcpy(bullet.shape, "\0");
                enemy_draw(enemy, canvas);
                bullet_draw(bullet, canvas);
            }
        }

        renderCanvas(canvas);
        Sleep(100);
        loop_count++;
    }

    deinitCanvas(canvas);

    return 0;
}