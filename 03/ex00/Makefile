# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvigara- <mvigara-@student.42school.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/01 14:12:31 by mvigara-          #+#    #+#              #
#    Updated: 2025/11/01 14:15:11 by mvigara-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME		= claptrap

# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# Source files
SRCS		= main.cpp \
			  ClapTrap.cpp 

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
