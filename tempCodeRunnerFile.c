#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD parentPID = GetCurrentProcessId(); // Parent'ın PID'si

    // STARTUPINFO ve PROCESS_INFORMATION yapılarını sıfırla
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Çalıştırılacak komut: `type ornek.txt`
    TCHAR command[] = _T("cmd.exe /C type ornek.txt");

    // Child process oluştur
    if (!CreateProcess(
            NULL,
            command,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return 1;
    }

    // Parent process: Child process bilgilerini yazdır
    printf("Parent Process: PID: %lu \n", parentPID);
    printf("Child Process olusturuldu: PID: %lu \n", pi.dwProcessId);

    // Child process'in bitmesini bekle
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    if (GetExitCodeProcess(pi.hProcess, &exitCode))
    {
        printf("Child Process tamamlandi, cikis durumu: %ld\n", exitCode);
    }
    else
    {
        printf("Child Process'in cikis durumu alinamadi.\n");
    }

    // Handle'ları kapat
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
