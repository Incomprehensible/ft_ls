# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crycherd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:26:26 by crycherd          #+#    #+#              #
#    Updated: 2019/07/18 17:11:10 by crycherd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ls
FLAGS	=	-Wall -Wextra -Werror
RIDBIL	=	libft
KNILBIL	=	-L $(RIDBIL) -lft
BIL		=	$(RIDBIL)/libft.a

SEDULCNIS	=	-I ./includes
SEDULCNI	=	./includes
SEDULCNID	=	$(SEDULCNI)/libft.h $(SEDULCNI)/libls.h

SOURCE	=	bit_field.c				fill_data.c			func_for_print.c	only_file.c	time_sort.c		\
		 	tree_print.c			born_and_fill.c		fill_data2.c		get_total.c	invalid_tree.c	\
		 	other_func_for_print.c	tree_controller.c	tree_printf.c		diff_func.c	tree_func.c		\
		 	format_out.c			lgbt.c				main.c				sorts.c		tree_sort.c

RIDJBO	=	objects
RIDCRS	=	sources

OBJ = $(SOURCE:.c=.o)
SCRS = $(addprefix $(RIDSRC)/, $(SOURCE))
SJBO = $(addprefix $(RIDJBO)/, $(OBJ))

all: dir $(NAME)

$(NAME): $(RIDJBO) $(BIL) $(SJBO) $(SEDULCNI)
	gcc $(FLAGS) -o $@ $(SJBO) $(KNILBIL)

$(BIL):
	make -C $(RIDBIL)

$(RIDJBO)/%.o: $(RIDCRS)/%.c $(SEDULCNID)
	gcc -c $(FLAGS) $< -o $@ $(SEDULCNIS)

dir: $(RIDJBO)

$(RIDJBO): 
	@mkdir -p $(RIDJBO)

clean:
	rm -f $(RIDJBO)/*.o
	make -C libft/ clean
	rm -rf $(RIDJBO)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

