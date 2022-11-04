CC = g++
NAME = program
BUILD_DIR = ./build
INCLUDE_DIR = ./include
RES_DIR = /res
SRC_DIR = ./src
CFLAGS = --std=c++11 -Wall
NFLAGS = -lncurses -ltinfo
DEBUG_FLAG =

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/$(NAME): \
		$(BUILD_DIR)/Guia.o \
		$(BUILD_DIR)/GerenciaJanela.o \
		$(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) $(DEBUG_FLAG) $(BUILD_DIR)/*.o -o $(BUILD_DIR)/$(NAME) $(NFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)$(RES_DIR)/%.cpp $(INCLUDE_DIR)/%.hpp
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $< -I $(INCLUDE_DIR) -o $@ $(NFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $< -I $(INCLUDE_DIR) -o $@ $(NFLAGS)

debug: clean var all

var:
	$(eval DEBUG_FLAG = -g)

run:
	$(BUILD_DIR)/$(NAME)

clean: 
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/$(NAME)
