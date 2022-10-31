#include "LogFun.h"
#include "StructProcessFun.h"
#pragma warning(disable:4996)

char LogName[30];
void startclean()
{
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	sprintf(LogName, "Log-%d-%d-%d_%d-%d-%d.log", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	FILE* f = fopen(LogName, "w");
	fputs("This is the log of the project:\n", f);
	fclose(f);
}
void Log(char message[100])
{

	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[100];
	sprintf(str, "%d.%d.%d-%d:%d:%d - %s", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
	FILE* f = fopen(LogName, "a");
	fputs("\n", f);
	fputs(str, f);
	fclose(f);
}
void LogError(char message[100])
{
	char addarr[100];
	sprintf(addarr, "Error - %s", message);
	Log(addarr);

}
void LogEvent(char message[100])
{
	char addarr[100];
	sprintf(addarr, "Event - %s", message);
	Log(addarr);
}
void LogWarning(char message[100])
{
	char addarr[100];
	sprintf(addarr, "Warning - %s", message);
	Log(addarr);
}
char *checkTime()
{

	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	char str[100];
	sprintf(str, "%d-%d-%d_%d-%d-%d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	return str;
}