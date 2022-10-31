#include "LogFun.h"
#include "StructProcessFun.h"
#pragma warning(disable:4996)

struct SnapshotHeader* HeadSnapheder =NULL;
struct Snapshot* CurrSnap;
struct Snapshot* PrevSnap;
struct ProcessDetails* CurrentProcess;
struct ProcessDetails* LastProcess;
struct Dlls* CurrDll;
struct Dlls* PrevDll;
int SnapNum=0;
int ProcessNumber;


struct Snapshot* MakeOneSnapshot()
{
	// Get Processes
	ProcessNumber = 0;
	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	// * Receive all process ID and put in aProcesses Array
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		//TO-DO!!
		// Error. Write to log
		return 0;
	}

	// Calculate how many process identifiers were returned.
	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the memory usage for each process
	// *Loop of all processes
	CurrSnap = (struct Snapshot*)malloc(sizeof(struct Snapshot));
	if (!CurrSnap)
	{
		//Log
		return 0;
	}
	SnapNum++;
	CurrSnap->ProcessHead = NULL;
	for (i = 0; i < cProcesses; i++)
	{
		PrintMemoryInfo(aProcesses[i]);
	}
	
	if (HeadSnapheder==NULL)
	{
		MakeHeaderSnap();
		HeadSnapheder->SnapshotNumbers = 1;
		HeadSnapheder->HeadSnap = CurrSnap;
		CurrSnap->Prev = NULL;
	}
	else
	{
		HeadSnapheder->SnapshotNumbers = SnapNum;
		PrevSnap->Next = CurrSnap;
		CurrSnap->Prev = PrevSnap;

	}
	CurrSnap->Next = NULL;
	CurrSnap->NumOfProcess = ProcessNumber;
	CurrSnap->SnapshotID = SnapNum;
	PrevSnap = CurrSnap;

	return CurrSnap;
}

struct ProcessDetails PrintMemoryInfo(DWORD processID)
{


	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	// Open process in order to receive information
	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
	{
		// Write to log a warning
		return;
	}

	HMODULE hMods[1024];
	DWORD cbNeeded;
	TCHAR tFoundProcessName[MAX_PATH];
	TCHAR tFoundDllName[MAX_PATH];
	// Get Process Name
	if (GetModuleFileNameEx(hProcess, 0, tFoundProcessName, MAX_PATH))
	{
		// At this point, buffer contains the full path to the executable
		
	}
	else
	{
		//TO-DO!!
		// You better call GetLastError() here
		// Write To log
	}

	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		CurrentProcess = (struct ProcessDetails*)malloc(sizeof(struct ProcessDetails));
		// process META-DATA
		if (CurrSnap->ProcessHead == NULL)
		{
			CurrSnap->ProcessHead = CurrentProcess;
			CurrentProcess->Prev = NULL;
		}
		else
		{
			LastProcess->Next = CurrentProcess;
			CurrentProcess->Prev = LastProcess;

		}
		CurrentProcess->Next = NULL;
		CurrentProcess->DllHead = NULL;
		LastProcess = CurrentProcess;

		//process DATA
		
		//Get process name
		char ProcessName[MAX_PATH];
		size_t numConverted;
		wcstombs_s(&numConverted, ProcessName, MAX_PATH, tFoundProcessName, MAX_PATH);

		// Add process name to the struct
		sprintf(CurrentProcess->ProcesName, "%s", ProcessName);

		//Add time to process struct
		strcpy(CurrentProcess->time, checkTime());

		CurrentProcess->ProcessID = (int)processID;
		CurrentProcess->SnapshotNumber = SnapNum;
		ProcessNumber++;
		CurrentProcess->ProcessNumber = ProcessNumber;

		CurrentProcess->pmc.PageFaultCount = pmc.PageFaultCount;
		CurrentProcess->pmc.WorkingSetSize = pmc.WorkingSetSize;
		CurrentProcess->pmc.QuotaPagedPoolUsage = pmc.QuotaPagedPoolUsage;
		CurrentProcess->pmc.QuotaPeakPagedPoolUsage = pmc.QuotaPeakPagedPoolUsage;
		CurrentProcess->pmc.PagefileUsage = pmc.PagefileUsage;
	}


	// Get Dlls List
	int numDll = 0;
	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		
		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			// Get the full path to the module's file.

			if (GetModuleFileNameEx(hProcess, hMods[i], tFoundDllName, MAX_PATH))
			{
				// * Get the module name and handle value.
				CurrDll = (struct Dlls*)malloc(sizeof(struct Dlls));
			    numDll++;

				//DATA
				
				// Convert wChar to regular char array (string)
				char dllName[MAX_PATH];
				size_t numConverted;
				wcstombs_s(&numConverted, dllName, MAX_PATH, tFoundDllName, MAX_PATH);
				sprintf(CurrDll->DllName, "%s", dllName);
				//Add ID
				CurrDll->DllID = numDll;

				//META-DATA
				if (CurrentProcess->DllHead == NULL)
				{
					CurrentProcess->DllHead = CurrDll;
					CurrDll->Prev = NULL;
				}
				else
				{
					PrevDll->Next = CurrDll;
					CurrDll->Prev = PrevDll;

				}
				CurrDll->Next = NULL;
				PrevDll = CurrDll;

			}
		}
		
	}
	if (numDll == 0)
	{
		CurrentProcess->NumberOfDlls = numDll;
		CurrentProcess->DllHead = NULL;
	}
	else
	{

		CurrentProcess->NumberOfDlls = numDll;
	}
	//CurrentProcess->NumberOfDlls = numDll;
	CloseHandle(hProcess);
}

void MakeHeaderSnap()
{
	HeadSnapheder = (struct SnapshotHeader*)malloc(sizeof(struct SnapshotHeader));
	if (!HeadSnapheder)
	{
		//LOG
		return 0;
	}

}
char* ResetAll() 
{
	if (HeadSnapheder==NULL)
	{
		return "Memory alredy clear\n";
	}
	else
	{
		CurrSnap = HeadSnapheder->HeadSnap;
		while (CurrSnap)
		{
			CurrentProcess = CurrSnap->ProcessHead;
			while (CurrentProcess)
			{
				CurrDll = CurrentProcess->DllHead;
				while (CurrDll)
				{
					//clear all dll
					if (CurrDll->Next!=NULL)
					{
						CurrDll = CurrDll->Next;
						free(CurrDll->Prev);
					}
					else
					{
						free(CurrDll);
						break;
					}
				}
				//clear all process
				if (CurrentProcess->Next!=NULL)
				{
					CurrentProcess = CurrentProcess->Next;
						free(CurrentProcess->Prev);
				}
				else
					{
						free(CurrentProcess);
						break;
					}
				}
			if (CurrSnap->Next != NULL)
			{
				CurrSnap = CurrSnap->Next;
				free(CurrSnap->Prev);
			}
			else
			{
				free(CurrSnap);
				break;
			}
		}
			free(HeadSnapheder);
	}
	HeadSnapheder = NULL;
	SnapNum = 0;
	return "Memory is clear now\n";
}