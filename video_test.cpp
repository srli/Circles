#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <typeinfo>

using namespace cv;
using namespace std;


void text_onscreen(Mat src){
  string text = "distance";
  int fontFace = cv::FONT_HERSHEY_PLAIN;
  double fontScale = 1.5;
  int thickness = 1;
  cv::Point textOrg(20, 20);
  putText(src, text, textOrg, fontFace, fontScale, Scalar(0,0,0,255), thickness,8);
}

int color_filter(Mat input_image){
  //(0,255,0)
 /*We want to filter out all the color in the image save for green
 We do this by changing all the other RGB channels to 0 if the green value
 is under a certain threshold. We can run the HoughCircle code on the
 filtered image which should make it easier.*/


}



int main(int argc,char *argv[])
{
    int c;
    Mat src, gray, gaussian_result;
    IplImage* color_img;
    //Mat imgHSV, imgThreshed;
    CvCapture* cv_cap = cvCaptureFromCAM(0);
    cvNamedWindow("Video",0); // create window
    //cvNamedWindow("Gaussian Blur",0);
    cvNamedWindow("Threshold", 0);

    for(;;) {
        color_img = cvQueryFrame(cv_cap); // get frame
        if(color_img != 0){
          //Mat converted_img(color_img);
          //cvtColor(converted_img, imgHSV, CV_BGR2HSV);
          //imgThreshed = cvCreateImage(cvGetSize(color_img), 8, 1);
          //cvinRange(imgHSV, Scalar(20, 100, 100), Scalar(30, 255, 255), imgThreshed);

          src = color_img;
          //cout << "image loaded" << endl;
          cvtColor( src, gray, CV_BGR2GRAY );
          //src_g = gray;
          // Reduce the noise so we avoid false circle detection
          GaussianBlur( gray, gaussian_result, Size(9, 9), 2, 2 );
          //cout << "grayscale acheived" << endl;
         
          vector<Vec3f> circles;

          CvSize dim = cvGetSize(color_img);
          //cout << "height" << dim.height << "width" << dim.width << endl;
          //cout << "circles vector" << endl;
          
          // Apply the Hough Transform to find the circles
          HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 50, 0, 0 );
         
          //cout << "transform applied" << endl;
          circle(src, Point(dim.width/2,dim.height/2), 3, Scalar(255,0,0), -1, 8, 0); //draws center point of screen
          // Draw the circles detected
          for( size_t i = 0; i < circles.size(); i++ )
          {
              Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
              int radius = cvRound(circles[i][2]);
              circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );// circle center     
              circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );// circle outline
              cout << "center : " << center << "\nradius : " << radius << endl;
              int x_distance = dim.width/2 - center.x;
              int y_distance = dim.height/2 - center.y;
              cout << "distance from center " << x_distance << ":" << y_distance << endl;
           
           }

           text_onscreen(src); 

            //cvShowImage("Video", gray); // show frame
          imshow("Video", src);
          imshow("Gaussian Blur", gaussian_result);
          //imshow("Threshold", imgThreshed);
        c = cvWaitKey(10); // wait 10 ms or for key stroke
        if(c == 27){
            break; // if ESC, break and quit
    }
  }
}
    /* clean up */
    cvReleaseCapture( &cv_cap );
    cvDestroyWindow("Video");

    return 0;
}