# src directory CMakeLists.txt

add_executable(main MACOSX_BUNDLE 
                main.cpp
                fssimplewindow.cpp
                fssimplewindow.h
                ysglfontdata.c
                ysglfontdata.h
                yspng.cpp
                yspng.h
                yssimplesound.cpp
                yssimplesound.h
                genericchararray.h
                textinput.cpp
                textinput.h
                textstring.cpp
                textstring.h
                tutorial.cpp
                tutorial.h
                minigame_mars.cpp
                minigame_mars.h
                minigame_rockets.cpp
                minigame_rockets.h
                overworld.cpp
                overworld.h
                Rover.cpp
                Rover.h
                Galaga.cpp
                Galaga.h
                Menu.cpp
                Menu.h)
target_link_libraries(main media)                
                
