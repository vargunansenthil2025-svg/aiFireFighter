#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void sendCommandToESP32(char command){
    cout<<"Sending to ESP32: "<<command<<endl;
}

int main()
{
    VideoCapture cap(0);
    if(!cap.isOpened()) return -1;

    Mat frame,hsv,mask;

    Scalar lower_fire(15,100,200);
    Scalar upper_fire(35,255,255);

    while(true){
        cap>>frame;
        if(frame.empty()) break;

        cvtColor(frame,hsv,COLOR_BGR2HSV);
        inRange(hsv,lower_fire,upper_fire,mask);

        vector<vector<Point>>contours;
        findContours(mask,contours,RETR_TREE,CHAIN_APPROX_SIMPLE);

        if(contours.size()>0){

            double maxArea=0;
            int maxIndex=0;
            for(size_t i=0;i<contours.size();i++){
                double area = contoursArea(contours[i]);
                if(area>maxArea){
                    maxArea=area;
                    maxIndex=i;
                }
            }

            Rect fireBox=boundingRect(contours[maxIndex]);
            rectangle(frame,firebox,Scalar(0,0,255),2);

            int fireCenter=fireBox.x + (fireBox.width/2);
            int frameCenter=frame.cols/2;
            int threshold=50;

            if(maxArea>15000){
                sendCommandToESP32("F");
            }
            else if(fireCenter<frameCenter-threshold){
                sendCommandToESP32("L");
            }
            else if(fireCenter>frameCenter+threshold){
                sendCommandToESP32("R");
            }
            else{
                sendCommandToESP32("C");
            }
    
        }
        else{
            sendCommandToESP32("S");
        }

        imshow("Fire Detection",frame);
        if(waitKey(30)==27) break;
    }
    return 0;
}