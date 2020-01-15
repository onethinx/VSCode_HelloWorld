# How to migrate from an all-in-one project
## Preparation
Make sure you have the VS Code IDE & Dependencies Pack setup done:
  - For Windows: [VSCode_OnethinxPack_Windows](https://github.com/onethinx/VSCode_OnethinxPack_Windows)
  - For Linux: [VSCode_OnethinxPack_Linux](https://github.com/onethinx/VSCode_OnethinxPack_Linux)
  - For MacOS: [VSCode_OnethinxPack_MacOS](https://github.com/onethinx/VSCode_OnethinxPack_MacOS)
## Transform project
1. Copy the all-in-one project to a new location.
1. Delete the following folders:
    - `.vscode`
    - `config`
    - `linker`
    - `psoc6pdl`
    - `tools_2.0`
1. Copy the [`.vscode` folder of the HelloWorld project](https://github.com/onethinx/VSCode_HelloWorld) to your project.
1. Copy (overwrite) the [CMakeLists.txt from the HelloWorld Project](https://github.com/onethinx/VSCode_HelloWorld/blob/master/CMakeLists.txt) to your project (and update changes if made to this file from here).
## Start coding and debugging :-)
1. Start VS Code
1. Load the project: File >> Open (Folder) >> Select the folder of the project >> OK
1. Go to the CMake Tools Extension >> `...` >> Reconfigure project
1. Happy coding and debugging!
