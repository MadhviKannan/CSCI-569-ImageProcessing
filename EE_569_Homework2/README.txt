# EE569 :Homework Assignment #2
# Date  : February 26, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu

# Compiled on WINDOWS 8 professional(64-bit)
# software used-Code Blocks 16.01
# Define compiler-GNU GCC Compiler
# C++ compiler - mingw64-g++.exe
# Linker for static libs - ar.exe

# To run the codes in Code blocks,
-->open code blocks software, go to build, and click on build and run option.

#Running the codes:
-There are 3 folders-Problem_1,Problem_2 and Problem_3.
-Problem_1 has 3 subfolders: -Warping
				-linearwarp.cpp
					-cup1.raw has been used in the program. (500x500)
					-In order to get the warped image of cup2, change line number 21 to cup2.raw (500x500)
				-Triangularwarp.cpp
					-cup1.raw has been used in the program
					-In order to get the warped image of cup2, change line 19 to cup2.raw
			       -Puzzle_Matching
				-Problem_2b.cpp
					-hillary_modify.raw and trump_final are the outputs produced each of size 512x512
			      -Image_Overlay
			        -Overlay_modify.cpp
					-overlay.raw is the output image(972x648) 
				-Overlay_tartans.cpp
					-overlay_tartans.raw is the output image(972x648)
			
                             
-Problem_2 : 		      -Dithering.cpp
			     	-man_new.raw produces the 2x2 dithered matrix
				-man_new_4.raw produces the 4x4 dithered matrix
				-man_new_8.raw produces the 8x8 dithered matrix
				-man_new_a.raw produces the 4x4 A matrix
				-man_four.raw produces the image with 4 greyscale intensities

			     -Error_Diffusion.cpp
				-Man_Floyd_Steinberg.raw is the Floyd Steinberg error diffused image
				-Man_JJN.raw is the JJN error diffused image
				-Man_Stucki.raw is the Stucki error diffused image
				-In order to obtain Stucki.raw image, uncomment the lines from 203-234
-Problem_3 has 2 subfolders: -Problem 3abc
				-Shrinking.cpp
					-square_shrink.raw is the name of the file that underwent 						shrinking
				-Thinning.cpp
					-letterE_thin.raw is the name of the file that underwent 						thinning
				-Skeletonizing.cpp
					-letterE_skeleton.raw is the name of the file that 						underwent skeletonizing	
			     -Problem 3d has two programs
				-Part_a_and_b.cpp
					-This program gives the output for number of holes and total number objects in the board.raw image
				-Part_c_and_d.cpp
					-This program gives the output for the number of squares and the number of circles with or without holes.

