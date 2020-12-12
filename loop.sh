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
while true
do
	printf 'Input arguments for `'$PROG'` program or type `q` to quit: '
	read -a ARR
	if [ ${#ARR} -gt 0 ] && [ ${ARR[0]} == "q" ]
	then
		exit 0
	fi
	if [ ${#ARR} -gt 0 ]
	then
		$PROG ${ARR[@]}
	fi
done
