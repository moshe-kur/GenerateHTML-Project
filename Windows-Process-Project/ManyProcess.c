#include "LogFun.h"
#include "StructProcessFun.h"
#include "ManyProcess.h"
#pragma warning(disable:4996)




struct Snapshot* Make20Loop(int NumberOfLoop)
{

	struct Snapshot* SaveSnap=MakeOneSnapshot();
	struct ProcessDetails* SaveCurrProcess = SaveSnap->ProcessHead;
	struct Dlls* SaveDll = SaveCurrProcess->DllHead;
	//data
	for (int i = 0; i < NumberOfLoop; i++)
	{
		//להוריד איידי בסוף הריצה ולשנות את הנקסט של הסנאפ שנשמר לנאל
		struct Snapshot* NewLoopSnap=MakeOneSnapshot();
		struct ProcessDetails* NewCurrProcess = NewLoopSnap->ProcessHead;
		while (NewCurrProcess!=NULL)
		{
			//לבדוק גם בלי שם-בדיקה רק עם איידי
			if (strcmp(NewCurrProcess->ProcesName,SaveCurrProcess->ProcesName)==0 && NewCurrProcess->ProcessID == SaveCurrProcess->ProcessID)
			{
				//+= info
				//Add info from new (current) snap to old (save)
				SaveCurrProcess->pmc.PageFaultCount += NewCurrProcess->pmc.PageFaultCount;
				SaveCurrProcess->pmc.WorkingSetSize += NewCurrProcess->pmc.WorkingSetSize;
				SaveCurrProcess->pmc.QuotaPagedPoolUsage += NewCurrProcess->pmc.QuotaPagedPoolUsage;
				SaveCurrProcess->pmc.QuotaPeakPagedPoolUsage += NewCurrProcess->pmc.QuotaPeakPagedPoolUsage;
				SaveCurrProcess->pmc.PagefileUsage += NewCurrProcess->pmc.PagefileUsage;
				
				//meta-data


				struct Dlls* NewDll = NewCurrProcess->DllHead;
				while (NewDll!=NULL)
				{
					if (SaveDll == NULL)
					{
						//to enter all the new dll to the savedll
						//malloc
						//NewCurrProcess = NewCurrProcess->Next;
						struct Dlls* AddDll = (struct Dlls*)malloc(sizeof(struct Dlls));
						AddDll->DllID = NewDll->DllID;
						strcpy(AddDll->DllName, NewDll->DllName);
						SaveDll = AddDll;
						AddDll->Prev = NULL;
						AddDll->Next = NULL;
						SaveCurrProcess->NumberOfDlls++;
						NewDll = NewDll->Next;
						SaveDll = SaveCurrProcess->DllHead;


					}
					else if (strcmp(NewDll->DllName,SaveDll->DllName)!=0)
					{
						if (SaveDll->Next==NULL)
						{
							//curr == NULL
							//add dll to save dlls
							//printf("MAke NEw DLL");
							struct Dlls* AddDll = (struct Dlls*)malloc(sizeof(struct Dlls));
							AddDll->DllID = NewDll->DllID;
							strcpy(AddDll->DllName, NewDll->DllName);
							SaveDll->Next = AddDll;
							AddDll->Prev = SaveDll;
							SaveCurrProcess->NumberOfDlls++;
							NewDll = NewDll->Next;
							SaveDll = SaveCurrProcess->DllHead;

						}
						else
						{
						
							SaveDll = SaveDll->Next;
							
						}
					}
					//else is if they are the same name
					else
					{
						NewDll = NewDll->Next;
						SaveDll = SaveCurrProcess->DllHead;
					}

				}
				//new-next and save back to top
				NewCurrProcess = NewCurrProcess->Next;
				SaveCurrProcess = SaveSnap->ProcessHead;

			}
			//Here if they NOT have the same name and id
			else
			{


				if (SaveCurrProcess->Next==NULL)
				{
					//new process to save process
					
					//Make new process
					//printf("MAke NEw PROCESS");
					struct ProcessDetails* AddProcess = (struct ProcessDetails*)malloc(sizeof(struct ProcessDetails));
					AddProcess->ProcessID = NewCurrProcess->ProcessID;
					AddProcess->ProcessNumber = NewCurrProcess->ProcessNumber;
					AddProcess->NumberOfDlls = NewCurrProcess->NumberOfDlls;
					AddProcess->SnapshotNumber = NewCurrProcess->SnapshotNumber;
					strcpy(AddProcess->ProcesName, NewCurrProcess->ProcesName);
					strcpy(AddProcess->time, NewCurrProcess->time);
					//Add 1 num to snap (number of process)
					SaveSnap->NumOfProcess++;
					//Copy pmc
					AddProcess->pmc.PageFaultCount = NewCurrProcess->pmc.PageFaultCount;
					AddProcess->pmc.WorkingSetSize = NewCurrProcess->pmc.WorkingSetSize;
					AddProcess->pmc.QuotaPagedPoolUsage = NewCurrProcess->pmc.QuotaPagedPoolUsage;
					AddProcess->pmc.QuotaPeakPagedPoolUsage = NewCurrProcess->pmc.QuotaPeakPagedPoolUsage;
					AddProcess->pmc.PagefileUsage = NewCurrProcess->pmc.PagefileUsage;
					//meta-data
					SaveCurrProcess->Next = AddProcess;
					AddProcess->Prev = SaveCurrProcess;
					AddProcess->Next = NULL;


					NewCurrProcess = NewCurrProcess->Next;
					SaveCurrProcess = SaveSnap->ProcessHead;
				}
				else
				{
				
				SaveCurrProcess = SaveCurrProcess->Next;
				}
			}


			//NewCurrProcess = NewCurrProcess->Next;
		};
		//i need?
		//SaveCurrProcess = NewLoopSnap->ProcessHead;
	};
	return SaveSnap;
}



/*
struct Dictionary* search(int key)
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

}
void rremove(int key)
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


}
void freeDictionary()
{
	//להוסיף פוקציה של לולאה שמשחררת האת הזיכרון של כל התאים
}
*/