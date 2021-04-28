

# for release cflags
# CFLAGS=-Wall -std=c11

# for debug cflags
CFLAGS=-Wall -std=c11 -DDEBUG

SRC_DIR=./src/
BIN_DIR=./build/
OBJ_DIR=$(BIN_DIR)obj/
INC_DIR=-I./src/

SRCS=$(wildcard $(SRC_DIR)*.c)
OBJS=$(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
DEPENDS=$(OBJS:.o=.depend)


ifeq ($(OS), Windows_NT)
    PROGRAM=matlab_converter.exe
    RM=rmdir
    RM_OPTION=/q /s
    RM_TARGET="$(BIN_DIR)"
    MKDIR_OBJ=build\obj
else
    PROGRAM=matlab_converter
    RM=rm
    RM_TARGET=$(OBJ_DIR) $(BIN_DIR)
    RM_OPTION=-rf
    MKDIR_OBJ=build/obj
endif


.PHONY : all
all: $(BIN_DIR)$(PROGRAM)

$(BIN_DIR)$(PROGRAM): $(OBJS)
	gcc $(CFLAGS) $^ -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) -o $@ -c $< $(INC_DIR)

.PHONY : clean
clean:
	$(RM) $(RM_OPTION) $(RM_TARGET)
	mkdir build
	mkdir $(MKDIR_OBJ)

.PHONY : run
run: clean $(BIN_DIR)$(PROGRAM)
	@$(BIN_DIR)$(PROGRAM).exe


-include $(DEPENDS)
