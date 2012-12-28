#include <linux/if_tun.h>

struct hila_net;

struct hila_net * hila_net_open (void);
void hila_net_close (struct hila_net *net);
