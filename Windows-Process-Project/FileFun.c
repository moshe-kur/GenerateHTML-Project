#include "LogFun.h"
#include "FileFun.h"
#include "StructProcessFun.h"
#pragma warning(disable:4996)



void MakeFileStruct()
{
	if (HeadSnapheder)
	{
	char FileName[30];
	time_t t;
	time(&t);
	struct tm* timeinfo;
	timeinfo = localtime(&t);
	//sprintf(FileName, "%d-%d-%d_%d-%d-%d.bin", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	printf("Please ENTER the file name\n");
	scanf(" %s", FileName);
	sprintf(FileName, "%s.bin", FileName);
	FILE* f = fopen(FileName, "wb");
	//LOG fopen

	fwrite(HeadSnapheder, sizeof(struct SnapshotHeader), 1, f);
	
	CurrSnap = HeadSnapheder->HeadSnap;
	while (CurrSnap)
	{
		fwrite(CurrSnap, sizeof(struct Snapshot), 1, f);
		CurrentProcess = CurrSnap->ProcessHead;
		while (CurrentProcess)
		{
			fwrite(CurrentProcess, sizeof(struct ProcessDetails), 1, f);
			CurrDll = CurrentProcess->DllHead;
			//Add all dlls
			while (CurrDll)
			{
				fwrite(CurrDll, sizeof(struct Dlls), 1, f);
				CurrDll = CurrDll->Next;
			}
			CurrentProcess = CurrentProcess->Next;
		}
		
		CurrSnap = CurrSnap->Next;
	}
	
	

	fclose(f);
	//LOG file saved with file name
	printf("The file is SAVE now\n");
	}
	else
	{
		//LOG header is empty
		printf("There is no Snapshot in memory\n");
	}

}

//TO-DO finish change from fwrite to fread
//LOG like write

void ReadFromFile()
{
	/*
	char FileName[30];
	printf("Please ENTER the file name\n");
	scanf(" %s", FileName);
	sprintf(FileName, "%s.bin", FileName);
	FILE* f = fopen(FileName, "rb");

	if (f)
	{
		struct SnapshotHeader* TheHeadSnap=NULL;
		TheHeadSnap = (struct SnapshotHeader*)malloc(sizeof(struct SnapshotHeader));
		fread(TheHeadSnap, sizeof(struct SnapshotHeader), 1, f);
				
		CurrSnap = HeadSnapheder->HeadSnap;
		while (CurrSnap)
		{
			//fread
			fread(CurrSnap, sizeof(struct Snapshot), 1, f);
			CurrentProcess = CurrSnap->ProcessHead;
			while (CurrentProcess)
			{
				fread(CurrentProcess, sizeof(struct ProcessDetails), 1, f);
				CurrDll = CurrentProcess->DllHead;
				//Add all dlls
				while (CurrDll)
				{
					fread(CurrDll, sizeof(struct Dlls), 1, f);
					CurrDll = CurrDll->Next;
				}
				CurrentProcess = CurrentProcess->Next;
			}

			CurrSnap = CurrSnap->Next;
		}
		


		fclose(f);

		printf("The file is LOAD now\n");
	}
	else
	{
		printf("There is no file with this name\n");
	}
	*/
}