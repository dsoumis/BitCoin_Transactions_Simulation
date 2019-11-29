#
# In order to execute this "Makefile" just type "make"
#

OBJS    = Hash_Table_Implementation.o List_Implementation.o main.o Tree_Implementation.o
SOURCE  = Hash_Table_Implementation.c List_Implementation.c main.c Tree_Implementation.c
HEADER  = Hash_Table_Implementation.h List_Implementation.h Structures.h  Tree_Implementation.h
OUT     = bitcoin

CC      = gcc
FLAGS   = -g -c 
# -g option enables debugging mode
# -c flag generates object code for separate files

all: 	$(OBJS)
		$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<<
Hash_Table_Implementation.o: Hash_Table_Implementation.c
	$(CC) $(FLAGS) Hash_Table_Implementation.c

List_Implementation.o: List_Implementation.c
	$(CC) $(FLAGS) List_Implementation.c

main.o: main.c
	$(CC) $(FLAGS) main.c

Tree_Implementation.o: Tree_Implementation.c
	$(CC) $(FLAGS) Tree_Implementation.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
