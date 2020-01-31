#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

int height = 480;
int width = 640;

string filename = "balloutput.stl";

int main()
{
    //VideoWriter video("output.avi",CV_FOURCC('F','F','V','1'),30, Size(width,height),0);
    VideoCapture video("output.avi");
    //cout << "Output Video Spec:" << "\n";
    //cout << "Height = " << to_string(height) << "\n";
    //cout << "Width = " << to_string(width) << "\n";
    ofstream file;
    file.open(filename, ios::binary);

    bool kill = false;
    int framecount = 0;
    Mat frame;
    cout << "PROCESSING" << "\n";
    video >> frame;
    while(frame.empty()==false)
    {
        int width = frame.size().width;
        int height = frame.size().height;
        for(int y=0; y<height; y++)
        {
            for(int x=0; x<width; x+=8)
            {
                bitset<8> bits;
                for(int i=0; i<8; i++)
                {
                    int value = frame.at<uchar>(y,x+i);
                    if(value > 200)
                    {
                        value = 1;
                    }
                    else if(value < 55)
                    {
                        value = 0;
                    }
                    if(value < 150)
                    {
                        if(value > 100)
                        {
                            kill = true;
                        }
                    }
                    bits.set(i,value);
                }
                if(kill == false)
                {
                    const char byte[] = {(char)(bits.to_ulong() & 0xFF)};
                    file.write(byte,1);
                }
            }
        }
        video >> frame;
    }

    file.close();
    video.release();
    cout << "DONE!";
    return 0;
}
