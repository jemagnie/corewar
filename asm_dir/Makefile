# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/02/25 16:43:57 by mhouppin     #+#   ##    ##    #+#        #
#    Updated: 2019/05/06 11:24:21 by jemagnie    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SHELL     = bash
NAME      = ../asm
OBJ_DIR   = obj
SRC_DIR   = src
INC_DIR   = inc:../libft
LIB       = ../libft
ARCHIVE  := $(LIB)/libft.a
SOURCES   = src/asm_file.c\
src/asm_filler.c\
src/asm_inst.c \
src/asm_label.c\
src/asm_main.c\
src/asm_opc.c\
src/asm_parser.c\
src/asm_des.c\
src/asm_exit.c\
src/asm_hexdump.c\
src/asm_ope.c\
src/asm_token.c\
src/asm_bits.c
OBJECTS  := $(patsubst ${SRC_DIR}/%.c,${OBJ_DIR}/%.o,${SOURCES})
DEPENDS  := $(patsubst ${SRC_DIR}/%.c,${SRC_DIR}/.%.d,${SOURCES})
CFLAGS    = -Wextra -Wall -Werror
CINC     := -I $(subst :, -I ,${INC_DIR})
CC        = gcc
INCLUDED := $(shell for deps in ${DEPENDS}; do if [[ -e $$deps ]]; then echo -n "$$deps "; fi; done)
QTY      := $(shell echo ${SOURCES} | wc -w)
CNT      = 0
COLSET   = 0
SIZE     = 0
ASIZE    = 100
COL_WIN	 = 0


.PHONY: all clean fclean re allc
# Chemins par defaut des .h


all: $(DEPENDS) $(OBJ_DIR) $(NAME)

# compilation des lib
#$(LIB):
#	$(MAKE) -C $@

# Creation du repertoire pour les .o
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Creation de l'executable
$(NAME): $(OBJECTS)
	@$(CC) -o $@ $^ $(ARCHIVE)
	@echo

# Creation des .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval CNT=$(shell echo "$(CNT) + 1" | bc))
	@$(eval COLSET=$(shell echo "$(CNT) * 255 / $(QTY)" | bc))
	@$(eval SIZE=$(shell echo "$(CNT) * 100 / $(QTY)" | bc))
	@$(eval COL_WIN=$(shell echo "($(SIZE) * $$(tput cols) / 100) / 2" | bc))
	@$(eval ASIZE=$(shell echo "$$(tput cols) / 2 - $(COL_WIN)" | bc))
	@printf "[48;2;255;$(COLSET);0m%$(COL_WIN)s[0m%$(ASIZE)s asm: %d%%\033[K\r" "" "" $(SIZE)
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
