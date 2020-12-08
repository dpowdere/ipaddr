# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/08 17:15:54 by dpowdere          #+#    #+#              #
#    Updated: 2020/12/08 17:20:09 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ipaddr
CC = gcc
CFLAGS = -Wall -Wextra -Werror

$(NAME): $(NAME).c $(NAME).h
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean fclean re

all: $(NAME)

clean:
	$(RM) *.o *.gch

fclean: clean
	$(RM) $(NAME) *.out

re: fclean all
