DIRSRC = ./srcs/

DIRCINC = ./includes/

DIRLIB = ./libft/

SRC =	main \
		parsing00 \
		parsing01 \
		parsing_utils00 \
		parsing_utils01 \
		parsing_utils02 \
		handle_quotes \
		pars_error \
		parserror_utils \
		var_env \
		quotes_env_utils \
		builtins \
		token \
		signal \
		free00 \
		free01 \
		exit \
		cd \
		env \
		env_utils00 \
		env_utils01 \
		pipex_utils00 \
		pipex_utils01 \
		pipex_newbis \
		split_pipe \
		temporary_utils \
		echo \
		redirections \
		here_doc \
		err_msg \

SRCS = $(addprefix ${DIRSRC}, $(addsuffix .c, ${SRC}))

OBJS = ${SRCS:.c=.o}

NAME = minishell
LFT = libft.a
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -g

.c.o:
	@${CC} ${CFLAGS} -c -I${DIRCINC} -I${DIRLIB} $< -o ${<:.c=.o}

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
