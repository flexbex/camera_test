#include <ctime>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam/raspicam_cv.h>
#include <raspicam/raspicam.h>
using namespace std;

int main ( int argc,char **argv ) {
	int height=480;
	int width=640;
    time_t timer_begin,timer_end;
    raspicam::RaspiCam cam;
    uchar *image=(uchar*)malloc(width*height*10);
    int nCount=200;

    //set camera params
    cam.setFormat(raspicam::RASPICAM_FORMAT_YUV420);
    cam.setWidth(width);
    cam.setHeight(height);
	cam.setFrameRate(180);

	//Open camera
    cout<<"Opening Camera..."<<endl;
    if (!cam.open()) {cerr<<"Error opening the camera"<<endl;return -1;}
    //Start capture
    cout<<"Capturing "<<nCount<<" frames ...."<<endl;

    for ( int i=0; i<nCount; i++ ) {
        cam.grab() ;
        cam.retrieve ( image,raspicam::RASPICAM_FORMAT_IGNORE);
		if(i==50)    time ( &timer_begin );
        if ( i%5==0 )  cout<<"\r captured "<<i+1<<" images and FPS:"<<cam.getFrameRate()<<std::flush;
    }
	nCount-=50;
    cout<<"Stop camera..."<<endl;
    cam.release();
    //show time statistics
    time ( &timer_end ); /* get current time; same as: timer = time(NULL)  */
    double secondsElapsed = difftime ( timer_end,timer_begin );
    cout<< secondsElapsed<<" seconds for "<< nCount<<"  frames : FPS = "<<  ( float ) ( ( float ) ( nCount ) /secondsElapsed ) <<endl;
    //save image
    cv::Mat byteImage = cv::Mat(height, width, CV_8UC1, image);
    cv::imwrite("raspicam_cv_image.jpg",byteImage);
    cout<<"Image saved at raspicam_cv_image.jpg"<<endl;
}

