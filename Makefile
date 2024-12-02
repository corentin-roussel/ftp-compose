
CC = g++

CFLAGS = -Wall -Werror -Wextra -g3

SRC1 = main.cpp
EXEC1 = lfp_serv
OBJDIR1 = server/obj/
SRCDIR1 = server/src/
SRCS1 = $(addprefix $(SRCDIR1), $(SRC1))
OBJ1 = $(SRCS1:$(SRCDIR1)%.cpp=$(OBJDIR1)%.o)

SRC2 = main.cpp
EXEC2 = lfp
OBJDIR2 = client/obj/
SRCDIR2 = client/src/
SRCS2 = $(addprefix $(SRCDIR2), $(SRC2))
OBJ2 = $(SRCS2:$(SRCDIR2)%.cpp=$(OBJDIR2)%.o)

SRC3 = Send.cpp Receive.cpp
OBJDIR3 = transfer/obj/
SRCDIR3 = transfer/src/
SRCS3 = $(addprefix $(SRCDIR3), $(SRC3))
OBJ3 = $(SRCS3:$(SRCDIR3)%.cpp=$(OBJDIR3)%.o)

all : $(EXEC1) $(EXEC2)

$(EXEC1) : $(OBJ1) $(OBJ3)
	$(CC) -o $@ $^

$(EXEC2) : $(OBJ2) $(OBJ3)
	$(CC) -o $@ $^

$(OBJDIR1)%.o : $(SRCDIR1)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR2)%.o : $(SRCDIR2)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR3)%.o : $(SRCDIR3)%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(OBJ1)* $(OBJ2)*

mrproper : clean
	rm -rf $(EXEC1) $(EXEC2)
