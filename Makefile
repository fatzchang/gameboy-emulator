CC = gcc
EMU = emu

SRC_DIR = src
BUILD_DIR = build
INCL_DIR = include
GBIT_DIR = gbit

FLAGS = -Wall -Werror


C_FILES	= $(wildcard $(SRC_DIR)/*.c)
H_FILES	= $(wildcard $(INCL_DIR)/*.c)
O_FILES	= $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: init $(EMU)

init:
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(H_FILES)
	$(CC) $(FLAGS) -I$(INCL_DIR) -I$(GBIT_DIR) -c $< -o $@

$(EMU): $(O_FILES) 
	$(CC) -o $(EMU) $(O_FILES) -lgbit -L./gbit

clean:
	rm -f $(EMU)
	rm -rf $(BUILD_DIR)