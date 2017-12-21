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
snd_pcm_t *handle;
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
	rc = snd_pcm_open(&handle, "hw:1,0,0", SND_PCM_STREAM_CAPTURE,0);
	if (rc < 0){
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		printf("successfully opened\n");
	}
	//Allocate hw parameter objects
	snd_pcm_hw_params_alloca(&params);
	//Fill with default values
	snd_pcm_hw_params_any(handle, params);
	//Interleaved mode
	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	//Signed 16-bit little-endian format
	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
	//one channels
	snd_pcm_hw_params_set_channels(handle, params, 1);
	//44100 bps samp rate
	val = 44100;
	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);
	//Period size to 32 frames
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
	//Write params to driver
	rc = snd_pcm_hw_params(handle, params);
	if(rc<0){
		fprintf(stderr,"unable to set hw parameters: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		printf("parameters sucessfully set\n");
	}
	//Set buffer
	snd_pcm_hw_params_get_period_size(params, &frames, &dir);
	size = frames * 2; //2 byte/sample, 1 channels
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
	rc = snd_pcm_open(&handle, "hw:1,0,0", SND_PCM_STREAM_PLAYBACK,0);
	if (rc < 0){
		fprintf(stderr, "unable to open pcm device: %s\n", snd_strerror(rc));
		exit(1);
	}else{
		printf("successfully opened\n");
	}
	//Allocate hw parameter objects
	snd_pcm_hw_params_alloca(&params);
	//Fill with default values
	snd_pcm_hw_params_any(handle, params);
	//Interleaved mode
	snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	//Signed 16-bit little-endian format
	snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
	//one channels
	snd_pcm_hw_params_set_channels(handle, params, 1);
	//44100 bps samp rate
	val = 44100;
	snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);
	//Period size to 32 frames
	frames = 32;
	snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
	//Write params to driver
	rc = snd_pcm_hw_params(handle, params);
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
		rc = snd_pcm_readi(handle, buffer, frames);
		if(rc == -EPIPE){
			fprintf(stderr, "overrun occured\n");
			snd_pcm_prepare(handle);
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
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
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
			fprintf(stderr, "short write: wrote %d bytes\n", rc);
		}
		rc = snd_pcm_writei(handle, buffer, frames);
		if(rc == -EPIPE){
			fprintf(stderr, "overrun occured\n");
			snd_pcm_prepare(handle);
		}else if(rc < 0){
			fprintf(stderr, "error from read: %s\n", snd_strerror(rc));
		}else if(rc != (int)frames){
			fprintf(stderr, "short read, read %d frames\n", rc);
		}
	}
	snd_pcm_drain(handle);
	snd_pcm_close(handle);
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
