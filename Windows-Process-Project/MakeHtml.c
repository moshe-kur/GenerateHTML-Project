#include "StructProcessFun.h"
#include "MakeHtml.h"

struct ProcessForHTML* DProcessHead = NULL;
struct ProcessForHTML* DCurrProcess;
struct ProcessForHTML* DPrevprocess = NULL;

struct DllsForHTML* DDllHead = NULL;



int dllIdcount = 0;
int processIdCount = 0;


void MakeHtmlIndex(struct SnapshotHeader* header)
{

	struct Snapshot* tempsnap = header->HeadSnap;
	int dllcount = 0;

	int snapsNumbers = header->SnapshotNumbers;
	int processNumbers=header->HeadSnap->NumOfProcess;
	char name[300];

	removeMultiplies(header);

	makeDllHtml();
	makesnapHtml(header);


	FILE* f = fopen("index.html", "w");
	fputs("<!DOCTYPE html> <html> <head> <link rel=\"stylesheet\" href=\"style.css\" /> <script src = \"https://kit.fontawesome.com/2d599e81d6.js\"crossorigin = \"anonymous\"> </script> </head> <body> <nav> <a href = \"index.html\"><i class = \"fa-solid fa-house fa-lg\"></i> Home</a> <a href=\"aboutMe.html\"><i class=\"fa-solid fa-user fa-lg\"></i>About Me</a></nav> <header> <ul>  <li>MOSHE'S PROJECT</li> </ul> </header> <div class=\"main\"> <div class=\"sampleList\"> <p>SNAPSHOT LIST</p> <table class=\"snapshotListTable\"> <tr> <th class=\"myBtnHead\">ID</th> <th class=\"myBtnHead\">Link</th> <th class=\"myBtnHead\">Process Count</th> </tr> ", f);
	
	char filename[30];
	int forColor = 0;
	while (tempsnap !=NULL)
	{
		//
		if (forColor%2==0)
		{

			sprintf(name, "<tr> <td class=\"myBtn1\">%d</td> ", tempsnap->SnapshotID);
			fputs(name, f);

			sprintf(filename, "Snapshot%d.html", tempsnap->SnapshotID);

			sprintf(name, " <td class=\" myBtn1 \"><a href= \" %s \">Snapshot%d.html</a></td> ", filename, tempsnap->SnapshotID);
			fputs(name, f);
			sprintf(name, " <td class=\" myBtn1 \">%d</td> </tr> ", tempsnap->NumOfProcess);
			fputs(name, f);
		}
		else
		{
			sprintf(name, "<tr> <td class=\"myBtn2\">%d</td> ", tempsnap->SnapshotID);
			fputs(name, f);

			sprintf(filename, "Snapshot%d.html", tempsnap->SnapshotID);

			sprintf(name, " <td class=\" myBtn2 \"><a href= \" %s \">Snapshot%d.html</a></td> ", filename, tempsnap->SnapshotID);
			fputs(name, f);
			sprintf(name, " <td class=\" myBtn2 \">%d</td> </tr> ", tempsnap->NumOfProcess);
			fputs(name, f);
		}
		

		forColor++;
		tempsnap=tempsnap->Next;
	}

	fputs("</table> </div> <div class=\"dllList\"> <p>DLL'S LIST</p> <table class=\"dllListTable\"> <tr> <th class=\"myBtnHead\">Dll Name</th> <th class=\"myBtnHead\">Link</th> </tr> ", f);
	
	struct DllsForHTML* tempdll = DDllHead;
	int forColorrr = 0;
	while (tempdll!=NULL)
	{
		/////////
		

		if (forColorrr % 2 == 0)
		{

			sprintf(name, "<tr> <td class=\"myBtn1\">%s</td> ", tempdll->DllName);
			fputs(name, f);

			sprintf(filename, "Dll%d.html", tempdll->DllID);

			sprintf(name, " <td class= \" myBtn1 \" ><a href= \" %s \">Dll%d.html</a></td> </tr> ", filename, tempdll->DllID);
			fputs(name, f);
			
		}
		else
		{
			sprintf(name, "<tr> <td class=\"myBtn2\">%s</td> ", tempdll->DllName);
			fputs(name, f);

			sprintf(filename, "Dll%d.html", tempdll->DllID);

			sprintf(name, " <td class=\"myBtn2\"><a href=\" %s \">Dll%d.html</a></td> </tr>", filename, tempdll->DllID);
			fputs(name, f);
		}

		
		forColorrr++;

		tempdll = tempdll->Next;
	}

	

	fputs("</table> </div> </div> </body> </html>", f);

	fclose(f);

}

