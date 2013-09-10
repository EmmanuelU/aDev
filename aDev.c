#define OUTPUT
char* output_log = "aDev-log.txt";

#include "include/emman.h"
#include "include/aDevFunctions.h"

int main(int argc, char *argv[ ]){
	ClearPrints();
	CmdOut("bold=`tput bold`");
	CmdOut("normal=`tput sgr0`");
	CmdOut("echo this is ${bold}bold${normal} but this isn't");
	exit(0);
	chdir(CombineStrings("/home/", GetUser()));
	DelFile(output_log);
	DebugLog("--- Begin Android Dev Tools");
	CmdOut("aDev_adb devices > tmp.txt");
	if(IsFileEmpty("tmp.txt")){
		ClearPrints();
		PrintText("--- Proprietary Files Not Found! ---");
		PrintText("Run: \'aDev config\'");
		LineSkip();
		exit(-1);		
	}
	DelFile("tmp.txt");
	if(argc <= 1){
		PrintText("--- Invalid parameters! ---");
		PrintText("Run: \'aDev --help\'");
		LineSkip();
		exit(-1);
	}
	for(tick = 1; tick < argc; tick++){
		if(CompareStrings(argv[tick], "--help") || CompareStrings(argv[tick], "-h")){
			PrintHelp();
			exit(0);
		}
		if(CompareStrings(argv[tick], "--version") || CompareStrings(argv[tick], "-v")){
			PrintVersion();
			exit(0);
		}
		else if(CompareStrings(argv[tick], "test")){
			PrintText("aDev was properly installed, enjoy!");
			LineSkip();
			exit(0);
		}
		else if(CompareStrings(argv[tick], "logcat")){
			DevLog(1);
			exit(0);
		}
		else if(CompareStrings(argv[tick], "dmesg")){
			DevLog(2);
			exit(0);
		}
		else if(CompareStrings(argv[tick], "kmsg")){
			DevLog(3);
			exit(0);
		}
		else if(CompareStrings(argv[tick], "screenshot")){
			ScreenShot();
			exit(0);
		}
		else {
			if(IsStringEmpty(argv[argc - 1])) PrintText(CombineStrings("Unknown Parameter: ", argv[argc - 2]));
			else PrintText(CombineStrings("Unknown Parameter: ", argv[argc - 1]));
			quit();
		}
	}
	return 0;
}
