# OpenGL_tutorial
Tutorials for OpenGL 3.3 workshops - Polygon Circle of Shadows

# Compiling tutorials (for Windows and Visual 2015)
1. Clone this repository
2. Download cmake portable: https://cmake.org/files/v3.7/cmake-3.7.1-win64-x64.zip
3. Unzip and run bin/cmake-gui.exe
  - Select source code path (e.g. repository_path/OpenGL_tutorial/tutorial_00-framework) and set build location to /build folder (confirm creating new folder)
  - Select Configure, choose Visual Studio 2015 (warning, NOT x64, because our libs are compiled for x86)
  - Click Generate
  - Copy Data folder to Build folder (Visual workspace path is inside build folder)
4. Open Visual solution
5. Build solution
