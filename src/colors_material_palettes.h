#define COLOR_LABELS_ALL \
    Y(Baseline, Primary,    0) \
    Y(Baseline, Secondary,  1) \
    Y(Baseline, Tertiary,   2) \
    Y(Baseline, Error,      3) \
    Y(Baseline, Neutral,    4) \
    Y(Static,   Grey,       5) \
    Y(Static,   Pink,       6) \
    Y(Static,   Red,        7) \
    Y(Static,   Orange,     8) \
    Y(Static,   Yellow,     9) \
    Y(Static,   Green,     10) \
    Y(Static,   Cyan,      11) \
    Y(Static,   Blue,      12) \
    Y(Static,   Purple,    13)

#define COLOR_LABELS_BASELINE \
    Y(PRIMARY,   Primary) \
    Y(SECONDARY, Secondary) \
    Y(TERTIARY,  Tertiary) \
    Y(NEUTRAL,   Neutral) \
    Y(ERROR,     Error)

#define COLOR_LABELS_STATIC \
    Y(BLUE,      Blue) \
    Y(YELLOW,    Yellow) \
    Y(RED,       Red) \
    Y(PURPLE,    Purple) \
    Y(CYAN,      Cyan) \
    Y(GREY,      Grey) \
    Y(GREEN,     Green) \
    Y(ORANGE,    Orange) \
    Y(PINK,      Pink)



/* from https://cs.android.com/androidx/platform/frameworks/support/+/androidx-main:compose/material3/material3/src/commonMain/kotlin/androidx/compose/material3/tokens/PaletteTokens.kt */

#define MATERIAL_PALETTE_BASELINE_ERROR \
    X(Error, 10, 65, 14, 11) \
    X(Error, 20, 96, 20, 16) \
    X(Error, 30, 140, 29, 24) \
    X(Error, 40, 179, 38, 30) \
    X(Error, 50, 220, 54, 46) \
    X(Error, 60, 228, 105, 98) \
    X(Error, 70, 236, 146, 142) \
    X(Error, 80, 242, 184, 181) \
    X(Error, 90, 249, 222, 220) \
    X(Error, 95, 252, 238, 238) \
    X(Error, 99, 255, 251, 249)

#define MATERIAL_PALETTE_BASELINE_NEUTRAL \
    X(Neutral, 4,  15, 13, 19) \
    X(Neutral, 6,  20, 18, 24) \
    X(Neutral, 10, 29, 27, 32) \
    X(Neutral, 12, 33, 31, 38) \
    X(Neutral, 17, 43, 41, 48) \
    X(Neutral, 20, 50, 47, 53) \
    X(Neutral, 22, 54, 52, 59) \
    X(Neutral, 24, 59, 56, 62) \
    X(Neutral, 30, 72, 70, 76) \
    X(Neutral, 40, 96, 93, 100) \
    X(Neutral, 50, 121, 118, 125) \
    X(Neutral, 60, 147, 143, 150) \
    X(Neutral, 70, 174, 169, 177) \
    X(Neutral, 80, 202, 197, 205) \
    X(Neutral, 87, 222, 216, 225) \
    X(Neutral, 90, 230, 224, 233) \
    X(Neutral, 92, 236, 230, 240) \
    X(Neutral, 94, 243, 237, 247) \
    X(Neutral, 95, 245, 239, 247) \
    X(Neutral, 96, 247, 242, 250) \
    X(Neutral, 98, 254, 247, 255) \
    X(Neutral, 99, 255, 251, 255)

#define MATERIAL_PALETTE_BASELINE_PRIMARY \
    X(Primary, 10, 33, 0, 93) \
    X(Primary, 20, 56, 30, 114) \
    X(Primary, 30, 79, 55, 139) \
    X(Primary, 40, 103, 80, 164) \
    X(Primary, 50, 127, 103, 190) \
    X(Primary, 60, 154, 130, 219) \
    X(Primary, 70, 182, 157, 248) \
    X(Primary, 80, 208, 188, 255) \
    X(Primary, 90, 234, 221, 255) \
    X(Primary, 95, 246, 237, 255) \
    X(Primary, 99, 255, 251, 254)

#define MATERIAL_PALETTE_BASELINE_SECONDARY \
    X(Secondary, 10, 29, 25, 43) \
    X(Secondary, 20, 51, 45, 65) \
    X(Secondary, 30, 74, 68, 88) \
    X(Secondary, 40, 98, 91, 113) \
    X(Secondary, 50, 122, 114, 137) \
    X(Secondary, 60, 149, 141, 165) \
    X(Secondary, 70, 176, 167, 192) \
    X(Secondary, 80, 204, 194, 220) \
    X(Secondary, 90, 232, 222, 248) \
    X(Secondary, 95, 246, 237, 255) \
    X(Secondary, 99, 255, 251, 254)

