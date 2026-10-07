#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main() {
    pid_t child1_pid = fork();

    if (child1_pid == 0) {
        clock_t start_time = clock();
        for (volatile int i = 0; i < 90000000; i++);
        printf("Process ID: %d, Parent ID: %d, Time: %.2f ms\n",
               getpid(), getppid(),
               (double)(clock() - start_time) * 1000 / CLOCKS_PER_SEC);
        exit(0);
    } else {
        pid_t child2_pid = fork();

        if (child2_pid == 0) {
            clock_t start_time = clock();
            for (volatile int i = 0; i < 90000000; i++);
            printf("Process ID: %d, Parent ID: %d, Time: %.2f ms\n",
                   getpid(), getppid(),
                   (double)(clock() - start_time) * 1000 / CLOCKS_PER_SEC);
            exit(0);
        }

        clock_t start_time = clock();
        for (volatile int i = 0; i < 90000000; i++);
        printf("Process ID: %d, Parent ID: %d, Time: %.2f ms\n",
               getpid(), getppid(),
               (double)(clock() - start_time) * 1000 / CLOCKS_PER_SEC);

        waitpid(child1_pid, NULL, 0);
        waitpid(child2_pid, NULL, 0);
    }

    return 0;
}
