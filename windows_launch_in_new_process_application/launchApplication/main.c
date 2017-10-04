#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int _tmain(int argc, TCHAR *argv[]) {
    enum 
    {
        programToLaunchIdx = 1,
        expectedArgs = 2
    };

    if (argc != expectedArgs) {
        fprintf(stderr, "argc was %d, but should have been %d\n", argc, expectedArgs);
        return EXIT_FAILURE;
    }

    STARTUPINFO si;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);

    PROCESS_INFORMATION pi;
    memset(&pi, 0, sizeof(pi));

    const BOOL result
        = CreateProcess(NULL,
                        argv[programToLaunchIdx],
                        NULL,
                        NULL,
                        FALSE,
                        DETACHED_PROCESS,
                        NULL,
                        NULL,
                        &si,
                        &pi);

    if (result) {
        return EXIT_SUCCESS;
    }

    LPTSTR errorText = NULL;

    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM
                  | FORMAT_MESSAGE_ALLOCATE_BUFFER
                  | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR) &errorText,
                  0,
                  NULL);

    if (errorText != NULL) {
#ifdef UNICODE
        fwprintf(stderr, L"Error: %s\n", errorText);
#else
        fprintf(stderr, "Error: %s\n", errorText);
#endif

        LocalFree(errorText);
        errorText = NULL;
    } else {
        fprintf(stderr, "%s\n", "Failed to allocated buffer for FormatMessage.");
    }

    return EXIT_FAILURE;
}
