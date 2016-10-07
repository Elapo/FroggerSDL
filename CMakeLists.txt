cmake_minimum_required(VERSION 3.3)
project(FroggerSDL)

# configure the SDL (cf. "SDL2-2.0.3\i686-w64-mingw32\lib\pkgconfig\sdl2.pc")
# C++ flags
set(SDL2_Flags "-Wl,--no-undefined -static-libgcc")
# library paths
set(SDL2_ROOT     "C:/MinGW")
set(SDL2_Includes "${SDL2_ROOT}/include")
set(SDL2_LibDir   "${SDL2_ROOT}/lib")
# imported targets for CMake (cf. https://cmake.org/Wiki/CMake/Tutorials/Exporting_and_Importing_Targets)
add_library(SDL2     STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
set_property(TARGET SDL2     PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2.a")
set_property(TARGET SDL2main PROPERTY IMPORTED_LOCATION "${SDL2_LibDir}/libSDL2main.a")
# the libs to link against
# note: as always with gcc, the order is important...
set(SDL2_Libs SDL2_image SDL2_ttf SDL2_mixer mingw32 SDL2 SDL2main m dinput8 dxguid dxerr8 user32 gdi32 winmm imm32 ole32 oleaut32 shell32 version uuid)

# configure the project
# include the SDL flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${SDL2_Flags}")
# collect the sources
set(SOURCE_FILES main.cpp AbstractFactory.cpp AbstractFactory.h SDLFactory.cpp SDLFactory.h Enemy.cpp Enemy.h GameObject.cpp GameObject.h Player.cpp Player.h SDLEnemy.cpp SDLEnemy.h SDLPlayer.cpp SDLPlayer.h keyNames.h Renderer.cpp Renderer.h Entity.cpp Entity.h FPSReg.cpp FPSReg.h SDLFPSReg.cpp SDLFPSReg.h settings.cpp settings.h settingStruct.h projectile.cpp projectile.h SDLProjectile.cpp SDLProjectile.h)
# define the target
add_executable(FroggerSDL ${SOURCE_FILES})
# include the SDL headers
target_include_directories(FroggerSDL SYSTEM PRIVATE ${SDL2_Includes})
# link against the SDL (and its dependencies)
target_link_libraries(FroggerSDL ${SDL2_Libs})