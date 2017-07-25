workspace "2D_Engine"
   configurations { "Debug", "Release" }

project "2D_Engine"
   kind "WindowedApp"
   language "C++"
   targetdir "bin/%{cfg.buildcfg}"
   includedirs { "$(ProjectDir)/src" }
   files { "src/**.h", "src/**.c", "src/**.cpp", "src/**.hpp", "src/**.hlsl" }
   excludes { "*.hlsl" }
   

   flags { "WinMain" }
   rtti ("On")
   links { "d3d11", "d3dcompiler" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"