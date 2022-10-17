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
	// int NumOfDll;  צריך?
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
struct SnapshotHeader* HeadSnapheder;
struct Snapshot* CurrSnap;
struct Snapshot* PrevSnap;
struct ProcessDetails* CurrentProcess;
struct ProcessDetails* LastProcess;
struct Dlls* CurrDll;
struct Dlls* PrevDll;
int SnapNum;
int ProcessNumber;

//loop snap
int LoopNumber;
void MGetProcessesInfo(char choice);
struct ProcessDetails MPrintMemoryInfo(DWORD processID);

