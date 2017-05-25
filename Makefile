# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/25 11:36:26 by agrumbac          #+#    #+#              #
#    Updated: 2017/05/25 14:53:16 by agrumbac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = minishell.c

OBJDIR = objs

CFLAGS = -Wall -Wextra -Werror

DEP = libft/includes/libft.h libft/includes/ft_printf.h minishell.h

CC = /Users/agrumbac/.brew/bin/gcc-7

OBJDIR = objs

OBJ = $(addprefix ${OBJDIR}/, $(SRC:.c=.o))

LIB = -Llibft -lft

INCL = -Ilibft/includes

BY = "\033[33;1m"
BR = "\033[31;1m"
BG = "\033[32;1m"
BB = "\033[34;1m"
BM = "\033[35;1m"
BC = "\033[36;1m"
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
W = "\033[0m""\033[34;1m"
WR = "\033[0m""\033[31;5m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: libft ${NAME}

libft: octopus
	@make -C libft/

${NAME}: ${OBJ}
	@echo ${B}Compiling [${NAME}]...${X}
	@${CC} ${CFLAGS} ${LIB} ${INCL} -o $@ ${OBJ}
	@echo ${G}Success"   "[${NAME}]${X}

${OBJDIR}/%.o: ./srcs/%.c ${DEP}
	@echo ${Y}Compiling [$@]...${X}
	@/bin/mkdir -p ${OBJDIR}
	@${CC} ${CFLAGS} ${INCL} -I. -c -o $@ $<
	@printf ${UP}${CUT}

clean:
	@echo ${R}Cleaning"  "[libft objs]...${X}
	@make -C libft/ clean
	@echo ${R}Cleaning"  "[objs]...${X}
	@/bin/rm -Rf ${OBJDIR}

fclean: clean
	@make -C libft/ fclean
	@echo ${R}Cleaning"  "[${NAME}]...${X}
	@/bin/rm -f ${NAME}

test:
	@${CC} -g -I./libft/includes/ -fsanitize=address -Llibft/ -lft \
	-I. -o ${NAME} $(addprefix srcs/, ${SRC})

build: ${OBJ}

re: fclean all

# BC BM BB BG BY BR

octopus:
	@echo ${BB}"                                            _       _     _          _ _"
	@echo "                        ___       _ __ ___ (_)_ __ (_)___| |__   ___| | |"
	@echo "                     .-'   \`'.   | '_ \` _ \\| | '_ \\| / __| '_ \\ / _ \\ | |"
	@echo "                    /         \\  | | | | | | | | | | \\__ \\ | | |  __/ | |"
	@echo "                    |         ;  |_| |_| |_|_|_| |_|_|___/_| |_|\\___|_|_|"
	@echo "                    |         |           ___.--,"
	@echo "           _.._     |"${BR}"o"${BB}") ~ ("${BR}"o"${BB}") |    _.---'\`__.-( (_.            ___"
	@echo "    __.--'\`_.. '.__.\\    '--. \\_.-' ,.--'\`     \`\"\"\`        .-\"; ! ;\"-."
	@echo "   ( ,.--'\`   ',__ /./;   ;, '.__.'\`  __                 .'!  : | :  !\`."
	@echo " _\`) )  .---.__.' / |   |\\   \\__..--\"\"  \"\"\"--.,_        /\\  ! : ! : !  /\\"
	@echo "\`---' .'.''-._.-'\`_./  /\\ '.  \\ _.-~~~\`\`\`\`~~~-._\`-.__.'/\\ |  ! :|: !  | /\\"
	@echo "      | |  .' _.-' |  |  \\  \\  '.               \`~---\`(  \\ \\ ; :!: ; / /  )"
	@echo "       \\ \\/ .'     \\  \\   '. '-._)                   ( \`. \\ | !:|:! | / .' )"
	@echo "        \\/ /        \\  \\    \`=.__\`~-.                (\`. \\ \\ \\!:|:!/ / / .')"
	@echo "        / /\\         \`) )    / / \`\"\".\`\\               \\ \`.\`.\\ |!|! |/,'.' /"
	@echo "  , _.-'.'\\ \\        / /    ( (     / /                \`._\`.\\\\\\!!!// .'_.'"
	@echo "    \`--~\`   ) )    .-'.'      '.'.  | (                   \`.\`.\\\\|//.'.'"
	@echo "            (/\`    ( (\`          ) )  '-;                  |\`._\`n'_.'|"
	@echo "             \`      '-;         (-'                        \"----^----\""${X}

.PHONY: all clean fclean re test octopus build
