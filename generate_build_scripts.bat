@echo off

IF "%1"=="debug" GOTO DEBUG_MODE

IF "%1"=="release" GOTO RELEASE_MODE

GOTO ERROR

:DEBUG_MODE
    cmake -DCMAKE_BUILD_TYPE=Debug .
    exit 0
    
:RELEASE_MODE
    cmake -DCMAKE_BUILD_TYPE=Release .
    exit 0
    
:ERROR
    ECHO Parameter must be Debug or Release!
    exit 1

