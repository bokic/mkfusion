@echo off

copy /Y common.h include\
copy /Y qcftemplate.h include\
copy /Y qcfrunningtemplate.h include\
copy /Y qwddx.h include\
copy /Y qmkfusionexception.h include\
copy /Y cffunctions.h include\

del /Q D:\Projects\MKFusion\templates\*
