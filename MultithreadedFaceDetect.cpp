#include <opencv2/highgui/highgui.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <vector>
#include <future>
#include <Windows.h>


using namespace cv;
using namespace std;

CascadeClassifier cascade;
vector <Rect> faces;
vector <Rect> new_faces;
bool is_running = true;
Mat gray;
Mat frame;
Mat framee;
VideoCapture camera(0);


void playVideo()
{
    while (true) {
        camera >> frame;
        resize(frame, framee, Size(640/3, 480/3));
        
        for (Rect& i : new_faces) {
            i.height *= 3;
            i.width *= 3;
            i.x *= 3;
            i.y *= 3;
            rectangle(frame, i, Scalar(0, 255, 0), 3, 8, 0);
        }
        
        imshow("output", frame);
        if (waitKey(30) == 27) {
            break;
        }
        else { continue; }
    }
    is_running = false;
}

void detect() {
    while (is_running) {
        cvtColor(framee, gray, COLOR_BGR2GRAY);
        cascade.detectMultiScale(gray, faces);
        new_faces = faces;
        faces.clear();
        waitKey(30);
    }
}


int main(int argc, char** argv)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    camera >> framee;
    cascade.load("haarcascade_frontalface_default.xml");
    future <void> t = async(playVideo);
    detect();
    return 0;
}

