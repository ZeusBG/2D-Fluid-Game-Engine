workspace "2D_Engine"
   configurations { "Debug", "Release" }

project "2D_Engine"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   includedirs { "$(ProjectDir)/src", "$(ProjectDir)/extern/sdl/include", "$(ProjectDir)/extern/enet-1.3.13/include", "$(ProjectDir)/extern" }
   files { "src/**.h", "src/**.c", "src/**.cpp", "src/**.hpp", "src/**.hlsl" }
   excludes { "*.hlsl", "src/networking/server/main.cpp" }
   

   flags { "WinMain" }
   rtti ("On")
   links { "$(ProjectDir)/extern/sdl/SDL2", "d3d11", "d3dcompiler", "$(ProjectDir)/extern/enet-1.3.13/enet.lib", "ws2_32.lib", "winmm.lib" }
   libdirs { "$(ProjectDir)/extern/sdl/SDL2.dll", "$(ProjectDir)/extern/sdl" }

   postbuildcommands { "copy /Y $(ProjectDir)extern\\sdl\\SDL2.dll $(ProjectDir)$(OutDir)" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"