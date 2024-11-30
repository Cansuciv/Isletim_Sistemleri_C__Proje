void child_process()
{
    FILE *file;

    // Dosyayı açmayı dene
    file = fopen("ornek.txt", "r");

    if (file == NULL)
    {
        // Dosya bulunamazsa, abort() ile çıkış yap
        printf("Dosya bulunamadi, child process zorla cikacak.\n");
        abort(); // Hata durumunda programı zorla sonlandırır
    }

    // Dosya başarıyla açılırsa, normal şekilde çık
    printf("Dosya basariyla acildi, child process duzgun bir sekilde cikacak.\n");
    fclose(file);
    exit(0); // Başarılı çıkış
}