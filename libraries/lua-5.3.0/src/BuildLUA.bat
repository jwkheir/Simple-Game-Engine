cl /MD /O2 /W3 /c /DLUA_BUILD_AS_DLL *.c
del *.o
ren lua.obj lua.o
ren luac.obj luac.o
ren print.obj print.o
link /DLL /IMPLIB:lua5.3.0.lib /OUT:lua5.3.0.dll *.obj
link /OUT:lua.exe lua.o lua5.3.0.lib
lib /out:lua5.3.0-static.lib *.obj
link /OUT:luac.exe luac.o print.o lua5.3.0-static.lib