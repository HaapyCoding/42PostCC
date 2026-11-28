# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/28 12:14:29 by ykeciri           #+#    #+#              #
#    Updated: 2026/11/28 12:15:38 by ykeciri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Bank

SRCS =	src/main.cpp src/Bank.cpp src/Loan.cpp src/Account.cpp
OBJS = $(SRCS:src/%.cpp=obj/%.o)
DEPS = $(SRCS:src/%.cpp=obj/%.d)
FLAGS = -Wall -Wextra -Werror -std=c++98
CXX = c++
INC = -I./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

obj/%.o: src/%.cpp
	@if [ ! -d obj ]; then mkdir obj; fi
	$(CXX) $(FLAGS) $(INC) -MMD -MP -c $< -o $@

create_dirs:
	mkdir -p obj

-include $(DEPS)

clean:
	rm -rf $(OBJS) $(DEPS) obj
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re