CC=cl.exe
LNK=link.exe

# https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category?view=msvc-170
C_FLAGS=/nologo /Fdbuild\\ /Febuild\\
# https://learn.microsoft.com/en-us/cpp/build/reference/linker-options?view=msvc-170
L_FLAGS=/nologo
exe=build/main.exe

SRC_FILES=$(wildcard src/*.c)
OBJ_FILES=$(patsubst %.c, %.obj, $(notdir $(SRC_FILES)))

.PHONY: all
all: $(exe)

.PHONY: debug
debug: C_FLAGS+=/Zi /D DEBUG
debug: L_FLAGS+=/DEBUG:FULL
debug: all

$(exe): $(addprefix build/, $(OBJ_FILES))
	$(LNK) $(L_FLAGS) /OUT:$@ $^

build/%.obj: src/%.c
	@dir build >nul 2>nul || mkdir build >nul 2>nul
	$(CC) $(C_FLAGS) /Fo:$@ $^

.PHONY: clean
clean:
	rmdir /S /Q build

-include *.d