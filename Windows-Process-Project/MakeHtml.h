

struct DllsForHTML
{
	//META-DATA
	struct DllsForHTML* Next;
	struct DllsForHTML* Prev;
	//DATA
	struct ProcessForHTML* Head;
	int DllID;
	char DllName[MAX_PATH];
};
struct ProcessForHTML
{
	//META-DATA
	struct ProcessForHTML* Next;
	struct ProcessForHTML* Prev;
	//DATA
	int ProcessID;
	char ProcesName[MAX_PATH];
};

void addDllToDi(char* dllName);



void makeDllHtml();

void removeMultiplies(struct SnapshotHeader* header);
void makesnapHtml(struct SnapshotHeader* header);
//void makeDllHtml();
