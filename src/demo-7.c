#include "demo-helpers.h"

static Vector2 MOUSE = {0};
static bool MOUSE_DOWN = false;
static bool MOUSE_PRESSED = false;

static MDCButton b_def = {0};
static MDCButton b_tog = {0};

#define TABS_COUNT 3
static MDCTab ptabs[TABS_COUNT] = {0};
static MDCTab stabs[TABS_COUNT] = {0};

void InitLayout(void) {
    // {{{

    b_def.box.x = 100;
    b_def.box.y = 100;
    b_def.design = MD_BUTTON_DESIGN_ELEVATED;
    b_def.type = MD_BUTTON_TYPE_DEFAULT;
    b_def.size = MD_SIZE_M;
    b_def.text = "Click Me!";
    b_def = mdc_button(b_def);

    b_tog.box.x = 100 + b_def.box.w + 100;
    b_tog.box.y = 100;
    b_tog.design = MD_BUTTON_DESIGN_ELEVATED;
    b_tog.type = MD_BUTTON_TYPE_TOGGLE;
    b_tog.size = MD_SIZE_M;
    b_tog.text = "Toggle Me!";
    b_tog = mdc_button(b_tog);

    // {{{ PTABS
    i32 icon_home = find_icon("home");
    ptabs[0].box.x = 100;
    ptabs[0].box.y = 100 + b_def.box.h + 100;
    ptabs[0].icon_code = icon_home;
    ptabs[0].icon_align = MD_ICON_ALIGN_STACKED;
    ptabs[0].type = MDC_TAB_TYPE_PRIMARY;
    ptabs[0].text = "Home";
    ptabs[0] = mdc_tab(ptabs[0]);

    i32 icon_delete = find_icon("delete");
    ptabs[1].box.x = ptabs[0].box.x + ptabs[0].box.w;
    ptabs[1].box.y = 100 + b_def.box.h + 100;
    ptabs[1].icon_code = icon_delete;
    ptabs[1].icon_align = MD_ICON_ALIGN_STACKED;
    ptabs[1].type = MDC_TAB_TYPE_PRIMARY;
    ptabs[1].text = "Delete";
    ptabs[1] = mdc_tab(ptabs[1]);

    i32 icon_inbox = find_icon("inbox");
    ptabs[2].box.x = ptabs[1].box.x + ptabs[1].box.w;
    ptabs[2].box.y = 100 + b_def.box.h + 100;
    ptabs[2].icon_code = icon_inbox;
    ptabs[2].icon_align = MD_ICON_ALIGN_STACKED;
    ptabs[2].type = MDC_TAB_TYPE_PRIMARY;
    ptabs[2].text = "Inbox";
    ptabs[2] = mdc_tab(ptabs[2]);
    // }}}

    // {{{ STABS
    stabs[0].box.x = 100;
    stabs[0].box.y = 100 + b_def.box.h + 100 + ptabs[0].box.h;
    stabs[0].box.w = ptabs[0].box.w;
    stabs[0].type = MDC_TAB_TYPE_SECONDARY;
    stabs[0].text = "Home";
    stabs[0] = mdc_tab(stabs[0]);

    stabs[1].box.x = stabs[0].box.x + stabs[0].box.w;
    stabs[1].box.y = stabs[0].box.y;
    stabs[1].box.w = ptabs[1].box.w;
    stabs[1].type = MDC_TAB_TYPE_SECONDARY;
    stabs[1].text = "Delete";
    stabs[1] = mdc_tab(stabs[1]);

    stabs[2].box.x = stabs[1].box.x + stabs[1].box.w;
    stabs[2].box.y = stabs[0].box.y;
    stabs[2].box.w = ptabs[2].box.w;
    stabs[2].type = MDC_TAB_TYPE_SECONDARY;
    stabs[2].text = "Inbox";
    stabs[2] = mdc_tab(stabs[2]);
    // }}}

    // }}}
}

