CC = gcc
EMU = emu

SRC_DIR = src
BUILD_DIR = build
INCL_DIR = include

FLAGS = -Wall -Werror


C_FILES	= $(wildcard $(SRC_DIR)/*.c)
O_FILES	= $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: init $(EMU)

init:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -I$(INCL_DIR) -c $< -o $@

$(EMU): $(O_FILES)
	$(CC) -o $(BUILD_DIR)/$(EMU) $(O_FILES)

clean:
	rm -rf $(BUILD_DIR)