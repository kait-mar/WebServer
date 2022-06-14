# 	The compilation ================================
CFLAGS			= -Wall -Wextra -Werror -g
CC 				= clang++ -g -fsanitize=address
CPPVERSION 		= -std=c++98

BINDIR		= bin
OBJDIR		= objs
SRCDIR		= srcs

SRCS =		$(wildcard $(SRCDIR)/*/*.cpp $(SRCDIR)/*/*/*.cpp $(SRCDIR)/*/*/*/*.cpp $(SRCDIR)/*/*/*/*/*.cpp $(SRCDIR)/*.cpp)
OBJS =		$(subst $(SRCDIR),$(OBJDIR), $(SRCS:.cpp=.o))

DEB	 =		$(OBJS:%.o=%.d)

NAME = $(BINDIR)/webServer

all : $(NAME)

$(NAME): $(OBJS)
	mkdir -p $(@D)
	$(CC) $(CPPVERSION) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(@D)
	$(CC) $(CPPVERSION) $(CFLAGS) -MMD -c $< -o $@

-include $(DEB)

clean :
	rm -rf $(OBJS)

re: clean all

run:
	./$(NAME) ConfigurationFiles/abc.conf

fclean : clean
	rm -rf $(DEB)
	rm -rf $(NAME)