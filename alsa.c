#include "alsa.h"

#include <alsa/asoundlib.h>

uint8_t alsaVolume(void)
{
	snd_mixer_t* mixer;
	snd_mixer_selem_id_t* sid;
	snd_mixer_elem_t* elem;
	long value, max, min;
	double normalized;

	snd_mixer_open(&mixer, 0);
	snd_mixer_attach(mixer, "default"); 
	snd_mixer_selem_register(mixer, NULL, NULL);
	snd_mixer_load(mixer);

	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, "Master");
	elem = snd_mixer_find_selem(mixer, sid);

	snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

	snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_FRONT_LEFT, &value);
	normalized = (double) (value - min) / (double) (max - min); 

	snd_mixer_close(mixer);
	return (uint8_t) (normalized * 100);
}