/*
void addDllToDi(char* dllName)
{
	dllIdcount++;

	currentItem = malloc(sizeof(struct Dictionary));
	if (head == NULL)
	{
		head = currentItem;
		currentItem->prev = NULL;
	}
	else
	{
		prevItem->next = currentItem;
		currentItem->prev = prevItem;
	}
	//currentItem->key = key;
	//currentItem->val = val;
	currentItem->next = NULL;
	prevItem = currentItem;
}
*/

void removeMultiplies(struct SnapshotHeader* header)
{
	struct Snapshot* sList = header->HeadSnap;
	struct ProcessDetails* currentProccess;
	struct Dlls* Check;
	struct DllsForHTML* Dll = NULL;
	struct DllsForHTML* curr =NULL;
	struct DllsForHTML* OldDll=NULL;
	


	while (sList != NULL)
	{
		currentProccess = sList->ProcessHead;
		//DLL'S LIST
		while (currentProccess != NULL)
		{
			Check = currentProccess->DllHead;

			while (Check != NULL)
			{
				
				//search if dll name exist in dictionary- add if not 
				if (searchDllByName(Check->DllName, DDllHead) != 0)
				{
					curr = (struct DllsForHTML*)malloc(sizeof(struct DllsForHTML)); //memory allocation
					if (!curr) //allocation check
					{
						//Log_Error(strerror(GetLastError()));   //log
						printf("Error of memory\n");
						return;
					}
					//curr->Head = NULL;
					strcpy(curr->DllName, Check->DllName); //copy name
					struct ProcessForHTML* currPro = (struct ProcessForHTML*)malloc(sizeof(struct ProcessForHTML));
					//TO-DO LOG
					currPro->Next = NULL;
					currPro->Prev = NULL;
					strcpy(currPro->ProcesName, currentProccess->ProcesName);

					dllIdcount++;
					curr->DllID = dllIdcount;
					
					currPro->ProcessID = currentProccess->ProcessID;
					

					curr->Head = currPro;

					if (DDllHead == NULL) 
					{
					    //if list is empty
						DDllHead = curr;
						curr->Prev = NULL;
					}
					else
					{ 
						//if not empty
						OldDll->Next = curr;
						curr->Prev = OldDll;
						//dictionary = curr;
					}
					curr->Next = NULL;
					OldDll = curr;

					
				}
				else
				{
					struct DllsForHTML* runDll = DDllHead;
					while (runDll!=NULL)
					{
						if (strcmp(runDll->DllName,Check->DllName)==0)
						{
							break;
						}

						runDll = runDll->Next;
					}


					struct ProcessForHTML* checkProcess = runDll->Head;
					struct ProcessForHTML* PrevcheckProcess = NULL;
					while (checkProcess!=NULL)
					{
						
						if (strcmp(checkProcess->ProcesName, currentProccess->ProcesName)==0)
						{
							break;
						}
						PrevcheckProcess = checkProcess;
						checkProcess = checkProcess->Next;
					}
					if (checkProcess==NULL)
					{
						struct ProcessForHTML* currPro = (struct ProcessForHTML*)malloc(sizeof(struct ProcessForHTML));
						//TO-DO LOG

						currPro->ProcessID = currentProccess->ProcessID;
						strcpy(currPro->ProcesName, currentProccess->ProcesName);
						
						
						PrevcheckProcess->Next = currPro;
						currPro->Prev = PrevcheckProcess;
						currPro->Next = NULL;
					}

				}
				Check = Check->Next;
			}
			currentProccess = currentProccess->Next;
		}
		sList = sList->Next;
	}
	//Log_Event("Dll multiplies removed.\n");
}

