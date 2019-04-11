# ffmpeg_tutorials
学习ffmpeg系列教程(从最基础的C语法到编写C++播放器)

使用的操作系统 Ubuntu 18.10  
编译器 gcc (Ubuntu 8.2.0-7ubuntu1) 8.2.0  
集成开发环境 CLion 2018.3.4
管理 CMake
  
邮件讨论  wangrl2016@gmail.com

## C语言基础
主要讲指针，内存管理，和文件读写操作。因为音视频很多都是以文件的形式存在，需要手动管理内存，指针又是必不可少的。
参考《Pointers On C》写的部分代码示例。

## ffmpeg安装
1. 下载源码
	`git clone https://github.com/FFmpeg/FFmpeg`	
2. ./configure
	进行配置，可以通过`./configure --help`进行查看。  
	`--enable-shared`编译动态库。
3. `make` && `sudo make install`
	头文件在/usr/local/include/目录下面，生成库文件在/usr/local/lib目录下面。 

## ffmpeg概述
主要库文件
    libavcodec encoding/decoding library
    libavfilter graph-based frame editing library
    libavformat I/O and muxing/demuxing library
    libavdevice special devices muxing/demuxing library
    libavutil common utility library
    libswresample audio resampling, format conversion and mixing
    libpostproc post processing library
    libswscale color conversion and scaling library



  



