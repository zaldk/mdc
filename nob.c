#define NOB_IMPLEMENTATION
#include "nob.h"

#define BUILD ".build/"
#define SRC "src/"
static Cmd cmd = {0};

int main(int argc, char **argv) {
    #ifndef _WIN32
        NOB_GO_REBUILD_URSELF(argc, argv);
    #endif

    #ifdef _WIN32
        cmd_append(&cmd, "cmd", "/c", "cls");
    #else
        cmd_append(&cmd, "clear");
    #endif
    assert(cmd_run(&cmd));

    assert(nob_mkdir_if_not_exists(BUILD));
    assert(nob_write_entire_file(BUILD".gitignore", "*", 1));

    char* nob_name = shift(argv, argc);
    if (argc == 0) {
        nob_log(NOB_INFO, "USAGE: %s N r?\n\tN - Number of the demo to build\n\tr - optional flag to run the built demo", nob_name);
        nob_log(NOB_INFO,
            "Available demos:\n\t"
            "1 - color schemes\n\t"
            "2 - all colors\n\t"
            "3 - rounded rectangles\n\t"
            "4 - buttons\n\t"
            "5 - icons\n\t"
            "6 - tabs\n\t"
            "7 - interactive (basic, manual)\n\t"
            "8 - layouting engine\n\t"
        );
        return 0;
    }

    char* arg_demo = shift(argv, argc);

    if (arg_demo != NULL && arg_demo[0] >= '0' && arg_demo[0] <= '9') {
        char build_here[64] = {0};
        snprintf((char*)build_here, 64, BUILD"demo-%c.exe", arg_demo[0]);
        char* source_here[64] = {0};
        snprintf((char*)source_here, 64, SRC"demo-%c.c", arg_demo[0]);

        #ifdef _WIN32
            cmd_append(&cmd, "zig", "cc");
        #else
            nob_cc(&cmd);
        #endif
        // cmd_append(&cmd, "-Wall", "-Wextra", "-g", "-std=c99");
        // cmd_append(&cmd, "-fsanitize=address", "-fsanitize=leak", "-fsanitize=undefined", "-fsanitize=null");
        #ifndef _WIN32
            cmd_append(&cmd, "-L./thirdparty/raylib/lib/");
        #endif
        cmd_append(&cmd, "-o", (char*)build_here, (char*)source_here);
        #ifdef _WIN32
            cmd_append(&cmd, "./thirdparty/raylib/lib/raylib.lib", "-lopengl32", "-lgdi32", "-lwinmm", "-luuid");
        #else
            cmd_append(&cmd, "-lm", "-l:libraylib.a");
        #endif
        if (!cmd_run(&cmd)) return 1;

        nob_log(NOB_INFO, "Built Demo %c", arg_demo[0]);
        if (argc == 0) return 0;

        char* arg_run = shift(argv, argc);
        if (arg_run != NULL && arg_run[0] == 'r') {
            cmd_append(&cmd, build_here);
            if (!cmd_run(&cmd)) return 1;
        }
    }

    return 0;
}
