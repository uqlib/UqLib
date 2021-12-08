@echo off

If not exist UqLibCppSample\x64 mkdir UqLibCppSample\x64
If not exist UqLibCppSample\x64\Gcc mkdir UqLibCppSample\x64\Gcc
If not exist x64\Debug mkdir x64\Debug
make
EXPLORER x64\Debug
pause