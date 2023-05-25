#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

//////////////edge detection////////////

// int main()
// {
    
//     Mat img, imgGray, imgBlur, imgCanny;
//     VideoCapture cap(0);

//     while(true)
//     {
//         cap.read(img);
//         cvtColor(img, imgGray, COLOR_BGR2GRAY);
// 	    GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
// 	    Canny(imgBlur, imgCanny, 25,75);




//         imshow("feed",imgCanny);
//         waitKey(1);
//     }
    
    
//     return 0;
// }


///////background removal ///////



// int main()
// {

    // VideoCapture cap(0);
    // Mat img;


    // while(true)
    // {

    

    // cap.read(img);

    // Mat gray,blur;
    // cvtColor(img, gray, COLOR_BGR2GRAY);
    // GaussianBlur(gray,blur,Size(7,7),5,0);

    // Mat binary;
    // threshold(blur, binary, 0, 255, THRESH_BINARY + THRESH_OTSU);
   
    // Mat opened,closed;
    // morphologyEx(binary, opened, MORPH_OPEN, Mat());  

    // morphologyEx(opened, closed, MORPH_OPEN, Mat());


   
    // Mat binary2;

    // cvtColor(closed,binary2,COLOR_GRAY2BGR);

    

    // Mat final = img - binary2;

    
    // imshow("final",final);
    // waitKey(1);

    // }
    

//     return 0;
// }



////////centroid detection////////


// int main()
// {

    // VideoCapture cap(0);
    // Mat img;


    // while(true)
    // {

    

    // cap.read(img);

    // Mat gray,blur;
    // cvtColor(img, gray, COLOR_BGR2GRAY);
    // GaussianBlur(gray,blur,Size(7,7),5,0);

   

    // Mat binary;
    // threshold(blur, binary, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
    // Mat opened,closed;
    // morphologyEx(binary, opened, MORPH_OPEN, Mat());  

    // morphologyEx(opened, closed, MORPH_OPEN, Mat());


    // Moments imageMoments = moments(closed);

    // // Extract the centroid coordinates
    // double cx = imageMoments.m10 / imageMoments.m00;
    // double cy = imageMoments.m01 / imageMoments.m00;
    // circle(img, Point(cx, cy), 15, Scalar(0, 0, 255),FILLED);
    
    // imshow("centroid marked",img);
    // waitKey(1);

    // }
    

//     return 0;
// }




int main()
{
    cout<<"type e for edge detection\nor\nb to remove background\nor\nc to find your centroid\n";

    char input;

    cin>>input;
    if(input == 'e')
    {


        Mat img, imgGray, imgBlur, imgCanny;
    VideoCapture cap(0);

    while(true)
    {
        cap.read(img);
        cvtColor(img, imgGray, COLOR_BGR2GRAY);
	    GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	    Canny(imgBlur, imgCanny, 25,75);




        imshow("feed",imgCanny);
        waitKey(1);


        
        
    }
    

    }
    else if(input == 'b')
    {
            VideoCapture cap(0);
    Mat img;


    while(true)
    {

    

    cap.read(img);

    Mat gray,blur;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray,blur,Size(7,7),5,0);

    Mat binary;
    threshold(blur, binary, 0, 255, THRESH_BINARY + THRESH_OTSU);
   
    Mat opened,closed;
    morphologyEx(binary, opened, MORPH_OPEN, Mat());  

    morphologyEx(opened, closed, MORPH_OPEN, Mat());


   
    Mat binary2;

    cvtColor(closed,binary2,COLOR_GRAY2BGR);

    

    Mat final = img - binary2;

    
    imshow("final",final);
    waitKey(1);

    }
    

    }
    else if(input == 'c')
    {
            VideoCapture cap(0);
        Mat img;


    while(true)
    {

    

    cap.read(img);

    Mat gray,blur;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray,blur,Size(7,7),5,0);

   

    Mat binary;
    threshold(blur, binary, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);
    Mat opened,closed;
    morphologyEx(binary, opened, MORPH_OPEN, Mat());  

    morphologyEx(opened, closed, MORPH_OPEN, Mat());


    Moments imageMoments = moments(closed);

    // Extract the centroid coordinates
    double cx = imageMoments.m10 / imageMoments.m00;
    double cy = imageMoments.m01 / imageMoments.m00;
    circle(img, Point(cx, cy), 15, Scalar(0, 0, 255),FILLED);
    
    imshow("centroid marked",img);
    waitKey(1);

    }
    }
    else
    {
        cout<<"\nthat is not a valid option";
        main();
    }

  
  return 0;

}