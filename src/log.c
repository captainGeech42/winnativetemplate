#include "log.h"

#define TS_SIZE 32
#define MSG_SIZE 0x1000
#define BUF_SIZE (MSG_SIZE+0x100)

#define RESET "\x1b[0m"
#define RED "\x1b[1;31m"
#define GREEN "\x1b[1;32m"
#define YELLOW "\x1b[1;33m"
#define BLUE "\x1b[1;34m"
#define GRAY "\x1b[38;5;244m"

#ifdef LOG_MIN
#define __logc_func_def
#define __logc_func_args
#define __logc_msg_def
#else
#define __logc_func_def const char *filename, int linenum, const char *func,
#define __logc_func_args filename, linenum, func,
#define __logc_msg_def const char *filename, int linenum, const char *func, 
#endif // LOG_MIN

static void _log_msg(const char *prefix, __logc_msg_def char *err, const char *fmt, va_list args) {
    char msg[MSG_SIZE] = {0};
    char ts[TS_SIZE] = {0};
    char buf[BUF_SIZE] = {0};

    // make an iso8601ish timestamp
    time_t curtime = time(NULL);
    struct tm *lt = localtime(&curtime);
    strftime(ts, TS_SIZE, "%Y-%m-%d %H:%M:%S", lt);

    // format the log fstr into the msg buf
    vsnprintf(msg, MSG_SIZE-1, fmt, args);

    // build the actual log buf according to the log preproc configuration
    int offset = 0;
    offset  = snprintf(buf+offset, BUF_SIZE-offset-1, "[%s]", ts);
#ifndef LOG_MIN
    offset += snprintf(buf+offset, BUF_SIZE-offset-1, "[" GRAY "%s:%d!%s" RESET "]", filename, linenum, func);
#endif // LOG_MIN
#ifdef LOG_PIDS
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    offset += snprintf(buf+offset, BUF_SIZE-offset-1, "[%lu:%lu]", pid, tid);
#endif // LOG_PIDS
    offset += snprintf(buf+offset, BUF_SIZE-offset-1, "[%s] %s", prefix, msg);

    if (err) {
        offset += snprintf(buf+offset, BUF_SIZE-offset-1, "(error: %s)", err);
        LocalFree(err);
    }

    fprintf(stderr, "%s\n", buf);
    fflush(stderr);
}

static char *_get_win_errstr(DWORD errnum) {
    char *err;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errnum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&err,
        0,
        NULL
    );

    // remove trailing \r\n
    err[strcspn(err, "\r")] = '\0';
    err[strcspn(err, "\n")] = '\0';

    // remove trailing .
    err[strcspn(err, ".")] = '\0';

    return err;
}

static char *_get_normal_error() {
    return _get_win_errstr(GetLastError());
}

void __LOG_Debug(__logc_func_def const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _log_msg(BLUE ">" RESET, __logc_func_args NULL, fmt, args);
    va_end(args);
}

void __LOG_Debug_Errno(__logc_func_def const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char *err = _get_normal_error();
    _log_msg(BLUE ">" RESET, __logc_func_args err, fmt, args);
    va_end(args);
}

void __LOG_Info(__logc_func_def const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _log_msg(GREEN "+" RESET, __logc_func_args NULL, fmt, args);
    va_end(args);
}

void __LOG_Warn(__logc_func_def const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _log_msg(YELLOW "*" RESET, __logc_func_args NULL, fmt, args);
    va_end(args);
}

void __LOG_Error(__logc_func_def const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _log_msg(RED "!" RESET, __logc_func_args NULL, fmt, args);
    va_end(args);
}

void __LOG_Error_Errno(__logc_func_def const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    char *err = _get_normal_error();
    _log_msg(RED "!" RESET, __logc_func_args err, fmt, args);
    va_end(args);
}