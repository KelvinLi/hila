#include <stdio.h>

#include "net.h"
#include "soundinit.h"
#include "soundtest.h"

static int
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

    if (soundtest_play () < 0) {
        printf ("could not play sound.\n");
        return 1;
    }
    printf ("sound should have played.\n");
    return 0;
}

int
main (int argc, char **argv)
{
    sound_init ();
    return hila_main ();
}
