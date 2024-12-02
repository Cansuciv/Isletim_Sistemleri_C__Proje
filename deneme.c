#include <windows.h>
#include <stdio.h>

int main()
{
    STARTUPINFO si = {sizeof(si)}; // İşlem başlangıç bilgileri
    PROCESS_INFORMATION pi;        // İşlem ve iş parçacığı bilgileri

    // Yeni bir notepad.exe işlemi başlatır
    if (CreateProcess(
            NULL,          // Çalıştırılacak programın yolu (NULL ise komut satırı kullanılır)
            "notepad.exe", // Çalıştırılacak programın adı
            NULL, NULL,    // Güvenlik özellikleri
            FALSE,         // İş parçacıkları miras alınmasın
            0,             // Ek işlem bayrakları
            NULL, NULL,    // Ortam değişkenleri ve çalışma dizini
            &si, &pi))
    { // Başlangıç bilgisi ve işlem bilgisi
        printf("Yeni bir islem olusturuldu.\n");

        // Çocuk işlem tamamlanana kadar bekle
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Kaynakları serbest bırak
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        printf("Islem olusturulamadi.\n");
    }

    return 0;
}