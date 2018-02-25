// CannyStill.cpp
#include <opencv2/xfeatures2d.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include"opencv2/features2d.hpp"
#include<vector>
#include<iostream>
#include<conio.h>           // may have to modify this line if not using Windows
#include<fstream>
using namespace std;
using namespace cv;
int* euclid(Mat descriptor, Mat vocabulary)
{
	double* euclid_8=new double[vocabulary.rows];
	double temp=0.0;
	double sum = 0.0;
	double sqrt_sum = 0.0;
	double min_euclid = 0.0;
	int index=0;

	int* histogram= new int[vocabulary.rows];
	for (int i = 0; i < vocabulary.rows; i++)
	{
		histogram[i] = 0;
	}
	for (int i = 0; i < descriptor.rows; i++)
	{
		for (int j = 0; j < vocabulary.rows; j++)
		{
			for (int k = 0; k < descriptor.cols; k++)
			{
				sum = sum + ((descriptor.at<float>(i, k) - vocabulary.at<float>(j, k))*(descriptor.at<float>(i, k) - vocabulary.at<float>(j, k)));
			}
			sqrt_sum = sqrt(sum);
			euclid_8[j] = sqrt_sum;
			sqrt_sum = 0.0;
			sum = 0.0;

		}
		
		temp = euclid_8[0];
		index = 0;
		for (int i = 1; i < vocabulary.rows; i++)
		{
			if (euclid_8[i] < temp)
			{
				euclid_8[i] = temp;
				index = i;
			}
		}
		histogram[index] += 1;
	}
	return histogram;
}
//unsigned char castle[481][321];
///////////////////////////////////////////////////////////////////////////////////////////////////
int main() {

	Mat imgOriginal;        // input image
	Mat imgOriginal1;
	Mat imgOriginal2;
	Mat imgOriginal3;
	/*cv::Mat imgGrayscale;       // grayscale of input image
	cv::Mat imgBlurred;         // intermediate blured image*/
	Mat imgSIFT;           // Canny edge image
	int thresh = 2;

	imgOriginal = cv::imread("convertible_1.jpg");
	imgOriginal1 = cv::imread("truck.jpg");
	imgOriginal2 = cv::imread("convertible_2.jpg");
	imgOriginal3 = cv::imread("suv.jpg");
	if (imgOriginal.empty()||imgOriginal1.empty()||imgOriginal2.empty()||imgOriginal3.empty()) {                                  // if unable to open image
		std::cout << "error: image not read from file\n\n";     // show error message on command line
		_getch();                                               // may have to modify this line if not using Windows
		return(0);                                              // and exit program
	}
	
	//-------feature extraction-------//
	cv::Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();//conv1 sift
	cv::Ptr<Feature2D> f2d1 = xfeatures2d::SURF::create();//conv1 surf
	cv::Ptr<Feature2D> f2d2_sift = xfeatures2d::SIFT::create();//truck sift
	cv::Ptr<Feature2D> f2d2_surf = xfeatures2d::SURF::create();//truck surf
	cv::Ptr<Feature2D> f2d3_sift = xfeatures2d::SIFT::create();//conv2 sift
	cv::Ptr<Feature2D> f2d5_surf = xfeatures2d::SURF::create();//conv2 surf
	cv::Ptr<Feature2D> f2d4_sift = xfeatures2d::SIFT::create();//suv sift
	cv::Ptr<Feature2D> f2d4_surf = xfeatures2d::SURF::create();//suv surf
	
	//-----Detecting keypoints-----//
	std::vector<KeyPoint> conv1_sift, keypoints_2,truck1_sift,keypoints_surf,conv2_sift,suv_sift,suv_surf,conv2_surf;
	f2d->detect(imgOriginal, conv1_sift); //sift for conv1
	f2d1->detect(imgOriginal, keypoints_2);//surf for conv1
	f2d2_sift->detect(imgOriginal1, truck1_sift); //sift for truck
	f2d2_surf->detect(imgOriginal1, keypoints_surf); //surf for truck
	f2d3_sift->detect(imgOriginal2, conv2_sift); //sift for conv2
	f2d5_surf->detect(imgOriginal2, conv2_surf); //surf for conv2
	f2d4_sift->detect(imgOriginal3, suv_sift);//sift for suv
	f2d4_surf->detect(imgOriginal3, suv_surf);//surf for suv
	//-- Step 2: Calculate descriptors (feature vectors)    
	Mat descriptors_1, descriptors_2,descriptors_3,descriptors_4,descriptors_5,descriptors_6,descriptors_7,descriptors_8;
	f2d->compute(imgOriginal, conv1_sift, descriptors_1); //sift for conv1
	f2d1->compute(imgOriginal, keypoints_2, descriptors_2);//surf for conv1
	f2d2_sift->compute(imgOriginal1, truck1_sift, descriptors_3);//sift for truck
	f2d2_surf->compute(imgOriginal1, keypoints_surf, descriptors_4);//surf for truck
	f2d3_sift->compute(imgOriginal2, conv2_sift, descriptors_5);//sift for conv2
	f2d4_surf->compute(imgOriginal2, conv2_surf, descriptors_8);//surf for conv2
	f2d4_sift->compute(imgOriginal3, suv_sift, descriptors_6);//sift for suv
	f2d4_surf->compute(imgOriginal3, suv_surf, descriptors_7);//surf for suv
	//-- Step 3: Matching descriptor vectors using BFMatcher :
	BFMatcher matcher,matcher1;
	std::vector< DMatch > matches,matches1;
	matcher.match(descriptors_1, descriptors_3, matches); //feature matching of conv1&conv2 using sift
	matcher.match(descriptors_2, descriptors_4, matches1); //feature matching of conv1&conv2 using surf
	// Calculating min and max distance of sift descriptors:
	double maxSift = 0; double minSift = 100;
	for (int i = 0; i < descriptors_1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < minSift) minSift = dist;
		if (dist > maxSift) maxSift = dist;
	}

	// Calculating min and max distance of surf descriptors:
	double maxSurf = 0; double minSurf = 100;
	for (int i = 0; i < descriptors_2.rows; i++)
	{
		double dist = matches1[i].distance;
		if (dist < minSurf) minSurf = dist;
		if (dist > maxSurf) maxSurf = dist;
	}
	// Finding good matches
	std::vector< DMatch > good_matches_sift, good_matches_surf;

	for (int i = 0; i < descriptors_1.rows; i++)
	{
		if (matches[i].distance <= thresh*minSift)
		{
			good_matches_sift.push_back(matches[i]);
		}
	}

	for (int i = 0; i < descriptors_2.rows; i++)
	{
		if (matches1[i].distance <= thresh*minSurf)
		{
			good_matches_surf.push_back(matches1[i]);
		}
	}

	// Save SIFT matches
	Mat img_matches_sift;
	drawMatches(imgOriginal, conv1_sift, imgOriginal1, truck1_sift,
		good_matches_sift, img_matches_sift, Scalar::all(-1), Scalar::all(-1),
		std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imwrite("final_good_sift.jpg", img_matches_sift);

	// Save SURF Matches:

	Mat img_matches_surf;
	drawMatches(imgOriginal, keypoints_2, imgOriginal1, keypoints_surf,
		good_matches_surf, img_matches_surf, Scalar::all(-1), Scalar::all(-1),
		std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imwrite("final_good_surf.jpg", img_matches_surf);

	//Display Key points
	Mat output_image_sift, output_image_surf,output_image1_sift,output_image1_surf,output_image2_sift,output_image3_sift,output_image3_surf,output_conv2_surf;
	drawKeypoints(imgOriginal, conv1_sift, output_image_sift);
	drawKeypoints(imgOriginal, keypoints_2, output_image_surf);
	drawKeypoints(imgOriginal1, truck1_sift, output_image1_sift);
	drawKeypoints(imgOriginal1, keypoints_surf, output_image1_surf);
	drawKeypoints(imgOriginal2, conv2_sift, output_image2_sift);
	drawKeypoints(imgOriginal2, conv2_surf, output_conv2_surf);
	drawKeypoints(imgOriginal3, suv_sift, output_image3_sift);
	drawKeypoints(imgOriginal3, suv_surf, output_image3_surf);
	//sAVE iMAGE
	imwrite("convertible1_sift.jpg", output_image_sift);
	imwrite("convertible1_surf.jpg", output_image_surf);
	imwrite("truck1_sift.jpg", output_image1_sift);
	imwrite("truck1_surf.jpg", output_image1_surf);
	imwrite("convertible2_sift.jpg", output_image2_sift);
	imwrite("convertible2_surf.jpg", output_conv2_surf);
	imwrite("suv_sift.jpg", output_image3_sift);
	imwrite("suv_surf.jpg", output_image3_surf);
	//draw matches.
	Mat match_sift, match_surf;
	drawMatches(imgOriginal, conv1_sift, imgOriginal1, truck1_sift, matches, match_sift);
	drawMatches(imgOriginal, keypoints_2, imgOriginal1, keypoints_surf, matches1, match_surf);

	imwrite("convertible_sift_match.jpg", match_sift);
	imwrite("convertible_surf_match.jpg", match_surf);
	BOWKMeansTrainer BGOWORDS(8);
	Ptr<DescriptorMatcher>matching(new FlannBasedMatcher);
	//////////sift feature extractor//////////
	//Ptr<DescriptorExtractor>extracting(new SiftDescriptorExtractor);
	BGOWORDS.add(descriptors_1);
	BGOWORDS.add(descriptors_3);
	BGOWORDS.add(descriptors_6);
	Mat vocabulary = BGOWORDS.cluster();
	ofstream outfile, outfile1, outfile2, outfile3;
	outfile.open("E:/MATLAB2016/histogram1.csv");
	outfile1.open("E:/MATLAB2016/histogram2.csv");
	outfile2.open("E:/MATLAB2016/histogram3.csv");
	outfile3.open("E:/MATLAB2016/histogram4.csv");
	int* histogram_1=euclid(descriptors_1, vocabulary);
	int* histogram_2 =euclid(descriptors_3 ,vocabulary);
	int* histogram_3= euclid(descriptors_5 ,vocabulary);
	int* histogram_4= euclid(descriptors_6 ,vocabulary);
	for (int i = 0; i < 8; i++)
	{
		outfile << histogram_1[i] << endl;
		outfile1<< histogram_2[i] << endl;
		outfile2<< histogram_3[i] << endl;
		outfile3<< histogram_4[i] << endl;
	}
	//cout << vocabulary << endl;

	waitKey(0);                 // hold windows open until user presses a key

	return(0);
}

