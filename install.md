Our application uses C++ 11 standard specific features and behaivor and CMake version 3.8 minimum. 

This game also uses the following libraries from [CaptainYS](https://github.com/captainys)
    FsSimpleWindow
    YsSimpleSound
    YsPng
    YsGLFontData
    GenericCharArray


# **Cloning the repository**
Below are common instructions for cloning our repository
  Clone the Unoptimized repository
```console

	  $ git clone https://github.com/cgeshan/Typing-Team.git

```
**Building the application**               
============
Below are instructions for building our application, build directory MUST be outside of the source directory. 
  Create build directory
```console

	  $ mkdir build

```
  Navigate to build folder
```console

	  $ cd build

```
  Generate project make files 
```console

	  $ cmake ../Typing-Team

```
  Build application (this will take some time)
```console

	  $ cmake --build . --config Release --target main

```
### Start the application OS specific
#### Linux
-------------------
```console

	  $ ./src/main

```
#### MAC OS X
-------------------

```console

	  $ ./src/main.app/Contents/MacOS/main

```

#### Windows
-------------------
```console

	  $ Release\main.exe

```