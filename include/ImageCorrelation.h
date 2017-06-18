/**
 * Description : 
 *
 * Author      : 
 * Date        : 
 */

#ifndef IMAGE_CORRELATION
#define IMAGE_CORRELATION

#include <cv.h>

class ImageCorrelation
{
    public:

    double mean(IplImage *img);
    double stdDev(IplImage *img);

    public:
        double getCorrCoeff(IplImage *img1, IplImage *img2);

};

#endif // IMAGE_CORRELATION
