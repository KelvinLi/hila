objects = main.o net.o
binname = hila
CFLAGS += -g -O2 -pipe \
          -Wall -Wextra -pedantic -Wunused-parameter \
          -Werror=declaration-after-statement \
          -Werror=implicit-function-declaration \
          -Wstrict-prototypes -Wunused-but-set-variable -Wdouble-promotion \
          -Wtrampolines -Wfloat-equal -Wunsafe-loop-optimizations \
          -Wcast-align -Wwrite-strings -Wconversion -Wlogical-op \
          -Waggregate-return -Wmissing-prototypes -Wmissing-declarations \
          -Wpadded -Wnormalized=nfkc

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(binname) : $(objects)
	$(CC) $(CFLAGS) -o $(binname) $(objects)

main.o : net.h
net.o : net.h

.PHONY : clean
clean :
	$(RM) $(binname) $(objects)
