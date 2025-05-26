/**
 * Task 2: Signal Blocking Program
 * 
 * This program blocks a signal (equivalent to SIGINT in UNIX)
 * using Windows-specific mechanisms, then enters an infinite loop.
 * 
 * Windows adaptation: Since Windows doesn't have direct POSIX signal equivalents,
 * we use a custom handler for console control events (Ctrl+C) to simulate
 * signal blocking behavior.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Global flag to indicate if SIGINT (Ctrl+C) is blocked
static BOOL g_bSigintBlocked = TRUE;

// Custom handler for console control events (Ctrl+C, Ctrl+Break, etc.)
BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType) {
    switch (dwCtrlType) {
        case CTRL_C_EVENT:
            // If SIGINT is blocked, ignore the event
            if (g_bSigintBlocked) {
                printf("SIGINT (Ctrl+C) received but blocked\n");
                return TRUE; // Event handled, don't call default handler
            }
            return FALSE; // Not handled, call default handler
            
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            return FALSE; // Not handled, call default handler
    }
    
    return FALSE;
}

int main() {
    // Set up the control handler (equivalent to sigprocmask)
    if (!SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE)) {
        printf("SetConsoleCtrlHandler failed (%d)\n", GetLastError());
        return 1;
    }
    
    printf("Signal blocking program started.\n");
    printf("Process ID: %lu\n", GetCurrentProcessId());
    printf("SIGINT (Ctrl+C) is blocked.\n");
    printf("Press Ctrl+C to test blocking.\n");
    printf("(Use Task Manager to terminate this program)\n");
    
    // Infinite loop (equivalent to the waiting loop in the UNIX version)
    while (1) {
        Sleep(1000); // Sleep to reduce CPU usage
    }
    
    // This code is never reached in normal operation
    return 0;
}
