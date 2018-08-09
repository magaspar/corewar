# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/07/27 19:23:11 by jjanin-r    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all libft asm corewar clean fclean re

CC = gcc

NAME_ASM = asm

NAME_VM = corewar
		
C_FLAGS = -Wall -Wextra -Werror

DIR_ROOT = ./

DIR_LIB = Libft/

DIR_VM = VM_Corewar/

DIR_ASM = ASM_Corewar/

INC = $(addprefix $(DIR_INC), $(NAME_INC))

SRC = $(addprefix $(DIR_SRC), $(NAME_SRC))

OBJ = $(SRC:.c=.o)

CURSOR = 0

NB_FILES = $(words $(SRC))

all: libft corewar asm

asm: libft 
	@if !(make -q -C $(DIR_ASM)); then \
		rm -rf $(NAME_ASM);\
		make -C $(DIR_ASM);\
	fi;

corewar: libft
	@if !(make -q -C $(DIR_VM)); then \
		rm -rf $(NAME_VM);\
		make -C $(DIR_VM);\
	fi;

libft: 
	@if !(make -q -C $(DIR_LIB)); then \
		rm -f $(NAME_VM); \
		rm -f $(NAME_ASM); \
		make -C $(DIR_LIB);\
	fi;

clean:
	@make clean -C $(DIR_LIB)
	@make clean -C $(DIR_VM)
	@make clean -C $(DIR_ASM)

fclean: clean
	@make fclean -C $(DIR_LIB)
	@make fclean -C $(DIR_VM)
	@make fclean -C $(DIR_ASM)

re: fclean all
