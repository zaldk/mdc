#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#define NOB_EXPERIMENTAL_DELETE_OLD
#include "nob.h"

#define BUILD ".build/"
#define SRC "src/"
static Cmd cmd = {0};

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    cmd_append(&cmd, "clear");
    if (!cmd_run(&cmd)) return 1;

    cmd_append(&cmd, "test", "-d", BUILD);
    if (!cmd_run(&cmd)) {
        cmd_append(&cmd, "mkdir", "-p", BUILD);
        if (!cmd_run(&cmd)) return 1;
    }

    cmd_append(&cmd, "test", "-f", BUILD".gitignore");
    if (!cmd_run(&cmd)) {
        cmd_append(&cmd, "printf", "*");
        if (!cmd_run(&cmd, .stdout_path = BUILD".gitignore")) return 1;
    }

    nob_cc(&cmd);
    cmd_append(&cmd, "-Wall", "-Wextra", "-g", "-std=gnu99");
    // cmd_append(&cmd, "-Wno-unused-parameter", "-Wno-unused-variable");
    // cmd_append(&cmd, "-fsanitize=address", "-fsanitize=leak", "-fsanitize=undefined", "-fsanitize=null");
    cmd_append(&cmd, "-L./thirdparty/raylib-5.5_linux_amd64/lib/");
    cmd_append(&cmd, "-o", BUILD"exe", SRC"main.c");
    cmd_append(&cmd, "-lm", "-lraylib");
    if (!cmd_run(&cmd)) return 1;

    shift(argv, argc);
    if (argc > 0) {
        char* arg = shift(argv, argc);
        if (arg != NULL && arg[0] == 'r') {
            cmd_append(&cmd, BUILD"exe");
            if (!cmd_run(&cmd)) return 1;
        }
    }

    return 0;
}
