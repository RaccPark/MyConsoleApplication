#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <Windows.h>

int main()
{
    char canvas[106 + 1];

    char player[] = "(^__^)";
    int player_pos = 10;    // player의 위치

    char enemy[] = "(*__*)";
    int enemy_pos = 50; // enemy의 위치

    char bullet[] = "->";
    int bullet_pos = player_pos + strlen(player);   // 총알 발사 위치
    bool bullet_flag = false;

    int loop_count = 0;

    // Game loop
    while (true) {
        for (int i = 0; i < (100 + 6); i++)
            canvas[i] = ' ';
        canvas[106] = '\0';

        // Draw Player
        for (int i = 0; i < strlen(player); i++)
            canvas[player_pos + i] = player[i];
        // Draw Enemy
        for (int i = 0; i < strlen(enemy); i++)
            canvas[enemy_pos + i] = enemy[i];

        // Check Time
        if (loop_count >= 30) bullet_flag = true;

        // Draw Bullet
        if (bullet_flag) {
            for (int i = 0; i < strlen(bullet); i++)
                canvas[bullet_pos + i] = bullet[i];

            bullet_pos++;

            if ((bullet_pos + strlen(bullet) - 1) == enemy_pos) {
                strcpy(bullet, "\0");
                bullet_flag = false;
            }
        }

        printf("%s\r", canvas);
        Sleep(100);
        loop_count++;
    }

    return 0;
}