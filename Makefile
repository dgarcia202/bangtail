CC = g++
LIB_NAME = bangtail
BUILD_DIR = build
SRC_DIR = src
TEST_DIR = test

TEST_FILES := $(wildcard $(TEST_DIR)/*.cpp)
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
BUILD_TARGET := $(BUILD_DIR)/lib$(LIB_NAME).a
TEST_TARGET := ./$(TEST_DIR)/test

# -w suppresses all warnings
COMPILER_FLAGS = -w -DDEBUG
LINKER_FLAGS = -lSDL2 -lSDL2_image -ltinyxml2

#Dependencies needed for windows
WIN_LINKER_FLAGS = -lmingw32 -lSDL2main

$(BUILD_TARGET): $(OBJS)
	@ar crf $(BUILD_TARGET) $(BUILD_DIR)/*.o

clean:
	@[ -z "$$(ls -A ./$(BUILD_DIR))" ] || rm $(BUILD_DIR)/*.*

test: $(BUILD_TARGET)
	$(CC) $(TEST_FILES) $(COMPILER_FLAGS) -L/home/diego/projects/bangtail/build -lbangtail $(LINKER_FLAGS) -o $(TEST_TARGET)
	@chmod +x $(TEST_TARGET) && $(TEST_TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $< -c $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

.PHONY: build clean test