#define MATERIAL_PALETTE_BASELINE_TERTIARY \
    X(Tertiary, 10, 49, 17, 29) \
    X(Tertiary, 20, 73, 37, 50) \
    X(Tertiary, 30, 99, 59, 72) \
    X(Tertiary, 40, 125, 82, 96) \
    X(Tertiary, 50, 152, 105, 119) \
    X(Tertiary, 60, 181, 131, 146) \
    X(Tertiary, 70, 210, 157, 172) \
    X(Tertiary, 80, 239, 184, 200) \
    X(Tertiary, 90, 255, 216, 228) \
    X(Tertiary, 95, 255, 236, 241) \
    X(Tertiary, 99, 255, 251, 250)
/*
#define MATERIAL_PALETTE_BASELINE_PRIMARY \
    X(Primary,   10, 0x21, 0x00, 0x5D) \
    X(Primary,   20, 0x38, 0x1E, 0x72) \
    X(Primary,   30, 0x4F, 0x37, 0x8B) \
    X(Primary,   40, 0x67, 0x50, 0xA4) \
    X(Primary,   50, 0x7F, 0x67, 0xBE) \
    X(Primary,   60, 0x9A, 0x82, 0xDB) \
    X(Primary,   70, 0xB6, 0x9D, 0xF8) \
    X(Primary,   80, 0xD0, 0xBC, 0xFF) \
    X(Primary,   90, 0xEA, 0xDD, 0xFF) \
    X(Primary,   95, 0xF6, 0xED, 0xFF) \
    X(Primary,   99, 0xFF, 0xFB, 0xFE)

#define MATERIAL_PALETTE_BASELINE_SECONDARY \
    X(Secondary, 10, 0x1D, 0x19, 0x2B) \
    X(Secondary, 20, 0x33, 0x2D, 0x41) \
    X(Secondary, 30, 0x4A, 0x44, 0x58) \
    X(Secondary, 40, 0x62, 0x5B, 0x71) \
    X(Secondary, 50, 0x7A, 0x72, 0x89) \
    X(Secondary, 60, 0x95, 0x8D, 0xA5) \
    X(Secondary, 70, 0xB0, 0xA7, 0xC0) \
    X(Secondary, 80, 0xCC, 0xC2, 0xDC) \
    X(Secondary, 90, 0xE8, 0xDE, 0xF8) \
    X(Secondary, 95, 0xF6, 0xED, 0xFF) \
    X(Secondary, 99, 0xFF, 0xFB, 0xFE)

#define MATERIAL_PALETTE_BASELINE_TERTIARY \
    X(Tertiary,  10, 0x31, 0x11, 0x1D) \
    X(Tertiary,  20, 0x49, 0x25, 0x32) \
    X(Tertiary,  30, 0x63, 0x3B, 0x48) \
    X(Tertiary,  40, 0x7D, 0x52, 0x60) \
    X(Tertiary,  50, 0x98, 0x69, 0x77) \
    X(Tertiary,  60, 0xB5, 0x83, 0x92) \
    X(Tertiary,  70, 0xD2, 0x9D, 0xAC) \
    X(Tertiary,  80, 0xEF, 0xB8, 0xC8) \
    X(Tertiary,  90, 0xFF, 0xD8, 0xE4) \
    X(Tertiary,  95, 0xFF, 0xEC, 0xF1) \
    X(Tertiary,  99, 0xFF, 0xFB, 0xFE)

#define MATERIAL_PALETTE_BASELINE_NEUTRAL \
    X(Neutral,   99, 0xFF, 0xFB, 0xFF) \
    X(Neutral,   98, 0xFE, 0xF7, 0xFF) \
    X(Neutral,   96, 0xF7, 0xF2, 0xFA) \
    X(Neutral,   95, 0xF5, 0xEF, 0xF7) \
    X(Neutral,   94, 0xF3, 0xED, 0xF7) \
    X(Neutral,   92, 0xEC, 0xE6, 0xF0) \
    X(Neutral,   90, 0xE6, 0xE0, 0xE9) \
    X(Neutral,   87, 0xDE, 0xD8, 0xE1) \
    X(Neutral,   80, 0xCA, 0xC5, 0xCD) \
    X(Neutral,   70, 0xAE, 0xA9, 0xB1) \
    X(Neutral,   60, 0x93, 0x8F, 0x96) \
    X(Neutral,   50, 0x79, 0x76, 0x7D) \
    X(Neutral,   40, 0x60, 0x5D, 0x64) \
    X(Neutral,   30, 0x48, 0x46, 0x4C) \
    X(Neutral,   24, 0x3B, 0x38, 0x3E) \
    X(Neutral,   22, 0x36, 0x34, 0x3B) \
    X(Neutral,   20, 0x32, 0x2F, 0x35) \
    X(Neutral,   17, 0x2B, 0x29, 0x30) \
    X(Neutral,   12, 0x21, 0x1F, 0x26) \
    X(Neutral,   10, 0x1D, 0x1B, 0x20) \
    X(Neutral,    6, 0x14, 0x12, 0x18) \
    X(Neutral,    4, 0x0F, 0x0D, 0x13)

#define MATERIAL_PALETTE_BASELINE_ERROR \
    X(Error,     10, 0x41, 0x0E, 0x0B) \
    X(Error,     20, 0x60, 0x14, 0x10) \
    X(Error,     30, 0x8C, 0x1D, 0x18) \
    X(Error,     40, 0xB3, 0x26, 0x1E) \
    X(Error,     50, 0xDC, 0x36, 0x2E) \
    X(Error,     60, 0xE4, 0x69, 0x62) \
    X(Error,     70, 0xEC, 0x92, 0x8E) \
    X(Error,     80, 0xF2, 0xB8, 0xB5) \
    X(Error,     90, 0xF9, 0xDE, 0xDC) \
    X(Error,     95, 0xFC, 0xEE, 0xEE) \
    X(Error,     99, 0xFF, 0xFB, 0xF9)
*/



