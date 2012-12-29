#include <stdio.h>

#include "net.h"
#include "soundinit.h"
#include "soundtest.h"
#include "recordtest.h"

#define RECORD_FRAMES_COUNT 100000

static int
test_tun (void)
{
    struct hila_net *net;

    net = hila_net_open ();
    if (!net) {
        printf ("cannot open tun.\n");
        return -1;
    }
    printf ("tun opened!\n");
    hila_net_close (net);
    return 0;
}

static int
play_sound (void)
{
    if (soundtest_play () < 0) {
        printf ("could not play sound.\n");
        return -1;
    }
    printf ("sound should have played.\n");
    return 0;
}

static int
print_record_samples (void)
{
    int err;
    int i;
    unsigned char record_frames[RECORD_FRAMES_COUNT];

    err = 0 > recordtest_record (record_frames, RECORD_FRAMES_COUNT);
    if (err) {
        printf ("could not record sound.\n");
        return -1;
    }
    for (i = 0; i < RECORD_FRAMES_COUNT; i++) {
        printf ("%d\n", (int) record_frames[i]);
    }
    return 0;
}

static int
hila_main (void)
{
    int err;

    err = test_tun () < 0;
    err = play_sound () < 0 || err;
    err = print_record_samples () < 0 || err;
    return -err;
}

int
main (int argc, char **argv)
{
    sound_init ();
    return -hila_main ();
}
