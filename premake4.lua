newoption {
   trigger     = "iup-inc",
   value       = "path/to/directory",
   description = "Where iup.h can be found",
}

newoption {
   trigger     = "iup-lib",
   value       = "path/to/directory",
   description = "Where IUP library can be found",
}

solution "ipwdqc"
	configurations { "Debug", "Release" }
	project "gui"
		kind "WindowedApp"
		language "C"
		files {
			"gui.c", "passwdqc/passwdqc_parse.c",
			"passwdqc/passwdqc_memzero.c",
			"passwdqc/passwdqc_random.c",
			"passwdqc/concat.c", "passwdqc/wordset_4k.c",
			"passwdqc/passwdqc_load.c"
		}
		links { "iup" }
		includedirs { "passwdqc" }

		if _OPTIONS['iup-inc'] then
			includedirs { _OPTIONS['iup-inc'] }
		end
		if _OPTIONS['iup-lib'] then
			libdirs { _OPTIONS['iup-lib'] }
			linkoptions {"-Wl,-rpath," .. _OPTIONS["iup-lib"] }
		end

		configuration "Debug"
			flags { "Symbols", "ExtraWarnings" }

		configuration "Release"
			flags { "Optimize", "ExtraWarnings" }

		configuration "windows"
			links { "gdi32", "comctl32", "ole32", "comdlg32", "uuid", "bcrypt" }
			files { "gui.rc" }
