replicate these layouts on a 800x600 screen, using the raylib C api:
```c
#define RL(C) (Color){(C).r,(C).g,(C).b,(C).a}

void DrawColorCard(const char* text, float x, float y, float w, float h, Color bg, Color textCol) {
    DrawRectangle(x, y, w, h, bg);
    DrawText(text, x + 10, y + 10, 10, textCol);
}

int main(void) {
    md_init_global_color(); // must be kept as-is

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN);
    InitWindow(800, 600, "FLOAT");
    SetTargetFPS(500);

    int themeIndex = 1;
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) themeIndex = !themeIndex;

        BeginDrawing();
        ClearBackground(RL_BLACK);

        DrawRectangle(100, 100, 200, 200, RL(COLOR.Scheme.Primary[0]));
        DrawText("Some Text", 130, 130, 20, RL(COLOR.Scheme.OnPrimary[0]));

        DrawFPS(0,0);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
```

Here is the global constant COLOR definition, assume it is filled:
```c
static struct {
    struct {
        color_t Blue[101];
        color_t Yellow[101];
        color_t Red[101];
        color_t Purple[101];
        color_t Cyan[101];
        color_t Grey[101];
        color_t Green[101];
        color_t Orange[101];
        color_t Pink[101];
    } Static; // [0] == Black; [100] == White
    struct {
        color_t Primary[101];
        color_t Secondary[101];
        color_t Tertiary[101];
        color_t Neutral[101];
        color_t Error[101];
    } Baseline; // [0] == Black; [100] == White
    struct {
        color_t Primary[2];
        color_t OnPrimary[2];
        color_t PrimaryContainer[2];
        color_t OnPrimaryContainer[2];
        color_t Secondary[2];
        color_t OnSecondary[2];
        color_t SecondaryContainer[2];
        color_t OnSecondaryContainer[2];
        color_t Tertiary[2];
        color_t OnTertiary[2];
        color_t TertiaryContainer[2];
        color_t OnTertiaryContainer[2];
        color_t PrimaryFixed[2];
        color_t OnPrimaryFixed[2];
        color_t PrimaryFixedDim[2];
        color_t OnPrimaryFixedVariant[2];
        color_t InversePrimary[2];
        color_t SecondaryFixed[2];
        color_t OnSecondaryFixed[2];
        color_t SecondaryFixedDim[2];
        color_t OnSecondaryFixedVariant[2];
        color_t TertiaryFixed[2];
        color_t OnTertiaryFixed[2];
        color_t TertiaryFixedDim[2];
        color_t OnTertiaryFixedVariant[2];
        color_t Error[2];
        color_t OnError[2];
        color_t ErrorContainer[2];
        color_t OnErrorContainer[2];
        color_t Surface[2];
        color_t OnSurface[2];
        color_t SurfaceVariant[2];
        color_t OnSurfaceVariant[2];
        color_t SurfaceContainerHighest[2];
        color_t SurfaceContainerHigh[2];
        color_t SurfaceContainer[2];
        color_t SurfaceContainerLow[2];
        color_t SurfaceContainerLowest[2];
        color_t InverseSurface[2];
        color_t InverseOnSurface[2];
        color_t SurfaceTint[2];
        color_t Outline[2];
        color_t OutlineVariant[2];
        color_t Background[2];
        color_t OnBackground[2];
        color_t SurfaceBright[2];
        color_t SurfaceDim[2];
    } Scheme; // [0] == Dark; [1] == Light
} COLOR = {0}; // Global Color Lookup
```

make the background the color like in the pictures, even if it isn't in the COLOR struct.
Also, do not write comments, make the code as simple and short as possible.
Make the theme switch on `Space` key.
