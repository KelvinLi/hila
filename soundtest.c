#include <alsa/asoundlib.h>

#include "soundtest.h"

static const char *device = "default";

int
soundtest_play (void)
{
    int err;
    snd_pcm_t *handle;

    err = snd_pcm_open (&handle, device, SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        printf ("Playback open error: %s\n", snd_strerror(err));
        return -1;
    }

    snd_pcm_close (handle);
    return 0;
}