int searchDllByName(char Name[500], struct DllsForHTML* search) //search if dll item is in the search list by its name
{
	struct DllsForHTML* curr = search;

	if (curr == NULL ) //list is empty- not found- return 1
	{
		return 1;
	}

	while (curr != NULL)
	{
		if (Name == NULL)
		{
			return 0;
		}
		if (strcmp(curr->DllName, Name) == 0) //if found- return 0
		{

			return 0;
		}
		curr = curr->Next;
	}
	return 1; //not found- return 1
}

void makeDllHtml() 
{
	struct DllsForHTML* temp = DDllHead;
	char name[500];
	char fileName[30];
	int dllnum = 0;

	for (int i = 0; i < dllIdcount; i++)
	{
		
		dllnum++;
		sprintf(fileName, "Dll%d.html", dllnum);
		FILE* f = fopen(fileName, "w");

		fputs("<!DOCTYPE html> <html> <head> <link rel=\"stylesheet\" href=\"style.css\"/> <script src=\"https://kit.fontawesome.com/2d599e81d6.js\" crossorigin=\"anonymous\"> </script> </head> <body> <nav> <a href=\"index.html\"><i class=\"fa-solid fa-house fa-lg\"></i> Home</a> <a href=\"aboutMe.html\"><i class=\"fa-solid fa-user fa-lg\"></i>About Me</a> </nav> <header>", f);


		sprintf(name, " <h2> DLL NAME IS: %s </h2>", temp->DllName);
		fputs(name, f);

		sprintf(name, " </header> <table class=\"dllList\"> <tr> <th class=\"myBtnHead\">Process ID</th> <th class=\"myBtnHead\">Process NAME</th> </tr>");
		fputs(name, f);
		int numOfProcess = 0;
		while (temp->Head!=NULL)
		{
			numOfProcess++;
			if (numOfProcess % 2!=0)
			{

				sprintf(name, " <tr><td class=\"myBtn1\">%d</td><td class=\"myBtn1\">%s</td></tr>", temp->Head->ProcessID, temp->Head->ProcesName);
				fputs(name, f);
			}
			else
			{
				sprintf(name, " <tr><td class=\"myBtn2\">%d</td><td class=\"myBtn2\">%s</td></tr>", temp->Head->ProcessID, temp->Head->ProcesName);
				fputs(name, f);
			}
			temp->Head = temp->Head->Next;
		}
		temp = temp->Next;
		sprintf(name, "<h3 class=\"myBtn1 processBtn\">%d Process USED</h3></table> </body></html>", numOfProcess);
		fputs(name, f);


		fclose(f);
	}

}

