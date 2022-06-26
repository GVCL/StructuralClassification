=====================================================================================
README for LiDAR Viewer version 0.0
Copyright (c) 
=====================================================================================

Requirements 
================================
LiDAR Viewer requires fluid library, OpenGL, PCL version 1.7 and CUDA-5.5.
LiDaR Viewer can be run on Ubuntu Operating system. We have tested this software
on Hp Z400 workstation, Ubuntu 12.04 Os, with gpu card GeForce GTX 480.

Installation Guide
================================
0. Install fltk, OpenGL library and dependencies
   > sudo apt-get update 
   > sudo apt-get install build-essential
   > sudo apt-get install freeglut3 freeglut3-dev
   > sudo apt-get install fluid
   > sudo apt-get install build-essential cmake cmake-curses-gui libboost-all-dev 
     libeigen3-dev libflann-dev libvtk5-dev libvtk5-qt4-dev libglew-dev libxmu-dev 
     libsuitesparse-dev libqhull-dev libpcap-dev libxmu-dev libxi-dev -y
     
1. Install OpenNI
   > sudo apt-get install libopenni-dev libopenni-sensor-primesense-dev -y

2. Install CUDA
   > sudo apt-get install nvidia-cuda-dev nvidia-cuda-toolkit -y
   > sudo dpkg -i <package.deb>
   > sudo apt-get update
   > sudo apt-get install cuda -y
   Set the environment variables for CUDA libraries and binaries. Add the cuda's bin
   directory to your path
   
3. Install PCL-1.7. Do not install PCL from terminal or synaptic packet manager.
   Donwload PCL source code and compile it using cmake with cuda support. Build 
   the compiled code and install it.
   
   Getting the Source code
   > sudo apt-get install git -y
   > git clone https://github.com/PointCloudLibrary/pcl PCL-trunk-Source
   
   Compiling the PCL source code. Go the the PCL source directory (pcl-pcl-1.7.1/
   or PCL-trunk-Source/), and create a new subdirectory to keep the build files in: 
   > mkdir build
   > cd build
   
   Build the code in Release (fully optimized, no debug capabilities) mode now, 
   and customize the rest of the options later. CMake should be able to find every 
   dependency, thus being able to build every subsystem except for the ones marked
   as "Disabled by default".
   > cmake -DCMAKE_BUILD_TYPE=Release ..
   > ccmake . 
   Here change the build options. Try turning all functionality "ON" except those whose
   dependencies are not installed. Enable the CUDA options and give CMake the path to 
   your SDK. Go to the "CUDA_SDK_ROOT_DIR" option and enter the correct path.
   
  When you are done, press C to configure and G to generate and exit the tool. Now 
  build the code.
  > make
  
  Install the PCL
  > sudo make install
   
4. Build LiDAR Viewer: Go to LiDaR Viewer folder and run the make file. Make sure that cuda 
   compiler path in make file is same as you set in environment variables. By default, 
   cuda compiler path is /usr/local/cuda-5.5/bin/nvcc. Change the path to your cuda 
   installation folder. Also make sure the path of cuda's and pcl's includes and libraries
   files in make file are set to their installation folder. By default, It is set to /usr/local.
   Now run the make file.
   > make clean
   > make
   This creates the ./app executable in bin folder.
   

Running LiDAR Viewer
================================





