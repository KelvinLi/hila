#include <stdio.h>
#include <stdlib.h>

#include "net.h"
#include "soundinit.h"
#include "soundtest.h"
#include "recordtest.h"
#include "fft.h"

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
test_fft (void)
{
    double *wsave;
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double *ret;
    int i;

    wsave = fft_initialize (5);
    if (!wsave)
        return -1;
    ret = fft_compute (5, data, wsave);
    if (!ret)
        goto fail;
    for (i = 0; i < 6; i++) {
        printf ("%.10g\n", ret[i]);
    }
    free (ret);
    free (wsave);
    return 0;
fail:
    free (wsave);
    return -1;
}

static int
hila_main (void)
{
    int err;

    err = test_tun () < 0;
    err = play_sound () < 0 || err;
    err = print_record_samples () < 0 || err;
    err = test_fft () < 0 || err;
    return -err;
}

int
main (int argc, char **argv)
{
    sound_init ();
    return -hila_main ();
}
