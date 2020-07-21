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

string filename;

std::ifstream::pos_type filesize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg(); 
}

int main()
{
    cout << "Enter path of target file to convert to video\n";
    cin >> filename;
    VideoWriter video("output.avi",CV_FOURCC('F','F','V','1'),30, Size(width,height),0);
    cout << "Output Video Spec:" << "\n";
    cout << "Height = " << to_string(height) << "\n";
    cout << "Width = " << to_string(width) << "\n";
    ifstream file;
    file.open (filename, ios::binary);

    bool kill = false;
    int framecount = 0;
    cout << "PROCESSING" << "\n";
    while(kill==false)
    {
        if(framecount%100==0)
        {
            cout << "Reached Frame: ";
            cout << framecount << "\n";
        }
        framecount += 1;
        Mat currentimage(Size(width,height), 0);//CV_8UC4);
        int vcount = 0;
        int hcount = 0;
        while(vcount<height)
        {
            char* byte = new char[0];
            file.read(byte,1);
            if(file.eof()){
                kill=true;
                currentimage.at<uchar>(vcount,hcount) = 125;
                if(hcount==width)
                {
                    vcount+=1;
                    hcount = 0;
                }
                else
                {
                    hcount+=1;
                }
            }
            else
            {
                //file.read(byte,1);
                bitset<8> bits((int)byte[0]);
                for(int i=0; i<8; i++)
                {
                    if(bits[i] == 1)
                    {
                        currentimage.at<uchar>(vcount,hcount) = 255;
                    }
                    else
                    {
                        currentimage.at<uchar>(vcount,hcount) = 0;
                    }
                    hcount += 1;
                }
                if(hcount==width)
                {
                    hcount = 0;
                    vcount += 1;
                }
            }
            delete byte;
        }
        video.write(currentimage);
        currentimage.release();
        if(framecount%2000==0)
        {
            video.release();
            VideoWriter video("output.avi",CV_FOURCC('F','F','V','1'),30, Size(width,height),0);
        }
    }
    file.close();
    video.release();
    cout << "Wrote " << framecount << " Frames!\n";
    cout << "DONE!\n";
    return 0;
}
