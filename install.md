Our application uses C++ 17 standard specific features and behaivor, CMake v3.8 minimim, and the “wxWidgets” library, which has dependencies that need to be installed. 

Please see the below installation instructions for wxWidgets dependencies needed **based on your OS**

# **Dependencies**                        

## Linux
-------------------
```text
  Install meson and ninja by running the following commands
```
```console

    $ sudo apt-get install meson ninja-build

```
```text
  Install GTK3 (GTK 3 is an old release, unknown if wxWidgets is compatible with GTK4)
```
```console

    $ sudo apt-get install libgtk-3-dev

```
## MAC OS X
-------------------
```text
  Smile, you don’t have anything to do. Way to go Steve Jobs	
```
## Windows
-------------------
```text
  Smile, you don’t have anything to do. Way to go Bill Gates
```
# **Cloning the repository**
Below are common instructions for cloning our repository
```text
  Clone the Unoptimized repository
```
```console

	  $ git clone https://ramennoodle.me.cmu.edu/Bonobo.Git.Server/Unoptimized.git

```
Navigate into wxWidgets subdirectory
```text
  Run the following command (this will take some time)
```
```console

	  $ git submodule update –init

```
```text
  Run the same command again to update the submodules
```
```console

	  $ git submodule update –init

```
**Building the application**               
============
Below are instructions for building our application
```text
  Create build directory
```
```console

	  $ mkdir Unoptimized_build

```
```text
  Navigate to build folder
```
```console

	  $ cd Unoptimized_build

```
```text
  Generate project make files 
```
```console

	  $ cmake .

```
```text
  Build application (this will take some time)
```
```console

	  $ cmake --build . --config Release --target main

```
```text
  Start the application 
```
```console

	  $ src/main

```