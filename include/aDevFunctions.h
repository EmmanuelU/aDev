typedef struct aDev {
	int adev_version;

} aDev;


static struct aDev dev = {
	.adev_version = 1.0,
};

void PrintHelp(){
	ClearPrints();
	PrintTextWithVar("Android Dev Tools v", dev.adev_version, ":");
	LineSkip();
	PrintText("Usage: aDev [OPTIONS]"); 
	LineSkip();
	PrintText("Options:"); 
	LineSkip();
	PrintText("[--help]          - Show this message");
	LineSkip();
	PrintText("[--version]       - Show aDev Version");
	LineSkip();
	PrintText("[adb]             - Foward a command to adb");
	LineSkip();
	PrintText("[screenshot]      - Screenshot Your Device");
	LineSkip();
	PrintText("[logcat]          - Pull Your Device's logcat");
	LineSkip();
	PrintText("[dmesg]           - Pull Your Device's Kernel Dmesg");
	LineSkip();
	PrintText("[kmsg]            - Pull Your Device's Last Kmsg");
	LineSkip();
	LineSkip();
	return;
}

void PrintVersion(){ // TODO add OTA Updating
	ClearPrints();
	PrintTextWithVar("Android Dev Tools v", dev.adev_version, ":");
	LineSkip();
	PrintText("By Emmanuel Utomi (aka Xmc Wildchild22)");
	PrintText("You can find the project hosted at: https://github.com/EmmanuelU/aDev");
	LineSkip();
	return;
}

void PrintDebugLogInfo(){
	PrintText(CombineStrings(CombineStrings("Debug log is stored in: /home/", GetUser()), "/aDev-log.txt\n\n"));
}

void DevLog(int logtype){
	switch(logtype){
		case 1:
		PrintText("Waiting for Device Connection ...");
		CmdOut("aDev_adb wait-for-device");
		ClearPrints();
		PrintText("Press enter to stop at anytime ...");
		CmdOut("AdbWaitForInput.sh");
		ClearPrints();
		PrintText(CombineStrings(CombineStrings("Done logging, aDev_logcat.txt is in /home/", GetUser()), "/"));
		LineSkip();
		break;
		case 2:
		PrintText("Waiting for Device Connection ...");
		CmdOut("aDev_adb wait-for-device");
		ClearPrints();
		CmdOut("aDev_adb shell dmesg > aDev_dmesg.txt");
		ClearPrints();
		PrintText(CombineStrings(CombineStrings("Done logging, aDev_dmesg.txt is in /home/", GetUser()), "/"));
		LineSkip();
		break;
		case 3:
		ClearPrints();
		DelFile("aDev_kmsg.txt");
		CmdOut("aDev_adb pull /proc/last_kmsg aDev_kmsg.txt");
		ClearPrints();
		if(IsFileEmpty("aDev_kmsg.txt")){
			ClearPrints();
			PrintText("--- last_kmsg was not found on device ---");
			quit();	
		}
		PrintText(CombineStrings(CombineStrings("Done logging, aDev_kmsg.txt is in /home/", GetUser()), "/"));
		LineSkip();
		break;
	}
	return;
}

void ScreenShot(){
	PrintText("Waiting for Device Connection ...");
	CmdOut("aDev_adb wait-for-device");
	ClearPrints();
	CmdOut("aDev_adb shell screencap -p /sdcard/tmp.png");
	CmdOut("aDev_adb pull /sdcard/tmp.png aDev_screenshot.png");
	CmdOut("aDev_adb shell rm /sdcard/tmp.png");
	ClearPrints();
	PrintText(CombineStrings(CombineStrings("Done, aDev_screenshot.png is in /home/", GetUser()), "/"));
	LineSkip();
	return;
}

bool IsValidArg(char* argv){
	if(CompareStrings(argv, "--help") || CompareStrings(argv, "-h")) return true;
	if(CompareStrings(argv, "--version") || CompareStrings(argv, "-v")) return true;
	if(CompareStrings(argv, "test")) return true;
	if(CompareStrings(argv, "adb")) return true;
	if(CompareStrings(argv, "logcat")) return true;
	if(CompareStrings(argv, "dmesg")) return true;
	if(CompareStrings(argv, "screenshot")) return true;
	if(CompareStrings(argv, "kmsg")) return true;
	return false;
}
