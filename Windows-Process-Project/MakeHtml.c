#include "StructProcessFun.h"
#include "MakeHtml.h"


void MakeHtmlIndex(struct SnapshotHeader* header)
{
	int snapsNumbers = header->SnapshotNumbers;
	int processNumbers=header->HeadSnap->NumOfProcess;
	char name[100];
	FILE* f = fopen("index.html", "w");

	fputs("<!DOCTYPE html> <html> <head> <link rel=\"stylesheet\" href=\"style.css\" /> <script src = \"https://kit.fontawesome.com/2d599e81d6.js\"crossorigin = \"anonymous\"> </script> </head> <body> <nav> <a href = \"index.html\"><i class = \"fa-solid fa-house fa-lg\"></i> Home</a> <a href=\"aboutMe.html\"><i class=\"fa-solid fa-user fa-lg\"></i>About Me</a></nav> <header> <ul> ", f);


	for (int i = 0; i < 3; i++)
	{
		if (i==0)
		{
			sprintf(name, " <li> Process Numbers:%d </li>", processNumbers);
		fputs(name, f);

		}
		else if (i==1)
		{
			sprintf(name, " <li> Dll Numbers:555 </li>");
			fputs(name, f);
		}
		else if (i ==2)
		{
			sprintf(name, " <li> Memory count:123455 </li>");
			fputs(name, f);
		}

	}


	


	fputs("</ul></header> </body> </html>", f);

	fclose(f);

}
