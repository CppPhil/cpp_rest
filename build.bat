@echo off

IF "%1"=="debug" GOTO DEBUG_MODE

IF "%1"=="release" GOTO RELEASE_MODE

GOTO ERROR

:DEBUG_MODE
    cmake -DCMAKE_BUILD_TYPE=Debug .
    cmake --build . --config "Debug"
    GOTO END
    
:RELEASE_MODE
    cmake -DCMAKE_BUILD_TYPE=Release .
    cmake --build . --config "Release"
    GOTO END
    
:ERROR
    ECHO Parameter must be Debug or Release!
    GOTO END

:END
