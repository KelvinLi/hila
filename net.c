#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_tun.h>

#include "net.h"

struct hila_net {
    int fd;
};

struct hila_net *
hila_net_open (void)
{
    struct hila_net *net;
    net = malloc (sizeof (struct hila_net));
    if (!net)
        return NULL;

    net->fd = open ("/dev/net/tun", O_RDWR);
    if (net->fd < 0) {
        free (net);
        return NULL;
    }
    return net;
}

void
hila_net_close (struct hila_net *net)
{
    if (!net)
        return;
    close (net->fd);
    free (net);
}
