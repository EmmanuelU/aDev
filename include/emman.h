#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <stdint.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#define WAIT -1

extern void PrintDebugLogInfo(void);
extern void PrintText(char* text);
extern bool IsStringEmpty(char* text);

int tick;
int tick2;
int i;

char* text;
FILE *file;

FILE *MkFile(char* text){
	FILE *file = fopen(text, "ab+");
	return file;
}

void WriteFile(char* buildlog, char* text){
	FILE *file = fopen(buildlog, "ab+");
	fprintf(file,"%s\n",text);
	fclose(file);
}

bool IsFileEmpty(char* text)
{
    FILE *file = fopen(text, "ab+");
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0)
    {
        return true;
    }

    fseek(file, savedOffset, SEEK_SET);
    return false;
}

void ReadFile(char* text){
	int size = 1024, pos;
	int c;
	char *buffer = (char *)malloc(size);

	FILE *f = fopen(text, "r");
	if(f) {
		do { // read all lines in file
			pos = 0;
			do{ // read one line
			c = fgetc(f);
			if(c != EOF) buffer[pos++] = (char)c;
			if(pos >= size - 1) { // increase buffer length - leave room for 0
				size *=2;
				buffer = (char*)realloc(buffer, size);
			}
			}while(c != EOF && c != '\n');
			buffer[pos] = 0;
			// line is now in buffer
			PrintText(buffer);
		} while(c != EOF); 
		fclose(f);
	}
	free(buffer);
	return;
}

char* GetLineFromFile(char* text, int line){
	int size = 1024, pos;
	int c;
	char *buffer = (char *)malloc(size);

	FILE *f = fopen(text, "r");
	if(f) {
		do { // read all lines in file
			pos = (line - 1);
			do{ // read one line
			c = fgetc(f);
			if(c != EOF) buffer[pos++] = (char)c;
			if(pos >= size - 1) { // increase buffer length - leave room for 0
				size *=2;
				buffer = (char*)realloc(buffer, size);
			}
			}while(c != EOF && c != '\n');
			buffer[pos] = 0;
			// line is now in buffer
			if(IsStringEmpty(buffer)) return "unknown";
			return buffer;
		} while(c != EOF); 
		fclose(f);
	}
	free(buffer);
	return;
}

void ClearPrints(){
	printf("\033c");
	return;
}

void LineSkip(){
	printf("\n");
	return;
}

void DebugLog(char* text){
	#ifdef OUTPUT
	MkFile(output_log);
	WriteFile(output_log,text);
	#endif
}

void CmdOut(char* text){
	#ifdef OUTPUT
	DebugLog(text);
	#endif
	system(text);
}

void PrintText(char* text){
	fprintf(stdout, "%s \n", text);
	#ifdef OUTPUT
	DebugLog(text);
	#endif
	return;
}

void PrintTextWithString(char* text, char* textvar, char* text2){
	fprintf(stdout, "%s%s%s\n", text, textvar, text2);
	#ifdef OUTPUT
	FILE *file = MkFile(output_log);
	fprintf(file, "%s%s%s\n", text, textvar, text2);
	#endif
	return;
}

void PrintTextWithVar(char* text, int var, char* text2){
	unsigned char string = var;
	fprintf(stdout, "%s%d%s\n", text,string,text2);
	#ifdef OUTPUT
	FILE *file = MkFile(output_log);
	fprintf(file, "%s%d%s\n", text, string, text2);
	#endif
	return;
}

char GetStringFromVar(int var){
	unsigned char string = var;
	return string;
}

void PrintVar(int var){
	unsigned char string = var;
	fprintf(stdout, "%d\n", string);
	#ifdef OUTPUT
	FILE *file = MkFile(output_log);
	fprintf(file, "%d\n", string);
	#endif
	return;
}

bool CompareStrings(char* text, char* text2){
	return !strcmp(text, text2);
}

char* CombineStrings(char* text, char* text2){
	asprintf(&text, "%s%s", text, text2);
	return text;
}

char* GetUser(){
	return getenv("USER");
}

char* GetCurDir(){
	return getenv("PWD");
}

void PrintFilesInDir(){
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d){
		while ((dir = readdir(d)) != NULL) PrintText(dir->d_name);
		closedir(d);
	}
	return;
}

bool DoesDirExist(char* text){
	struct stat dir;
	tick = stat(text, &dir);
	if(-1 == tick) {
		if(ENOENT == errno) return false;
		else {
			perror("stat");
			exit(1);
		}
	} else return S_ISDIR(dir.st_mode);
}

bool DoesFileExist(char* text){
	struct stat dir;
	tick = stat(text, &dir);
	if(-1 == tick) {
		if(ENOENT == errno) return false;
		else {
			perror("stat");
			exit(1);
		}
	} else return !S_ISDIR(dir.st_mode);
}

void DelFile(char* text){
	remove(text);
}

void quit(){
	PrintText("\n--- Fatal Error ---");
	PrintDebugLogInfo();
	exit(-1);
}

char* GetTime(){
	char* text; 
	time_t seconds;
	seconds = time(NULL);
	asprintf(&text, "%ld", seconds/3600);
	return text;
}

char* GetUserInput(){
	LineSkip();
	int max = 20;
	void *filename;
	text = (char*) malloc(max); // allocate buffer
	if (text == 0) quit();

	while (true) { // skip leading whitespace
		tick = getchar();
		if (tick == EOF) break; // end of file
		if (!isspace(tick)) {
			ungetc(tick, stdin);
			break;
		}
	}
	
	i = 0;
	while (true) {
		tick2 = getchar();
		if (isspace(tick2) || tick2 == EOF){ // at end, add terminating zero
			text[i] = 0;
			break;
		}
		text[i] = tick2;
		if (i==max-1) { // buffer full
			max = max+max;
			text = (char*)realloc(text,max); // get a new and larger buffer
			if (text == 0) quit();
		}
		i++;
	}

	return text;
	free(filename); // release memory
}

void WaitForEnterKey(){
	LineSkip();	
	getchar();
	return;
}

bool IsStringEmpty(char* text){
	if(CompareStrings(text, "")) return true;
	if(CompareStrings(text, "(null)")) return true;
	if(text == NULL) return true;
	return false;
}

bool IsYes(char* text){
	if(CompareStrings(text,"YES")) return true;
	if(CompareStrings(text,"Yes")) return true;
	if(CompareStrings(text,"yes")) return true;
	if(CompareStrings(text,"y")) return true;
	if(CompareStrings(text,"Y")) return true;
	return false;
}

bool IsNo(char* text){
	if(CompareStrings(text,"NO")) return true;
	if(CompareStrings(text,"No")) return true;
	if(CompareStrings(text,"no")) return true;
	if(CompareStrings(text,"n")) return true;
	if(CompareStrings(text,"n")) return true;
	return false;
}
