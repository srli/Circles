#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
 
using namespace cv;
using namespace std;
 
int main()
{
  Mat src, gray, gaussian_output;
  src = imread( "result.jpg", 1 );
  cout << "image loaded" << endl;
  cvtColor( src, gray, CV_BGR2GRAY );
 
  // Reduce the noise so we avoid false circle detection
  GaussianBlur( gray, gaussian_output, Size(3, 3), 2, 2 );

 
  vector<Vec3f> circles;


  // Apply the Hough Transform to find the circles
  HoughCircles( gaussian_output, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0 );
 


  // Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);     
      circle( gaussian_output, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center     
      circle( gaussian_output, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
      cout << "center : " << center << "\nradius : " << radius << endl;
   }
 
  // Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", src );
  imshow("grayscale", gray);
  imshow("Guassian Output", gaussian_output);
 
  waitKey(0);
  return 0;
}