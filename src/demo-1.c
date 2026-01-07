#include "../thirdparty/raylib-5.5_linux_amd64/include/raylib.h"
#include "../thirdparty/RAYLIB_PREFIXES.h"
#define MD_UI_IMPLEMENTATION
#include "md_ui.h"

#define RL(C) (Color){(C).r,(C).g,(C).b,(C).a}

#define ROBOTO_FLEX "assets/Roboto/Flex/RobotoFlex-VariableFont_GRAD,XOPQ,XTRA,YOPQ,YTAS,YTDE,YTFI,YTLC,YTUC,opsz,slnt,wdth,wght.ttf"
#define ROBOTO_CONDENSED "assets/Roboto/Condensed/static/RobotoCondensed-Regular.ttf"
static Font roboto;

void DrawColorCard(const char* text, float x, float y, float w, float h, Color bg, Color textCol) {
    DrawRectangleRec((Rectangle){x, y, w, h}, bg);
    Vector2 sz = MeasureTextEx(roboto, text, 15.0, 0.0);
    DrawTextEx(roboto, text, (Vector2){x+(w-sz.x)/2.0, y+(h-sz.y)/2.0}, 15.0, 0.0, textCol);
}

void DrawLayout1() {
    float x = 20.0f, y = 20.0f;
    const float w_full = 130.0f, w_half = 64.0f;
    const float h = 50.0f;
    const float gap = 2.0f;
    const float section_x_gap = 20.0f;
    const float section_y_gap = 20.0f;

    float start_x = x;

    DrawColorCard("Primary", x, y, w_full, h, RL(COLOR.Scheme.Primary), RL(COLOR.Scheme.OnPrimary)); x += w_full + gap;
    DrawColorCard("Secondary", x, y, w_full, h, RL(COLOR.Scheme.Secondary), RL(COLOR.Scheme.OnSecondary)); x += w_full + gap;
    DrawColorCard("Tertiary", x, y, w_full, h, RL(COLOR.Scheme.Tertiary), RL(COLOR.Scheme.OnTertiary)); x += w_full + gap + section_x_gap;
    DrawColorCard("Error", x, y, w_full, h, RL(COLOR.Scheme.Error), RL(COLOR.Scheme.OnError));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary", x, y, w_full, h, RL(COLOR.Scheme.OnPrimary), RL(COLOR.Scheme.Primary)); x += w_full + gap;
    DrawColorCard("On Secondary", x, y, w_full, h, RL(COLOR.Scheme.OnSecondary), RL(COLOR.Scheme.Secondary)); x += w_full + gap;
    DrawColorCard("On Tertiary", x, y, w_full, h, RL(COLOR.Scheme.OnTertiary), RL(COLOR.Scheme.Tertiary)); x += w_full + gap + section_x_gap;
    DrawColorCard("On Error", x, y, w_full, h, RL(COLOR.Scheme.OnError), RL(COLOR.Scheme.Error));

    y += h + gap; x = start_x;
    DrawColorCard("Primary Container", x, y, w_full, h, RL(COLOR.Scheme.PrimaryContainer), RL(COLOR.Scheme.OnPrimaryContainer)); x += w_full + gap;
    DrawColorCard("Secondary\nContainer", x, y, w_full, h, RL(COLOR.Scheme.SecondaryContainer), RL(COLOR.Scheme.OnSecondaryContainer)); x += w_full + gap;
    DrawColorCard("Tertiary Container", x, y, w_full, h, RL(COLOR.Scheme.TertiaryContainer), RL(COLOR.Scheme.OnTertiaryContainer)); x += w_full + gap + section_x_gap;
    DrawColorCard("Error Container", x, y, w_full, h, RL(COLOR.Scheme.ErrorContainer), RL(COLOR.Scheme.OnErrorContainer));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary\nContainer", x, y, w_full, h, RL(COLOR.Scheme.OnPrimaryContainer), RL(COLOR.Scheme.PrimaryContainer)); x += w_full + gap;
    DrawColorCard("On Secondary\nContainer", x, y, w_full, h, RL(COLOR.Scheme.OnSecondaryContainer), RL(COLOR.Scheme.SecondaryContainer)); x += w_full + gap;
    DrawColorCard("On Tertiary\nContainer", x, y, w_full, h, RL(COLOR.Scheme.OnTertiaryContainer), RL(COLOR.Scheme.TertiaryContainer)); x += w_full + gap + section_x_gap;
    DrawColorCard("On Error Container", x, y, w_full, h, RL(COLOR.Scheme.OnErrorContainer), RL(COLOR.Scheme.ErrorContainer));

    y += h + gap + section_y_gap; x = start_x;
    DrawColorCard("Primary\nFixed", x, y, w_half, h, RL(COLOR.Scheme.PrimaryFixed), RL(COLOR.Scheme.OnPrimaryFixed)); x += w_half + gap;
    DrawColorCard("Primary\nFixed Dim", x, y, w_half, h, RL(COLOR.Scheme.PrimaryFixedDim), RL(COLOR.Scheme.OnPrimaryFixed)); x += w_half + gap;
    DrawColorCard("Secondary\nFixed", x, y, w_half, h, RL(COLOR.Scheme.SecondaryFixed), RL(COLOR.Scheme.OnSecondaryFixed)); x += w_half + gap;
    DrawColorCard("Secondary\nFixed Dim", x, y, w_half, h, RL(COLOR.Scheme.SecondaryFixedDim), RL(COLOR.Scheme.OnSecondaryFixed)); x += w_half + gap;
    DrawColorCard("Tertiary\nFixed", x, y, w_half, h, RL(COLOR.Scheme.TertiaryFixed), RL(COLOR.Scheme.OnTertiaryFixed)); x += w_half + gap;
    DrawColorCard("Tertiary\nFixed Dim", x, y, w_half, h, RL(COLOR.Scheme.TertiaryFixedDim), RL(COLOR.Scheme.OnTertiaryFixed));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary\nFixed", x, y, w_full, h, RL(COLOR.Scheme.OnPrimaryFixed), RL(COLOR.Scheme.PrimaryFixed)); x += w_full + gap;
    DrawColorCard("On Secondary\nFixed", x, y, w_full, h, RL(COLOR.Scheme.OnSecondaryFixed), RL(COLOR.Scheme.SecondaryFixed)); x += w_full + gap;
    DrawColorCard("On Tertiary\nFixed", x, y, w_full, h, RL(COLOR.Scheme.OnTertiaryFixed), RL(COLOR.Scheme.TertiaryFixed));

    y += h + gap; x = start_x;
    DrawColorCard("On Primary\nFixed Variant", x, y, w_full, h, RL(COLOR.Scheme.OnPrimaryFixedVariant), RL(COLOR.Scheme.PrimaryFixedDim)); x += w_full + gap;
    DrawColorCard("On Secondary\nFixed Variant", x, y, w_full, h, RL(COLOR.Scheme.OnSecondaryFixedVariant), RL(COLOR.Scheme.SecondaryFixedDim)); x += w_full + gap;
    DrawColorCard("On Tertiary\nFixed Variant", x, y, w_full, h, RL(COLOR.Scheme.OnTertiaryFixedVariant), RL(COLOR.Scheme.TertiaryFixedDim));

    y += h + gap + section_y_gap; x = start_x;
    float inverse_start_x = start_x + (w_full * 3) + (gap * 2) + section_x_gap;

    DrawColorCard("Surface Dim", x, y, w_full, h, RL(COLOR.Scheme.SurfaceDim), RL(COLOR.Scheme.OnSurface)); x += w_full + gap;
    DrawColorCard("Surface", x, y, w_full, h, RL(COLOR.Scheme.Surface), RL(COLOR.Scheme.OnSurface)); x += w_full + gap;
    DrawColorCard("Surface Bright", x, y, w_full, h, RL(COLOR.Scheme.SurfaceBright), RL(COLOR.Scheme.OnSurface));

    DrawColorCard("Inverse Surface", inverse_start_x, y, w_full, h, RL(COLOR.Scheme.InverseSurface), RL(COLOR.Scheme.InverseOnSurface));

    y += h + gap; x = start_x;
    float w_container = (w_full * 3 + gap*2 - gap*4) / 5.0f;
    DrawColorCard("Surface\nC. Lowest", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerLowest), RL(COLOR.Scheme.OnSurface)); x += w_container + gap;
    DrawColorCard("Surface\nC. Low", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerLow), RL(COLOR.Scheme.OnSurface)); x += w_container + gap;
    DrawColorCard("Surface\nContainer", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainer), RL(COLOR.Scheme.OnSurface)); x += w_container + gap;
    DrawColorCard("Surface\nC. High", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerHigh), RL(COLOR.Scheme.OnSurface)); x += w_container + gap;
    DrawColorCard("Surface\nC. Highest", x, y, w_container, h, RL(COLOR.Scheme.SurfaceContainerHighest), RL(COLOR.Scheme.OnSurface));

    DrawColorCard("Inverse On Surface", inverse_start_x, y, w_full, h, RL(COLOR.Scheme.InverseOnSurface), RL(COLOR.Scheme.InverseSurface));

    y += h + gap; x = start_x;
    w_container = (w_full * 3 + gap*2 - gap*4) / 4.0f;
    DrawColorCard("On Surface", x, y, w_container, h, RL(COLOR.Scheme.OnSurface), RL(COLOR.Scheme.Surface)); x += w_container + gap;
    DrawColorCard("On Surface\nVariant", x, y, w_container, h, RL(COLOR.Scheme.OnSurfaceVariant), RL(COLOR.Scheme.Surface)); x += w_container + gap;
    DrawColorCard("Outline", x, y, w_container, h, RL(COLOR.Scheme.Outline), RL(COLOR.Scheme.Surface)); x += w_container + gap;
    DrawColorCard("Outline\nVariant", x, y, w_container+2, h, RL(COLOR.Scheme.OutlineVariant), RL(COLOR.Scheme.OnSurface));

    DrawColorCard("Inverse Primary", inverse_start_x, y, w_full, h, RL(COLOR.Scheme.InversePrimary), RL(COLOR.Scheme.OnPrimaryContainer));
}

