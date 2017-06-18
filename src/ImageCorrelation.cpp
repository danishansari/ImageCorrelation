/**
 * Description : 
 *
 * Author      : 
 * Date        : 
 */

#include "ImageCorrelation.h"

#include <math.h> 
#include <highgui.h>

using namespace cv;

double ImageCorrelation::getCorrCoeff(IplImage *img1, IplImage* img2)
{
    if (!img1 || !img2)
        return -1;

    int W = img1->width;
    int H = img1->height;
    
    int w = img2->width;
    int h = img2->height;

    double maxCorrn = 0;

    for (int i = 0; i < W-w+1; i++)
    {
        for (int j = 0; j < H-h+1; j++)
        {
            IplImage *img = cvCreateImage(cvSize(w, h), img1->depth, img1->nChannels);

            cvSetImageROI(img1, cvRect(i, j, w, h));
            cvCopy(img1, img);
            cvResetImageROI(img1);

            double mean1 = mean(img);
            double mean2 = mean(img2);

            double stdDev1 = stdDev(img);
            double stdDev2 = stdDev(img2);

            int sumVal = 0;
            for (int m = 0; m < h; m++)
            {
                unsigned char *data1 = (unsigned char*)(img->imageData + m*img->widthStep);

                unsigned char *data2 = (unsigned char*)(img2->imageData + m*img2->widthStep);

                for (int n = 0; n < w; n++)
                    sumVal += ((int)*data1++ - mean1) * ((int)*data2++ - mean2);
            }
          
            double corrn = sumVal/(stdDev1*stdDev2);
            if (maxCorrn < corrn)
            {
                maxCorrn = corrn;
                cvSaveImage("./data/best.png", img);
            }
            
            cvReleaseImage(&img);
        }
    }

    return maxCorrn;
}

double ImageCorrelation::stdDev(IplImage *img)
{
    if (!img)
        return -1;

    if (img->width == 0 || img->height == 0)
        return -2;

    int w = img->width;
    int h = img->height;

    double me = mean(img);
    
    double var = 0.0;

    for (int i = 0; i < h; i++)
    {
        char *data = (char*)(img->imageData + i*(img->widthStep-w));

        for (int j = 0; j < w; j++)
            var += pow((int) (*data++) - me, 2);
    }

    return sqrt(var/(double)(w*h));
}

double ImageCorrelation::mean(IplImage *img)
{
    if (!img)
        return -1;
   
    int w = img->width;
    int h = img->height;
    int ws = img->widthStep;

    if (w == 0 || h == 0)
        return -2;

    int sum = 0;
    for (int i = 0; i < h; i++)
    {
        unsigned char *data = (unsigned char*)(img->imageData + i*ws);
        for (int j = 0; j < w; j++)
            sum += (int) *data++;
    }
    
    return sum/(double)(w*h);
}
