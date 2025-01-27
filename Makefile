# Main
NAME				=	pipex
CC					=	cc
# -Wall -Werror -Wextra
CFLAGS				=	-g3 -Idependencies/ft_libc/includes -Iincludes
RM					=	rm -rf
MAKE				=	make --no-print-directory -C

# Colors
RESET				=	\033[0m
BLACK				=	\033[0;30m
RED					=	\033[0;31m
GREEN				=	\033[1;32m
YELLOW				=	\033[0;33m
BLUE				=	\033[0;34m
PURPLE				=	\033[1;35m
CYAN				=	\033[1;36m
WHITE				=	\033[0;37m

# Symbols
OK					=	✓
FAIL				=	✗
INFO				=	ⓘ

# Sources and Objects
FT_LIBC 			= ./dependencies/ft_libc/ft_libc.a

SRCS				=	src/main.c\
						src/test.c\
						src/commands/commands.c\
						src/commands/pipes.c\
						src/commands/proccess.c\
						src/commands/queue.c\
						src/parsing/parsing.c\
						src/parsing/utils.c\
						src/garbadge_collector/garbadge.c\
						src/env/variables.c

SRC_COUNT			=	$(words $(SRCS))

OBJS				=	$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRCS))

OBJ_DIR				=	objects

all : header $(FT_LIBC) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(FT_LIBC) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -c $< -o $@
		@printf "$(GREEN)$(OK)$(RESET)"

$(OBJ_DIR): $(OBJS)
		@if [ ! -d "$(OBJ_DIR)" ]; \
			then mkdir -p "$(OBJ_DIR)"; \
		fi
		@printf "]"
		@printf "\n"

$(FT_LIBC) :
	@if [ ! -e "$(shell dirname $@)" ]; then \
		git clone git@github.com:R0-main/ft_libc.git $(shell dirname $@); \
	fi;
	$(MAKE) $(shell dirname $@) SAFE=1

header :
		@printf  "_______ _________ _______  _______				\n"; \
		printf  "(  ____ )\__   __/(  ____ )(  ____ \|\     /| \n"; \
		printf  "| (    )|   ) (   | (    )|| (    \/( \   / )	\n"; \
		printf  "| (____)|   | |   | (____)|| (__     \ (_) /	\n"; \
		printf  "|  _____)   | |   |  _____)|  __)     ) _ (	\n"; \
		printf  "| (         | |   | (      | (       / ( ) \\	\n"; \
		printf  "| )      ___) (___| )      | (____/\( /   \ )	\n"; \
		printf  "|/       \_______/|/       (_______/|/     \|	\n"; \
		printf  "\n"; \
		printf "Compiling Project : ["

clean :
		@$(RM) $(OBJ_DIR)
		@$(MAKE) $(shell dirname $(FT_LIBC)) fclean

fclean : clean
		@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re header