void DrawContainer(char* text, int x, int y, int w, int h, color_t bg, color_t fg) {
    DrawRectangleRec((Rectangle){x, y, w, h}, RL(bg));
    Vector2 sz = MeasureTextEx(roboto, text, 15.0, 0.0);
    DrawTextEx(roboto, text, (Vector2){x+(w-sz.x)/2.0, y+10}, 15.0, 0.0, RL(fg));
}

void DrawLayout2() {
    int x = 600;
    int y = 20;
    DrawContainer("Surface Container Lowest",  x +  0, y +   0, 280, 250, COLOR.Scheme.SurfaceContainerLowest,  COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container Low",     x + 10, y +  30, 260, 200, COLOR.Scheme.SurfaceContainerLow,     COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container",         x + 20, y +  60, 240, 150, COLOR.Scheme.SurfaceContainer,        COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container High",    x + 30, y +  90, 220, 100, COLOR.Scheme.SurfaceContainerHigh,    COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container Highest", x + 40, y + 120, 200,  50, COLOR.Scheme.SurfaceContainerHighest, COLOR.Scheme.OnSurface);

    y += 300;
    DrawContainer("Surface Container Highest", x +  0, y +   0, 280, 250, COLOR.Scheme.SurfaceContainerHighest, COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container High",    x + 10, y +  30, 260, 200, COLOR.Scheme.SurfaceContainerHigh,    COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container",         x + 20, y +  60, 240, 150, COLOR.Scheme.SurfaceContainer,        COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container Low",     x + 30, y +  90, 220, 100, COLOR.Scheme.SurfaceContainerLow,     COLOR.Scheme.OnSurface);
    DrawContainer("Surface Container Lowest",  x + 40, y + 120, 200,  50, COLOR.Scheme.SurfaceContainerLowest,  COLOR.Scheme.OnSurface);
}

int main(void) {
    md_color_global_init(true);

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(900, 600, "FLOAT");
    SetTargetFPS(500);

    roboto = LoadFontEx(ROBOTO_FLEX, 60, NULL, 0);
    GenTextureMipmaps(&roboto.texture);
    SetTextureFilter(roboto.texture, TEXTURE_FILTER_TRILINEAR);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();
        BeginDrawing();
        ClearBackground(RL(COLOR.Scheme.Background));
        DrawLayout1();
        DrawLayout2();
        DrawTextEx(roboto, "Press 'Space' To Change Theme", (Vector2){5, 580}, 20.0, 0.0, RL(COLOR.Scheme.OnBackground));
        EndDrawing();
    }
    UnloadFont(roboto);
    CloseWindow();
    return 0;
}
