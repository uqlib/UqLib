@echo off

If not exist obj mkdir obj
If not exist bin mkdir bin
make
EXPLORER bin
pause