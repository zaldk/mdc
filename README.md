# Material Design in C

## Building

1. Unpack the archives in `thirdparty/` and `assets/`
2. Bootstrap the builder: `cc -o nob nob.c`
3. Run the builder: `./nob`

---

## Demo 1 - Scheme Colors

| Dark Scheme | Light Scheme |
|-------------|--------------|
| ![Dark Theme](images/demo_1_layout_dark.png) | ![Light Theme](images/demo_1_layout_light.png) |

---

## Demo 2 - All Colors

| All Colors (Interpolated) | Provided Colors |
|---------------------------|-----------------|
| ![Dark Theme](images/demo_2_all_colors_interpolated.png) | ![Light Theme](images/demo_2_all_colors_raw.png) |

---

## Demo 3 - Rounded Rectangles

![Rounded Rectangles](images/demo_3_round_boxes.png)

---

## Demo 4 - Button Reference

| Dark Scheme | Light Scheme |
|-------------|--------------|
| ![Dark Theme](images/demo_4_button_colors_dark.png) | ![Light Theme](images/demo_4_button_colors_light.png) |

---

## Demo 5 - Material Symbols

| Dark Scheme | Light Scheme |
|-------------|--------------|
| ![Dark Theme](images/demo_5_icons_dark.png) | ![Light Theme](images/demo_5_icons_light.png) |

---

## Demo 6 - Tabs

| Dark Scheme | Light Scheme |
|-------------|--------------|
| ![Dark Theme](images/demo_6_tabs_inline_dark.png) | ![Light Theme](images/demo_6_tabs_inline_light.png) |
| ![Dark Theme](images/demo_6_tabs_stacked_dark.png) | ![Light Theme](images/demo_6_tabs_stacked_light.png) |

---

## Demo 7 - Interactive (Manual)

| Dark Scheme | Light Scheme |
|-------------|--------------|
| ![Dark Theme](images/demo_7_basic_interaction_dark.png) | ![Light Theme](images/demo_7_basic_interaction_light.png) |

---

## Demo 8 - Layoting Engine (Interactive)

> [!Note]
> This is an actually interactive demo,  
> the tabs can be selected and the dividers can be moved.  
> The layout is described in the `MakeLayout` function in the `demo-8.c` file.

| Dark Scheme | Light Scheme |
|-------------|--------------|
| ![Dark Theme](images/demo_8_layouting_engine_dark.png) | ![Light Theme](images/demo_8_layouting_engine_light.png) |
