# Setup Onethinx Core Project for VS Code

## 1. Prerequisites
- **VS Code**
    - https://code.visualstudio.com/download  
- **CMake**
    - **macOS and Windows**
        https://cmake.org/download/
    - **Linux**
        install CMake: sudo apt install cmake
- **Make**
    - **macOS**
        Install homebrew GNU by: 'make brew install homebrew/core/make' as [explained here](https://apple.stackexchange.com/questions/261918/how-to-upgrade-gnu-make-in-os-x-el-capitan).
    - **Windows**
        **Full MinGW install** with make: 
       https://osdn.net/projects/mingw/releases/
       **Lightweight manual**: 
       [These](https://github.com/onethinx/GetStartedWithVSCode/tree/master/VScode_supply) files can be copied to, for example the "?/Program Files (x86)/make/" folder and it's path needs to be added to the environment ([here's how to do it](https://docs.alfresco.com/4.2/tasks/fot-addpath.html), reboot after adding the path).

## 2. VS Code Extensions
   - ARM Support For Visual Studio Code (dan-c-underwood)
   - C/C++ IntelliSense, debugging (microsoft)
   - CMake language support (twxs)
   - CMake Tools (microsoft)
   - Cortex-Debug GDB support (marus25)
   - LinkerScript support for GNU (Zixuan Wang)
   - Open in Application (Fabio Spampinato)
   - Output Colorizer (IBM)
   - Tasks (actboy168)
   
## 3. Configure
   - Command Palette (CTRL+SHIFT+P) > type: JSON > Click Preferences: Open Settings (JSON)
   - Add the following lines to the VS Code User settings:
   ```
   "C_Cpp.default.configurationProvider": "vector-of-bool.cmake-tools",
   "C_Cpp.default.compilerPath": "arm-none-eabi-gcc",
   "C_Cpp.loggingLevel":"Debug",
   // Location of the cmake executable when using macOS
   "cmake.cmakePath": "/Applications/CMake.app/Contents/bin/cmake",
   // Location of the cmake executable when using windows
   //"cmake.cmakePath": "C:/Program Files/CMake/bin/cmake.exe",
   "cmake.configureOnOpen": true,
   "cmake.sourceDirectory": "${workspaceRoot}"
   ```
   - **Linux:** execute `tools_2.0/linux/openocd/udev_rules/install_rules.sh` to apply the OpenOCD rules
## 4. Check
   - If make is installed by typing `make -v` (or `mingw32-make.exe -v`) into the bash / powershell terminal window of VS Code
       (the folder of the make binary needs to be added to the system's path variable)
   - If the compiler is installed and the path variable for the compiler is okay:
   `arm-none-eabi-gcc -v`
       
## 5. Remind
   - after changing the device configuration (or project file structure) to use
       - Clean Reconfigure
       - Clean Rebuild
       in order to build the image properly
     
   - to delete the contents of the build folder
       - if you copied the project including build folder from another location / machine
       - when build fails.
