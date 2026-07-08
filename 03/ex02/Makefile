# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvigara- <mvigara-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/01 14:12:31 by mvigara-          #+#    #+#              #
#    Updated: 2025/11/04 19:49:47 by mvigara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME		= fragtrap

# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# Source files
SRCS		= main.cpp \
			  ClapTrap.cpp \
			  ScavTrap.cpp \
			  FragTrap.cpp 

# Object files
OBJS		= $(SRCS:.cpp=.o)

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Main rule
all: $(NAME)

# Compile the program
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compile .cpp files to .o
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	@rm -f $(OBJS)
	@echo "$(RED)✗ Object files removed$(RESET)"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

# Recompile
re: fclean all

.PHONY: all clean fclean re
