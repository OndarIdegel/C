#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage: %s <pid> [-s <signal_name>]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);
    int signo = SIGUSR1; // Default signal

    if (argc == 4) {
        if (strcmp(argv[2], "-s") == 0) {
            if (strcmp(argv[3], "SIGINT") == 0) {
                signo = SIGINT;
            } else if (strcmp(argv[3], "SIGUSR1") == 0) {
                signo = SIGUSR1;
            } else {
                fprintf(stderr, "Unsupported signal: %s\n", argv[3]);
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Usage: %s <pid> [-s <signal_name>]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (kill(pid, signo) == -1) {
        perror("kill");
        exit(EXIT_FAILURE);
    }

    printf("Sent signal %d to PID %d\n", signo, pid);

    return 0;
}
