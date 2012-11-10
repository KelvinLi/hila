#include <stdio.h>

#include "net.h"

int
main (int argc, char **argv)
{
    struct hila_net *net;
    net = hila_net_open ();
    printf ("opened!\n");
    hila_net_close (net);
    return 0;
}
