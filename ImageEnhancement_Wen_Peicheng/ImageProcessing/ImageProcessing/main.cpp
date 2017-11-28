//
//  main.cpp
//  ImageProcessing
//
//  Created by Peicheng Wen on 2017/4/18.
//  Copyright © 2017年 Troy University. All rights reserved.
//

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    Mat src, dst;
    
    char const *source_window = "Source Image";
    char const *equalized_window = "Equalized Image";
    char const *custom_window = "Custom Image";
   
    src = imread( "/Users/WEN/Desktop/ImageProcessing/ImageProcessing/SourceImage4.jpg");
    
    if( !src.data )
    { cout<<"No Image Available"<<endl;
        return -1;}
    
    cvtColor( src, src, CV_BGR2GRAY );
    
    equalizeHist( src, dst );
    
    IplImage *img = cvLoadImage("/Users/WEN/Desktop/ImageProcessing/ImageProcessing/SourceImage4.jpg", 0);
    CvScalar pixel;
    CvScalar newPixel;
    CvMat* mat=cvCreateMat(img->height, img->width, CV_64FC1);
    for (int i = 0; i < img->height; ++i)
    {
        for (int j = 0; j < img->width; ++j)
        {
            
            pixel = cvGet2D(img, i, j);
            //printf("B=%f\n", pixel.val[0]);
            
            
            cvmSet(mat, i, j, pixel.val[0]);
            
           
        }
    }
    for (int i = 0; i < img->height; ++i)
    {
        for (int j = 0; j < img->width; ++j)
        {
            double c = cvmGet(mat, i, j);
            double m;
            if (c < 5)
            {
                m = c;
            }else if (c < 10)
            {
                m = c * 1.5;
            }else if (c < 20)
            {
                m = c * 1.8;
            }else if (c < 50)
            {
                m = c * 2;
            }
            else
            {
                m = c * 2.2;
            }
            if(m > 255)
            {
                    m = 255;
            }
            newPixel.val[0]= m;
            cvSet2D(img, i, j, newPixel);
        }
    }
    cvNamedWindow(custom_window, CV_WINDOW_AUTOSIZE);
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    namedWindow( equalized_window, CV_WINDOW_AUTOSIZE );
    
    cvShowImage(custom_window, img);
    imshow( source_window, src );
    imshow( equalized_window, dst );
    
    waitKey(0);
    
    return 0;
}
