#include "LogFun.h"
#include "StructProcessFun.h"
#pragma warning(disable:4996)
int main()
{
	startclean();
	Log("START LOG PROJECT");
	//TO-DO איפוס משתנים של צבירות פרוססים ודיאלאלים ואיפוס איידי של משתנים
	printf("START 1 SNAP\n");
	struct Snapshot* first=MakeOneSnapshot();
	printf("FINISH 1 SNAP\n");
	printf("START 2 SNAP\n");
	MakeOneSnapshot();
	printf("FINISH 2 SNAP\n");
	MakeOneSnapshot();

	CurrSnap = first;
	while (CurrSnap!=NULL)
	{
	printf("id snap: %d\nnum of process is:%d\n", CurrSnap->SnapshotID, CurrSnap->NumOfProcess);
	CurrSnap = CurrSnap->Next;
	}

	Log("END LOG PROJECT");


	/*
	Head = NULL;
	Tail = NULL;

	struct Item* popedItem;

	char userResponse = 0;
	while (userResponse != 'E')
	{
		printf("Hi Dear User \n What would you like to do?\n A-to add new item  P-Print all list R-Pop next item E-to exit");
		userResponse = getchar();

		switch (userResponse)
		{
		case 'A':

			Push(rand(), rand());
			break;
		case 'P': PrintList();
			break;
		case 'R':

			//	popedItem = Pop();

				//printf("Item %d %d %d", popedItem->id, popedItem->val, popedItem->val2);
			free(popedItem);
			break;
		case 'E': printf("Thank you for use our Great service. See you next time. Drink only water\n");
			break;

		default:
			printf("Wrong selection. Try be more sharp\n");
			break;
		}
	}

	*/

	return 0;
}
