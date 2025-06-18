#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void sigusr1_handler(int signo) {
    printf("Received SIGUSR1 signal!\n");
    fflush(stdout);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("SIGUSR1 receiver program started. PID: %d\n", getpid());
    fflush(stdout);
    printf("Waiting for SIGUSR1 signal...\n");
    fflush(stdout);

    while (1) {
        sleep(1);
    }

    return 0;
}
