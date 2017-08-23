CXX := @clang++

CXXFLAGS += -Iincludes/
#CXXFLAGS += -Werror -g3
CXXFLAGS += -std=c++11
CXXFLAGS += -O2
CXXFLAGS += -Wextra -Wall -Wshadow -Wfloat-equal -Wundef -Wpointer-arith
CXXFLAGS += -Wcast-align -Wstrict-prototypes -Waggregate-return
CXXFLAGS += -Wswitch-default -Wswitch-enum -Wunreachable-code -pedantic

SRCS = srcs/Chip8.cpp \
       srcs/Cpu.cpp \
       srcs/Keypad.cpp \
       srcs/Memory.cpp \
       srcs/Screen.cpp \
       srcs/main.cpp


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