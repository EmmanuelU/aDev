typedef struct aDev {
	int adev_version;

} aDev;


static struct aDev dev = {
	.adev_version = 1.0,
};

bool DoToolsExist(){
	return DoesDirExist("tools");
}

void devlog(int logtype){
	if(DoToolsExist){
		switch(logtype){

			case 1:
			PrintText("Press Enter to stop logging ...");
			CmdOut("./tools/AdbWaitForInput.sh");
			ClearPrints();
			PrintText(CombineStrings(CombineStrings("Done logging, aDev_logcat.txt is in /home/", GetUser()), "/"));
			LineSkip();
			return;

		}
	}
	else{
		PrintText("Proprietary files not found ...");
		LineSkip();
		PrintText("Please run 'make config'");
		quit();
	}
	return;
}
