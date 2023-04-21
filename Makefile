DIRSRC = ./srcs/

DIRCINC = ./includes/

DIRLIB = ./libft/

SRC =	main \
		parsing00 \
		parsing01 \
		parsing02 \
		parsing_utils00 \
		parsing_utils01 \
		pars_error \
		var_env \
		token \
		free \
		builtins \

SRCS = $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS = ${SRCS:.c=.o}

NAME = minishell
LFT = libft.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -g

.c.o:
	@${CC} ${CFLAGS} -c -I${DIRCINC} -I${DIRLIB} $< -o ${<:.c=.o} -lreadline 

${NAME}: ${OBJS}
	@cd ${DIRLIB} && ${MAKE}
	@${CC} ${CFLAGS} -o ${NAME} ${OBJS} -lreadline -L./libft -lft
	@echo "✅ minishell created"

all: ${NAME}

clean:
	@${RM} ${OBJS}
	@cd ${DIRLIB} && ${MAKE} clean
	@echo "🧽 Directory is clean"

fclean:
	@${RM} ${OBJS}
	@${RM} ${NAME}
	@cd ${DIRLIB} && ${MAKE} fclean
	@echo "🧹 Directory is fclean"

re : fclean all

.PHONY : all clean fclean re
