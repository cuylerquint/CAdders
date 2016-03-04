CFLAGS	= -g -Wall -Werror
LDFLAGS	=
CC	= gcc
LD	= gcc
TARG1	= a3
OBJ1	= a3.o

all:	$(TARG1)
$(TARG1): $(OBJ1)
	$(LD) $(LDFLAGS) $(OBJ1) -o $(TARG1)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o *Ã‹Å“ a.out $(TARG1)
