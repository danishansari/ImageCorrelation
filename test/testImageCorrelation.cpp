/**
 * Description : 
 *
 * Author      : 
 * Date        : 
 */

#include <iostream>

#include <sys/time.h>
#include <stdlib.h>

#include <highgui.h>

#include "ImageCorrelation.h"

using namespace std;
using namespace cv;

int main(int argc, char*argv[])
{
    if (argc < 3)
    {
        cout << "usage: " << argv[0] << " <image1> <image2> <pad-up> <pad-down>" << endl;
        return 0;
    }

    IplImage *img1 = cvLoadImage(argv[1], 0);

    int pad1 = 0;
    if (argc > 3)
        pad1 = atoi(argv[3]);

    int pad2 = 0;
    if (argc > 4)
        pad2 = atoi(argv[4]);

    IplImage *img = cvCreateImage(cvSize(img1->width+pad1+pad2, img1->height+pad1+pad2), 8, 1);
    cvZero(img);

    cvSetImageROI(img, cvRect(pad1, pad1, img1->width, img1->height));
    cvCopy(img1, img);
    cvResetImageROI(img);

    cvShowImage("img", img);
    cvWaitKey(0);

    IplImage *img2 = cvLoadImage(argv[2], 0);

    ImageCorrelation imgCorr;

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    cout << "Corr = " << imgCorr.getCorrCoeff(img, img2) << endl;
    gettimeofday(&t2, NULL);

    double tt = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0; 

    cout << "Time Taken = " << tt << " msec" << endl;

    return 0;
}

