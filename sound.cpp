// Sound capture and analyzation
//
// Copyright (C) 2010  Martin Sandsmark - martin.sandsmark@kde.org
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of the
// License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, 51 Franklin Steet, Fifth Floor, Boston, MA 02110-1301, USA

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "sound.h"
#include "msg.h"

Sound::Sound (const char *device, const char *file) : 
    m_running(true),
    m_fht(BUFEXP),
    m_samples(0),
    m_playbackHandle(0),
    m_history(new float[64]),
    m_vorbisfile(new OggVorbis_File),
    m_thread(0)
{
    LOG("opening file: " << file);
    if (ov_fopen(file, m_vorbisfile)) {
        fprintf(stderr, "FATAL: Unable to open music file!\n");
        m_running = false;
        return;
    }

    vorbis_info *info = ov_info(m_vorbisfile, -1);
    unsigned int channels = info->channels;
    unsigned int rate = info->rate;
    LOG("Channels: " << channels << " Rate: " << rate << " Buffer size: " << BUFSIZE);

    snd_pcm_hw_params_t *hw_params;

    if ((m_err = snd_pcm_open (&m_playbackHandle, device, SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
        fprintf (stderr, "cannot open audio device %s (%s)\n", 
             device,
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
        fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params_any (m_playbackHandle, hw_params)) < 0) {
        fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params_set_access (m_playbackHandle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
        fprintf (stderr, "cannot set access type (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params_set_format (m_playbackHandle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
        fprintf (stderr, "cannot set sample format (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params_set_rate_near (m_playbackHandle, hw_params, &rate, 0)) < 0) {
        fprintf (stderr, "cannot set sample rate (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params_set_channels (m_playbackHandle, hw_params, 1)) < 0) {
        fprintf (stderr, "cannot set channel count (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    if ((m_err = snd_pcm_hw_params (m_playbackHandle, hw_params)) < 0) {
        fprintf (stderr, "cannot set parameters (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    snd_pcm_hw_params_free (hw_params);

    if ((m_err = snd_pcm_prepare (m_playbackHandle)) < 0) {
        fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
             snd_strerror (m_err));
        exit (1);
    }

    m_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)); 
    pthread_mutex_init(m_mutex, 0); // fuck error handling
}

Sound::~Sound() {
    m_running = false;
    if (m_thread)
        pthread_join((*m_thread), 0);

    if (m_playbackHandle)
        snd_pcm_close (m_playbackHandle);
    ov_clear(m_vorbisfile);

    free(m_samples);
    delete [] m_history;
}

void Sound::play()
{
    if (!m_running)
        return;

    if (!m_thread) {
        m_thread = (pthread_t*)malloc(sizeof(pthread_t));
        pthread_create(m_thread, 0, &Sound::startLoop, this);
    }
    pthread_mutex_unlock(m_mutex);
}

void Sound::pause()
{
    pthread_mutex_lock(m_mutex);
}

void *Sound::startLoop(void *obj) {
    reinterpret_cast<Sound*>(obj)->mainloop();

    return 0;
}

void Sound::mainloop() {
    long ret = 1L;
    int pos;
    uint16_t *buffer;
    LOG("playing");
    while (m_running && ret > 0) {
        buffer = (uint16_t*)calloc(sizeof(uint16_t), BUFSIZE);
        ret = ov_read(m_vorbisfile, reinterpret_cast<char*>(buffer), BUFSIZE, 0, 1, 1, &pos);

        snd_pcm_writei(m_playbackHandle, buffer, BUFSIZE/2);
        pthread_mutex_lock(m_mutex);
        free(m_samples);
        m_samples = buffer;
        pthread_mutex_unlock(m_mutex);
    }

    if (ret == 0) {
        LOG("finished playing, end of file");
    } else if (ret == OV_HOLE) {
        LOG("finished playing, corrupt data");
    } else if (ret == OV_EBADLINK) {
        LOG("finished playing, invalid stream");
    } else if (ret == OV_EINVAL) {
        LOG("unable to read headers");
    } else {
        LOG("finished playing, unknown error");
    }
}

/*float *Sound::getBass()
{
    float *buffer = new float[BUFSIZE];
    float input[BUFSIZE];
    pthread_mutex_lock(m_mutex);
    for (int i=0; i<BUFSIZE; i++) {
        input[i] = static_cast<float>(m_samples[i]) / static_cast<float>(0x7fff);
    }
    pthread_mutex_unlock(m_mutex);

//    m_fht.copy(buffer, input);
//    m_fht.logSpectrum(input, buffer);
    m_fht.logSpectrum(buffer, input);
    m_fht.scale(buffer, 1.0/20);

    //m_fht.ewma(m_history, buffer, .0050);
//    m_fht.ewma(buffer, m_history, .75);

//    bass += 10 * buffer[1];// 64 audio samples in → 32 data points out
//    bass += 10 * buffer[2];// 64 audio samples in → 32 data points out
//    bass /= 2;
//    printf("%i\n", bass);

//    delete input;
//    delete buffer;

    return buffer;
}*/

