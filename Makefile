CC	=	gcc
CFLAGS	=	-W	-Wall	-ansi	-pedantic	-std=c99	-lm   -pthread
SRC	=	$(wildcard *.c)
OBJ	=	$(SRC:.c=.o)
EXEC	=	lect_red
$(EXEC)	:	$(OBJ)
				  				$(CC)	-o	$(EXEC)	$(OBJ)	$(CFLAGS)
%.o	:	%.c
	$(CC)	-o	$@	-c	$<	$(CFLAGS)
clean	:	
								rm	-rf	*.o
clean_all	:	clean							
								rm	-rf	lect_red
