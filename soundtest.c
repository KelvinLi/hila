#include <stdarg.h>
#include <stdio.h>
#include <alsa/asoundlib.h>

#include "soundtest.h"

#undef DEBUG_SOUND_ERROR

static const char *device = "default";

/* Modified version of ALSA default error handler */
static void
sound_error_handler (const char *file,
                     int line,
                     const char *function,
                     int err,
                     const char *fmt,
                     ...)
{
    va_list arg;

#ifdef DEBUG_SOUND_ERROR
    fprintf (stderr, "soundtest handling ALSA error:\n");
    fprintf (stderr, "\t%s:%i:(%s) ", file, line, function);
    va_start (arg, fmt);
    vfprintf (stderr, fmt, arg);
    va_end (arg);
    if (err)
        fprintf (stderr, ": %s", snd_strerror(err));
    putc ('\n', stderr);
#endif
}

void
sound_init (void)
{
    snd_lib_error_set_handler (sound_error_handler);
}

int
soundtest_play (void)
{
    int err;
    snd_pcm_t *handle;

    err = snd_pcm_open (&handle, device, SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        fprintf (stderr, "Playback open error: %s\n", snd_strerror(err));
        return -1;
    }

    snd_pcm_close (handle);
    return 0;
}
