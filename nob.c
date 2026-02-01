#define NOB_IMPLEMENTATION
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

#define BUILD ".build/"
#define SRC "src/"
static Cmd cmd = {0};

int main(int argc, char **argv) {
    #ifdef _WIN32
    #error Microslop Windows is a toy OS for niche gamers.
    #endif

    NOB_GO_REBUILD_URSELF(argc, argv);

    cmd_append(&cmd, "clear");
    assert(cmd_run(&cmd));

    if (!nob_file_exists(BUILD)) assert(nob_mkdir_if_not_exists(BUILD));
    assert(nob_write_entire_file(BUILD".gitignore", "*", 1));

    char* arg = NULL;
    char* nob_name = shift(argv, argc);
    char demo_num = 0;
    bool do_run = false;
    bool use_mingw = false;

    while (argc > 0 && (arg = shift(argv, argc))) {
        if (arg[0] > '0' && arg[0] <= '9') {
            if (demo_num == 0) {
                demo_num = arg[0] - '0';
            } else {
                nob_log(NOB_WARNING, "Only the first demo number is used, others are ignored. Using #%d", demo_num);
            }
        }
        if (arg[0] == 'r') do_run = true;
        if (arg[0] == 'w') use_mingw = true;
    }

    if (demo_num == 0) {
        nob_log(NOB_ERROR, "You must provide a number for the Demo you want to build.\n");
        nob_log(NOB_INFO,
            "USAGE: %s N r? w?\n\t"
            "N\tnumber of the demo to build (required)\n\t"
            "r\tflag to run the built demo  (optional)\n\t"
            "w\tflag to build using MinGW   (optional)\n\t"
        , nob_name);
        nob_log(NOB_INFO,
            "Available demos:\n\t"
            "1\tcolor schemes\n\t"
            "2\tall colors\n\t"
            "3\trounded rectangles\n\t"
            "4\tbuttons\n\t"
            "5\ticons\n\t"
            "6\ttabs\n\t"
            "7\tinteractive (basic, manual)\n\t"
            "8\tlayouting engine\n\t"
        );
        return 0;
    }

    char build_here[64] = {0};
    snprintf((char*)build_here, 64, BUILD"demo-%d.exe", demo_num);
    char source_here[64] = {0};
    snprintf((char*)source_here, 64, SRC"demo-%d.c", demo_num);

    if (use_mingw) {
        cmd_append(&cmd, "x86_64-w64-mingw32-gcc");
    } else {
        nob_cc(&cmd);
    }
    cmd_append(&cmd, "-Wall", "-Wextra", "-g", "-std=c99");
    // cmd_append(&cmd, "-fsanitize=address", "-fsanitize=leak", "-fsanitize=undefined", "-fsanitize=null");
    cmd_append(&cmd, "-I./thirdparty/raylib/include/");
    cmd_append(&cmd, "-L./thirdparty/raylib/lib/");
    cmd_append(&cmd, "-o", (char*)build_here, (char*)source_here);
    if (use_mingw) {
        cmd_append(&cmd, "./thirdparty/raylib-5.5_win64_mingw-w64/lib/libraylib.a");
        cmd_append(&cmd, "-lopengl32", "-lgdi32", "-lwinmm");
    } else {
        cmd_append(&cmd, "-lm");
        cmd_append(&cmd, "-l:libraylib.a");
    }
    if (!cmd_run(&cmd)) return 1;

    nob_log(NOB_INFO, "Built Demo %c", demo_num);

    if (do_run) {
        if (use_mingw) {
            cmd_append(&cmd, "wine", build_here);
        } else {
            cmd_append(&cmd, build_here);
        }
        if (!cmd_run(&cmd)) return 1;
    }

    return 0;
}
