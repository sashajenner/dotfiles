//Modify this file to change what commands output to your statusbar, and recompile using the make command.

static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/

    // Packages to update
	//{"",      "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	30,		0},
    
	//{"",        "shownightmode",0,		            2}, // sig 2
	{"",        "showtime",	    30,		            0}, // 30 sec
	{"",        "showvolume -q",	0,		            1}, // sig 1
	//{"",        "showdate",	    300,		        0}, // 5 min
	//{"",        "showwttr",	    3600,		        0}, // 1 hr
	//{"",        "showsurf",	    10800,		        0}, // 3 hr
	{"",        "showcpus",	    10,		            0}, // 10 sec
	//{"",        "showwifi",	    10,		            0}, // 10 sec
	//{"",        "showvolume",	0,		            1}, // sig 1
	{"",        "showbattery",  10,		            0}, // 10 sec

};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
