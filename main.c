#include <stdio.h>

#include "net.h"
#include "soundtest.h"

static void
hila_main (void)
{
    struct hila_net *net;
    net = hila_net_open ();
    if (!net) {
        printf ("cannot open tun.\n");
        return 1;
    }
    printf ("tun opened!\n");
    hila_net_close (net);

    soundtest_play ();
    return 0;
}

int
main (int argc, char **argv)
{
    sound_init ();
    hila_main ();
}
