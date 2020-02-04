# file-to-video-converter
This program will indeed convert any given file to video data and back again. The idea of this project is to enable a way to store data on a VHS player
However, my VHS player broke before i had the chance to test the code so until i get a new VHS player, this code will remain a concept.
The code itself does work, you can convert files to video and back to a file again.

# Install
This program requires opencv4, i'm pretty sure opencv3 would work too, but i have not tried it yet.
to install opencv on ubuntu run: `sudo apt-get update` then: `sudo apt-get install libopencv-dev`

you will also need the g++ compiler, however i believe this comes default in ubuntu.

# How to run
run compile.sh for both the file converter and the video converter. This can be done by running the following commands from the home directory of the project:
`sh file-to-video/compile.sh`
`sh video-to-file/compile.sh`

once compiled, run the program by running the following commands from the home directory of the project:
To convert a file to video data:
`./file-to-video/convert-file`

To convert a video back to a file:
`./video-to-file/convert-video`

If you encouter a problem with the code, submit a issue to the git repository and i will awnser as soon as i can.

# How to help
Convert-file.cpp has some kind of tiny memory leak and i can't find out what's causing it. If you can find out what is causing it, please let me know!
