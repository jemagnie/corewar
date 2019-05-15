# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/05/03 23:08:27 by jemagnie    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SHELL     = bash
NAME     := ../corewar
OBJ_DIR  := obj
SRC_DIR  := src
INC_DIR  := inc:../libft
ARCHIVE  := ../libft/libft.a

SOURCES  := \
	src/champ_intro.c\
	src/corewar.c\
	src/exec_calcs.c\
	src/exec_checks.c\
	src/exec_cooldowns.c\
	src/exec_jumps.c\
	src/exec_loads.c\
	src/exec_misc.c\
	src/exec_tools.c\
	src/execute.c\
	src/font.c\
	src/graph_arena.c\
	src/graph_toolbar.c\
	src/graph_tools.c\
	src/graphics.c\
	src/launch_corewar.c\
	src/load_champs.c\
	src/load_tools.c\
	src/main.c\
	src/param_get.c\
	src/param_tools.c\
	src/parsing.c\
	src/process.c\
	src/struct.c\
	src/tools.c

OBJECTS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS  := $(patsubst ${SRC_DIR}/%.c,${SRC_DIR}/.%.d,${SOURCES})
CFLAGS   := -Wall -Wextra -Werror -O3 -fno-builtin
CINC     := -I $(subst :, -I ,${INC_DIR}) $(shell sdl2-config --cflags)
CSDL     := $(shell sdl2-config --libs)
CC       := gcc
INCLUDED := $(shell for deps in ${DEPENDS}; do if [[ -e $$deps ]]; then echo -n "$$deps "; fi; done)
QTY      := $(shell echo ${SOURCES} | wc -w)
CNT      = 0
COLSET   = 0
SIZE     = 0
ASIZE    = 100
COL_WIN	 = 0


.PHONY: all $(LIB) clean fclean re allc


all: $(LIB) $(DEPENDS) $(OBJ_DIR) $(NAME)

# Creation du repertoire pour les .o
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Creation de l'executable
$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(CINC) -o $@ $^ $(CSDL) $(ARCHIVE)
	@echo

# Creation des .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval CNT=$(shell echo "$(CNT) + 1" | bc))
	@$(eval COLSET=$(shell echo "$(CNT) * 255 / $(QTY)" | bc))
	@$(eval SIZE=$(shell echo "$(CNT) * 100 / $(QTY)" | bc))
	@$(eval COL_WIN=$(shell echo "($(SIZE) * $$(tput cols) / 100) / 2" | bc))
	@$(eval ASIZE=$(shell echo "$$(tput cols) / 2 - $(COL_WIN)" | bc))
	@printf "[48;2;255;$(COLSET);0m%$(COL_WIN)s[0m%$(ASIZE)s corewar: %d%%\033[K\r" "" "" $(SIZE)
	@$(CC) $(CFLAGS) $(CINC) -c $< -o $@

# creation des .d
$(SRC_DIR)/.%.d: $(SRC_DIR)/%.c
	@set -e; echo "$(OBJ_DIR)/`$(CC) $(CINC) -MM $<`" > $@

# inclusion des regles contenues dans les .d
include $(INCLUDED)

clean:
	@/bin/rm -rf $(OBJ_DIR)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean
