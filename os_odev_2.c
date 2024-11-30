#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void child_process()
{
    // Child process içinde dosya açma işlemi
    FILE *file = fopen("ornek.txt", "r");
    if (file == NULL)
    {
        // Dosya açılamazsa abort() ile zorla çıkış
        perror("Dosya aciamadi");
        abort(); // Hata durumu ve zorla çıkış
    }
    perror("Dosya hatasiz acildi");
    // Dosya başarıyla açıldı, düzgün çıkış
    fclose(file);
    exit(0); // Düzgün çıkış
}

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;

    // Başlangıç bilgileri sıfırlanıyor
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Child process için bir işlem başlatılıyor
    if (CreateProcess(
            NULL,                    // Uygulama adı
            "cmd /c type ornek.txt", // Çalıştırılacak uygulama adı
            NULL,                    // Proses güvenliği
            NULL,                    // Thread güvenliği
            FALSE,                   // İletişim kanalları
            0,                       // İşlem bayrağı
            NULL,                    // Çevre değişkenleri
            NULL,                    // Çalışma dizini
            &si,                     // Başlangıç bilgileri
            &pi                      // Process bilgileri
            ) == 0)
    {
        printf("Child process baslatilamadi. Hata: %lu\n", GetLastError());
        return 1;
    }

    // Child process sonlanana kadar bekleniyor
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Çıkış durumu kontrol ediliyor
    GetExitCodeProcess(pi.hProcess, &exitCode);
    if (exitCode == 0)
    {
        printf("Child process hatasiz sonlandi, exit kodu: %lu\n", exitCode);
    }
    else
    {
        printf("Child process hata ile sonlandi, exit kodu: %lu\n", exitCode);
    }

    // Child process ve kaynakları serbest bırakma
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    child_process();
    return 0;
}
