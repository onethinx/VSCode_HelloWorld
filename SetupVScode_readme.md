# Setup Onethinx Core Project for VS Code

## 1.a Windows prerequisites
- **VS Code**
    - https://code.visualstudio.com/download
- **Onethinx Dependencies Pack**
    - Setup your Onethinx dependencies pack [from here](https://github.com/onethinx/VSCode_OnethinxPack_Windows)
## 1.b MAC OS prerequisites
- **VS Code**
    - https://code.visualstudio.com/download
- **CMake**
    - Download and install CMake: https://cmake.org/download/
    - Apply the CMake path to VS Settings: `"cmake.cmakePath": "/Applications/CMake.app/Contents/bin/cmake",`
- **Make**
    - Install homebrew GNU by: 'make brew install homebrew/core/make' as [explained here](https://apple.stackexchange.com/questions/261918/how-to-upgrade-gnu-make-in-os-x-el-capitan).
- **Onethinx Dependencies Pack**
    - Setup your Onethinx dependencies pack [from here](https://github.com/onethinx/VSCode_OnethinxPack_macOS)
## 1.c Linux prerequisites
- **VS Code**
    - https://code.visualstudio.com/download
- **CMake**
    install CMake: `sudo apt install cmake`
- **Onethinx Dependencies Pack**
    - Setup your Onethinx dependencies pack [from here](https://github.com/onethinx/VSCode_OnethinxPack_Linux)
- **Apply OpenOCD rules**
    - execute `yourpath\VSCode_OnethinxPack_Linux/tools_2.0/linux/openocd/udev_rules/install_rules.sh` to apply the OpenOCD rules
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
   
## 3. Check
   - If make is installed by typing `make -v` (or `mingw32-make.exe -v`) into the bash / powershell terminal window of VS Code
       (the folder of the make binary needs to be added to the system's path variable)
   - If the compiler is installed and the path variable for the compiler is okay:
   `arm-none-eabi-gcc -v`
       
## 4. Remind
   - after changing the device configuration (or project file structure) to use
       - Clean Reconfigure
       - Clean Rebuild
       in order to build the image properly
     
   - to delete the contents of the build folder
       - if you copied the project including build folder from another location / machine
       - when build fails.
