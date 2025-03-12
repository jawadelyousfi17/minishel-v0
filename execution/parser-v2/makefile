# CFLAGS = cc 

SRC = builtin/echo.c builtin/env.c builtin/export.c builtin/export_no_args.c builtin/unset.c builtin/utils_builtin.c \
		env/get_env.c env/init_env.c env/set_env.c env/utils_env.c \
		garbage_collector/garbage_collector.c \
		parser/execut_here_doc.c parser/expander.c parser/ft_count_tokens.c parser/init_data.c parser/init_data_utils.c parser/lexer.c parser/parser.c parser/spliter.c parser/utils_parser.c \


LIBS = libft/libft.a

NAME = libparser.a

OBJ = $(SRC:.c=.o)

all : libft $(NAME)

test : all tests/test.c 
	clang $(NAME)  tests/test.c -lreadline -o test
	@echo "Test file created"

builtin/*.o : builtin/*.c builtin/builtin.h include/parser.h include/minishell.h
	@clang -c $< -o $@

env/*.o : env/*.c env/env.h include/parser.h include/minishell.h
	@clang -c $< -o $@

garbage_collector/*.o : garbage_collector/*.c include/parser.h include/minishell.h
	@clang -c $< -o $@

parser/*.o : parser/*.c include/parser.h include/minishell.h
	@clang -c $< -o $@

$(NAME) : $(OBJ) 
	@ar rc $(NAME) $(OBJ) libft/*.o
	@echo "Library created"
libft :
	@make bonus -C libft

clean :
	rm -f $(OBJ)
	@make -C libft clean

fclean : clean
	rm -f $(NAME)
	@make -C libft fclean

.PHONY : all clean fclean re libft