CXX := @clang++

CXXFLAGS += -Iincludes/
CXXFLAGS += -Werror -g3
CXXFLAGS += -std=c++14
CXXFLAGS += -O2
CXXFLAGS += -Wextra -Wall -Wshadow -Wfloat-equal -Wundef -Wpointer-arith
CXXFLAGS += -Wcast-align -Wstrict-prototypes -Waggregate-return
CXXFLAGS += -Wswitch-default -Wunreachable-code -pedantic

LDFLAGS += -lsfml-window -lsfml-graphics -lsfml-system

SRCS = srcs/main.cpp \
       srcs/Chip8.cpp \
       srcs/Pixels.cpp \
       srcs/opcodes.cpp \

OBJS = $(SRCS:.cpp=.o)

NAME = yache

RM = @rm -f

ECHO = -@printf
GREEN = "\x1b[32m"
RESET = "\x1b[0m"

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)
	$(ECHO) $(GREEN)"✓ Build successful !"$(RESET)"\n"

clean:
	$(RM) $(OBJS)
	$(ECHO) "✓ Cleaning object...\n"

fclean: clean
	$(RM) $(NAME)
	$(ECHO) "✓ Cleaning binaries...\n"

re: fclean all

.PHONY: all clean fclean re
