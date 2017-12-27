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

	configuration "Debug"
	configuration "Release"
