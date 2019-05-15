NAME = libft.a
CC = gcc -Wall -Werror -Wextra -O3 -fno-builtin
OBJ = ft_atoi.o\
ft_atoi_hexa.o\
ft_atoi_octal.o\
ft_atoi_ptr.o\
ft_atol.o\
ft_bzero.o\
ft_crep.o\
ft_crepall.o\
ft_crrep.o\
ft_free_assign.o\
ft_free_options.o\
ft_free_strarray.o\
ft_get_opt_value.o\
ft_get_options.o\
ft_getline.o\
ft_getline_mfd.o\
ft_isalnum.o\
ft_isalpha.o\
ft_isascii.o\
ft_isdigit.o\
ft_isnumeric.o\
ft_isblank.o\
ft_isnumber.o\
ft_isprint.o\
ft_isset_option.o\
ft_isspace.o\
ft_isoctal.o\
ft_ishexa.o\
ft_itoa.o\
ft_ltoa.o\
ft_ltrim.o\
ft_memalloc.o\
ft_memccpy.o\
ft_memchr.o\
ft_memcmp.o\
ft_memcpy.o\
ft_memcrep.o\
ft_memcrepall.o\
ft_memcrrep.o\
ft_memdel.o\
ft_memdup.o\
ft_memmove.o\
ft_mempcpy.o\
ft_memrchr.o\
ft_memrcpy.o\
ft_memset.o\
ft_print_options.o\
ft_putbin.o\
ft_putc.o\
ft_putchar.o\
ft_putchar_fd.o\
ft_putendl.o\
ft_putendl_fd.o\
ft_puts.o\
ft_putwstr.o\
ft_putwchar.o\
ft_putstr_fd.o\
ft_sort.o\
ft_strcat.o\
ft_strchr.o\
ft_strclr.o\
ft_strcmp.o\
ft_strcpy.o\
ft_strctrim.o\
ft_strdup.o\
ft_strepur.o\
ft_strfcat.o\
ft_strjoin.o\
ft_strjpath.o\
ft_strlcat.o\
ft_strlen.o\
ft_strncat.o\
ft_strncmp.o\
ft_strncpy.o\
ft_strndup.o\
ft_strnew.o\
ft_strnfcat.o\
ft_strnlen.o\
ft_strnstr.o\
ft_strrchr.o\
ft_strrep.o\
ft_strsplit.o\
ft_strstr.o\
ft_strsub.o\
ft_strtolower.o\
ft_strtoupper.o\
ft_strtrim.o\
ft_strwhile.o\
ft_swap.o\
ft_swap_ptr.o\
ft_tolower.o\
ft_toupper.o\
ft_realloc.o\
ft_wclen.o\
ft_wordlen.o\
ft_wstrlen.o\
get_next_line.o\
get_file_contents.o\
get_fd_contents.o\
printf/ft_printf.o\
printf/number.o\
printf/string.o\
printf/tools.o\
printf/parse.o\
printf/print.o\
vector/delete_insert.o\
vector/free.o\
vector/new_vector.o\
vector/pop.o\
vector/push.o\
vector/get.o

QTY := $(shell echo ${OBJ} | wc -w)
CNT = 0
COLSET = 0
SIZE = 0
ASIZE = 100
COL_WIN = 0

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@
	@echo

%.o: %.c
	@$(eval CNT=$(shell echo "$(CNT) + 1" | bc))
	@$(eval COLSET=$(shell echo "$(CNT) * 255 / $(QTY)" | bc))
	@$(eval SIZE=$(shell echo "$(CNT) * 100 / $(QTY)" | bc))
	@$(eval COL_WIN=$(shell echo "($(SIZE) * $$(tput cols) / 100) / 2" | bc))
	@$(eval ASIZE=$(shell echo "$$(tput cols) / 2 - $(COL_WIN)" | bc))
	@printf "\033[48;2;255;$(COLSET);0m%$(COL_WIN)s[0m%$(ASIZE)s libft.a: %d%%\033[K\r" "" "" $(SIZE)
	@$(CC) -c $< -o $@

$(OBJ): libft.h

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

allc: all clean
