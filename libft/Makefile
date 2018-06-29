# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obalagur <obalagur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/07/25 21:13:53 by pbondoer          #+#    #+#              #
#    Updated: 2017/12/08 20:12:35 by obalagur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = 	ft_bzero.c\
		ft_memcpy.c\
		ft_strlen.c\
		ft_strdup.c\
		ft_atoi.c\
		ft_strdel.c\
		ft_strsub.c\
		ft_strjoin.c\
		ft_lstnew.c\
		ft_list_add.c\
		ft_splinter.c\
		ft_atoi_base.c\
		get_next_line.c\
		ft_putstr.c\
		ft_strchr.c\
		ft_list_clear.c\
		ft_lst_delone.c\
		ft_tolower.c\
		ft_str_contains.c\
		ft_memdel.c\
		ft_strtrim.c\
		for_each_gnl.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -c -Wall -Wextra -Werror -o $@ $<

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
