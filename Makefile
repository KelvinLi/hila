objects := main.o net.o fft.o soundinit.o soundtest.o recordtest.o
binname := hila

lib_opts := -lasound
CFLAGS += -g -O2 -pipe @ccopts $(lib_opts)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(binname) : $(objects)
	$(CC) $(CFLAGS) -o $(binname) $(objects)

main.o : net.h
net.o : net.h
soundinit.o : soundinit.h
soundtest.o : soundtest.h
recordtest.o : recordtest.h
fft.o : fft.h

.PHONY : clean
clean :
	$(RM) $(binname) $(objects)
