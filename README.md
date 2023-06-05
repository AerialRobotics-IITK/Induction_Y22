# Resources for Induction

Here is a set of resources that will help you out to learn and explore the various topics going to be taught in your induction. This is not exhaustive, and will keep on updating as we continue with the induction.

## 0) Unix and Git

### a) UNIX FileSystem

As everything is a file, so to manage all the files (whether large or small) many systems are used... One of such system is **Unix FileSystem**

#### Files in Unix Subsystem

1. Files in unix file system are arranged heirarchy with on the top being **Root** file denoted by **/**.
2. Under Root directory there are multiple directories and one of them being **~** --> **Home** Directory .
3. There are others as well, some of them are listed below:
   - **/bin** --> contains binary files.
   - **/dev** --> contains info about devices.
   - **/root** ---> The home directory of super user "root" i.e. the system administrator.
   - etc.

---

#### Unix Commands

1. pwd --> show current location
2. man **name** -- show manual page of **name**
3. ls --> show content of current file location: _attributes_ [-l]--> list view with file details,[-a]--> hidden files, [-h]--> show memory of files in more readable format.
4. cat **path** --> show content of file at **path**
5. cd **path** --> change directory/location.... here **"cd../"** can be used to go one heirarchy up (**/** ends command)
6. mkdir --> make/create new directory.
7. touch **path** --> create a new empty file.
8. echo **text** --> prints **text** as it is.... "**>**" is used to execute output of echo into some other file. "**>>**" will append instead of write from start.
9. rm --> delete file
10. chmod --> change file mode bits (actually change permissions)
11. sudo --> it is super user command i.e. to run as administrator... eg: sudo apt-get install python: to install python.
12. etc.

---

#### Permissions in linux file system

**chmod**

<pre>
for example: a directory
drwxr-xr-- "filename/directoryName is xyz"
Here d => directory
r=> readable           weight: 4
w=> writable                   2
x=> executable                 1
</pre>

if file is readable + writable + executable 
now here, xyz is **rwx** by owner, **r & x** by group and only **r** by others.

---

### b) Git

It is version control manager/tracker. It will track how your file changes and stores/keeps the history of your file(s). What they were before and are now.

#### Commands

```git
git init --> creates/initialises a git repository

git status --> shows the status or any update you have made to your files in your current directory and its sub directories.

git branch [-m] xyz--> creates a new branch, actually a copy of current branch in which you can do any modification which will not be showed up in your master/main branch. 

git checkout (main) --> to change branch (here to main)

git add *  --> update all the changes you have made to your **files** in the current directory.

git add -A --> update the changes in **directories** as well.

git commit -m xyz --> A commit, or "revision", is an individual change to a file (or set of files). It's like when you save a file, except with Git, every time you save it creates a unique ID (a.k.a. the "SHA" or "hash") that allows you to keep record of what changes were made when and by who.

git log --> to check the log of your changes and commits.

rm -rf git --> to get out of git.
```

#### Steps to update github repository

1. Fork the repo, create personal access command line token and copy the URL.
   OR
   **you can directly access any repository directly from VSCode.**

2. Follow the following commands:
   - git clone "URL"
   - Start editing in any text editor
   - after making changes, git add * and git add -A
   - then check git status
   - then do git commit -m "your_message".
   - push your code using git push -u origin **"branch_name"**.

3. Make a pull request on github.

### c) Markdown Files

Markdown is a markup language, that is just used to make your documentation look neat and uniform, like Latex.

- All you need is the syntax, so here are the [docs](https://www.markdownguide.org/basic-syntax/).

- Also go through a few repos on [Github](www.github.com) to know how to make the READMEs more systematic and follow general convention.

## 1) Standard Template Library (STL)

STL is a library in C++ which allows you to make use of various data structures and algorithms (DSA), without having to implement them yourself.

There are a lot of DSAs that are part of this.

- Get started: [here](https://www.youtube.com/watch?v=ltBdTiRgSaw)

> This will introduce you to the basics of how to get started with STL

- [Geeks for Geeks](https://www.geeksforgeeks.org/cpp-stl-tutorial/)

> Once you are done, you can get started with these. This is a compilation of most of the DSAs in STL.

## 2) Object Oriented Programming (OOPs)

- A good [introduction](https://www.w3schools.com/cpp/cpp_oop.asp)

## 3) OpenCV

### Installation

- Enter the following command in the terminal

```bash
sudo apt install libopencv-dev python3-opencv
```

- You will also need CMake,a build utility. It helps you link different cpp and hpp files, without much hassle, especially as your project grows larger.

```bash
sudo apt-get install build-essential libssl-dev
cd /tmp
wget https://github.com/Kitware/CMake/releases/download/v3.20.0/cmake-3.20.0.tar.gz
tar -zxvf cmake-3.20.0.tar.gz
cd cmake-3.20.0
./bootstrap
make
sudo make install
```

For creating any starter folder,

- Create a folder, and go inside it. This will be your root folder.
- Create your cpp file, let's say, `file_name.cpp`
- Create a file called CMakeLists.txt
- Create a folder called bin

Put this basic Video Capture from WebCam code in `file_name.cpp`

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    cv::Mat myImage;
    cv::namedWindow("Video Player");
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "No video stream detected" << std::endl;
        system("pause");
        return -1;
    }
    while (true) {
        cap >> myImage;
        if (myImage.empty())
            break;
        imshow("Video Player", myImage);
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }
    cap.release();
    return 0;
}
```

Put this file content inside the `CMakeLists.txt`

```c
cmake_minimum_required(VERSION 2.8)
PROJECT(OPENCV)
find_package(OpenCV REQUIRED)
include_directories( ${OPENCV_INCLUDE_DIRS} )
add_executable(bin/file_name file_name.cpp)
target_link_libraries(bin/file_name ${OpenCV_LIBS})
```

Replace `file_name` with your cpp file name.

Now you should have a directory/folder with these files:

```bash
.
├── bin
├── CMakeLists.txt
└── your_file_name.cpp
```

Now to build the cpp files you have,
Type the following commands:

```bash
cmake . # to create CMake build files
make # to build your cpp files/project, according to the build files made above
```

You'll now have the binary of your cpp file within ./bin
To run it:

```./bin/your_file_name```

You should see a window pop up with your camera feed.

### Resources

- As always, the Documentation is always good, but way too general: [here](https://docs.opencv.org/4.2.0/d1/dfb/intro.html)

- Introduction: [C++](https://github.com/murtazahassan/Learn-OpenCV-cpp-in-4-Hours) and [Python](https://www.youtube.com/watch?v=WQeoO7MI0Bs)

> Pretty long. Recommended to look a the code given and see the end products. You can skip over the part where the code is being written. Don't worry, it won't take more than 2 hours to familiarize yourself

- You can also go through these lec if you like: [Photogrammetry](https://www.ipb.uni-bonn.de/photo12-2021/)
- For CNNs and other aspects of DL, you can try these: [DL/CNNs](https://www.coursera.org/specializations/deep-learning)
- Knowing the concepts always helps: [Theory](https://web.stanford.edu/class/ee368/handouts.html)

- YOLO (You Only Look Once) is a real-time object detection system that uses a deep neural network and is implemented using the Darknet neural network framework. The Darknet framework is an open-source neural network framework written in C and CUDA, and it is optimized for both CPU and GPU computing.[Official Github Repo](https://github.com/AlexeyAB/darknet)

## 4) Python

Here are some Python codes for [robotics algorithms](https://github.com/AtsushiSakai/PythonRobotics)

> This is optional.

- Once you are familiar with this, moving on to solving some [examples](https://iitmcvg.github.io/problem_statements/Problem_statements/)

- Read more about multiprocessing and multithreading [here](https://towardsdatascience.com/multithreading-and-multiprocessing-in-10-minutes-20d9b3c6a867)

## Test
A test commit
