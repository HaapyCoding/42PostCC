# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/01 08:49:27 by ykeciri           #+#    #+#              #
#    Updated: 2025/12/01 14:05:33 by ykeciri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all: 
	docker compose up -d --build

logs:
	docker compose logs -f

stop:
	docker compose down

clear: stop
	docker image prune --force
	docker image prune -a --force
	
re: stop clear all

onion:
	@docker compose exec web sh -c 'service tor status && cat /var/lib/tor/my_website/hostname'
