CC = g++
NAME = program
CFLAGS = --std=c++11 -Wall
NFLAGS = -lncurses -ltinfo
DEBUG_FLAG =

BUILD_DIR = ./build
DOC_DIR = ./docs
INCLUDE_DIR = ./include
RES_DIR = /res
SRC_DIR = ./src

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

run: all
	$(BUILD_DIR)/$(NAME)

doc: clean_doc doc
	doxygen Doxyfile

clean_doc:
	rm -rf $(DOC_DIR)/html
	rm -rf $(DOC_DIR)/latex

clean_build:
	rm -f $(BUILD_DIR)/*.o
	rm -f $(BUILD_DIR)/$(NAME)

clean: clean-build clean-doc