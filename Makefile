objects = main.o net.o

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

hila : $(objects)
	$(CC) -o hila $(objects)

main.o : net.h
net.o : net.h

.PHONY : clean
clean :
	$(RM) hila $(objects)
