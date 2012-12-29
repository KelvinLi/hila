#include <alsa/asoundlib.h>

#include "recordtest.h"

struct record_info {
    snd_pcm_t *handle;
    unsigned int desired_size;
};

struct record_data {
    unsigned char *frames;
    unsigned int actual_size;
};

static const unsigned int SAMPLE_RATE = 48000;
static const char *device = "default";

static int
record_to_data (struct record_data *data, struct record_info *info)
{
    int err;
    snd_pcm_sframes_t readi_ret;

    err = 0 > snd_pcm_set_params(info->handle,
                                 SND_PCM_FORMAT_U8,
                                 SND_PCM_ACCESS_RW_INTERLEAVED,
                                 1,           /* number of channels */
                                 SAMPLE_RATE,
                                 0,           /* disallow resampling */
                                 5000000);    /* latency in microseconds */
    if (err)
        return -1;
    readi_ret = snd_pcm_readi(info->handle,
                              data->frames,
                              (snd_pcm_uframes_t) info->desired_size);
    if (readi_ret < 0)
        return -1;
    data->actual_size = (unsigned int) readi_ret;
    if (data->actual_size != info->desired_size)
        return -1;
    return 0;
}

static int
init_record_info (struct record_info *info, unsigned int desired_size)
{
    info->desired_size = desired_size;
    return snd_pcm_open (&info->handle,
                         device,
                         SND_PCM_STREAM_CAPTURE,
                         0); /* blocking mode */
}

static int
destroy_record_info (struct record_info *info)
{
    return snd_pcm_close (info->handle);
}

int
recordtest_record (unsigned char *frames, unsigned int size)
{
    int err;
    struct record_info info;
    struct record_data data;

    err = 0 > init_record_info (&info, size);
    if (err)
        return -err;
    data.frames = frames;
    err = 0 > record_to_data (&data, &info);
    err = 0 > destroy_record_info (&info) || err;
    return -err;
}
