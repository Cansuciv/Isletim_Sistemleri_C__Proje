#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Dosya oluşturma işlevi
void create_file()
{
    FILE *file = fopen("ornek.txt", "w");
    if (file == NULL)
    {
        perror("Dosya olusturulamadi");
        exit(1);
    }
    else
    {
        fprintf(file, "Bu dosya 1.cocuk surec tarafindan olusturuldu. "); // oluşturulan ornek.txt'nin içerisine yazılacak
        fclose(file);
        printf("Dosya olusturuldu.\n");
    }
}

// Dosyaya veri yazma işlevi
void write_file()
{
    FILE *file = fopen("ornek.txt", "a");
    if (file == NULL)
    {
        perror("Dosyaya yazilamadi");
        exit(1);
    }
    else
    {
        fprintf(file, "Veri 2.cocuk surec tarafindan eklendi.\n"); // oluşturulan ornek.txt'nin içerisine yazılacak
        fclose(file);
        printf("Veri dosyaya eklendi.\n");
    }
}

// Dosya içeriğini okuma işlevi
void read_file()
{
    char buffer[256];
    FILE *file = fopen("ornek.txt", "r");
    if (file == NULL)
    {
        perror("Dosya acilamadi");
        exit(1);
    }
    else
    {
        printf("Dosya icerigi:");
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(file);
    }
}

int main()
{
    HANDLE hThread1, hThread2, hThread3;
    DWORD threadId1, threadId2, threadId3;

    // İlk çocuk süreci (dosya oluşturma)
    hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)create_file, NULL, 0, &threadId1);
    if (hThread1 == NULL)
    {
        printf("Cocuk surec 1 olusturulamadi\n");
        return 1;
    }

    // Tüm çocuk süreçlerin tamamlanmasını bekle
    WaitForSingleObject(hThread1, INFINITE);

    // İkinci çocuk süreci (dosyaya veri yazma)
    hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)write_file, NULL, 0, &threadId2);
    if (hThread2 == NULL)
    {
        printf("Cocuk surec 2 olusturulamadi\n");
        return 1;
    }

    // Tüm çocuk süreçlerin tamamlanmasını bekle
    WaitForSingleObject(hThread2, INFINITE);

    // Üçüncü çocuk süreci (dosya içeriğini okuma)
    hThread3 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)read_file, NULL, 0, &threadId3);
    if (hThread3 == NULL)
    {
        printf("Cocuk surec 3 olusturulamadi\n");
        return 1;
    }

    // Tüm çocuk süreçlerin tamamlanmasını bekle
    WaitForSingleObject(hThread3, INFINITE);

    // Handle'leri kapat
    CloseHandle(hThread1);
    CloseHandle(hThread2);
    CloseHandle(hThread3);

    printf("Tum cocuk surecler tamamlandi.\n");

    return 0;
}
