#include <stdio.h>

#include "net.h"

int
main (int argc, char **argv)
{
    struct hila_net *net;
    net = hila_net_open ();
    if (!net) {
        printf ("cannot open tun");
        return 1;
    }
    printf ("opened!\n");
    hila_net_close (net);
    return 0;
}
