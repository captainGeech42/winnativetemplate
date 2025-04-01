#pragma once

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <Windows.h>

#ifdef LOG_MIN
#define __log_func_args const char *fmt
#define __log_func_wide_args const wchar_t *fmt
#define __log_macro_args
#else
#define __log_func_args const char *filename, int linenum, const char *func, const char *fmt
#define __log_func_wide_args const char *filename, int linenum, const char *func, const wchar_t *fmt
#define __log_macro_args __FILE__, __LINE__, __func__,
#endif // LOG_MIN

void __LOG_Debug(__log_func_args, ...);
void __LOG_Debug_Errno(__log_func_args, ...);
void __LOG_Info(__log_func_args, ...);
void __LOG_Warn(__log_func_args, ...);
void __LOG_Error(__log_func_args, ...);
void __LOG_Error_Errno(__log_func_args, ...);

void __LOG_Wide_Debug(__log_func_wide_args, ...);
void __LOG_Wide_Debug_Errno(__log_func_wide_args, ...);
void __LOG_Wide_Info(__log_func_wide_args, ...);
void __LOG_Wide_Warn(__log_func_wide_args, ...);
void __LOG_Wide_Error(__log_func_wide_args, ...);
void __LOG_Wide_Error_Errno(__log_func_wide_args, ...);

#ifdef DEBUG
#define LOG_DEBUG(fmt, ...) __LOG_Debug(__log_macro_args fmt, ##__VA_ARGS__)
#define LOG_DEBUG_ERRNO(fmt, ...) __LOG_Debug_Errno(__log_macro_args fmt, ##__VA_ARGS__)
#define LOGW_DEBUG(fmt, ...) __LOG_Wide_Debug(__log_macro_args fmt, ##__VA_ARGS__)
#define LOGW_DEBUG_ERRNO(fmt, ...) __LOG_Wide_Debug_Errno(__log_macro_args fmt, ##__VA_ARGS__)
#else
#define LOG_DEBUG(fmt, ...) do {} while (0);
#define LOG_DEBUG_ERRNO(fmt, ...) do {} while (0);
#define LOGW_DEBUG(fmt, ...) do {} while (0);
#define LOGW_DEBUG_ERRNO(fmt, ...) do {} while (0);
#endif

#define LOG_INFO(fmt, ...) __LOG_Info(__log_macro_args fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) __LOG_Warn(__log_macro_args fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) __LOG_Error(__log_macro_args fmt, ##__VA_ARGS__)
#define LOG_ERROR_ERRNO(fmt, ...) __LOG_Error_Errno(__log_macro_args fmt, ##__VA_ARGS__)

#define LOGW_INFO(fmt, ...) __LOG_Wide_Info(__log_macro_args fmt, ##__VA_ARGS__)
#define LOGW_WARN(fmt, ...) __LOG_Wide_Warn(__log_macro_args fmt, ##__VA_ARGS__)
#define LOGW_ERROR(fmt, ...) __LOG_Wide_Error(__log_macro_args fmt, ##__VA_ARGS__)
#define LOGW_ERROR_ERRNO(fmt, ...) __LOG_Wide_Error_Errno(__log_macro_args fmt, ##__VA_ARGS__)