#include <windows.h> 
VOID CALLBACK MyTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime); 

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow) 
{ 
        SetTimer(NULL, 0, TIMER_LAP, TIMERPROC MyTimerProc); 
        while(GetMessage(&Msg, 0, 0, 0)) 
        { 
                TranslateMessage(&Msg); 
                DispatchMessage(&Msg); 
        } 
        return(1); 
} 

VOID CALLBACK MyTimerProc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime) 
{ 
        KillTimer(hWnd, idEvent); // Evitamos posible colapso si el sistema va sobrecargado 

        // Aquí pones tu código de lectura o las llamadas a las funciones para leer el puerto 

        // Relanzamos el Timer 
        SetTimer(hWnd, idEvent, TIMER_LAP, TIMERPROC MyTimerProc); 
} 

