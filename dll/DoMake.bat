@echo off

If not exist UqLib\x64 mkdir UqLib\x64
If not exist UqLib\x64\Gcc mkdir UqLib\x64\Gcc
If not exist x64\Debug mkdir x64\Debug
make
EXPLORER x64\Debug
pause