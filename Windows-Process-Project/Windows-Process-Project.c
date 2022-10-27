#include "LogFun.h"
#include "FileFun.h"
#include "StructProcessFun.h"
#include "ManyProcess.h"
#pragma warning(disable:4996)
	 

struct SnapshotHeader* HeadSnapheder;
struct Snapshot* NowSnap;



int main()
{
	startclean();
	Log("START LOG PROJECT");


	printf("Hi Dear User \nWhat would you like to do?\n T-Take One SnapShot\n M-Make Generate HTML\n R-Reset ALL Snapshot Memory\n S-Save To File\n L-Load From File\n P-Print all list\n E-to EXIT\n");

	char userResponse =0;
	while (userResponse != 'E')
	{
		
		scanf(" %c", &userResponse);

		switch (userResponse)
		{
		case 'T':
			MakeOneSnapshot();
			printf("One snapshot Add to list\n");

			break;
		case 'M':

			break;
		case 'R':
			printf("%s", ResetAll());
			
			break;
		case 'S':
			MakeFileStruct();

			break;
		case 'L':
			ReadFromFile();
			break;
		case 'P': 
			if (HeadSnapheder!=NULL)
			{
				NowSnap = HeadSnapheder->HeadSnap;
				while (NowSnap != NULL)
				{
					printf("id snap: %d\nnum of process is:%d\n", NowSnap->SnapshotID, NowSnap->NumOfProcess);
					NowSnap = NowSnap->Next;
				};
			}
			else
			{
				printf("The memory is empty!!\n");

			}
			break;
		case 'E': printf("Thank you for use our Great service. See you next time. Drink only water\n");
			//
			break;

			
		}
				printf("\nHi Dear User \nWhat would you like to do?\n T-Take One SnapShot\n M-Make Generate HTML\n R-Reset ALL Snapshot Memory\n S-Save To File\n L-Load From File\n P-Print all list\n E-to EXIT\n");
	}

	
	//TO-DO איפוס משתנים של צבירות פרוססים ודיאלאלים ואיפוס איידי של משתנים
	//struct Snapshot* first = Make20Loop(4);

	Log("END LOG PROJECT");
	return 0;
}
