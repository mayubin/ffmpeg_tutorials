# ffmpeg_tutorials
学习FFmpeg系列教程(从最基础的C语法到编写实用的C++播放器)

使用的操作系统 Ubuntu 18.10  
编译器 gcc (Ubuntu 8.2.0-7ubuntu1) 8.2.0  
集成开发环境 CLion 2018.3.4
管理 CMake
  
邮件讨论  wangrl2016@gmail.com

## C语言进阶
主要讲指针，内存管理，和文件读写操作。因为音视频很多都是以文件的形式存在，需要手动管理内存，指针又是必不可少的。
参考《Pointers On C》写的部分代码示例。
### 01 A Quick Start
`rearrange_characters.c`
    

## FFmpeg安装
1. 下载源码
	`git clone https://github.com/FFmpeg/FFmpeg`	
2. ./configure
	进行配置，可以通过`./configure --help`进行查看。  
	`--enable-shared`编译动态库。
3. `make` && `sudo make install`
　　头文件在/usr/local/include/目录下面，生成库文件在/usr/local/lib/目录下面。 

## FFmpeg概述
主要库文件  
libavcodec encoding/decoding library  
libavfilter graph-based frame editing library  
libavformat I/O and muxing/demuxing library  
libavdevice special devices muxing/demuxing library  
libavutil common utility library  
libswresample audio resampling, format conversion and mixing  
libpostproc post processing library  
libswscale color conversion and scaling library
![Transcoding in ffmpeg](res/diagram_ffmpeg.png)    
牢记上面这张图，接下来的部分都会围绕这张图展开，其中很重要的几个概念，Demuxer, Muxer, Packet, Frame, Decoder, Encoder，后续后详
细介绍。先介绍命令行的使用，然后开始编写代码，需要的资源文件在res/目录下面。

    
## FFmpeg命令行使用
### 01. FFmpeg Fundamentals
ffmpeg终端语法规则  
`ffmpeg [global options] [input file options] -i input_file [output file options] output_file`  

`ffmpeg -f lavfi -i rgbtestsrc -pix_fmt yuv420p -f sdl Example`  
输出视频并调用sdl显示。

`ffplay -f lavfi -i testsrc -vf transpose=1`
`ffmpeg -i input.mp3 -af atempo=0.8 output.mp3`  
-vf表示video filters, -af表示audio filters.

### 02. Displaying Help and Features
### 03. Bit Rate, Frame Rate and File Size
### 04. Resizing and Scaling Video
### 05. Cropping Video
### 06. Padding Video
### 07. Flipping and Rotating Video
### 08. Blur, Sharpen and Other Denoising
### 09. Overlay-Picture in Picture
### 10. Adding Text on Video
### 11. Conversion Between Formats
### 12. Time Operations
### 13. Mathematical Functions
### 14. Metadata and Subtitles
### 15. Image Processing
### 16. Digital Audio
### 17. Presets for Codecs
### 18. Interlaced Video
### 19. FFmpeg Components and Projects
### 20. Microphone and Webcam
### 21. Batch Files
### 22. Color Corrections
### 23. Advanced Techniques
### 24. Video on Web
### 25. Debugging and Tests

## FFmpeg官方示例
详细解释都在代码注释中。  
`metadata.c` 读取文件的元数据输出。  
`decode_video.c` 解码视频的前几帧，保存为灰度图片。

    
## 音视频协议

## FFmpeg源码分析

## C++语言进阶
示例参考[cppreference官网](https://en.cppreference.com/w/)
### General utilities library
### Containers library
### Algorithms library
### Thread support library

## SFML框架编写
SFML的安装`sudo apt-get install libsfml-dev`  
测试代码 `sfml/examples/SFMLTest.cpp`

### 流媒体

## 编写多媒体播放器





  



