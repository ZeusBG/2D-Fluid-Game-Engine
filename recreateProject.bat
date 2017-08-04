@echo off 
Rem This is for listing down all the files in the directory Program files 
if exist 2D_Engine.sln (del "2D_Engine.sln")
if exist 2D_Engine.VC.db (del "2D_Engine.VC.db")
if exist 2D_Engine.vcxproj (del "2D_Engine.vcxproj")
start "" "premake5.exe" vs2017