#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#pragma warning(disable:4996)

void startclean();
void Log(char message[100]);
void LogError(char message[100]);
void LogEvent(char message[100]);
void LogWarning(char message[100]);
char *checkTime();