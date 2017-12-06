/*
 * Author: MSOE Team Xi Senior Design 2017
 * Date: 12/2017
 * Description: Contains functions that will control video
 */

#ifndef VIDEO_H
#define VIDEO_H

#ifdef VIDEO_H
#define EXTERN_PFX
#else
#define EXTERN_PFX extern
#endif
/*****************************
 * Function Prototypes       *
 *****************************/
 
void  initVideo();
void  cleanUpVideo();
void  displayData();
void* runVideo(void*);
void  bluetoothRead();

#endif /* VIDEO_H */