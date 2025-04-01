@echo off
set BUILD_DIR=build

:: clean previous build
echo Cleaning previous build...
if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%

:: create build directory
mkdir %BUILD_DIR%
cd %BUILD_DIR%

:: run cmake
echo Configuring project with CMake...
cmake ..
echo Building project...
cmake --build .

:: run if build successful
if %ERRORLEVEL% == 0 (
    echo Build successful. Running application...
    ./Debug/ouros.exe
) else (
    echo Build failed!
)

pause