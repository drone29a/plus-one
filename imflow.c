/*
 * Simple Image Flow Example
 * Detects Image Flow Between Two Images
 * (images passed on command line)
 * MBS, 4/22/08
 *
 * Code snippets taken from:
 * (1) lkdemo.c (available at: http://www.csie.ntu.edu.tw/~r94082/samples/c/lkdemo.c)
 * (2) Gady Agam's Introduction to programming with OpenCV (available at: http://www.cs.iit.edu/~agam/cs512/lect-notes/opencv-intro/opencv-intro.html#SECTION00025000000000000000)
 * (3) ymazari@yahoo.fr (available at: http://groups.google.ws/group/OpenCV/msg/ec125224a1123fc2)
 * (4) cegparamesh@gmail.com (available at: http://opencvlibrary.sourceforge.net/DisplayManyImages)
*/

#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#endif

// constants
#define BOOL_COLOR_IMG 1
#define PROGRAM_NAME "imflow"
#define NUMBER_OF_KEYPRESSES 1
#define ORIG_WINDOW_NAME_1 "imflow Original Image #1"
#define ORIG_WINDOW_NAME_2 "imflow Original Image #2"
#define LK_WINDOW_NAME_1 "imflow Lucas & Kanade X Velocity"
#define LK_WINDOW_NAME_2 "imflow Lucas & Kanade Y Velocity"

// error codes
#define FIRST_IMAGE_ERROR 1
#define SECOND_IMAGE_ERROR 2

int main(int argc, char *argv[])
{
  // local variables used for reading in images
  IplImage *img1 = NULL, *img2 = NULL, *gray1 = NULL, *gray2 = NULL;	// used to store image information
  IplImage *lkvelX = NULL, *lkvelY = NULL; 				// used to store flow velocities (Lucas & Kanade)
  int height1,width1,step1,channels1;
  int height2,width2,step2,channels2;
  uchar *data1, *data2;
  int loop;

  if(argc<3){
    printf("Usage: %s [first-image-filename] [second-image-filename]\n\7", PROGRAM_NAME);
    exit(0);
  }

  // load the first image  
  img1=cvLoadImage(argv[1],BOOL_COLOR_IMG);
  if(!img1){
    printf("Could not load first image file: %s\n",argv[1]);
    exit(FIRST_IMAGE_ERROR);
  }

  // load the second image  
  img2=cvLoadImage(argv[2],BOOL_COLOR_IMG);
  if(!img2){
    printf("Could not load first image file: %s\n",argv[2]);
    exit(SECOND_IMAGE_ERROR);
  }

  // parse first image data
  height1    = img1->height;
  width1     = img1->width;
  step1      = img1->widthStep;
  channels1  = img1->nChannels;
  data1      = (uchar *)img1->imageData;
  printf("[%s]: %dx%d image with %d channels\n",argv[1],height1,width1,channels1); 

  // parse second image data
  height2    = img2->height;
  width2     = img2->width;
  step2      = img2->widthStep;
  channels2  = img2->nChannels;
  data2      = (uchar *)img2->imageData;
  printf("[%s]: %dx%d image with %d channels\n",argv[2],height2,width2,channels2); 

  // check for inequality in image dimensions, channels
  if(height1 != height2 || width1 != width2 || channels1 != channels2){
    printf("[ERROR] Images are not same dimensions, number of channels!");
  }

  // convert images to 8-bit, single channel
  gray1 = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U, BOOL_COLOR_IMG);
  gray2 = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, BOOL_COLOR_IMG);
  cvCvtColor(img1, gray1, CV_BGR2GRAY);	 // convert img1 to color space of gray1
  cvCvtColor(img2, gray2, CV_BGR2GRAY);  // convert img2 to color space of gray2

  // create images to store velocities in X and Y directions
  lkvelX = cvCreateImage(cvGetSize(img1), IPL_DEPTH_32F, BOOL_COLOR_IMG);
  lkvelY = cvCreateImage(cvGetSize(img2), IPL_DEPTH_32F, BOOL_COLOR_IMG);

  // calculate flow (Lucas & Kanade algorithm)
  cvCalcOpticalFlowLK(gray1, gray2, cvSize(3, 3), lkvelX, lkvelY); 

  // show the original images
  cvNamedWindow(ORIG_WINDOW_NAME_1, CV_WINDOW_AUTOSIZE); 
  cvShowImage(ORIG_WINDOW_NAME_1, img1);
  cvNamedWindow(ORIG_WINDOW_NAME_2, CV_WINDOW_AUTOSIZE); 
  cvShowImage(ORIG_WINDOW_NAME_2, img1);

  // show the Lucas & Kanade velocities
  cvNamedWindow(LK_WINDOW_NAME_1, CV_WINDOW_AUTOSIZE); 
  cvShowImage(LK_WINDOW_NAME_1, lkvelX);
  cvNamedWindow(LK_WINDOW_NAME_2, CV_WINDOW_AUTOSIZE); 
  cvShowImage(LK_WINDOW_NAME_2, lkvelY);

  // wait for key press (multiple to allow screenshot, etc.)
  for(loop = 0; loop < NUMBER_OF_KEYPRESSES; loop++) cvWaitKey(0);

  // destroy windows
  cvDestroyAllWindows();

  // release the images
  cvReleaseImage(&img1);
  cvReleaseImage(&img2);
  cvReleaseImage(&gray1);
  cvReleaseImage(&gray2);
  cvReleaseImage(&lkvelX);
  cvReleaseImage(&lkvelY);

  return 0;
}

#ifdef _EiC
main(1,"imflow.c");
#endif

