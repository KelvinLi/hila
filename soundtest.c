#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>

#include "soundtest.h"

static const unsigned int SAMPLE_RATE = 48000;
static const char *device = "default";

/* writes data to frames */
static void
generate_frames (unsigned char *frames, unsigned int size)
{
    /* complete one cycle in (SAMPLE_RATE / frequency) frames */
    const unsigned int frequency = 700;
    const unsigned int max_value = 255;
    unsigned int i;

    for (i = 0; i < size; i++) {
        frames[i] = (unsigned char) (i * max_value * frequency / SAMPLE_RATE);
    }
}

static int
play_with_handle (snd_pcm_t *handle)
{
    const unsigned int size = 100000;
    int err;
    snd_pcm_sframes_t frames_ret;
    unsigned char *frames;

    err = snd_pcm_set_params (handle,
                              SND_PCM_FORMAT_U8,
                              SND_PCM_ACCESS_RW_INTERLEAVED,
                              1,           /* number of channels */
                              SAMPLE_RATE,
                              0,           /* disallow resampling */
                              500000);     /* latency in microseconds */
    if (err < 0)
        return -1;
    frames = malloc (sizeof (*frames) * size);
    if (!frames)
        return -1;
    generate_frames (frames, size);
    frames_ret = snd_pcm_writei (handle,
                                 frames,
                                 (snd_pcm_uframes_t) size);
    free (frames);
    return frames_ret < 0 ? -1 : 0;
}

int
soundtest_play (void)
{
    int err;
    snd_pcm_t *handle;

    err = snd_pcm_open (&handle,
                        device,
                        SND_PCM_STREAM_PLAYBACK,
                        0); /* blocking mode */
    if (err < 0)
        return -1;
    err = play_with_handle (handle);
    snd_pcm_close (handle);
    return err < 0 ? -1 : 0;
}
