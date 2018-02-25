# EE569 :Homework Assignment #3
# Date  : March 26, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu

# Compiled on WINDOWS 8 professional(64-bit)
# software used-Code Blocks 16.01
# software used- Visual Studio 15/OpenCV 3.2.0
# software used- MATLAB 2016a
# Define compiler-GNU GCC Compiler
# C++ compiler - mingw64-g++.exe
# Linker for static libs - ar.exe

# To run the codes in Code blocks,
-->open code blocks software, go to build, and click on build and run option.

#Running the codes:
-There are 3 folders-Problem_1,Problem_2 and Problem_3.
-Problem_1 has 3 files: -	1) Texture_classification.cpp
				- This code is used to get the clustered 12 texture images
				- It also gives supervised  and unsupervised classification outputs of the 6 test images
				- PCA is performed on MATLAB on the 12x25 texture images to reduce
				2) texture_segmentation_final.cpp
				- This code give the output for a 15x15 window size and number of clusters=5
				- In order to change the window size, 
					In function conv_boundary_extend(), the window size has to be changed in lines 223, 225 and 230.
				- K-means is performed on MATLAB using the csv file of dimension 206500x25. Number of clusters can be altered in the mat file. 
				- PCA is performed on the 206500x25 
				3) kmeans_cluster.m
				- This file is used to perform multiple operations
				- Run the section labeled 'PCAfor texture classification and texture segmentation' to obtain the scatter plot
				-k-means clustering for texture segmentation for running section 'For K-means clustering for texture segmentation' 
                             
-Problem_2 has 1 file : 	-Canny.cpp
					-The following linker libraries were added in Project Properties
					The following libraries were included to run the code(The same ones have to be included in the Release Mode as well)	
					-opencv_core320d.lib
					opencv_highgui320d.lib
					opencv_imgcodecs320d.lib
					opencv_imgproc320d.lib
					opencv_features2d320d.lib
			    	-For stuctural edge, the code was run using the link 'https://github.com/pdollar/edges'

-Problem_3 has 2 files: 	Problem3.cpp
				
				- This code gives the outputs for Sift, Surf, Object Matching and Bag OF words. 			
				The following libraries were included to run the code(The same ones have to be included in the Release Mode as well)	
			     -	opencv_xfeatures2d320d.lib
				opencv_imgproc320d.lib
				opencv_imgcodecs320d.lib
				opencv_highgui320d.lib
				opencv_core320d.lib
				opencv_ml320d.lib
				opencv_video320d.lib
				opencv_features2d320d.lib
				opencv_calib3d320d.lib
				opencv_objdetect320d.lib
				opencv_flann320d.lib
				opencv_ximgproc320d.lib
				opencv_videoio320d.lib
				opencv_videostab320d.lib
				opencv_superres320d.lib
				opencv_shape320d.lib
				opencv_stitching320d.lib
				-kmeans_cluster.m
				- In order to get the histograms for the BagOfWords run section 'Histogram Generation of the 4 images'