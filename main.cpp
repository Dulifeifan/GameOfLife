#include <iostream>
#include <ctime>
#include <list>
#include <fstream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <tbb/tbb.h>
#include <unistd.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"
#include <boost/algorithm/string.hpp>

struct arg_t {
    /** The input image */
    std::string infilename = "";
    /** The output image */
    std::string outfilename = "";
    int framerate;
    int pixel;
    int round;
    std::string watermark = "";
    std::string fraimg = "";
};

using namespace cv;
using namespace std;

void parse_args(int argc, char **argv, arg_t &args) {
    using namespace std;
    long opt;
    while ((opt = getopt(argc, argv, "i:o:f:p:r:w:s:")) != -1) {
        switch (opt) {
            case 'i':
                args.infilename = string(optarg);
                break;
            case 'o':
                args.outfilename = string(optarg);
                break;
            case 'f':
                args.framerate = atoi(optarg);
                break;
            case 'p':
                args.pixel = atoi(optarg);
                break;
            case 'r':
                args.round = atoi(optarg);
                break;
            case 'w':
                args.watermark = string(optarg);
                break;
            case 's':
                args.fraimg= string(optarg);
                break;
        }
    }
}

int W;
int H;
// the following two numbers should be in the range of 0 and 8,
// and the LONELY_NUM should be strictly smaller than CROWD_NUM
const int LONELY_NUM = 1;
const int CROWD_NUM =4;
// the BIRTH_NUM should be between LONELY_NUM and CROWD_NUM
const int BIRTH_NUM = 3;
// the symbol for a living cell and a dead cell (or space)
const char CELL = '1';
const char NO_CELL = '0';
inline bool isACell(int i, int j, std::vector<std::vector<char>>& world)
// tells whether world[i][j] is occupied by a cell.
{
    return (world[i][j]==CELL)? true:false;
}
int surroundedBy(int i, int j,std::vector<std::vector<char>>& world);
void generate(std::vector<std::vector<char>>& world);

int main(int argc, char*argv[])
{
    using namespace std;
    arg_t args;
    parse_args(argc, argv, args);
    list<list<char>> col;
    ifstream fin(args.infilename);
    string s1;
    while( getline(fin,s1) )
    {
        list<char> row;
        for(char ss:s1)
        {
            row.push_back(ss);
        }
        col.push_back(row);
        W=row.size();
    }
    fin.close();
    H=col.size();
    vector<vector<char> > world(H);
    for(int i=0;i<H;i++) {
        world[i].resize(W);

    }
    int count=0;
    ifstream fin1(args.infilename);
    string s2;
    while( getline(fin1,s2) )
    {
        list<char> row;
        for(int i=0;i<W;i++)
        {
            world[count][i]=s2[i];
        }
        count++;
    }
    fin1.close();
    int i=0,j=0;
    int celllength=args.pixel;
    cv::VideoWriter out;
    out.open(
            args.outfilename,
            CV_FOURCC('M','J','P','G'),
            args.framerate, //FPS
            cv::Size(W*celllength, H*celllength ),
            false
    );

    vector<string> destination;
    boost::split( destination, args.fraimg, boost::is_any_of( "," ), boost::token_compress_on );
    for(int it=0;it<args.round;it++) {
    cv::Mat image = cv::Mat::zeros(H*celllength,W*celllength,CV_8UC1);

    parallel_for(tbb::blocked_range<size_t>(0,H,2), [&](const tbb::blocked_range<size_t> &r) {
                     for(size_t i = r.begin(); i != r.end() ; i++){
                         for(int j = 0; j <W ; j++){
                             if(world[i][j]=='1'){
                                 for(int k = i*celllength; k<(i+1)*celllength;k++){
                                     for(int l = j*celllength;l<(j+1)*celllength;l++){
                                         image.at<uchar>(k,l)=255;
                                     }
                                 }
                             }
                         }
                     }
        putText(image, args.watermark, Point(50, 250), FONT_HERSHEY_DUPLEX, 1,
                cvScalar(183, 183, 183), 1, CV_AA);
                 });
        if(!destination.empty()) {
            for (int fi = 0; fi < destination.size(); fi++) {
                if (it ==stoi(destination[fi]))
                {
                    imwrite("frame"+destination[fi]+".png", image);
                }
            }
        }
        out << image;
        generate(world);
    }
}

int surroundedBy(int i, int j, std::vector<std::vector<char> >& world)
{
    int liveCells=0;
    for(int index1 = i-1; index1 <= i+1; ++index1)
    {
        for(int index2 = j-1; index2 <= j+1; ++index2)
        {
            if( (index1 != i) || (index2 != j))
            {
                if( (index1>=0) && (index1 < H)
                    && (index2 >=0) && (index2 < W) )
                {
                    if(isACell(index1,index2,world))
                    {
                        ++liveCells;
                    }
                }
            }
        }
    }
    return liveCells;
}

void generate(std::vector<std::vector<char> >& world)
{
    //char temp[H][W];
    std::vector<std::vector<char> > temp(H);

    for(int i=0;i<H;i++) {
        temp[i].resize(W);
    }

    // first copy the content of world[][] into a temporary 2d array
    for(int i=0; i<H; ++i)
    {
        for(int j=0; j<W; ++j)
        {
            temp[i][j]=world[i][j];
        }
    }

    for(int i=0; i<H; ++i)
    {
        for(int j=0; j<W; ++j)
        {
            if(isACell(i,j,temp))
            {
                if( (surroundedBy(i,j,temp)<=LONELY_NUM) ||
                    (surroundedBy(i,j,temp)>=CROWD_NUM) )
                    world[i][j]=NO_CELL;
            }
            else
            if(surroundedBy(i,j,temp) == BIRTH_NUM)
                world[i][j]=CELL;
        }
    }
}