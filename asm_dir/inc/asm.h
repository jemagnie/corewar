/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jemagnie <jemagnie@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/28 15:20:01 by jemagnie     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/06 16:47:58 by jemagnie    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../../libft/libft.h"
# include <errno.h>

# define DISSAMBLER_OPTION	1
# define OUTPUT_OPTION		2
# define HEXDUMP_OPTION		4

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	4
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','
# define SEP_CHAR			SEPARATOR_CHAR
# define REG_CHAR			'r'

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16
# define INST_NUMBER       	16
# define MAX_PARAM			3

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define COREWAR_EXEC_MAGIC	0xea83f3

# define IS_RIGHT_PAR		1 << 0
# define IS_LEFT_PAR		1 << 1
# define IS_NB				1 << 2
# define IS_OP				1 << 3

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_token
{
	char			*s;
	int				predecence;
	int				nb;
	int				type;
	char			*err;
	struct s_token	*next;
	struct s_token	*ope;
	struct s_token	*out;
}					t_oken;

typedef struct		s_inst
{
	char			opcode;
	char			ocp;
	char			*arg[3];
	char			*tmp[3];
	char			code[3];
	int				len[3];
	int				n_arg;
	int				total;
	int				addr;
}					t_inst;

typedef struct		s_label
{
	char			*name;
	int				addr;
}					t_label;

typedef struct		s_op_tab
{
	char			*name;
	char			opcode;
	int				n_arg;
	int				arg[3];
	int				opc;
	int				dir_size;
}					t_op_tab;

typedef struct		s_parser
{
	int				fd;
	char			flag;
	char			*to_open;
	char			*suffix;
	char			*file;
	char			*offset;
	char			*name;
	long			len_file;
	t_header		head;
	char			mem[CHAMP_MAX_SIZE];
	int				len_mem;
	t_label			*label;
	int				n_label;
	t_inst			*inst;
	int				n_inst;
	t_oken			*token;
}					t_parser;

extern t_op_tab		g_asm_tab[];

/*
** parsing func
*/

char				*skip_blank_and_comment(char *line);
void				asm_parser(t_parser *p);

int					asm_is_label(t_parser *p, char *s);
void				get_asm_label(t_parser *p, char *s);

void				get_asm_inst(t_parser *p, char *s, int index);
int					asm_is_inst(t_parser *p, char *s);
int					get_addr_label(t_parser *p, t_label *label, char *s);

short				reverse_short_bits(short bin);
int					reverse_int_bits(int bin);

void				get_asm_ocp(t_parser *p, t_inst *inst);
void				asm_filler(t_parser *p, t_inst *inst, char *mem);
void				asm_reverse(t_parser *p);

void				asm_hexdump(const unsigned char *addr, unsigned long size);
void				asm_usage_hexdump(void);

t_pos				get_pos_error(t_parser *p, char *s);

void				asm_free(t_parser *p);
void				exit_errno(t_parser *p, char *error);
void				exit_usage();
void				exit_fail(t_parser *p, char *error, char *s);

void				free_token(t_oken *token);
int					asm_get_calc(t_parser *p, char *s, char *err);
void				ft_tokenrev(t_oken **token);
void				new_token(t_parser *p, char *s, int size, char *err);
void				asm_get_token(t_parser *p, char *s, char *e);
int					check_token_calc(t_parser *p, t_oken *token, int stack);

#endif
