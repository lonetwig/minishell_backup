CC = cc

PATH_F = functions
C_FILES_F = $(PATH_F)/free.c $(PATH_F)/ft_strcmp.c $(PATH_F)/ft_strdup.c $(PATH_F)/ft_strjoin.c \
$(PATH_F)/ft_strlen.c $(PATH_F)/ft_substr.c $(PATH_F)/ft_write.c $(PATH_F)/unsigned_to_str.c \
$(PATH_F)/get_error.c $(PATH_F)/get_error.c $(PATH_F)/ft_malloc.c

PATH_G = get_next_line
C_FILES_G = $(PATH_G)/get_next_line.c $(PATH_G)/get_next_line_utils.c

PATH_PT = parsing/parse_tree
C_FILES_PT = $(PATH_PT)/build/adjust_redirectionals.c $(PATH_PT)/build/build_tree.c $(PATH_PT)/build/parse_tree.c \
$(PATH_PT)/check/check_here_doc.c $(PATH_PT)/check/check_opers.c $(PATH_PT)/check/check_q_p.c \
$(PATH_PT)/check/check_wildcard.c $(PATH_PT)/check/conditions.c $(PATH_PT)/get/get_environment.c \
$(PATH_PT)/get/get_files.c $(PATH_PT)/get/get_here_doc.c $(PATH_PT)/get/get_input_output.c \
$(PATH_PT)/get/get_wildcard.c $(PATH_PT)/split/split_by_oper.c $(PATH_PT)/split/split_by_parantheses.c \
$(PATH_PT)/split/split_by_space.c $(PATH_PT)/split/split_by_space2.c $(PATH_PT)/split/split_cmds.c


C_FILES = $(C_FILES_F) $(C_FILES_G) $(C_FILES_PT) minibash.c
O_FILES = $(C_FILES:.c=.o)
FLAGS = -Wall -Wextra -Werror
NAME = minibash.a
BONUS_NAME = minibash_bonus.a
EXE = minibash
EXE_BONUS = minibash_bonus

all:$(NAME)

bonus:$(BONUS_NAME)

$(NAME):$(O_FILES)
	ar -rcs $(NAME) $(O_FILES)
	$(CC) $(NAME) -o $(EXE) -lreadline

# $(BONUS_NAME):$(BONUS_O_FILES)
# 	ar -rcs $(BONUS_NAME) $(BONUS_O_FILES)
# 	$(CC) $(BONUS_NAME) -o $(BONUS_EXE)

%.o:%.c push_swap.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(O_FILES) $(BONUS_O_FILES)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(EXE) $(EXE_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re