# Nombre del ejecutable
NAME		= account

# Compilador y flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# Archivos fuente
SRCS		= tests.cpp \
			  Account.cpp

# Archivos objeto
OBJS		= $(SRCS:.cpp=.o)

# Colores
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Regla principal
all: $(NAME)

# Compilar el programa
$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

# Compilar archivos .cpp a .o
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos objeto
clean:
	@rm -f $(OBJS)
	@echo "$(RED)✗ Object files removed$(RESET)"

# Limpiar todo
fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

# Recompilar
re: fclean all

.PHONY: all clean fclean re
