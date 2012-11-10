objects = main.o net.o
binname = hila
CFLAGS += -g -O2 -pipe \
          -Wall -Wunused-parameter -Werror=declaration-after-statement \
          -Wstrict-prototypes  -Wno-char-subscripts

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(binname) : $(objects)
	$(CC) $(CFLAGS) -o $(binname) $(objects)

main.o : net.h
net.o : net.h

.PHONY : clean
clean :
	$(RM) $(binname) $(objects)
