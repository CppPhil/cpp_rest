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
	- Generate the build files: cmake .
	- Build: cmake --build .
- On Microsoft Windows:
    - Generate the build files (debug mode): cmake -DCMAKE_BUILD_TYPE=Debug .
	- Build (debug mode): cmake --build . --config "Debug"
	- Generate the build files (release mode): cmake -DCMAKE_BUILD_TYPE=Release .
	- Build (release mode): cmake --build . --config "Release"	
	
## Running the tests
After having built the application, launch the application.
Run the tests: cmake --verbose .
