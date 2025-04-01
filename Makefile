CC=cl.exe
LNK=link.exe

# logging preprocessor definitions you can configure:
#   - LOG_PIDS: this will include the pid/tid in each message
#   - LOG_MIN: this will minify the logging by removing source file/function information from log messages
#   - LOG_PLAIN: this will disable the ANSI coloring of log messages
#   - DEBUG: this enables debug log messages

# https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170
C_FLAGS=/nologo /Fdbuild\\ /Febuild\\ /Iinc /c /DLOG_PIDS
# https://learn.microsoft.com/en-us/cpp/build/reference/linker-options?view=msvc-170
L_FLAGS=/nologo
exe=build/main.exe

# if you need to troubleshoot preprocessor issues, uncomment this:
# C_FLAGS+=/P /C /Fibuild\\

SRC_FILES=$(wildcard src/*.c)
OBJ_FILES=$(patsubst %.c, %.obj, $(notdir $(SRC_FILES)))

.PHONY: all
all: $(exe)

.PHONY: debug
debug: C_FLAGS+=/Zi /DDEBUG
debug: L_FLAGS+=/DEBUG:FULL
debug: all

# TODO: put some code optimization stuff here probably (O2)
.PHONY: min
min: C_FLAGS+=/DLOG_MIN
min: all

$(exe): $(addprefix build/, $(OBJ_FILES))
	$(LNK) $(L_FLAGS) /OUT:$@ $^

build/%.obj: src/%.c
	@dir build >nul 2>nul || mkdir build >nul 2>nul
	$(CC) $(C_FLAGS) /Fo:$@ $^

.PHONY: clean
clean:
	rmdir /S /Q build