CFLAGS=-Wall -std=c11

PROGRAM=matlab_converter

SRC_DIR=./src/
BIN_DIR=./build/
OBJ_DIR=$(BIN_DIR)obj/
INC_DIR=-I./src/

SRCS=$(wildcard $(SRC_DIR)*.c)
OBJS=$(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
DEPENDS=$(OBJS:.o=.depend)

RM=rmdir

ifeq ($(OS), Windows_NT)
    RM_OPTION=/q /s
    RM_TARGET="$(BIN_DIR)"
else
    RM_TARGET=$(OBJ_DIR) $(BIN_DIR)
endif

.PHONY : all
all: $(BIN_DIR)$(PROGRAM)

$(BIN_DIR)$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) -o $@ -c $< $(INC_DIR)

.PHONY : clean
clean:
	$(RM) $(RM_TARGET) $(RM_OPTION)
	mkdir "$(OBJ_DIR)"

.PHONY : run
run: clean $(BIN_DIR)$(PROGRAM)
	@$(BIN_DIR)$(PROGRAM).exe


-include $(DEPENDS)