void DrawLayout() {
    // {{{
    if (CheckCollisionPointRec(MOUSE, *(Rectangle*)&b_def.box)) {
        if (MOUSE_DOWN) {
            b_def.state = MD_BUTTON_STATE_PRESSED;
        } else {
            b_def.state = MD_BUTTON_STATE_HOVERED;
        }
    } else {
        b_def.state = MD_BUTTON_STATE_ENABLED;
    }
    b_def = mdc_button(b_def);
    mdc_render_button(b_def);

    if (CheckCollisionPointRec(MOUSE, *(Rectangle*)&b_tog.box)) {
        if (MOUSE_PRESSED) {
            b_tog.selected = !b_tog.selected;
        } else {
            if (MOUSE_DOWN) {
                b_tog.state = MD_BUTTON_STATE_PRESSED;
            } else {
                b_tog.state = MD_BUTTON_STATE_HOVERED;
            }
        }
    } else {
        b_tog.state = MD_BUTTON_STATE_ENABLED;
    }
    b_tog = mdc_button(b_tog);
    mdc_render_button(b_tog);

    DrawBoxRound(
        ptabs[0].box.x-20,
        ptabs[0].box.y-20,
        ptabs[TABS_COUNT-1].box.x + ptabs[TABS_COUNT-1].box.w - ptabs[0].box.x + 40,
        ptabs[0].box.h + stabs[0].box.h + 40,
        20,20,20,20,
        COLOR.Scheme.SurfaceContainerLow
    );
    for (i32 index = 0; index < TABS_COUNT; index++) {
        MDCTab* tab = &ptabs[index];
        if (CheckCollisionPointRec(MOUSE, *(Rectangle*)&(tab->box))) {
            if (MOUSE_PRESSED) {
                for (i32 jndex = 0; jndex < TABS_COUNT; jndex++) {
                    ptabs[jndex].active = false;
                }
                tab->active = true;
            } else {
                if (MOUSE_DOWN) {
                    tab->state = MDC_TAB_STATE_PRESSED;
                } else {
                    tab->state = MDC_TAB_STATE_HOVERED;
                }
            }
        } else {
            tab->state = MDC_TAB_STATE_ENABLED;
        }
        *tab = mdc_tab(*tab);
        mdc_render_tab(*tab);
    }
    for (i32 index = 0; index < TABS_COUNT; index++) {
        MDCTab* tab = &stabs[index];
        if (CheckCollisionPointRec(MOUSE, *(Rectangle*)&(tab->box))) {
            if (MOUSE_PRESSED) {
                for (i32 jndex = 0; jndex < TABS_COUNT; jndex++) {
                    stabs[jndex].active = false;
                }
                tab->active = true;
            } else {
                if (MOUSE_DOWN) {
                    tab->state = MDC_TAB_STATE_PRESSED;
                } else {
                    tab->state = MDC_TAB_STATE_HOVERED;
                }
            }
        } else {
            tab->state = MDC_TAB_STATE_ENABLED;
        }
        *tab = mdc_tab(*tab);
        mdc_render_tab(*tab);
    }
    // }}}
}

Vec2 measure_text_fn(char* text, f32 font_size_px) {
    return MeasureTextEx(ROBOTO, text, font_size_px, 0);
}

int main(void) {
    const int W = 600;
    const int H = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_ALWAYS_RUN | FLAG_MSAA_4X_HINT);
    InitWindow(W, H, "FLOAT");
    // SetTargetFPS(500);

    init_fonts(true); // demo-helper; must be done AFTER InitWindow()
    md_color_global_init(true);

    i32 mon = GetCurrentMonitor();
    Vec2 monitor_size = (Vec2){GetMonitorPhysicalWidth(mon), GetMonitorPhysicalHeight(mon)};
    Vec2 monitor_resolution = (Vec2){GetMonitorWidth(mon), GetMonitorHeight(mon)};
    md_ctx_init(monitor_size, monitor_resolution);
    md_ctx_set_scaling(2);
    md_ctx_set_measure_text(measure_text_fn);

    InitLayout();
    while (!WindowShouldClose()) {
        // {{{
        MOUSE = GetMousePosition();
        MOUSE_DOWN = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        MOUSE_PRESSED = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        if (IsKeyPressed(KEY_SPACE)) md_color_global_switch_theme();

        BeginDrawing();
        ClearBackground(COLOR.Scheme.Background);

        // dotted background
        f32 dp = md_dp2px(1);
        for (f32 y = 0; y < GetScreenHeight(); y += dp*10) {
            for (f32 x = 0; x < GetScreenWidth(); x += dp*10) {
                MDColor col = COLOR.Scheme.OnBackground;
                col.a = 51;
                DrawPixel((i32)x, (i32)y, col);
            }
        }

        DrawLayout();
        MDCommand cmd = {0};
        while (md_ctx_poll(&cmd)) {
            // {{{
            switch (cmd.type) {
                case MD_COMMAND_DRAW_BOX: {
                    MDBox box = cmd.as.box.box;
                    MDCorners round = cmd.as.box.round;
                    MDColor col = cmd.as.box.color;
                    DrawBoxRound(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, col);
                }; break;
                case MD_COMMAND_DRAW_OUTLINE: {
                    MDBox box = cmd.as.outline.box;
                    MDCorners round = cmd.as.outline.round;
                    MDColor col = cmd.as.outline.color;
                    f32 thickness = cmd.as.outline.thickness;
                    DrawBoxRoundLines(box.x, box.y, box.w, box.h, round.tl, round.tr, round.bl, round.br, thickness, col);
                }; break;
                case MD_COMMAND_DRAW_TEXT: {
                    MDBox box = cmd.as.text.box;
                    MDColor col = cmd.as.text.color;
                    f32 fs = cmd.as.text.font_size;
                    DrawTextEx(ROBOTO, cmd.as.text.text, (Vector2){box.x, box.y}, fs, 0, col);
                }; break;
                case MD_COMMAND_DRAW_ICON: {
                    MDBox box = cmd.as.icon.box;
                    MDColor col = cmd.as.icon.color;
                    f32 fs = cmd.as.icon.icon_size;
                    // 0.1fs is needed because the font's symbols are not squares,
                    // so by default the icons are shown a bit to the left.
                    DrawTextCodepoint(ICONS, cmd.as.icon.codepoint, (Vector2){box.x+fs*0.1, box.y}, fs, col);
                }; break;
                default: UNREACHABLE();
            }
            // }}}
        }

        // DrawFPS(0,0);
        DrawTextEx(ROBOTO, "Press 'Space' To Change Theme", (Vector2){5, GetScreenHeight()-20}, 20.0, 0.0, COLOR.Scheme.OnBackground);
        EndDrawing();
        // }}}
    }

    UnloadFont(ICONS);
    UnloadFont(ROBOTO);
    CloseWindow();
    return 0;
}
