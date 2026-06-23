#include <stdio.h>
typedef struct oyuncu{
    int no;
    int sure;
    int macSayisi;
    int *gol;
    char takim[50];

    struct oyuncu *next;
} OYUNCU;
// Listenin en sonuna Node ekler
OYUNCU *oyuncuEkle(OYUNCU *head){ // Liste ilk kez oluşturulurken head = NULL olmalı, mainde NULL atanmalı!
    OYUNCU *yeni;
    OYUNCU *gecici;
    int i;
    yeni = (OYUNCU *)malloc(sizeof(OYUNCU));

    if (yeni == NULL){ printf("Bellek ayirma hatasi!\n"); exit(1); }

    printf("\nOyuncu No: "); scanf("%d", &yeni->no);
    printf("Takim Adi: "); scanf("%49s", yeni->takim);
    printf("Kac mac oynadi: "); scanf("%d", &yeni->macSayisi);

    yeni->gol = (int *)calloc(yeni->macSayisi, sizeof(int)); // free ederken önce her oyuncunun gollerini free et!
    if (yeni->gol == NULL){ printf("Bellek ayirma hatasi!\n"); free(yeni); exit(1); }

    printf("Her mac icin gol sayilari:\n");
    for (i = 0; i < yeni->macSayisi; i++){ printf("%d. mac: ", i + 1); scanf("%d", &yeni->gol[i]);}

    printf("Toplam sure: "); scanf("%d", &yeni->sure);

    yeni->next = NULL; // UNUTMA

    if (head == NULL) return yeni;

    gecici = head;
    while (gecici->next != NULL) gecici = gecici->next;

    gecici->next = yeni;

    return head;
}

// Listeyi gezerek gördüğü her takım için dosya açıp en sonuna o oyuncu bilgilerini yazar
void takimDosyalaraYaz(OYUNCU *head)
{
    OYUNCU *p;
    FILE *fp;
    char dosyaAdi[100]; // s-printf yani string printf, içine yazacağı char[]'ı ister
    int i;

    p = head;

    while (p != NULL){
        sprintf(dosyaAdi, "%s.txt", p->takim); // Galatasaray görünce "Galatasaray.txt" dosyasını açacak ve en sona ekleme yapacak

        fp = fopen(dosyaAdi, "a"); // EN SONA EKLENECEĞİ İÇİN APPEND MODDA AÇTI, WRİTE OLSAYDI ÖNCEKİLERİ SİLECEKTİ!!!

        if (fp == NULL)
        {
            printf("%s dosyasi acilamadi!\n", dosyaAdi);
            p = p->next;
            continue;
        }

        fprintf(fp, "Oyuncu No : %d\n", p->no);
        fprintf(fp, "Takim     : %s\n", p->takim);
        fprintf(fp, "Sure      : %d\n", p->sure);

        fprintf(fp, "Goller    : ");

        for (i = 0; i < p->macSayisi; i++)
            fprintf(fp, "%d ", p->gol[i]);

        fprintf(fp, "\n");
        fprintf(fp, "--------------------------\n");

        fclose(fp); // UNUTMA

        p = p->next;
    }

    printf("\nTakim dosyalari olusturuldu.\n");
}

void listeYazdirRecursive(OYUNCU *p){ // Önce printfler var, sonra next'e geçiyor. Sırasıyla Node'ları yazdırıyor
    int i;
    if (p == NULL)
        return;
    printf("\nOyuncu No : %d\n", p->no);
    printf("Sure      : %d\n", p->sure);
    printf("Maclar    : ");
    for (i = 0; i < p->macSayisi; i++)
        printf("%d ", p->gol[i]);
    printf("\n");

    /* recursive call */
    listeYazdirRecursive(p->next);
}

void listeTersYazdirRecursive(OYUNCU *p)
{
    int i;
    if (p == NULL)
        return;
    listeTersYazdirRecursive(p->next); // Önce recursive call var. En sona gidecek, NULL dönünce sondan başlayıp yazdıracak
    printf("\nOyuncu No : %d\n", p->no);
    printf("Sure      : %d\n", p->sure);
    printf("Maclar    : ");

    for (i = 0; i < p->macSayisi; i++) printf("%d ", p->gol[i]);
    printf("\n");
}