#define MATERIAL_PALETTE_STATIC_BLUE \
    X(Blue,   98, 0xF5, 0xFA, 0xFF) \
    X(Blue,   95, 0xE7, 0xF2, 0xFF) \
    X(Blue,   90, 0xD0, 0xE4, 0xFF) \
    X(Blue,   80, 0xA1, 0xC9, 0xFF) \
    X(Blue,   70, 0x76, 0xAC, 0xFF) \
    X(Blue,   60, 0x4E, 0x8F, 0xF8) \
    X(Blue,   50, 0x32, 0x71, 0xEA) \
    X(Blue,   40, 0x11, 0x57, 0xCE) \
    X(Blue,   30, 0x04, 0x40, 0x9F) \
    X(Blue,   20, 0x01, 0x2C, 0x6F) \
    X(Blue,   10, 0x00, 0x19, 0x44)

#define MATERIAL_PALETTE_STATIC_YELLOW \
    X(Yellow, 98, 0xFF, 0xFA, 0xDE) \
    X(Yellow, 95, 0xFF, 0xF2, 0xB4) \
    X(Yellow, 90, 0xFF, 0xE0, 0x7C) \
    X(Yellow, 80, 0xFC, 0xBD, 0x00) \
    X(Yellow, 70, 0xEF, 0x98, 0x00) \
    X(Yellow, 60, 0xD3, 0x7B, 0x00) \
    X(Yellow, 50, 0xB1, 0x63, 0x00) \
    X(Yellow, 40, 0x8F, 0x4E, 0x06) \
    X(Yellow, 30, 0x6D, 0x3A, 0x01) \
    X(Yellow, 20, 0x4D, 0x26, 0x00) \
    X(Yellow, 10, 0x2F, 0x14, 0x00)

#define MATERIAL_PALETTE_STATIC_RED \
    X(Red,    98, 0xFF, 0xF8, 0xF8) \
    X(Red,    95, 0xFF, 0xEC, 0xEE) \
    X(Red,    90, 0xFF, 0xDA, 0xDC) \
    X(Red,    80, 0xFF, 0xB3, 0xAE) \
    X(Red,    70, 0xFF, 0x89, 0x83) \
    X(Red,    60, 0xF5, 0x5E, 0x57) \
    X(Red,    50, 0xDB, 0x37, 0x2D) \
    X(Red,    40, 0xB3, 0x25, 0x1E) \
    X(Red,    30, 0x8A, 0x1A, 0x16) \
    X(Red,    20, 0x60, 0x15, 0x0F) \
    X(Red,    10, 0x3A, 0x09, 0x07)

#define MATERIAL_PALETTE_STATIC_PURPLE \
    X(Purple, 98, 0xFD, 0xF8, 0xFF) \
    X(Purple, 95, 0xF7, 0xEC, 0xFE) \
    X(Purple, 90, 0xEE, 0xDC, 0xFE) \
    X(Purple, 80, 0xD9, 0xBA, 0xFD) \
    X(Purple, 70, 0xC5, 0x97, 0xFF) \
    X(Purple, 60, 0xAD, 0x72, 0xFF) \
    X(Purple, 50, 0x92, 0x54, 0xEA) \
    X(Purple, 40, 0x74, 0x38, 0xD2) \
    X(Purple, 30, 0x56, 0x29, 0xA4) \
    X(Purple, 20, 0x40, 0x0B, 0x84) \
    X(Purple, 10, 0x28, 0x02, 0x55)

