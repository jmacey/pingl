# Basic Install and configuration #

pingl is a port of the NCCA graphics library for the raspberry pi, it uses OpenGL ES and has a number of classes to allow 3D graphics programming using C++. For more detail on the different versions of NGL see the webpage here http://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/


## Downloading ##

pingl is designed to live in the root of the users home directory (this simplifies the installation and running of other demo programs). To download change into the root of your home directory by typing cd then execute the following code
```
git clone https://code.google.com/p/pingl/
```

This will download the latest source version of pingl.

## pre-requisite packages ##
Several packages are required to build pingl, these can all be installed using the apt-get package manager on the pi. The packages required are boost++, ImageMagick and SDL. The following line will install them on the pi (this is using the wheezy image)
```
sudo apt-get install libmagick++-dev boost-dev libsdl1.2-dev
```
Once these are installed you can change into the pingl directory and do the following
```
cd ~/pingl
make
```
The build can take a long time, but when complete the file libpiNGL should be in the lib directory.
Finally we need to add the directory to the LD\_LIBRARY\_PATH as follows
```
vi ~/.bashrc
# in the file add
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/pingl/lib
# then type source ~/.bashrc
```
This should now be ready to test the demo programs, it may be necessary to add the user to both the video and input groups this may be done with the following commands
```
usermod -G video,input [user name]
```