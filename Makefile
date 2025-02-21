
NAME= minishell

FLAGS = 

parser_src = 
executions_src = 

libs = shared_libs/libft/libft.a

parser_objs = $(parser_objs:.c=.o)
executions_obj = $(executions_obj:.c=.o)

all : libft $(NAME)

$(NAME) : $(parser_objs) $(executions_obj) 
	cc $(FLAGS) $(parser_objs) $(executions_obj) $(libs)

parser/%.o : parser/%.c includes/minishell.h
	cc $(FLAGS) -c $< -o $@

execution/%.o : execution/%.c includes/minishell.h
	cc $(FLAGS) -c $< -o $@

libft : 
	make -C shared_libs/libft

clean : 
	make clean -C shared_libs/libft
	rm -rf $(parser_objs) $(executions_obj)

fclean : clean
	make fclean -C shared_libs/libft
	rm -rf $(NAME)

re : fclean all

.PHONY : libft clean