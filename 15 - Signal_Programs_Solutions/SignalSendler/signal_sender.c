/**
 * Signal Sender Program
 * 
 * This program sends a signal (equivalent to SIGUSR1 in UNIX) to another process
 * using Windows-specific mechanisms.
 * 
 * Windows adaptation: Since Windows doesn't have direct POSIX signal equivalents,
 * we use Windows events for inter-process communication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define EVENT_NAME "Global\\SIGUSR1_Event"

int main(int argc, char* argv[]) {
    HANDLE hEvent;
    DWORD targetPid;
    
    // Check if target process ID was provided
    if (argc < 2) {
        printf("Usage: %s <target_process_id>\n", argv[0]);
        return 1;
    }
    
    // Get target process ID from command line
    targetPid = (DWORD)atoi(argv[1]);
    if (targetPid == 0) {
        printf("Invalid process ID\n");
        return 1;
    }
    
    // Open the named event
    hEvent = OpenEvent(
        EVENT_MODIFY_STATE,    // Need permission to set the event
        FALSE,                 // Don't need to inherit handle
        TEXT(EVENT_NAME)       // Event name
    );
    
    if (hEvent == NULL) {
        printf("OpenEvent failed (%d). Make sure the target process is running.\n", GetLastError());
        return 1;
    }
    
    // Set the event (equivalent to sending SIGUSR1)
    if (!SetEvent(hEvent)) {
        printf("SetEvent failed (%d)\n", GetLastError());
        CloseHandle(hEvent);
        return 1;
    }
    
    printf("Signal sent to process %lu\n", targetPid);
    
    // Cleanup
    CloseHandle(hEvent);
    
    return 0;
}
