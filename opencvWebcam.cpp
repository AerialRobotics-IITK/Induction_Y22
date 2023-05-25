#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
using namespace std;
using namespace cv;
// int T1,T2;
void getOpening(Mat dst,int kSize){
Mat kernel=getStructuringElement(MORPH_RECT,Size(kSize, kSize));
morphologyEx(dst,dst,MORPH_OPEN,kernel);
}
void getClosing(Mat dst,int kSize){
Mat kernel=getStructuringElement(MORPH_RECT,Size(kSize, kSize));
morphologyEx(dst,dst,MORPH_CLOSE,kernel);
}
int maxEl(vector<int>length){
    int g,i;
    for( i=0;i<length.size();i++){
        g=0;
        for(int j=0;j<length.size();j++){
        if(length[i]<length[j]){
            g=1;
        }
        }
        if(g==0)break;
    }
    return i;
}
void getContours(Mat final,Mat finalC){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(finalC,contours,hierarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
    vector<int>length(contours.size());
    for(int i=0;i<contours.size();i++){
         length[i]=arcLength(contours[i],false);
    }
    int i=maxEl(length);
             drawContours(final,contours,i,Scalar(0,255,0),2);
             Moments mu=moments(contours[i],false);
             Point2f mc=Point2f(mu.m10/mu.m00,mu.m01/mu.m00);
             circle(final,mc,4,Scalar(0,0,255),FILLED);
        
    }

int main(){
    VideoCapture cap(0);
    Mat img;
    string path;
    cout<<"Please click your Background photo and save it in your codes folder."<<endl<<"Then Enter the file name below.\n";
    cin>>path;
    Mat bgimg=imread(path);
    Mat bgimgGray,bgimgGB;
cvtColor(bgimg,bgimgGray,COLOR_BGR2GRAY);
GaussianBlur(bgimgGray,bgimgGB,Size(5,5),20,20);
    while(1){
cap.read(img);
Mat imgGray,imgGB,imgC;
cvtColor(img,imgGray,COLOR_BGR2GRAY);
GaussianBlur(imgGray,imgGB,Size(5,5),20,20);
Canny(imgGB,imgC,20,80);
Mat change,dst;
absdiff(bgimgGB,imgGB,change);
imshow("c",change);
imshow("canny",imgC);
// namedWindow("Trackbar1",(500,500));
//  createTrackbar("Thres1","Trackbar1",&T1,255);
//  while(1){
threshold(change,dst,10,255,THRESH_BINARY);
// imshow("thres",dst);
// char c1=waitKey(1);
// if(c1==27){
//     break;
// }
//  }
getOpening(dst,5);
getClosing(dst,5);
 imshow("d",dst);
 Mat final;
 bitwise_and(img,img,final,dst);
 imshow("f",final);
 Mat finalGray,finalGB,finalC,finalT;
 cvtColor(final,finalGray,COLOR_BGR2GRAY);
 GaussianBlur(finalGray,finalGB,Size(5,5),20,20);
Canny(dst,finalC,20,80);
imshow("cannyF",finalC);
getContours(final,finalC);
imshow("FwithCentroid",final);
 char c=waitKey(1);
 if(c==27)break;
}
    }