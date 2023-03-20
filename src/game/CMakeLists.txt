
add_executable(menu MACOSX_BUNDLE 
                Menu.cpp
                Menu.h
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
                Galaga.h)

target_link_libraries(menu simplewindow)  