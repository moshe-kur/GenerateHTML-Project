#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <psapi.h>
#pragma warning(disable:4996)

struct Dlls
{
	//META-DATA
	struct Dlls* Next;
	struct Dlls* Prev;
	//DATA
	int DllID;
	char DllName[MAX_PATH];
};
struct ProcessDetails
{
	//META-DATA
	struct ProcessDetails* Next;
	struct ProcessDetails* Prev;
	//DATA
	PROCESS_MEMORY_COUNTERS pmc;
	struct Dlls* DllHead;
	int ProcessID;
	int ProcessNumber;
	int NumberOfDlls;
	int SnapshotNumber;
	char ProcesName[MAX_PATH];
	char time[30];

};
struct Snapshot
{
	//NETA-DATA
	struct Snapshot* Next;
	struct Snapshot* Prev;
	//DATA
	int SnapshotID;
	int NumOfProcess;
	struct ProcessDetails* ProcessHead;
	// int NumOfDll;  ����?
};
struct SnapshotHeader
{
	struct Snapshot* HeadSnap;
	int SnapshotNumbers;
	char Reserved[100];
};
void add(struct ProcessDetails ret);
struct ProcessDetails PrintMemoryInfo(DWORD processID);
struct Snapshot* MakeOneSnapshot();
void MakeHeaderSnap();

// extern ???

extern struct SnapshotHeader* HeadSnapheder;
extern struct Snapshot* CurrSnap;
extern struct Snapshot* PrevSnap;
extern struct ProcessDetails* CurrentProcess;
extern struct ProcessDetails* LastProcess;
extern struct Dlls* CurrDll;
extern struct Dlls* PrevDll;
extern int SnapNum;
extern int ProcessNumber;

//loop snap
int LoopNumber;
void MGetProcessesInfo(char choice);
struct ProcessDetails MPrintMemoryInfo(DWORD processID);
char* ResetAll();
