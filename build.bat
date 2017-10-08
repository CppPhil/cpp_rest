@echo off

IF "%1"=="debug" GOTO DEBUG_MODE

IF "%1"=="release" GOTO RELEASE_MODE

GOTO ERROR

:DEBUG_MODE
    generate_build_scripts.bat debug
    cmake --build . --config "Debug"
    exit 0
    
:RELEASE_MODE
    generate_build_scripts.bat debug
    cmake --build . --config "Release"
    exit 0
    
:ERROR
    ECHO Parameter must be Debug or Release!
    exit 1


