#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

char* get_path(char *cmd) {
    static char buf[256];
    char *dirs[] = {"/bin/", "/usr/bin/", NULL};
    for (int i = 0; dirs[i]; i++) {
        snprintf(buf, sizeof(buf), "%s%s", dirs[i], cmd);
        if (access(buf, X_OK) == 0) return buf;
    }
    return NULL;
}

int main() {
    char line[256];
    while (1) {
        printf("myshell> ");
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\n")] = 0;
        if (!strlen(line)) continue;

        int bg = 0;
        char *bg_pos = strstr(line, " bg");
        if (bg_pos) {
            bg = 1;
            *bg_pos = '\0';
        }

        char *argv[64];
        int argc = 0;
        char *tok = strtok(line, " ");
        while (tok) {
            argv[argc++] = tok;
            tok = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        char *path = get_path(argv[0]);
        if (!path) {
            printf("not found: %s\n", argv[0]);
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            execve(path, argv, environ);
            perror("execve");
            exit(1);
        } else if (pid > 0) {
            if (!bg) waitpid(pid, NULL, 0);
            else printf("[bg] pid=%d\n", pid);
        } else {
            perror("fork");
        }
    }
    return 0;
}
