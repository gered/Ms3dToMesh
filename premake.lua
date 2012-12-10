
BUILD_DIR         = "build"

if _ACTION == "clean" then
	os.rmdir(BUILD_DIR)
end

solution "Ms3dToMesh"
	configurations { "Debug", "Release" }
	location (BUILD_DIR .. "/" .. _ACTION)
	
project "Ms3dToMesh"
	kind "ConsoleApp"
	language "C++"
	location (BUILD_DIR .. "/" .. _ACTION)
	files {
		"./src/**.c*",
		"./src/**.h",
	}
	debugdir "."
	
	---- PLATFORM SPECIFICS ----------------------------------------------------
	configuration "vs*"
		flags {
			"NoPCH",
			"NoMinimalRebuild"
		}
		buildoptions { "/MP" }
		defines {
			"_CRT_SECURE_NO_WARNINGS",
			"_CRT_NONSTDC_NO_WARNINGS"
		}
		
	configuration "gmake"
		kind "ConsoleApp"
		buildoptions { "-Wall" }
		
	configuration { "windows", "gmake" }
		kind "ConsoleApp"
		defines {
			"_GNU_SOURCE=1",
		}
		links {
			"mingw32",
		}
		linkoptions {
			"-static-libgcc",
			"-static-libstdc++",
		}
	----------------------------------------------------------------------------
			
	configuration "Debug"
		defines {
			"DEBUG",
			"DEBUG_ASSERT_BREAK",
		}
		flags { "Symbols" }
	
	configuration "Release"
		defines {
			"NDEBUG",
		}
		flags { "Optimize" }
