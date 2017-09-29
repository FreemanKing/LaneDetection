/*
2017 �̰������� ĸ���� ��
CCTV ���󿡼� ���θ� ���ϴ� ���α׷��� ���� �κ�
FindLargestArea -> Contour �� ���� ū ������ �����ϴ� Contour�� ���ϴ� ���α׷�.
nonedge_area -> ������ ���� �κ��� ���� n*n �� mask�� ����� ���α׷�
roadFilter -> Ư���� Scalar ���� �ָ� float ���� �������� ���� �ִ� Scalar ������ ���͸�
Normalization -> ������ Lab �������� �ٲٰ� ��� ���� ��Ȱȭ ���ִ� ���α׷�.
callBackFunc -> ���콺 �̺�Ʈ���� ���� Ŭ�� ��, �ش��ϴ� Color Space ǥ��.
LabBgrMask -> ���ȭ���� Lab�� Bgr ���� ǥ�������� Mask�� ����� �Լ�.
*/

//#include "cv.hpp" //���⿡ �ʿ��� �� �� ����
//#include "opencv2/opencv.hpp" //�̷��Ը� �ϸ� �� ��� �� ���


#include <opencv2/opencv.hpp>

#include <iostream>
#include <vector>
#include <time.h> 

using namespace cv;
Point2f A, B;

//! Normalization the matrix.
Mat Normalization(Mat src);

//! Find largest area using canny image
Mat FindLargestArea(Mat origin, Mat cannies);

/*
! Find Non edge area for road detection.
Mat src :  ���� ����(����ó����->2��ȭ�������� ��ȯ�� �����̾����.
float sky_rate : �ϴÿ� �ش��ϴ� ���� (ex/ 0.3 : ���� 30%�� �����Ѵ�)
int window_size : �������� ũ�� : �������� �����ϰ� �˻�.
*/
Mat nonedge_area(Mat src, float sky_rate, int window_size);

//! In Lab Color space, Filtering only L's value with sigma
Mat roadFilter(const Mat& src, double sigma, Mat mask);

//! BGR Color Space Filter with Sigma
Mat roadFilter2(const Mat& src, double sigma, Mat mask);

//! Show various color space's Scalar value on clicked pixel
void callBackFunc2(int event, int x, int y, int flags, void* userdata);

//! Find road area using similar 'LAB & BGR' in largest non edge area.
Mat FindRoad(Mat src);

int ifLRline(Point2f A, Point2f B, Point2f P);
bool intersection(Point2f o1, Point2f p1, Point2f o2, Point2f p2, Point2f &r);
void OpticalFlow_Count(int Pnum, vector<uchar> status, int & Car_num, Mat& frame, Point2f & pass, vector<Point2f> after, vector<Point2f> Center, Point2f A, Point2f B);

//! Calc distance between two Points.
double dist(Point2f A, Point2f B);

//! Detect and draw contour in Haar cascade's XML.
void detect_haarcascades(Mat src, string path="");//Input source & Input Cascade XML's path.

//! Distribute matrix to SEG_SIZE's matrixs and compare histogram between Origin and compare1,2,3
Mat DistHisto(Mat Origin, Mat compare1, Mat compare2, Mat compare3, int SEG_SIZE);//Distribute Histogram Compare

/* 
! Calculate prime and secondary bin of edge direction. 1st, 2nd bin will return, not edge direction.
Origin is the source matrix, NumBins is the degree bin(divide 180 degree with NumBins).
*/
int* calcEdgeDirection(Mat Origin, int NumBins);

//! ��ü HOG
int* calcEdgeDirection2(Mat Origin, int NumBins);

//! Distribute matrix to SEG_SIZE's matrix and compare Edge direction's portion with Origin to compare 1,2,3.
Mat DistEdgeCompare(Mat Origin, Mat compare1, Mat compare2, Mat compare3, int SEG_SIZE);

//! Using calcEdgeDirection2
Mat DistEdgeCompare2(Mat Origin, Mat compare1, Mat compare2, Mat compare3, int SEG_SIZE);

//! Split matrix , check Edge direction.
void splitEdgeDirection(Mat Origin, int BIN_SIZE, int SEG_SIZE=0);

//! Check Direction where mouse clicked.
void callBackFunc3(int event, int x, int y, int flags, void* userdata);

//Vector Normalize.
vector<float> nomalize(vector<float> a);


//Direct area
Mat direct_area(Mat src, int window_size, float sky_rate = 0);

//For testing
bool calcEdgeDirection3(Mat Origin, int NumBins);