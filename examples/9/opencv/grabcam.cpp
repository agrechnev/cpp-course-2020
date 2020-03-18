#include "opencv2/opencv.hpp"
using namespace cv;
int main(int, char**)
{
    using namespace std;
    VideoCapture cap(CV_CAP_ANY); // open the default camera
    
    // check if we succeeded
    if(!cap.isOpened())  {
        cerr << "Cannot open camera ! \n";
        return -1;
    }    
    
    // Print the data
    cerr << "width = " << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cerr << "height = " << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cerr << "framerate = " << cap.get(CAP_PROP_FPS) << endl;
        
    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        int key = waitKey(1);
        
        if (key >= 0 && key < 255) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

