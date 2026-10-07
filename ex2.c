#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        return 1;
    }

    int count = atoi(argv[1]);

    for (int k = 0; k < count; ++k) {
        pid_t child_id = fork();
        if (child_id < 0) {
            perror("Fork failed");
            exit(1);
        if (child_id > 0) {
            sleep(5);
            break; 
        }

    }

    return 0;
}
