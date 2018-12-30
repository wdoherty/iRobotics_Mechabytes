#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
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

  //string filePath = "Image_Tests/left-side.jpg";
  //Mat frame = openFileImage(filePath); //grab image

  VideoCapture cap(0);
  if(!cap.isOpened()) return -1;

  for(;;)
  {

    Mat frame;

    cap >> frame;

    if(frame.empty())
    {
      return -1; //error, end prog
    }

    string label = "Video Capture";
    //string label = "Test Image";
    displayFrame(frame, label); //show image

  }

  return 0;
}
