/* Author: MSOE Team Xi Senior Design 2017
 * Date: 12/2017
 * Description: Contains functions that will control audio
 */

 /********************
 * External Includes *
 *********************/
#include "Audio.h"
#include <stdio.h>
#include <alsa/asoundlib.h>

#define ALSA_PCM_NEW_HW_PARAMS_API

long loops;
int rc;
int size;
snd_pcm_t *playbackHandle;
snd_pcm_t *captureHandle;
snd_pcm_hw_params_t *params;
unsigned int val;
int dir;
snd_pcm_uframes_t frames;
char *buffer;

/*
 * Description:
 * @param:
 * @return: NULL
 */
 void  initCapture(){
	//Open for capture
	rc = snd_pcm_open(&captureHandle, "hw:1,0,0", SND_PCM_STREAM_CAPTURE,0);
	if (rc < 0){
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		fprintf(stderr, "successfully opened\n");
	}
	//Allocate hw parameter objects
	snd_pcm_hw_params_alloca(&params);
	//Fill with default values
	snd_pcm_hw_params_any(captureHandle, params);
	//Interleaved mode
	snd_pcm_hw_params_set_access(captureHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	//Signed 16-bit little-endian format
	snd_pcm_hw_params_set_format(captureHandle, params, SND_PCM_FORMAT_S16_LE);
	//two channels
	snd_pcm_hw_params_set_channels(captureHandle, params, 1);
	//44100 bps samp rate
	val = 44100;
	snd_pcm_hw_params_set_rate_near(captureHandle, params, &val, &dir);
	//Period size to 32 frames
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(captureHandle, params, &frames, &dir);
	//Write params to driver
	rc = snd_pcm_hw_params(captureHandle, params);
	if(rc<0){
		fprintf(stderr,"unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		fprintf(stderr, "parameters sucessfully set\n");
	}
	//Set buffer
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	size = frames * 2; //2 byte/sample, 2 channels
	buffer = (char*) malloc(size);
	//Set period
	snd_pcm_hw_params_get_period_time(params, &val, &dir);
	loops = 5000000 / val;
 }


/*
 * Description:
 * @param:
 * @return: NULL
 */
 void  initPlayback(){
	//Open for capture
	rc = snd_pcm_open(&playbackHandle, "hw:1,0,0", SND_PCM_STREAM_PLAYBACK,0);
	if (rc < 0){
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		printf("successfully opened\n");
	}
	//Allocate hw parameter objects
	snd_pcm_hw_params_alloca(&params);
	//Fill with default values
	snd_pcm_hw_params_any(playbackHandle, params);
	//Interleaved mode
	snd_pcm_hw_params_set_access(playbackHandle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	//Signed 16-bit little-endian format
	snd_pcm_hw_params_set_format(playbackHandle, params, SND_PCM_FORMAT_S16_LE);
	//one channels
	snd_pcm_hw_params_set_channels(playbackHandle, params, 1);
	//44100 bps samp rate
	val = 44100;
	snd_pcm_hw_params_set_rate_near(playbackHandle, params, &val, &dir);
	//Period size to 32 frames
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(playbackHandle, params, &frames, &dir);
	//Write params to driver
	rc = snd_pcm_hw_params(playbackHandle, params);
	if(rc<0){
		fprintf(stderr,"unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1); 
	}else{
		printf("parameters sucessfully set\n");
	}
	//Set buffer
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	size = frames * 2; //2 byte/sample, 2 channels
	buffer = (char*) malloc(size);
	//Set period
	snd_pcm_hw_params_get_period_time(params, &val, &dir);
	loops = 5000000 / val;
 }

void testCapture(){
	while(loops > 0){
		loops--;
		rc = snd_pcm_readi(captureHandle, buffer, frames);
		if(rc == -EPIPE){
			fprintf(stderr, "overrun occured\n");
			snd_pcm_prepare(captureHandle);
		}else if(rc < 0){
			fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
		}else if(rc != (int)frames){
			fprintf(stderr, "short read, read %d frames\n", rc);
		}
		rc = write(1, buffer, size);
		if(rc != size){
			fprintf(stderr, "short write: wrote %d bytes\n", rc);
		}
	}
	snd_pcm_drain(captureHandle);
	snd_pcm_close(captureHandle);
	free(buffer);
}
 
void testPlayback(){
	while(loops > 0){
		loops--;
		rc = read(0, buffer, size);
		if(rc==0){
			fprintf(stderr, "end of file on input\n");
			break;
		}else if(rc != size){
			fprintf(stderr, "short read: read %d bytes\n", rc);
		}
		rc = snd_pcm_writei(playbackHandle, buffer, frames);
		if(rc == -EPIPE){
			fprintf(stderr, "overrun occured\n");
			snd_pcm_prepare(playbackHandle);
		}else if(rc < 0){
			fprintf(stderr, "error from writei: %s\n", snd_strerror(rc));
		}else if(rc != (int)frames){
			fprintf(stderr, "short write, write %d frames\n", rc);
		}
	}
	snd_pcm_drain(playbackHandle);
	snd_pcm_close(playbackHandle);
	free(buffer);
}

 /*
 * Description:
 * @param:
 * @return: NULL
 */
 void  cleanUpAudio(){
	 
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
