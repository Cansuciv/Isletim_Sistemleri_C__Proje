#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    STARTUPINFO si;         // child process’in başlatılacağı ortam hakkında bilgi verir.
    PROCESS_INFORMATION pi; // yeni bir işlem başlatıldığında işlem hakkında bilgi sağlar (handle’lar, işlem kimlikleri vb.).

    // STARTUPINFO ve PROCESS_INFORMATION yapılarının sıfırlanması.
    ZeroMemory(&si, sizeof(si)); // STARTUPINFO yapısının tüm üyelerini sıfırlamak.
    si.cb = sizeof(si);          // STARTUPINFO yapısının boyutunu belirtmek.
    ZeroMemory(&pi, sizeof(pi)); // PROCESS_INFORMATION yapısının tüm üyelerini sıfırlamak.

    // Parent process ID
    DWORD parentProcessId = GetCurrentProcessId();
    printf("\nAna Process ID: %lu\n", parentProcessId);

    // Child process'in oluşturulması
    if (!CreateProcess(              // fork() windows karşılığı
            NULL,                    // Program adı (NULL olursa komut satırını kullanır).
            "cmd /c type ornek.txt", // Çalıştırılacak komut (örneğin, dosya içeriğini yazdırma).
            NULL,                    // Process için güvenlik özellikleri.
            NULL,                    // Thread için güvenlik özellikleri.
            FALSE,                   // Child process'in parent ile etkileşimi (miras).
            0,                       // Durum bayrakları
            NULL,                    // Çevre değişkenleri
            NULL,                    // Çalışma dizini
            &si,                     // STARTUPINFO yapısı
            &pi                      // PROCESS_INFORMATION yapısı
            ))
    {
        printf("\nProcess olusturulamadi. Hata kodu: %d\n", GetLastError());
        return 1; // Başarısız olduğunda hata kodu döndür
    }

    // Child process ID
    printf("\nChild Process ID: %lu\n", pi.dwProcessId);

    // Parent process, child process'in bitmesini bekler
    WaitForSingleObject(pi.hProcess, INFINITE); // wait() windows karşılığı

    printf("\nChild process tamamlandi.");

    // Kaynakları serbest bırak
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