void makesnapHtml(struct SnapshotHeader* header)
{
	struct Snapshot* tempSnap = header->HeadSnap;
	int snapsNumbers = header->SnapshotNumbers;
	char name[500];
	char fileName[30];

	for (int i = 0; i < snapsNumbers; i++)
	{

		sprintf(fileName, "Snapshot%d.html", tempSnap->SnapshotID);
		FILE* f = fopen(fileName, "w");

		fputs("<!DOCTYPE html> <html> <head> <link rel=\"stylesheet\" href=\"style.css\"/> <script src=\"https://kit.fontawesome.com/2d599e81d6.js\" crossorigin=\"anonymous\"> </script> </head> <body> <nav> <a href=\"index.html\"><i class=\"fa-solid fa-house fa-lg\"></i> Home</a> <a href=\"aboutMe.html\"><i class=\"fa-solid fa-user fa-lg\"></i>About Me</a> </nav> <header>", f);


		sprintf(name, " <h2> %s: AT %s </h2>", fileName, tempSnap->ProcessHead->time);
		fputs(name, f);

		sprintf(name, " </header> <table class=\"processList\"> <tr> <th class=\"myBtnHead\">ID</th> <th class=\"myBtnHead processNameBTN\">Process Name</th> <th class=\"myBtnHead\">PageFaultCount</th> <th class=\"myBtnHead\">WorkingSetSize</th> <th class=\"myBtnHead\">QuotaPagedPoolUsage</th> <th class=\"myBtnHead\">QuotaPeakPagedPoolUsage</th> <th class=\"myBtnHead\">PagefileUsage</th> <th class=\"myBtnHead\">Dll Count</th> </tr>");
		fputs(name, f);
		int numOfProcess = 0;
		struct ProcessDetails* tempProcess = tempSnap->ProcessHead;
		while (tempProcess !=NULL)
		{
			numOfProcess++;
			if (tempProcess->ProcessNumber % 2!=0)
			{

				sprintf(name, "<tr><td class=\"myBtn1\">%d</td> <td class=\"myBtn1 nameBtn\">%s</td> <td class=\"myBtn1\">%lu</td> <td class=\"myBtn1\">%zu</td> <td class=\"myBtn1\">%zu</td> <td class=\"myBtn1\">%zu</td><td class=\"myBtn1\">%zu</td> <td class=\"myBtn1\"> <div class=\"dropdown\"> <button class=\"dropbtn\">%d</button> <div class=\"dropdown-content\">", tempProcess->ProcessID, tempProcess->ProcesName, tempProcess->pmc.PageFaultCount, tempProcess->pmc.WorkingSetSize, tempProcess->pmc.QuotaPagedPoolUsage, tempProcess->pmc.QuotaPeakPagedPoolUsage, tempProcess->pmc.PagefileUsage, tempProcess->NumberOfDlls);
				fputs(name, f);
				struct Dlls* tempDlls = tempProcess->DllHead;
				while (tempDlls!=NULL)
				{
					sprintf(name, "<p>%s</p>", tempDlls->DllName);
					fputs(name, f);
					tempDlls = tempDlls->Next;
				}
				fputs("</div></div></td></tr>", f);
			}
			else
			{

				sprintf(name, " <tr><td class=\"myBtn2\">%d</td> <td class=\"myBtn2 nameBtn\">%s</td> <td class=\"myBtn2\">%lu</td> <td class=\"myBtn2\">%zu</td> <td class=\"myBtn2\">%zu</td> <td class=\"myBtn2\">%zu</td><td class=\"myBtn2\">%zu</td> <td class=\"myBtn2\"> <div class=\"dropdown\"> <button class=\"dropbtn\">%d</button> <div class=\"dropdown-content\">", tempProcess->ProcessID, tempProcess->ProcesName, tempProcess->pmc.PageFaultCount, tempProcess->pmc.WorkingSetSize, tempProcess->pmc.QuotaPagedPoolUsage, tempProcess->pmc.QuotaPeakPagedPoolUsage, tempProcess->pmc.PagefileUsage, tempProcess->NumberOfDlls);
				fputs(name, f);
				struct Dlls* tempDlls = tempProcess->DllHead;
				while (tempDlls != NULL)
				{
					sprintf(name, "<p>%s</p>", tempDlls->DllName);
					fputs(name, f);
					tempDlls = tempDlls->Next;
				}
				fputs("</div></div></td></tr>", f);

			}

			tempProcess = tempProcess->Next;
		}
		
		sprintf(name, "<h3 class=\"myBtn1 processBtn\">%d Process USED</h3></table> </body></html>", tempSnap->NumOfProcess);
		fputs(name, f);
		fclose(f);

		tempSnap = tempSnap->Next;
	}
	
}
