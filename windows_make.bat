del /q /f Snake.exe

gcc main.c -o Snake.exe -mwindows -lalleg_s -lkernel32 -luser32 -lcomdlg32 -lole32 -ldinput -lddraw -ldxguid -lwinmm -ldsound

Snake.exe