.SUFFIXES: .t

CC		:= clang
CFLAGS 	:= -Wall

CPPFLAGS := -Ilib/unity -MMD -MP 	# -I is a preprocessor flag, not a compiler flag
CFLAGS   := -Wall              		# some warnings about bad code
LDFLAGS  := -Llib              		# -L is a linker flag
LDLIBS   := -l		        		# Left empty if no libs are needed

SRC_DIR := src
OBJ_DIR := build/src
BIN_DIR := bin
TEST_DIR := test
TEST_OBJ_DIR := build/test
TEST_RUNNER_OBJ_DIR := build/test/runner

TEST_RUNNER_DIR := test/runner

EXE := $(BIN_DIR)/Fuego

TEST_RUNNER_SRC := := $(wildcard $(TEST_RUNNER_DIR)/*.c)
TEST_SRC := $(wildcard $(TEST_DIR)/*.c)
SRC := $(wildcard $(SRC_DIR)/*.c)

TEST_OBJ := $(TEST_SRC:$(TEST_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)
TEST_RUNNER_OBJ := $(TEST_RUNNER_SRC:$(TEST_RUNNER_DIR)/%.c=$(TEST_RUNNER_OBJ_DIR)/%.o)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# You can also do it like that
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
OBJ_NO_MAIN := $(filter-out $(OBJ_DIR)/main.o, $(OBJ))

TEST_EXE := $(patsubst $(TEST_DIR)/%.c,%.t,$(TEST_SRC))

$(info $$SRC is [${SRC}])
$(info $$TEST_EXE is [${TEST_EXE}])

.PHONY: all clean run unity test

.SECONDARY:

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR) $(TEST_OBJ_DIR)


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
#	TEST			#
#####################  

test: $(TEST_EXE)
#	./$(BIN_DIR)/$(TEST_EXE)

%.t: $(TEST_OBJ_DIR)/%.o $(TEST_RUNNER_OBJ_DIR)/%_Runner.o $(OBJ_NO_MAIN) | $(BIN_DIR)
	$(CC) -Llib/unity $^ -lunity -o $(BIN_DIR)/$@

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Isrc -c $< -o $@

$(TEST_RUNNER_OBJ_DIR)/%.o: $(TEST_RUNNER_DIR)/%.c | $(TEST_RUNNER_OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Isrc -c $< -o $@

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_RUNNER_OBJ_DIR)

#####################
#	UNITY LIBRARY	#
#####################

unity: ./lib/unity/libunity.a

./lib/unity/libunity.a: ./lib/unity/unity.o
	ar rcs ./lib/unity/libunity.a ./lib/unity/unity.o

./lib/unity/unity.o: ./lib/unity/unity.c
	$(CC) -c ./lib/unity/unity.c -o ./lib/unity/unity.o

-include $(OBJ:.o=.d)