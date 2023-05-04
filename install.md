Our application uses C++ 11 standard specific features and behaivor and CMake version 3.8 minimum. 

This game also uses the following libraries from [CaptainYS](https://github.com/captainys)
    FsSimpleWindow
    YsSimpleSound
    YsPng
    YsGLFontData
    GenericCharArray


# **Cloning the repository**
Below are common instructions for cloning our repository
  Clone the project repository
```
	  git clone https://github.com/cgeshan/Typing-Team.git
```
**Building the application**               
============
Below are instructions for building our application, build directory MUST be outside of the source directory. 
   Navigate to the cloned folder
```
	cd Typing-team
```
   Initialize submodules
```
	cd Typing-team
	git submodule update --init	
```
  Create build directory
```
	mkdir ../build
```
  Navigate to build folder
```
	cd ../build
```
  Generate project make files 
```
	cmake ../Typing-Team
```
  Build application (this will take some time)
```
	cmake --build . --config Release --target main
```
### Start the application OS specific
#### Linux
-------------------
```
	./src/main
```
#### MAC OS X
-------------------

```	
	./src/main.app/Contents/MacOS/main
```

#### Windows
-------------------
```
	Release\main.exe
```
