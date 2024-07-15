# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    exemple.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoyern <zoyern@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/06/12 23:16:59 by zoyern           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEMPLE_DIR		= $(CURDIR)/exemple

EXEMPLE_FILES	= main.c

SRC_EXEMPLE	= $(addprefix $(EXEMPLE_DIR)/, $(EXEMPLE_FILES))
