CC		:= clang
CFLAGS 	:= -Wall

CPPFLAGS := -Ilib/unity -MMD -MP 	# -I is a preprocessor flag, not a compiler flag
CFLAGS   := -Wall              		# some warnings about bad code
LDFLAGS  := -Llib              		# -L is a linker flag
LDLIBS   := -l		        		# Left empty if no libs are needed

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
TEST_DIR := test


TEST_EXE := $(BIN_DIR)/Test
EXE := $(BIN_DIR)/Fuego

TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
SRC := $(wildcard $(SRC_DIR)/*.c)

TEST_OBJ := $(TEST_SRC:$(TEST_DIR)/%.c=$(TEST_DIR)/%.o)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# You can also do it like that
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_NO_MAIN := $(filter-out build/main.o, $(OBJ))

# $(info $$OBJ_NO_MAIN is [${OBJ_NO_MAIN}])

.PHONY: all clean run unity test run_test

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

#####################
#	EXECUTABLE		#
#####################

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CPPFLAGS) $^ -o $(EXE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run:
	./$(EXE)

#####################
#	UNITY LIBRARY	#
#####################

unity: ./lib/unity/libunity.a

./lib/unity/libunity.a: ./lib/unity/unity.o
	ar rcs ./lib/unity/libunity.a ./lib/unity/unity.o

./lib/unity/unity.o: ./lib/unity/unity.c
	$(CC) -c ./lib/unity/unity.c -o ./lib/unity/unity.o

#####################
#	TEST			#
#####################

test: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(OBJ_NO_MAIN) | $(BIN_DIR)
	$(CC) -Llib/unity $(TEST_OBJ) $(OBJ_NO_MAIN) -lunity -o $(TEST_EXE)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -Isrc -c $< -o $@

-include $(OBJ:.o=.d)