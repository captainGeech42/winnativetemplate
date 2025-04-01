#include <Windows.h>
#include <stdio.h>

#include "log.h"
#include "pls.h"

int main(int argc, char* argv[]) {
    LOG_INFO("hello world");

    LOG_DEBUG("this is a debug message");

    HANDLE hFile = CreateFileA("C:\\thesearenotthedroidsyourelookingfor.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        LOG_ERROR_ERRNO("file open failed");
    } else {
        LOG_ERROR("failed to error the error");
        CloseHandle(hFile);
    }

    LOG_ERROR("%d", myadd(5, 8));
    return 0;
}