#define MATERIAL_PALETTE_STATIC_CYAN \
    X(Cyan,   98, 0xF0, 0xFB, 0xFF) \
    X(Cyan,   95, 0xD8, 0xF6, 0xFF) \
    X(Cyan,   90, 0xAC, 0xED, 0xFF) \
    X(Cyan,   80, 0x60, 0xD5, 0xF3) \
    X(Cyan,   70, 0x00, 0xBB, 0xDF) \
    X(Cyan,   60, 0x00, 0x9E, 0xBB) \
    X(Cyan,   50, 0x00, 0x83, 0x9B) \
    X(Cyan,   40, 0x00, 0x68, 0x7C) \
    X(Cyan,   30, 0x00, 0x4E, 0x5D) \
    X(Cyan,   20, 0x00, 0x36, 0x41) \
    X(Cyan,   10, 0x00, 0x1F, 0x26)

#define MATERIAL_PALETTE_STATIC_GREY \
    X(Grey,   98, 0xF9, 0xF9, 0xF9) \
    X(Grey,   95, 0xF2, 0xF2, 0xF2) \
    X(Grey,   90, 0xE3, 0xE3, 0xE3) \
    X(Grey,   80, 0xC7, 0xC7, 0xC7) \
    X(Grey,   70, 0xAB, 0xAB, 0xAB) \
    X(Grey,   60, 0x91, 0x91, 0x91) \
    X(Grey,   50, 0x77, 0x77, 0x77) \
    X(Grey,   40, 0x5E, 0x5E, 0x5E) \
    X(Grey,   30, 0x47, 0x47, 0x47) \
    X(Grey,   20, 0x30, 0x30, 0x30) \
    X(Grey,   10, 0x1B, 0x1B, 0x1C)

#define MATERIAL_PALETTE_STATIC_GREEN \
    X(Green,  98, 0xF2, 0xFC, 0xEF) \
    X(Green,  95, 0xDD, 0xF8, 0xD8) \
    X(Green,  90, 0xBE, 0xEF, 0xBB) \
    X(Green,  80, 0x80, 0xDA, 0x88) \
    X(Green,  70, 0x44, 0xC2, 0x65) \
    X(Green,  60, 0x1A, 0xA6, 0x4A) \
    X(Green,  50, 0x12, 0x89, 0x37) \
    X(Green,  40, 0x00, 0x6C, 0x35) \
    X(Green,  30, 0x00, 0x52, 0x2C) \
    X(Green,  20, 0x00, 0x38, 0x1F) \
    X(Green,  10, 0x00, 0x21, 0x10)

#define MATERIAL_PALETTE_STATIC_ORANGE \
    X(Orange, 98, 0xFF, 0xF8, 0xF4) \
    X(Orange, 95, 0xFF, 0xED, 0xE1) \
    X(Orange, 90, 0xFF, 0xDC, 0xC3) \
    X(Orange, 80, 0xFF, 0xB6, 0x83) \
    X(Orange, 70, 0xFF, 0x8D, 0x41) \
    X(Orange, 60, 0xE8, 0x6E, 0x00) \
    X(Orange, 50, 0xC0, 0x5A, 0x01) \
    X(Orange, 40, 0x9A, 0x46, 0x00) \
    X(Orange, 30, 0x75, 0x34, 0x03) \
    X(Orange, 20, 0x52, 0x23, 0x02) \
    X(Orange, 10, 0x32, 0x12, 0x00)

#define MATERIAL_PALETTE_STATIC_PINK \
    X(Pink,   98, 0xFF, 0xF7, 0xFC) \
    X(Pink,   95, 0xFF, 0xEC, 0xF6) \
    X(Pink,   90, 0xFF, 0xD8, 0xEF) \
    X(Pink,   80, 0xFF, 0xAE, 0xE4) \
    X(Pink,   70, 0xFF, 0x7D, 0xD2) \
    X(Pink,   60, 0xF9, 0x4A, 0xAB) \
    X(Pink,   50, 0xDC, 0x25, 0x8D) \
    X(Pink,   40, 0xB6, 0x0D, 0x6E) \
    X(Pink,   30, 0x8D, 0x00, 0x53) \
    X(Pink,   20, 0x62, 0x04, 0x38) \
    X(Pink,   10, 0x3D, 0x00, 0x23)
