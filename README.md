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

## Documentation
Documentation for this project can be generated using Doxygen.

### Documentation of the dependencies
restbed: https://github.com/Corvusoft/restbed/tree/master/documentation


rapidjson: http://rapidjson.org/


boost: http://www.boost.org/doc/libs/1_63_0/


GSL: https://github.com/Microsoft/GSL (see the source code),

also see: https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md


doctest: https://github.com/onqtam/doctest/blob/master/doc/markdown/readme.md#reference

## REST parameters
### Receiving requests with path parameters
In a registered callback function such as ExampleRestApi::handlePostResource

Call has_path_parameter  

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requesthas_path_parameter),


get_path_parameter  

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requestget_path_parameter) and
     
     
get_path_parameters 

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requestget_path_parameters)
on the request object.

### Sending requests with path parameters
Use something like "resource/1" as the pathToResource parameter of one of the
sendRequest functions exported by request.hpp

### Listening for requests with path parameters
Use something like "/resource/{name: .*}" as the path parameter of 
registerResource in ExampleRestApi::ExampleRestApi for instance.


Restbed example: https://github.com/Corvusoft/restbed/blob/master/example/path_parameters/source/example.cpp

### Receiving requests with query parameters
In a registered callback function such as ExampleRestApi::handlePostResource

Call has_query_parameter  

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requesthas_query_parameter),
     
get_query_parameter  

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requestget_query_parameter) and
     
get_query_parameters 

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requestget_query_parameters)
on the request object.

### Sending requests with query parameters
Use the queryParameters parameter for any of the sendRequest functions
exported by request.hpp

### Listening for requests with query parameters
Just use the resource itself, like "/resource".

### Receiving requests with body parameters
The body parameters are part of the body, most likely JSON.

They will have to conform to the REST API as it is specified.

### Sending requests with body parameters
The body parameters are part of the body, 
they will have to conform to the receiving REST API as it is specified.

### Listening for requests with body parameters
Just use the resource itself, like "/resource".

### Receiving requests with header parameters
In a registered callback function such as ExampleRestApi::handlePostResource

Call has_header  

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requesthas_header),

get_header  

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requestget_header) and
     
get_headers 

(documentation: https://github.com/Corvusoft/restbed/blob/master/documentation/API.md#requestget_headers)
on the request object.

### Sending requests with header parameters
Use the headers parameter for any of the sendRequest functions
exported by request.hpp

### Sending responses with header parameters
Use the headers parameter for any of the respond functions
exported by response.hpp

### Listening for requests with header parameters
Just use the resource itself, like "/resource".

