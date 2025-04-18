workspace "Collider Game"
    configurations { "Debug", "Release", "Dist" }
    architecture "x86"

project "Collider Game"
    kind "ConsoleApp"
    language "C++"
    OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    targetdir("build/" .. OutputDir .. "/")
    objdir("build/Intermediates" .. OutputDir .. "/")

    files{
        "source/**.h",
        "source/**.hpp",
        "source/**.c",
        "source/**.cpp"
    }

    includedirs{
        "Dependencies/SFML-2.6.1/include",
        "Dependencies/Box2D/include",
        -- Engine headers
        "source/Engine"
    }

    libdirs{
        "Dependencies/SFML-2.6.1/lib",
        "Dependencies/Box2D/lib"
    }

    -- Libs we need for SFML
    links { 
        "opengl32.lib",
        "freetype.lib", 
        "winmm.lib", 
        "gdi32.lib",
        "openal32.lib",
        "flac.lib",
        "vorbisenc.lib",
        "vorbisfile.lib",
        "vorbis.lib",
        "ogg.lib",
        "ws2_32.lib",
        "box2d.lib"
    }
    -- Windows specific settings, maybe needed for Linux support we wont have
    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    defines { "GAME_PLATFORM_WINDOWS", "SFML_STATIC" }

    -- Settings for different build modes
    filter "configurations:Debug"
        defines { "DEBUG", "ST_PLATFORM_WINDOWS" }
        runtime "Debug"
        symbols "On"
        -- Debug variants for SFML libs
        links { 
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-network-s-d.lib",
            "sfml-system-s-d.lib",
            "sfml-window-s-d.lib" 
        }
        postbuildcommands {
           '{COPY} "%{wks.location}Dependencies/SFML-2.6.1/bin/openal32.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Release"
        defines { "RELEASE", "ST_PLATFORM_WINDOWS" }
        runtime "Release"
        optimize "On"
        symbols "On"
        -- Normal release variants for SFML libs
        links { 
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib" 
        }
        postbuildcommands {
           '{COPYDIR} "%{wks.location}Assets" "%{cfg.targetdir}/Assets"',
           '{COPY} "%{wks.location}Dependencies/SFML-2.6.1/bin/openal32.dll" "%{cfg.targetdir}"'
        }

    filter "configurations:Dist"
        defines { "DIST", "ST_PLATFORM_WINDOWS" }
        runtime "Release"
        optimize "On"
        symbols "Off"
        links { 
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-network-s.lib",
            "sfml-system-s.lib",
            "sfml-window-s.lib" 
        }
        postbuildcommands {
           '{COPYDIR} "%{wks.location}Assets" "%{cfg.targetdir}/Assets"',
           '{COPY} "%{wks.location}Dependencies/SFML-2.6.1/bin/openal32.dll" "%{cfg.targetdir}"'
        }
