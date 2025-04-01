#include <Windows.h>
#include <stdio.h>

#include "log.h"
#include "pls.h"

int main(int argc, char* argv[]) {
    LOG_INFO("hello world");

    LOG_ERROR("%d", myadd(5, 8));
    return 0;
}