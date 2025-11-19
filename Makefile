# PLATFORM DETECTION
ifeq ($(OS),Windows_NT)
    PLATFORM = WINDOWS
else
    UNAME_S := $(shell uname -s)
    ifneq (,$(findstring MINGW,$(UNAME_S)))
        PLATFORM = WINDOWS
    else
        PLATFORM = LINUX
    endif
endif

# COMPILER
CC = gcc

# DIRECTORIES
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
ROMS_DIR = ROMs
BUILD_ROMS_DIR = $(BUILD_DIR)/ROMs

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET = chip8

# FLAGS
CFLAGS = -g -I$(INC_DIR) -I$(SRC_DIR)

ifeq ($(PLATFORM),WINDOWS)
    CFLAGS += -I"C:/msys64/mingw64/include"
    CFLAGS += -I"C:/msys64/mingw64/include/SDL2"

    LDFLAGS = -L"C:/msys64/mingw64/lib" -lmingw32 -lSDL2main -lSDL2

    MKDIR = mkdir
    COPY = copy /Y

    # 🔥 Windows-style path (DÜZELTİLDİ)
    SDL_DLL = C:\msys64\mingw64\bin\SDL2.dll

    NULLDEV = >nul
else
    CFLAGS += $(shell pkg-config --cflags sdl2)
    LDFLAGS += $(shell pkg-config --libs sdl2)
    MKDIR = mkdir -p
    COPY = cp
    NULLDEV =
endif

# TARGETS

all: $(BUILD_DIR)/$(TARGET) copy_roms copy_sdl

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR):
ifeq ($(PLATFORM),WINDOWS)
	$(MKDIR) "$(BUILD_DIR)"
else
	$(MKDIR) $(BUILD_DIR)
endif

copy_roms: | $(BUILD_ROMS_DIR)
ifeq ($(PLATFORM),WINDOWS)
	$(COPY) "$(ROMS_DIR)\*" "$(BUILD_ROMS_DIR)" $(NULLDEV)
else
	$(COPY) $(ROMS_DIR)/* $(BUILD_ROMS_DIR) $(NULLDEV)
endif

$(BUILD_ROMS_DIR):
ifeq ($(PLATFORM),WINDOWS)
	$(MKDIR) "$(BUILD_DIR)\ROMs"
else
	$(MKDIR) $(BUILD_ROMS_DIR)
endif

copy_sdl:
ifeq ($(PLATFORM),WINDOWS)
	$(COPY) "$(SDL_DLL)" "$(BUILD_DIR)\SDL2.dll" $(NULLDEV)
endif

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean copy_roms copy_sdl
