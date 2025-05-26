/**
 * Task 1: Signal Handler Program
 * 
 * This program redefines the disposition of a signal (equivalent to SIGUSR1 in UNIX)
 * using Windows-specific mechanisms, then enters an infinite waiting loop.
 * When the signal is received, it displays a message.
 * 
 * Windows adaptation: Since Windows doesn't have direct POSIX signal equivalents,
 * we use Windows events for inter-process communication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define EVENT_NAME "Global\\SIGUSR1_Event"

// Global handle to the event
HANDLE g_hEvent = NULL;

// Signal handler function (equivalent to SIGUSR1 handler)
DWORD WINAPI SignalHandlerThread(LPVOID lpParam) {
    while (1) {
        // Wait for the event to be signaled
        WaitForSingleObject(g_hEvent, INFINITE);
        
        // Display message when signal is received
        printf("Signal received: SIGUSR1 equivalent\n");
        
        // Reset the event for the next signal
        ResetEvent(g_hEvent);
    }
    
    return 0;
}

int main() {
    DWORD threadId;
    HANDLE hThread;
    
    // Create or open a named event (equivalent to setting up a signal handler)
    g_hEvent = CreateEvent(
        NULL,               // Default security attributes
        TRUE,               // Manual reset event
        FALSE,              // Initial state is non-signaled
        TEXT(EVENT_NAME)    // Event name
    );
    
    if (g_hEvent == NULL) {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return 1;
    }
    
    printf("Signal handler program started.\n");
    printf("Process ID: %lu\n", GetCurrentProcessId());
    printf("Waiting for signals...\n");
    printf("(Press Ctrl+C to exit)\n");
    
    // Create a thread to handle the signal (equivalent to sigaction handler)
    hThread = CreateThread(
        NULL,                   // Default security attributes
        0,                      // Default stack size
        SignalHandlerThread,    // Thread function
        NULL,                   // No thread function arguments
        0,                      // Default creation flags
        &threadId               // Receive thread identifier
    );
    
    if (hThread == NULL) {
        printf("CreateThread failed (%d)\n", GetLastError());
        CloseHandle(g_hEvent);
        return 1;
    }
    
    // Infinite loop (equivalent to the waiting loop in the UNIX version)
    while (1) {
        Sleep(1000); // Sleep to reduce CPU usage
    }
    
    // Cleanup (this code is never reached in normal operation)
    CloseHandle(hThread);
    CloseHandle(g_hEvent);
    
    return 0;
}
