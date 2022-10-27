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
int ProcessNumber =0;

/*void add(struct ProcessDetails ret)
{
	ret = malloc(sizeof(struct ProcessDetails));
	if (ret)
	{
		if (ProcessHead == NULL)
		{
			ProcessHead = ret;
			ret->Prev = NULL;
		}
		else
		{
			LastProcess->Next = ret;
		}
		ret->Next = NULL;
		LastProcess = ret;
	}
	else
	{
		//error to log - last error or memory error
	}
}*/
/*struct Dictionary* search(int key)
{
	
	currentProcess = Head;
	while (currentProcess->key != key)
	{
		if (currentProcess->Next != NULL)
		{
			currentProcess = currentProcess->Next;
		}
		else
		{
			return NULL;
		}
	}

	return currentProcess;
	
}*/
/*void rremove(int key)
{
	
	currentProcess = search(key);

	if (currentProcess)
	{
		if (currentProcess == Head && currentProcess->Next == NULL)
		{
			free(currentProcess);
		}
		else if (currentProcess == Head)
		{
			Head = currentProcess->Next;
			free(currentProcess);
		}
		else if (currentProcess->Next != NULL)
		{
			currentProcess->Next->Prev = currentProcess->Prev;
			currentProcess->Prev->Next = currentProcess->Next;
			free(currentProcess);
		}
		else if (currentProcess->Next == NULL)
		{
			currentProcess->Prev->Next = NULL;
			free(currentProcess);
		}
	}

	//פקודת הדפסת הפריט שנמצא
	//להעביר לכאן את שחרור המצביע כדי שיהיה אפשר להדפיס אותו לפני שחרור

	
}*/
/*void freeDictionary()
{
	//להוסיף פוקציה של לולאה שמשחררת האת הזיכרון של כל התאים
}*/
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

	// מספר הפרוססים שרצו במערכת שמור כאנסינג לונג
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
		//META-DATA
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

		//Get process name
		char ProcessName[MAX_PATH];
		size_t numConverted;
		wcstombs_s(&numConverted, ProcessName, MAX_PATH, tFoundProcessName, MAX_PATH);
		// Add process name to the struct
		sprintf(CurrentProcess->ProcesName, "%s", ProcessName);
		//Add id to process struct
		CurrentProcess->ProcessID = (int)processID;
		CurrentProcess->SnapshotNumber = SnapNum;
		ProcessNumber++;
		CurrentProcess->ProcessNumber = ProcessNumber;
		//Add time to process struct
		strcpy(CurrentProcess->time, checkTime());
		//DATA
		CurrentProcess->pmc.PageFaultCount = pmc.PageFaultCount;
		CurrentProcess->pmc.WorkingSetSize = pmc.WorkingSetSize;
		CurrentProcess->pmc.QuotaPagedPoolUsage = pmc.QuotaPagedPoolUsage;
		CurrentProcess->pmc.QuotaPeakPagedPoolUsage = pmc.QuotaPeakPagedPoolUsage;
		CurrentProcess->pmc.PagefileUsage = pmc.PagefileUsage;
	}


	// Get Dlls List
	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		int numDll = 0;
		
		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			// Get the full path to the module's file.

			if (GetModuleFileNameEx(hProcess, hMods[i], tFoundDllName, MAX_PATH))
			{
				// * Get the module name and handle value.
				CurrDll = (struct Dlls*)malloc(sizeof(struct Dlls));
			    numDll++;

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

				//DATA
				// Convert wChar to regular char array (string)
				char dllName[MAX_PATH];
				size_t numConverted;
				wcstombs_s(&numConverted, dllName, MAX_PATH, tFoundDllName, MAX_PATH);
				sprintf(CurrDll->DllName, "%s", dllName);
			}
		}
		if (numDll==0)
		{
			CurrentProcess->NumberOfDlls = numDll;
			CurrentProcess->DllHead = NULL;
		}
		else
		{

		CurrentProcess->NumberOfDlls = numDll;
		}

		//printf("%s\n his id: %d,Have a %d Dlls\n", CurrentProcess->ProcesName, CurrentProcess->ProcessNumber, numDll);
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
		return;
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