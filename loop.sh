#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    loop.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpowdere <dpowdere@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/12 17:21:55 by dpowdere          #+#    #+#              #
#    Updated: 2020/12/12 17:21:55 by dpowdere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG=./ipaddr
QUIT_ARG=q
CLEAR_ARG=c

while true
do
	echo "'$QUIT_ARG' quit"
	echo "'$CLEAR_ARG' clear the screen (default action)"
	printf 'input arguments for `'$PROG'` program: '
	read -a ARR
	if [ ${#ARR} -eq 0 ] || [ ${ARR[0]} == "$CLEAR_ARG" ]
	then
		clear
	fi
	if [ ${#ARR} -gt 0 ] && [ ${ARR[0]} == "$QUIT_ARG" ]
	then
		exit 0
	fi
	if [ ${#ARR} -gt 0 ] && ! [ ${ARR[0]} == "$CLEAR_ARG" ]
	then
		$PROG ${ARR[@]}
	fi
done
