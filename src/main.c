#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "md_ui.h"
#include <stdio.h>

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(100, 100, "FLOAT");
    int monitor = -1;
    while (!WindowShouldClose()) {
        if (GetCurrentMonitor() != monitor) {
            monitor = GetCurrentMonitor();
            SetTargetFPS(GetMonitorRefreshRate(monitor));
            Vector2 phys = { (f32)GetMonitorPhysicalWidth(monitor), (f32)GetMonitorPhysicalHeight(monitor) };
            Vector2 dpi = GetWindowScaleDPI();
            printf("dpi.x=%f\tdpi.y=%f\tphys.x=%f\tphys.y=%f\n", dpi.x, dpi.y, phys.x, phys.y);
        }
        BeginDrawing();
        ClearBackground((Color){20,20,20,0xFF});

        for (int y = 0; y < 100; y += 10) {
            for (int x = 0; x < 100; x += 10) {
                DrawRectangle(x, y, 10, 10, (x/10+y/10)%2 == 0 ? RAYWHITE : BLACK);
            }
        }
        for (int y = 0; y < 10; y += 2) {
            for (int x = 0; x < 10; x += 2) {
                DrawRectangle(90+x, 90+y, 2, 2, (x/2+y/2)%2 == 0 ? RED : BLUE);
            }
        }

        DrawFPS(0,0);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
