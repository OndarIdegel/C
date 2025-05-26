/**
 * Task 3: Event Loop with Signal Wait
 * 
 * This program implements an event loop using a mechanism similar to sigwait() in UNIX.
 * It blocks a signal (equivalent to SIGUSR1 in UNIX) and waits for it in a loop.
 * When the signal is received, it displays a message and continues the loop.
 * 
 * Windows adaptation: Since Windows doesn't have direct POSIX signal equivalents,
 * we use Windows events for inter-process communication and WaitForSingleObject
 * as an equivalent to sigwait().
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define EVENT_NAME "Global\\SIGUSR1_Event"

int main() {
    HANDLE hEvent;
    DWORD waitResult;
    
    // Create or open a named event (equivalent to setting up a signal)
    hEvent = CreateEvent(
        NULL,               // Default security attributes
        TRUE,               // Manual reset event
        FALSE,              // Initial state is non-signaled
        TEXT(EVENT_NAME)    // Event name
    );
    
    if (hEvent == NULL) {
        printf("CreateEvent failed (%d)\n", GetLastError());
        return 1;
    }
    
    printf("Event loop program started.\n");
    printf("Process ID: %lu\n", GetCurrentProcessId());
    printf("Waiting for signals in event loop...\n");
    printf("(Press Ctrl+C to exit)\n");
    
    // Event loop (equivalent to the sigwait loop in the UNIX version)
    while (1) {
        // Wait for the event to be signaled (equivalent to sigwait)
        waitResult = WaitForSingleObject(hEvent, INFINITE);
        
        if (waitResult == WAIT_OBJECT_0) {
            // Signal received
            printf("Signal received: SIGUSR1 equivalent\n");
            
            // Reset the event for the next signal
            ResetEvent(hEvent);
        }
        else {
            // Error occurred
            printf("WaitForSingleObject failed (%d)\n", GetLastError());
            break;
        }
    }
    
    // Cleanup
    CloseHandle(hEvent);
    
    return 0;
}
