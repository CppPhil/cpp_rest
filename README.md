# cpp_rest

## Required software
- Git 
- CMake

## Installing the dependencies
- On GNU/Linux:
    Run the install_dependencies.sh in scripts/dependencies/linux like so:
    
    sh ./scripts/dependencies/linux/install_dependencies.sh
    
    
    Then run the install_boost.sh in scripts/dependencies/linux like so:
    
    sudo sh ./scripts/dependencies/linux/install_boost.sh
- On Microsoft Windows:
    Run the install_dependencies.bat in /scripts/dependencies/windows
	
	using the Visual Studio 2017 Developer command prompt
	
	located in C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2017\Visual Studio Tools
    
## Building
- On GNU/Linux:
	- Generate just the build files: sh ./generate_build_scripts.sh
	- Build: sh ./build.sh
- On Microsoft Windows:
    - Generate just the build files (debug mode): generate_build_scripts.bat debug
	- Build (debug mode): build.bat debug
	- Generate just the build files (release mode): generate_build_scripts.bat release 
	- Build (release mode): build.bat release
	
## Running the tests
After having built the application, launch the application.

Run the tests: ctest --verbose .
