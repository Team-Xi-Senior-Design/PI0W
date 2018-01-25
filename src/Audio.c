/* Author: MSOE Team Xi Senior Design 2017
 * Date: 12/2017
 * Description: Contains functions that will control audio
 */

 /********************
 * External Includes *
 *********************/
#include "Audio.h"
#include "Global.h"
#include "NetworkPacket.h"
#include <stdio.h>
#include <alsa/asoundlib.h>

#define ALSA_PCM_NEW_HW_PARAMS_API

int rc;
int size;
snd_pcm_t *playbackHandle;
snd_pcm_t *captureHandle;
snd_pcm_hw_params_t *params;
unsigned int val;
//int dir;
snd_pcm_uframes_t frames = 32768;

/*
 * Description:
 * @param:
 * @return: NULL
 */
 void  initCapture(){
	//Open for capture
	rc = snd_pcm_open(&captureHandle, "default", SND_PCM_STREAM_CAPTURE,0);
	if (rc < 0){
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		fprintf(stderr, "successfully opened\n");
	}
	//Allocate hw parameter objects
	snd_pcm_hw_params_malloc(&params);
	//Fill with default values
	snd_pcm_hw_params_any(captureHandle, params);
	//Interleaved mode
	snd_pcm_hw_params_set_access(captureHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	//Signed 16-bit little-endian format
	snd_pcm_hw_params_set_format(captureHandle, params, SND_PCM_FORMAT_S16_LE);
	//44100 bps samp rate
	val = 32000;
	snd_pcm_hw_params_set_rate_near(captureHandle, params, &val, NULL);
	//one channel
	snd_pcm_hw_params_set_channels(captureHandle, params, 1);
	//Period size to 32 frames
	snd_pcm_hw_params_set_period_size_near(captureHandle, params, &frames, NULL);
	//Write params to driver
	rc = snd_pcm_hw_params(captureHandle, params);
	if(rc<0){
		fprintf(stderr,"unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		fprintf(stderr, "parameters sucessfully set\n");
	}
	//Set buffer
	snd_pcm_hw_params_get_period_size(params, &frames, NULL);
	size = frames * 2; //2 byte/sample, 1 channels
	snd_pcm_hw_params_free(params);
 }


/*
 * Description:
 * @param:
 * @return: NULL
 */
 void  initPlayback(){
	//Open for playback
	rc = snd_pcm_open(&playbackHandle, "default", SND_PCM_STREAM_PLAYBACK,0);
	if (rc < 0){
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		fprintf(stderr, "successfully opened\n");
	}
	//Allocate hw parameter objects
	snd_pcm_hw_params_malloc(&params);
	//Fill with default values
	snd_pcm_hw_params_any(playbackHandle, params);
	//Interleaved mode
	snd_pcm_hw_params_set_access(playbackHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	//Signed 16-bit little-endian format
	snd_pcm_hw_params_set_format(playbackHandle, params, SND_PCM_FORMAT_S16_LE);
	//one channel
	snd_pcm_hw_params_set_channels(playbackHandle, params, 1);
	//44100 bps samp rate
	val = 32000;
	snd_pcm_hw_params_set_rate_near(playbackHandle, params, &val, NULL);
	//Period size to 32 frames
	snd_pcm_hw_params_set_period_size_near(playbackHandle, params, &frames, NULL);
	//Write params to driver
	rc = snd_pcm_hw_params(playbackHandle, params);
	if(rc<0){
		fprintf(stderr,"unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		fprintf(stderr, "parameters sucessfully set\n");
	}
	//Set buffer
	snd_pcm_hw_params_get_period_size(params, &frames, NULL);
	size = frames * 2; //2 byte/sample, 1 channels
	snd_pcm_hw_params_free(params);
 }

int captureAudio(char* buffer, int size){
	rc = snd_pcm_readi(captureHandle, buffer, size);
	if(rc == -EPIPE){
		fprintf(stderr, "cap overrun occured\n");
		snd_pcm_prepare(captureHandle);
	}else if(rc < 0){
		fprintf(stderr, "error from readi: %s\n", snd_strerror(rc));
		rc = 0;
	}
	else if(rc != (int)size){
		fprintf(stderr, "short read, read %d frames\n", rc);
	}
	return rc;
}

void playbackAudio(char* buffer, int bufSize){
	if ((rc = snd_pcm_writei(playbackHandle, buffer, bufSize))==-EPIPE)
	{
		fprintf(stderr, "play overrun occured\n");
		snd_pcm_prepare(playbackHandle);
	}
	else if(rc < 0){
		fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
	}
	else if(rc != (int)(bufSize)){
		fprintf(stderr, "short write, write %d frames\n", rc);
	}
}

 /*
 * Description:
 * @param:
 * @return: NULL
 */
 void  cleanUpAudio(){
	snd_pcm_drain(captureHandle);
	snd_pcm_close(captureHandle);
	snd_pcm_drain(playbackHandle);
	snd_pcm_close(playbackHandle);
}

void* handleAudio(void* params){
	packet_t packet;
	packet.datatype = VOICE_DATA;
	while(1)
	{
		packet.size = captureAudio(packet.data, BUFFER_SIZE);
		write(audioPipeBlue[1], &packet, sizeof(packet_t));
	}
}

void* handlePlayAudio(void* params){
	packet_t packet;
	while(1)
	{
		read(audioPipeHead[0], &packet, sizeof(packet_t));
		playbackAudio(packet.data, packet.size);
	}
}

 /*
 * Description:
 * @param:
 * @return: NULL
 */
 void  audioFromNetwork(){
	 
}

 /*
 * Description:
 * @param:
 * @return: NULL
 */
 void* audioToNetwork(void* toNetwork){
	
}

 /*
 * Description:
 * @param:
 * @return:
 */
 void* networkToAudio(void* toAudio){
	 
}

 /*
 * Description:
 * @param:
 * @return:
 */
 void  readFromAudioDev(){
	 
}

 /*
 * Description:
 * @param:
 * @return: NULL
 */
 void  writeToAudioDev(){
	 
}
