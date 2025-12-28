#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#include "md_ui.h"

#define RL(C) (Color){(C).r,(C).g,(C).b,(C).a}

void DrawColorCard(const char* text, float x, float y, float w, float h, Color bg, Color textCol) {
    DrawRectangle(x, y, w, h, bg);
    int textWidth = MeasureText(text, 10);
    DrawText(text, x + (w - textWidth) / 2, y + (h - 10) / 2, 10, textCol);
}

void DrawLayout(int t) {
    float x = 20.0f, y = 20.0f;
    const float w_full = 130.0f, w_half = 64.0f;
    const float h = 38.0f;
    const float gap = 2.0f;
    const float section_x_gap = 20.0f;
    const float section_y_gap = 20.0f;

    float start_x = x;
    float start_y = y;

    DrawColorCard("Primary", x, y, w_full, h, RL(COLOR.Scheme.Primary[t]), RL(COLOR.Scheme.OnPrimary[t])); x += w_full + gap;
    DrawColorCard("Secondary", x, y, w_full, h, RL(COLOR.Scheme.Secondary[t]), RL(COLOR.Scheme.OnSecondary[t])); x += w_full + gap;
    DrawColorCard("Tertiary", x, y, w_full, h, RL(COLOR.Scheme.Tertiary[t]), RL(COLOR.Scheme.OnTertiary[t])); x += w_full + gap + section_x_gap;
    DrawColorCard("Error", x, y, w_full, h, RL(COLOR.Scheme.Error[t]), RL(COLOR.Scheme.OnError[t]));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary", x, y, w_full, h, RL(COLOR.Scheme.OnPrimary[t]), RL(COLOR.Scheme.Primary[t])); x += w_full + gap;
    DrawColorCard("On Secondary", x, y, w_full, h, RL(COLOR.Scheme.OnSecondary[t]), RL(COLOR.Scheme.Secondary[t])); x += w_full + gap;
    DrawColorCard("On Tertiary", x, y, w_full, h, RL(COLOR.Scheme.OnTertiary[t]), RL(COLOR.Scheme.Tertiary[t])); x += w_full + gap + section_x_gap;
    DrawColorCard("On Error", x, y, w_full, h, RL(COLOR.Scheme.OnError[t]), RL(COLOR.Scheme.Error[t]));

    y += h + gap; x = start_x;
    DrawColorCard("Primary Container", x, y, w_full, h, RL(COLOR.Scheme.PrimaryContainer[t]), RL(COLOR.Scheme.OnPrimaryContainer[t])); x += w_full + gap;
    DrawColorCard("Secondary Container", x, y, w_full, h, RL(COLOR.Scheme.SecondaryContainer[t]), RL(COLOR.Scheme.OnSecondaryContainer[t])); x += w_full + gap;
    DrawColorCard("Tertiary Container", x, y, w_full, h, RL(COLOR.Scheme.TertiaryContainer[t]), RL(COLOR.Scheme.OnTertiaryContainer[t])); x += w_full + gap + section_x_gap;
    DrawColorCard("Error Container", x, y, w_full, h, RL(COLOR.Scheme.ErrorContainer[t]), RL(COLOR.Scheme.OnErrorContainer[t]));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary Container", x, y, w_full, h, RL(COLOR.Scheme.OnPrimaryContainer[t]), RL(COLOR.Scheme.PrimaryContainer[t])); x += w_full + gap;
    DrawColorCard("On Secondary Container", x, y, w_full, h, RL(COLOR.Scheme.OnSecondaryContainer[t]), RL(COLOR.Scheme.SecondaryContainer[t])); x += w_full + gap;
    DrawColorCard("On Tertiary Container", x, y, w_full, h, RL(COLOR.Scheme.OnTertiaryContainer[t]), RL(COLOR.Scheme.TertiaryContainer[t])); x += w_full + gap + section_x_gap;
    DrawColorCard("On Error Container", x, y, w_full, h, RL(COLOR.Scheme.OnErrorContainer[t]), RL(COLOR.Scheme.ErrorContainer[t]));

    y += h + gap + section_y_gap; x = start_x;
    DrawColorCard("Primary\nFixed", x, y, w_half, h, RL(COLOR.Scheme.PrimaryFixed[t]), RL(COLOR.Scheme.OnPrimaryFixed[t])); x += w_half + gap;
    DrawColorCard("Primary\nFixed Dim", x, y, w_half, h, RL(COLOR.Scheme.PrimaryFixedDim[t]), RL(COLOR.Scheme.OnPrimaryFixed[t])); x += w_half + gap;
    DrawColorCard("Secondary\nFixed", x, y, w_half, h, RL(COLOR.Scheme.SecondaryFixed[t]), RL(COLOR.Scheme.OnSecondaryFixed[t])); x += w_half + gap;
    DrawColorCard("Secondary\nFixed Dim", x, y, w_half, h, RL(COLOR.Scheme.SecondaryFixedDim[t]), RL(COLOR.Scheme.OnSecondaryFixed[t])); x += w_half + gap;
    DrawColorCard("Tertiary\nFixed", x, y, w_half, h, RL(COLOR.Scheme.TertiaryFixed[t]), RL(COLOR.Scheme.OnTertiaryFixed[t])); x += w_half + gap;
    DrawColorCard("Tertiary\nFixed Dim", x, y, w_half, h, RL(COLOR.Scheme.TertiaryFixedDim[t]), RL(COLOR.Scheme.OnTertiaryFixed[t]));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary Fixed", x, y, w_full, h, RL(COLOR.Scheme.OnPrimaryFixed[t]), RL(COLOR.Scheme.PrimaryFixed[t])); x += w_full + gap;
    DrawColorCard("On Secondary Fixed", x, y, w_full, h, RL(COLOR.Scheme.OnSecondaryFixed[t]), RL(COLOR.Scheme.SecondaryFixed[t])); x += w_full + gap;
    DrawColorCard("On Tertiary Fixed", x, y, w_full, h, RL(COLOR.Scheme.OnTertiaryFixed[t]), RL(COLOR.Scheme.TertiaryFixed[t]));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary\nFixed Variant", x, y, w_full, h, RL(COLOR.Scheme.OnPrimaryFixedVariant[t]), RL(COLOR.Scheme.PrimaryFixedDim[t])); x += w_full + gap;
    DrawColorCard("On Secondary\nFixed Variant", x, y, w_full, h, RL(COLOR.Scheme.OnSecondaryFixedVariant[t]), RL(COLOR.Scheme.SecondaryFixedDim[t])); x += w_full + gap;
    DrawColorCard("On Tertiary\nFixed Variant", x, y, w_full, h, RL(COLOR.Scheme.OnTertiaryFixedVariant[t]), RL(COLOR.Scheme.TertiaryFixedDim[t]));

    y += h + gap + section_y_gap; x = start_x;
    float surface_start_y = y;
    float inverse_start_x = start_x + (w_full * 3) + (gap * 2) + section_x_gap;

    DrawColorCard("Surface Dim", x, y, w_full, h, RL(COLOR.Scheme.SurfaceDim[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_full + gap;
    DrawColorCard("Surface", x, y, w_full, h, RL(COLOR.Scheme.Surface[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_full + gap;
    DrawColorCard("Surface Bright", x, y, w_full, h, RL(COLOR.Scheme.SurfaceBright[t]), RL(COLOR.Scheme.OnSurface[t]));

    DrawColorCard("Inverse Surface", inverse_start_x, y, w_full, h, RL(COLOR.Scheme.InverseSurface[t]), RL(COLOR.Scheme.InverseOnSurface[t]));

    y += h + gap; x = start_x;
    float w_container = ((w_full * 3 + gap * 2) / 5.0f);
    DrawColorCard("Surface\nC. Lowest", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerLowest[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_container + gap;
    DrawColorCard("Surface\nC. Low", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerLow[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_container + gap;
    DrawColorCard("Surface\nContainer", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainer[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_container + gap;
    DrawColorCard("Surface\nC. High", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerHigh[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_container + gap;
    DrawColorCard("Surface\nC. Highest", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerHighest[t]), RL(COLOR.Scheme.OnSurface[t]));

    DrawColorCard("Inverse On Surface", inverse_start_x, y, w_full, h, RL(COLOR.Scheme.InverseOnSurface[t]), RL(COLOR.Scheme.InverseSurface[t]));

    y += h + gap; x = start_x;
    DrawColorCard("On Surface", x, y, w_full, h, RL(COLOR.Scheme.OnSurface[t]), RL(COLOR.Scheme.Surface[t])); x += w_full + gap;
    DrawColorCard("On Surface Variant", x, y, w_full, h, RL(COLOR.Scheme.OnSurfaceVariant[t]), RL(COLOR.Scheme.Surface[t]));

    DrawColorCard("Inverse Primary", inverse_start_x, y, w_full, h, RL(COLOR.Scheme.InversePrimary[t]), RL(COLOR.Scheme.OnPrimaryContainer[t]));

    y += h + gap; x = start_x;
    DrawColorCard("Outline", x, y, w_full, h, RL(COLOR.Scheme.Outline[t]), RL(COLOR.Scheme.OnSurface[t])); x += w_full + gap;
    DrawColorCard("Outline Variant", x, y, w_full, h, RL(COLOR.Scheme.OutlineVariant[t]), RL(COLOR.Scheme.OnSurface[t]));
}

int main(void) {
    md_init_global_color();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(800, 600, "FLOAT");
    SetTargetFPS(500);

    int themeIndex = 1;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) themeIndex = !themeIndex;

        BeginDrawing();
        // ClearBackground(RL_BLACK);

        // DrawRectangle(100, 100, 200, 200, RL(COLOR.Scheme.Primary[0]));
        // DrawText("Some Text", 130, 130, 20, RL(COLOR.Scheme.OnPrimary[0]));

        ClearBackground(RL(COLOR.Scheme.Background[themeIndex]));
        DrawLayout(themeIndex);

        // DrawFPS(0,0);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
