#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <typeinfo>

using namespace cv;
using namespace std;

int main(int argc,char *argv[])
{
    int c;
    Mat src, gray;
    IplImage* color_img;
    CvCapture* cv_cap = cvCaptureFromCAM(1);
    cvNamedWindow("Video",0); // create window
    for(;;) {
        color_img = cvQueryFrame(cv_cap); // get frame
        if(color_img != 0)
          src = color_img;
          //cout << "image loaded" << endl;
          cvtColor( src, gray, CV_BGR2GRAY );
         
          // Reduce the noise so we avoid false circle detection
          GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
          //cout << "grayscale acheived" << endl;
         
          vector<Vec3f> circles;

          //cout << "circles vector" << endl;
         
          // Apply the Hough Transform to find the circles
          HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0 );
         
          //cout << "transform applied" << endl;

          // Draw the circles detected
          for( size_t i = 0; i < circles.size(); i++ )
          {
              Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
              int radius = cvRound(circles[i][2]);     
              circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center     
              circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
              cout << "center : " << center << "\nradius : " << radius << endl;
           }
            
            //cvShowImage("Video", color_img); // show frame
            imshow("Video", gray);
        c = cvWaitKey(10); // wait 10 ms or for key stroke
        if(c == 27)
            break; // if ESC, break and quit
    }
    /* clean up */
    cvReleaseCapture( &cv_cap );
    cvDestroyWindow("Video");

    return 0;
}


/*int locate_circle()
{
  Mat src, gray;
  src = imread( "result.jpg", 1 );
  cout << "image loaded" << endl;
  cvtColor( src, gray, CV_BGR2GRAY );
 
  // Reduce the noise so we avoid false circle detection
  GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
  cout << "grayscale acheived" << endl;
 
  vector<Vec3f> circles;

  cout << "circles vector" << endl;
 
  // Apply the Hough Transform to find the circles
  HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0 );
 
  cout << "transform applied" << endl;

  // Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);     
      circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center     
      circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
      cout << "center : " << center << "\nradius : " << radius << endl;
   }
 
  // Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", src );
 
  waitKey(0);
  return 0;
}*/