objects = main.o net.o
binname = hila

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(binname) : $(objects)
	$(CC) -o $(binname) $(objects)

main.o : net.h
net.o : net.h

.PHONY : clean
clean :
	$(RM) $(binname) $(objects)
