/*
 * Author: MSOE Team Xi Senior Design 2017
 * Date: 12/2017
 * Description: Contains functions that will control audio
 */

#ifndef AUDIO_H
#define AUDIO_H

#ifdef AUDIO_H
#define EXTERN_PFX
#else
#define EXTERN_PFX extern
#endif
/*****************************
 * Function Prototypes       *
 *****************************/
 
 void  initAudio();
 void  cleanUpAudio();
 void  audioFromNetwork();
 void* audioToNetwork(void*);
 void* networkToAudio(void*);
 void  readFromAudioDev();
 void  writeToAudioDev();

#endif /* AUDIO_H */