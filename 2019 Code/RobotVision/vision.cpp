#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>
#include <algorithm>

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

  int dimX = 100; //expected dimensions
  int dimY = 100;
  int maxX = 800; //image dimensions
  int maxY = 600;
  int centerX = 400; //center of image
  int centerY = 300;
  int error = 10; //error for dist movement
  int sizeTolerance = 30; //error of dim of box

  for(;;)
  {
//left-side.jpg
    string filePath = "Image_Tests/pinkgreen-with-noise.jpg";
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
      //cout << approx << endl;
      if(approx.size() == 4)
      {
        Point pts[1][4];
        for(int j = 0; j < 4; j++)
        {
          pts[0][j] = approx[j];
        }

        int x1 = min(approx[0].x, min(approx[1].x, min(approx[2].x, approx[3].x)));
        int x2 = max(approx[0].x, max(approx[1].x, max(approx[2].x, approx[3].x)));
        int y1 = min(approx[0].y, min(approx[1].y, min(approx[2].y, approx[3].y)));
        int y2 = max(approx[0].y, max(approx[1].y, max(approx[2].y, approx[3].y)));

        int x = x2 - x1;
        int y = y2 - y1;

        if(x <= dimX + sizeTolerance && x >= dimX - sizeTolerance
           && y <= dimY + sizeTolerance && y >= dimY - sizeTolerance)
        {

          Point center((x2 + x1)/2, (y2 + y1)/2);

          Point topLeft(x1, y1);

          Point botRight(x2, y2);

          cout << "Top left is at: " <<  topLeft << endl;

          cout << "Bottom right is at: " <<  botRight << endl;

          cout << "Center is at: " << center << endl;

          Mat1b mask(frame.rows, frame.cols, uchar(0));
          const Point* points[1] = {pts[0]};
          int npoints = 4;
          fillPoly(mask, points, &npoints, 1, Scalar(255));

          Scalar average = mean(frame, mask);

          int R = average[0];
          int G = average[1];
          int B = average[2];

          cout << "Color data: " << endl;
          cout << "R: " << R << " (Rounded)" << endl;
          cout << "G: " << G << " (Rounded)" << endl;
          cout << "B: " << B << " (Rounded)" << endl;

          int expR = 34;
          int expG = 248;
          int expB = 3;
          int colorError = 10;

          if(R > expR + colorError || R < expR - colorError ||
             G > expG + colorError || G < expG - colorError ||
             B > expB + colorError || B < expB - colorError) continue;

          if(center.x > centerX + error)
          {
            cout << "Move left " << center.x - centerX << " pixels." << endl;
          }
          else if(center.x + error < centerX)
          {
            cout << "Move right " << centerX - center.x << " pixels." << endl;
          }

          if(center.y > centerY + error)
          {
            cout << "Move up " << center.y - centerY << " pixels." << endl;
          }
          else if(center.y + error < centerY)
          {
            cout << "Move down " << centerY - center.y << " pixels." << endl;
          }

          rectangle(frame, topLeft, botRight, (255, 255, 255), 5, CV_FILLED);
        }
      }
    }

    //string label = "Video Capture";
    string label = "Test Image";
    displayFrame(frame, label); //show image

    if((char)waitKey(0) == 'q') break;

  }

  return 0;
}
