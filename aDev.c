#define OUTPUT
char* output_log = "adev-log.txt";

#include "include/emman.h"
#include "include/aDevFunctions.h"

static struct aDev test = {
	.adev_version = 1.0,
};

void PrintHelp(){
	ClearPrints();
	PrintTextWithVar("Android Dev Tools v", test.adev_version, ":");
	LineSkip();
	PrintText("Usage: aDev [OPTIONS]"); 
	LineSkip();
	PrintText("Options:"); 
	LineSkip();
	PrintText("[--help] - Show this message");
	LineSkip();
	PrintText("[adb] - Foward a command to adb");
	LineSkip();
	PrintText("[last_kmsg] - Screenshot Your Device");
	LineSkip();
	PrintText("[logcat] - Pull your device's logcat");
	LineSkip();
	PrintText("[kmsg] - Pull your device's kmsg");
	LineSkip();
	PrintText("[last_kmsg] - Pull your device's last kmsg");
	LineSkip();
	LineSkip();
	return;
}

int main(int argc, char *argv[ ]){
	ClearPrints();
	DelFile(output_log);
	if(argc <= 1){
		PrintText("Invalid parameters!");
		PrintText("Type Adev --help");
		exit(-1);
	}
	for(tick = 1; tick < argc; tick++){
		if(CompareStrings(argv[tick], "--help") || CompareStrings(argv[tick], "-h")){
			PrintHelp();
			exit(0);
		}
		else if(CompareStrings(argv[tick], "logcat")){
			devlog(1);
			exit(0);
		}
		else {
			PrintText(CombineStrings("Unknown Parameter: ", argv[argc - 1]));
			quit();
		}
	}
	return 0;
}
