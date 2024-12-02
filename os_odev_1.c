#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD parentPID = GetCurrentProcessId(); // Parent'ın PID'sinin alınması

    // STARTUPINFO ve PROCESS_INFORMATION yapılarını sıfırla
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Çalıştırılacak komut: `type ornek.txt`
    TCHAR command[] = _T("cmd.exe /C type ornek.txt");

    // Child process oluştur ve child processin dosya içeriğini ekrana yazdırması
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
        printf("\nCreateProcess basarisiz(%d).\n", GetLastError()); // Child process oluşturulamadığında hata mesajı
        return 1;
    }

    // Parent process: Child process bilgilerini yazdır
    printf("\nParent Process PID: %lu \n", parentPID);                   // Parent process id
    printf("\nChild Process olusturuldu PID: %lu \n\n", pi.dwProcessId); // Child process id

    WaitForSingleObject(pi.hProcess, INFINITE); // Child process'in bitmesini bekleme

    DWORD exitCode; // çıkış durumunun kontrolu
    if (GetExitCodeProcess(pi.hProcess, &exitCode))
    {
        printf("\nChild Process tamamlandi, cikis durumu: %ld\n", exitCode); // Hatasız bir şekilde çalışırsa
    }
    else
    {
        printf("\nChild Process'in cikis durumu alinamadi.\n"); // Hatalı çalışırsa
    }

    // Handle'ları kapat
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
