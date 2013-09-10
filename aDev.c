#define OUTPUT
char* output_log = "aDev-log.txt";

#include "include/emman.h"
#include "include/aDevFunctions.h"

int main(int argc, char *argv[ ]){
	ClearPrints();
	chdir(CombineStrings("/home/", GetUser()));
	DelFile(output_log);
	DebugLog("--- Begin Android Dev Tools ARGS");
	for(tick = 1; tick < argc; tick++) DebugLog(CombineStrings("ARG: ", argv[tick]));
	DebugLog("");
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
		if(IsStringEmpty(argv[tick])) continue;
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
		else if(CompareStrings(argv[tick], "info")){
			Info();
			exit(0);
		}
		else if(CompareStrings(argv[tick], "adb")){
			text = "aDev_adb ";
			for(tick2 = 1; tick2 < argc; tick2++) if(!CompareStrings(argv[tick2], "adb")) text = CombineStrings(text, CombineStrings(argv[tick2], " "));
			CmdOut(text);
			exit(0);
		}
		else if(CompareStrings(argv[tick], "fastboot")){
			text = "aDev_fastboot ";
			for(tick2 = 1; tick2 < argc; tick2++) if(!CompareStrings(argv[tick2], "fastboot")) text = CombineStrings(text, CombineStrings(argv[tick2], " "));
			CmdOut(text);
			exit(0);
		}
		else{
			for(tick2 = (argc - 1); tick2 < 0; tick2--){
				if(!IsValidArg(argv[tick2])) break;
				if(tick2 == 1) quit();
			}
			if(IsValidArg(argv[tick2])) tick2--;
			if(IsValidArg(argv[tick2])) quit();
			PrintText(CombineStrings("Unknown Parameter: ", argv[tick2]));
			quit();
		}
	}
	return 0;
}
