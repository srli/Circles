#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include <math.h>

using namespace cv;
using namespace std;


void text_onscreen(Mat src){
  string text = "Reference radius is 50px";
  int fontFace = cv::FONT_HERSHEY_PLAIN;
  double fontScale = 1.5;
  int thickness = 1;
  Point textOrg(20, 20);
  putText(src, text, textOrg, fontFace, fontScale, Scalar(0,0,0,255), thickness,8);
}

int main(int argc,char *argv[])
{
    int c, key;
    Mat src, gray, gaussian_result;
    Mat imgHSV, imgThreshed, masked;
    
    IplImage* color_img;
    CvCapture* cv_cap = cvCaptureFromCAM(0);
    cvNamedWindow("Circle Detection",0); // create window
    cvNamedWindow("Gaussian Blur",0);
    cvNamedWindow("HSV Image", 0);
    //cvNamedWindow("Masked", 0);
    printf("Please press a to display information.\n");

    for(;;) {
      color_img = cvQueryFrame(cv_cap); // get frame
      if(color_img != 0){
        src = color_img;

        //Changing color image to HSV for color filtering
        //cvtColor(src, gray, CV_BGR2GRAY);
        cvtColor(src, imgHSV, CV_BGR2HSV);
        inRange(imgHSV, Scalar(5, 150, 150), Scalar(15, 255, 255), imgThreshed);

        // Reduce the noise so we avoid false circle detection
        GaussianBlur( imgThreshed, gaussian_result, Size(13, 13), 2, 2 );
        //vector<Vec3f> circles;
        //std::vector<int> circles_radius;

        
        CvSize dim = cvGetSize(color_img);
        Point center_screen(dim.width/2,dim.height/2);
        
        //Draw center point of screen
        circle(src, center_screen, 3, Scalar(255,0,0), -1, 8, 0);
        circle(src, center_screen, 50, Scalar(255,0,0), 1, 8, 0);

        cornerHarris(gaussian_result, )



        //Masks the thresholded image to the color, aloows only the untreshed parts through
        //src.copyTo(masked, imgThreshed);
        // Apply the Hough Transform to find the circles
/*        HoughCircles(gaussian_result, circles, CV_HOUGH_GRADIENT, 1, 30, 200, 30, 20, 0 );
        if (circles.size() != 0){


            // Draw the circles detected
            //for( size_t i = 0; i < circles.size(); i++ )
            for( size_t i = 0; i < circles.size(); i++ ){
                Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
                int radius = cvRound(circles[i][2]);

                //Drawing each circle
                circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );//center
                circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );//circumference

                //Drawing lines relative to center
                Point midpoint(center.x, center_screen.y);
                line(src, center_screen, center, Scalar(255,0,0), 1, 8, 0);//center to center
                line(src, center_screen, midpoint, Scalar(255,0,0), 1, 8, 0);//y
                line(src, midpoint, center, Scalar(255,0,0), 1, 8, 0);//x
                
                //cout << "center : " << center << "\nradius : " << radius << endl;
                
                double x_distance = center.x - center_screen.x;
                double y_distance = center.y - center_screen.y;

                double distance = 126.964*exp(-0.0216358 * radius);
                double pan_angle = tan(x_distance/distance);
                double tilt_angle = tan(y_distance/distance);

                key = cvWaitKey(50);

                if(key == 97){
                //angle = fmod(angle, pi);
                printf("Robot Coordinates\n");
                cout << "radius:  " << radius << endl;
                cout << "pan:  " << pan_angle << endl;
                cout << "tilt:  " << tilt_angle << endl;
                cout << "distance:  " << distance << endl;
                cout << "-------------" << endl;
                }
        }
    }
*/
/*        else{
            break;
        }
           */ 

        text_onscreen(src); 

        imshow("Circle Detection", src);
        imshow("Gaussian Blur", gaussian_result);
        imshow("HSV Image", imgHSV);
        //imshow("Masked", masked);
        //masked = Mat::zeros(masked.rows, masked.cols, CV_64F);

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