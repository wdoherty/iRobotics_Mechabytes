#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

Mat openFileImage(string filePath)
{
  //read image from file path (testing)
  Mat image = imread(filePath);

  if(image.empty())
  {
    cout << "Could not open or find the image" << endl;
    cin.get(); //wait for key press to continue
  }

  return image;

}

void displayFrame(Mat frame, string label)
{
  namedWindow(label); //create window
  imshow(label, frame); //display frame to window
  waitKey(30); //wait 30 ms
}

int main()
{



  //VideoCapture cap(0);
  //if(!cap.isOpened()) return -1;

  int dimX = 80; //expected dimensions
  int dimY = 80;

  for(;;)
  {

    string filePath = "Image_Tests/rotated_rectangle.png";
    Mat frame = openFileImage(filePath); //grab image

    //Mat frame;

    //cap >> frame;

    if(frame.empty())
    {
      return -1; //error, end prog
    }

    Mat grayFrame;

    cvtColor(frame, grayFrame, CV_RGB2GRAY);

    Mat threshFrame;

    threshold(grayFrame, threshFrame, 127, 255, 1);

    vector<vector<Point>> contours;

    findContours(threshFrame, contours, 1, 2);

    int size = contours.size();

    //drawContours(frame, contours, -1, (0,255,0), 3);

    for(int i = 0; i < size; i++)
    {
      vector<Point> approx;
      approxPolyDP(contours[i], approx, 0.01*arcLength(contours[i], 1), 1);
      cout << approx << endl;
      if(approx.size() == 4)
      {
        int idx = 0;
        int tolerance = 10;
        for(int i = 1; i < 4; i++)
        {
          if(approx[i].x <= approx[idx].x + tolerance && approx[i].y <= approx[idx].y + tolerance)
          {
            idx = i;
          }
        }
        Point upperLeft = approx[idx];
        cout << upperLeft << endl;
        idx = 0;
        for(int i = 1; i < 4; i++)
        {
          if(approx[i].x + tolerance >= approx[idx].x  && approx[i].y + tolerance >= approx[idx].y)
          {
            idx = i;
          }
        }
        Point lowerRight = approx[idx];
        cout << lowerRight << endl;

        rectangle(frame, lowerRight, upperLeft, (255, 255, 255), 5, CV_FILLED);
      }
    }

    //string label = "Video Capture";
    string label = "Test Image";
    displayFrame(frame, label); //show image

    if((char)waitKey(0) == 'q') break;

  }

  return 0;
}
