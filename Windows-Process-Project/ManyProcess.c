



#include "LogFun.h"
#include "StructProcessFun.h"
#include "ManyProcess.h"
#pragma warning(disable:4996)


void Make20Loop(int NumberOfLoop)
{
	struct Snapshot* SaveSnap=MakeOneSnapshot();
	struct ProcessDetails* SaveCurrProcess = SaveSnap->ProcessHead;
	struct Dlls* SaveDll = SaveCurrProcess->DllHead;
	//data
	for (int i = 0; i < 4; i++)
	{
		//להוריד איידי בסוף הריצה ולשנות את הנקסט של הסנאפ שנשמר לנאל
		struct Snapshot* NewLoopSnap=MakeOneSnapshot();
		struct ProcessDetails* NewCurrProcess = NewLoopSnap->ProcessHead;
		while (NewCurrProcess!=NULL)
		{
			//לבדוק גם בלי שם-בדיקה רק עם איידי
			if (NewCurrProcess->ProcesName == SaveCurrProcess->ProcesName && NewCurrProcess->ProcessID == SaveCurrProcess->ProcessID)
			{
				struct Dlls* NewDll = NewCurrProcess->DllHead;
				while (NewDll!=NULL)
				{
					if (NewDll->DllName!=SaveDll->DllName)
					{
						if (SaveDll->Next==NULL)
						{
							//add dll to save dlls
							struct Dlls* AddDll = (struct Dlls*)malloc(sizeof(struct Dlls));
							// AddDll = NewDll;
							AddDll->DllID = NewDll->DllID;
							strcpy(AddDll->DllName, NewDll->DllName);
							SaveDll->Next = AddDll;
							AddDll->Prev = SaveDll;
							SaveCurrProcess->NumberOfDlls++;
							NewDll = NewDll->Next;
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
					}
				}
			}
			//Here if they NOT have the same name and id
			else
			{

				SaveCurrProcess = SaveCurrProcess->Next;
			}


			// NewCurrProcess = NewCurrProcess->Next;
		};
	};
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