#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Author{
    int authorID;
    char name[30];
    char surname[30];
    struct Author *next;
} Author;

typedef enum { RAFTA, ODUNC_VERILDI } BookStatus;

typedef union { // Tasarruflu şekilde bellek ayrımı yaptık
    char rafBilgisi[6];
    int studentID;
} State;

typedef struct {
    char tagNumber[25];
    BookStatus statusFlag;
    State currentState; // Kopyanın şu anki durumu
} BookCopy;

typedef struct Book {
    char ISBN[14];
    char title[50];
    int kopya_adedi;
    BookCopy* kopyalar;
    struct Book *next;
} Book;

typedef struct {
    char bookISBN[14];
    int authorID;
} BookAuthorMatch;

typedef struct{ // Öğrenciler Linked List olarak değil dinamik dizi olarak istenmiş
    char name[30];
    char surname[30];
    int studentID;
    int score; // Başlangıç 100
} Student;

typedef struct {
    char tagNumber[25];
    int studentID;
    int actionType;     // 0: Ödünç Aldı, 1: Teslim Etti
    char date[11];      // DD.MM.YYYY
} islemGecmisi;

void kitapMenu(Book**, Author*, BookAuthorMatch**, int*, Student*, int, islemGecmisi**, int*);
void kitapOduncVer(Book*, Student*, int, islemGecmisi**, int*);
void kitapTeslimEt(Book*, Student*, int, islemGecmisi**, int*);
void kitapListele(Book*, BookAuthorMatch*, int);
void kitapBulVeGoster(Book*);
void kitapGuncelle(Book*);
void kitapYazarEslestir(Book*, Author*, BookAuthorMatch**, int*);
void kitapYazarGuncelle(Book*, Author*, BookAuthorMatch*, int);
void kitapEkle(Book**, Author*, BookAuthorMatch**, int*);
void kitapSil(Book**, BookAuthorMatch**, int*);

void yazarMenu(Author**, Book*, BookAuthorMatch**, int);
void yazarEkle(Author**);
void yazarListele(Author*);
void yazarGuncelle(Author*);
void yazarSil(Author**, BookAuthorMatch**, int);
void yazarBulVeGoster(Author*, Book*, BookAuthorMatch*, int);


void ogrenciMenu(Student**, int*, islemGecmisi**, int*, Book*, BookAuthorMatch*, int);
void ogrenciEkle(Student**, int*);
void ogrenciSil(Student**, int*);
void ogrenciGuncelle(Student*, int);
void ogrenciListeleDetayli(Student*, int, islemGecmisi*, int);
int gunFarkiHesapla(char*, char*);

void yazarlariDosyadanOku(Author**);
void yazarlariDosyayaYaz(Author*);
void ogrencileriDosyadanOku(Student**, int*);
void ogrencileriDosyayaYaz(Student*, int);
void kitaplariDosyadanOku(Book**);
void kitaplariDosyayaYaz(Book*);
void eslestirmeleriDosyadanOku(BookAuthorMatch**, int*);
void eslestirmeleriDosyayaYaz(BookAuthorMatch*, int);
void islemGecmisiniDosyadanOku(islemGecmisi**, int*);
void islemGecmisiniDosyayaYaz(islemGecmisi*, int);

int main() {
    Author *authorHead = NULL;
    Book *bookHead = NULL;
    Student* ogrenciListesi = NULL;
    int toplamOgrenci = 0;
    BookAuthorMatch *eslestirmeTablosu = NULL;
    int eslesmeSayisi = 0;
    islemGecmisi *islemGecmisiTablosu = NULL;
    int islemSayisi = 0;
    char secim;
    int sistemAcik = 1;
    yazarlariDosyadanOku(&authorHead);
    ogrencileriDosyadanOku(&ogrenciListesi, &toplamOgrenci);
    kitaplariDosyadanOku(&bookHead);
    eslestirmeleriDosyadanOku(&eslestirmeTablosu, &eslesmeSayisi);
    islemGecmisiniDosyadanOku(&islemGecmisiTablosu, &islemSayisi);

    while (sistemAcik == 1){
        printf("\n=================================================\n");
        printf("      KUTUPHANE OTOMASYONU ANA MENU\n"); // Main'de dallara ayrılan bir menü tasarımı yapmak istedim
        printf("=================================================\n");
        printf("1-> Ogrenci Islemleri\n");
        printf("2-> Yazar Islemleri\n");
        printf("3-> Kitap Islemleri\n");
        printf("0-> Sistemi Kapat \n");
        printf("Seciminiz: ");
        scanf(" %c", &secim);

        if(secim == '1'){
            printf("\n Ogrenci Modulune Geciliyor...\n");
            ogrenciMenu(&ogrenciListesi, &toplamOgrenci, &islemGecmisiTablosu, &islemSayisi, bookHead, eslestirmeTablosu, eslesmeSayisi);
        }else if(secim == '2'){
            printf("\n Yazar Modulune Geciliyor...\n");
            yazarMenu(&authorHead, bookHead, &eslestirmeTablosu, eslesmeSayisi); 
        }else if(secim == '3'){
            printf("\n Kitap Modulune Geciliyor...\n");
            kitapMenu(&bookHead, authorHead, &eslestirmeTablosu, &eslesmeSayisi, ogrenciListesi, toplamOgrenci, &islemGecmisiTablosu, &islemSayisi); 
        }else if(secim == '0'){
            printf("\nSistem kapatiliyor. Veriler diske isleniyor\n");
            yazarlariDosyayaYaz(authorHead);
            ogrencileriDosyayaYaz(ogrenciListesi, toplamOgrenci);
            kitaplariDosyayaYaz(bookHead);
            eslestirmeleriDosyayaYaz(eslestirmeTablosu, eslesmeSayisi);
            islemGecmisiniDosyayaYaz(islemGecmisiTablosu, islemSayisi);
            
            sistemAcik = 0;
        }else{
            printf("\nGecersiz komut! Lutfen gecerli bir islem seciniz.\n");
        }
    }
    return 0;
}
// Fonkisyon pointer istenmiş. Listeleme fonksiyonunu çoğu yerde kulanıyoruz, o nedenle Listeleme için pointer yaratacağız.
int cezaliMi(Student *ogr, Book* books) {
    if(ogr->score < 100) return 1;
    return 0;
}

int banliMi(Student *ogr, Book* books) {
    if(ogr->score < 0) return 1;
    return 0;
}

int isKitapTeslimEtmemis(Student *ogr, Book *bookHead) {
    Book *tempBook = bookHead;
    int i, kitapVar = 0;
    while(tempBook != NULL && kitapVar == 0) {
        for(i=0; i<tempBook->kopya_adedi; i++){
            if(tempBook->kopyalar[i].statusFlag == ODUNC_VERILDI){ // Kitap ödünç verilmişse ve alan kişi aranan öğrenciyse
                if(tempBook->kopyalar[i].currentState.studentID == ogr->studentID) {
                    kitapVar = 1;
                }
            }
        }
        tempBook = tempBook->next;
    }
    return kitapVar;
}

int tumOgrenciler(Student *ogr, Book* books) {
    return 1;
}
int RAFTA_mi(BookCopy *kopya, islemGecmisi *islemTablosu, int islemSayisi, char *bugununTarihi) {
    if(kopya->statusFlag == RAFTA) return 1;
    return 0;
}

int odunc_Mu(BookCopy *kopya, islemGecmisi *islemTablosu, int islemSayisi, char *bugununTarihi) {
    if(kopya->statusFlag == ODUNC_VERILDI) return 1;
    return 0;
}

int gecikmis_Mi(BookCopy *kopya, islemGecmisi *islemTablosu, int islemSayisi, char *bugununTarihi) {
    int i;
    int bulundu = 0;
    char *alinmaTarihi = NULL;
    if(kopya->statusFlag == RAFTA) return 0; // Kitap raftaysa zaten gecikmiş olamaz

    for(i = islemSayisi - 1; i >= 0 && bulundu == 0; i--) {
        // Bu kopyayı bulduk. İşlem tipi de 0 (Odunc Alma) ise
        if(strcmp(islemTablosu[i].tagNumber, kopya->tagNumber) == 0 && islemTablosu[i].actionType == 0) {
            alinmaTarihi = islemTablosu[i].date;
            bulundu = 1;
        }
    }
    if(bulundu == 1) {
        if(gunFarkiHesapla(alinmaTarihi, bugununTarihi) > 15) {
            return 1; // Bulduk :)
        }
    }
    return 0;
}

void kitapMenu(Book **bookHead, Author *authorHead, BookAuthorMatch **eslestirmeTablosu, int *eslesmeSayisi, Student *ogrenciDizisi, int ogrenciSayisi, islemGecmisi **islemTablosu, int *islemSayisi) {
    int secim;
    int menuAcik = 1;

    while(menuAcik == 1) {
        printf("\n--- KITAP ISLEMLERI MENUSU ---\n");
        printf("1-> Kitap Ekle \n"); // Referans bütünlüğü için Kopya ve Yazar bilgisi de isteniuor
        printf("2-> Kitap Sil\n");
        printf("3-> Kitap Guncelle \n");
        printf("4-> Kitap Listele \n");
        printf("5-> Kitap Odunc Ver\n");
        printf("6-> Kitap Teslim Al \n"); // Ceza kontrolü burada yapılacak
        printf("7-> Kitap Ismine Gore Arama Yap\n");
        printf("8-> Raftaki Kitaplari Listele \n"); // Fonk. Pointer kullanmamız istenmişti
        printf("9-> Odunc Verilmis / Teslim Edilmeyenleri Listele\n");
        printf("10-> Zamaninda Teslim Edilmeyen (Ceza Verilecek) Kitaplari Listele \n");
        printf("11-> Kitap-Yazar Sonradan Eslestir \n");
        printf("12-> Kitabin Yazarini Guncelle \n");
        printf("0-> Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf(" %d", &secim);

        if(secim == 1){
            kitapEkle(bookHead, authorHead, eslestirmeTablosu, eslesmeSayisi);
        }else if(secim == 2){
            kitapSil(bookHead, eslestirmeTablosu, eslesmeSayisi);
        }else if(secim == 3){
            kitapGuncelle(*bookHead);
        }else if(secim == 4){
            kitapListele(*bookHead, *eslestirmeTablosu, *eslesmeSayisi);
        }else if(secim == 5){
            kitapOduncVer(*bookHead, ogrenciDizisi, ogrenciSayisi, islemTablosu, islemSayisi);
        }else if(secim == 6){
            kitapTeslimEt(*bookHead, ogrenciDizisi, ogrenciSayisi, islemTablosu, islemSayisi);
        }else if(secim == 7){
            kitapBulVeGoster(*bookHead);
        }else if(secim == 8){
            kitapFiltreliListele(*bookHead, *islemTablosu, *islemSayisi, "00.00.0000", RAFTA_mi); // Tarih&tablo lazzım değil ama formatı bozmamak için dummy değer yolladık
        }else if(secim == 9){
            kitapFiltreliListele(*bookHead, *islemTablosu, *islemSayisi, "00.00.0000", odunc_Mu);
        }else if(secim == 10){
            char bugun[15];
            printf("Bugunun tarihini giriniz (GG.AA.YYYY): "); scanf("%s", bugun);
            kitapFiltreliListele(*bookHead, *islemTablosu, *islemSayisi, bugun, gecikmis_Mi);
        }else if(secim == 11){
            kitapYazarEslestir(bookHead, authorHead, eslestirmeTablosu, eslesmeSayisi);
        }else if(secim == 12){
            kitapYazarGuncelle(*bookHead, authorHead, *eslestirmeTablosu, *eslesmeSayisi);
        }else if(secim == 0){
            menuAcik = 0;
        } 
        else{
            printf("-> HATA: Gecersiz secim yaptiniz!\n");
        }
    }
}

void kitapEkle(Book **bookHead, Author *authorHead, BookAuthorMatch **eslestirmeTablosu, int *eslesmeSayisi) {
    Book *yeniKitap, *curr, *prev = NULL;
    Author *tempAuthor;
    int i, yazarSayisi, girilenID, yazarBulundu, eklendi = 0, isimCmp;
    if (authorHead == NULL) {
        printf("-> Sistemde hic yazar yok! Once yazar eklemelisiniz.\n");
        return; 
    }

    yeniKitap = (Book*)malloc(sizeof(Book));
    if(yeniKitap == NULL){
        printf("Gerekli bellek tahsis edilemedi!\n");
        return;
    }

    printf("Kitabin ISBN Numarasi: "); scanf("%s", yeniKitap->ISBN);
    // İsimde boşluk olabileceği için %s yerine %[^\n]s kullanmalıyız
    printf("Kitabin Adi: "); scanf(" %[^\n]s", yeniKitap->title); 
    
    printf("Bu kitaptan kutuphaneye kac adet (kopya) eklenecek? ");
    scanf("%d", &yeniKitap->kopya_adedi);

    yeniKitap->kopyalar = (BookCopy *)malloc(yeniKitap->kopya_adedi * sizeof(BookCopy));
    for(i=0; i<yeniKitap->kopya_adedi; i++) {
        sprintf(yeniKitap->kopyalar[i].tagNumber, "%s_%d", yeniKitap->ISBN, i+1);
        yeniKitap->kopyalar[i].statusFlag = 0; // 0: RAFTA 
        strcpy(yeniKitap->kopyalar[i].currentState.rafBilgisi, "RAFTA");
    }
    // Kitabı eklerkken aynı zamanda Eşleştirme tablosunu da güncel tutmak için başka bilgileri de sordum
    printf("Bu kitap kac farkli yazar tarafindan yazildi? "); scanf("%d", &yazarSayisi);
    for(i=0; i<yazarSayisi; i++) {
        yazarBulundu = 0;
        while (yazarBulundu == 0) {
            printf("%d. Yazarin ID'sini giriniz: ", i+1); scanf("%d", &girilenID);
            
            tempAuthor = authorHead;
            while(tempAuthor != NULL && yazarBulundu == 0){
                if(tempAuthor->authorID == girilenID) {
                    yazarBulundu = 1;
                } else {
                    tempAuthor = tempAuthor->next;
                }
            }
            
            if (yazarBulundu == 0) {
                printf("-> %d ID'li yazar bulunamadi!\n", girilenID);
            }
        }
        
        // Kalıcı değişiklikler yapmalıyız!
        *eslestirmeTablosu = (BookAuthorMatch *)realloc(*eslestirmeTablosu, (*eslesmeSayisi+1) * sizeof(BookAuthorMatch));
        strcpy((*eslestirmeTablosu)[*eslesmeSayisi].bookISBN, yeniKitap->ISBN);
        (*eslestirmeTablosu)[*eslesmeSayisi].authorID = girilenID;
        (*eslesmeSayisi)++;
    }

    curr = *bookHead;
    while(curr != NULL && eklendi == 0){ // Kitabı isme göre yerleştirmemiz istenmiş
        isimCmp = strcmp(yeniKitap->title, curr->title);
        
        if(isimCmp < 0){
            eklendi = 1;
        } 
        else if(isimCmp == 0){
            // İsimler aynıysa ISBN'e bakmamız istenmiş
            if(strcmp(yeniKitap->ISBN, curr->ISBN) < 0) {
                eklendi = 1;
            }else{
                prev = curr;
                curr = curr->next;
            }
        } 
        else{
            prev = curr;
            curr = curr->next;
        }
    }

    if(prev == NULL){
        yeniKitap->next = *bookHead;
        *bookHead = yeniKitap;
    }else{
        yeniKitap->next = curr;
        prev->next = yeniKitap;
    }

    printf("-> %s kitabi ve %d adet kopyasi, sisteme eklendi!\n", yeniKitap->title, yeniKitap->kopya_adedi);
    kitaplariDosyayaYaz(*bookHead);
}

void kitapSil(Book **bookHead, BookAuthorMatch **eslestirmeTablosu, int *eslesmeSayisi) {
    char silinecekISBN[14];
    Book *curr = *bookHead, *prev = NULL;
    int bulundu = 0,i,j;
    int silinebilir = 1; // Kitap veya kopyası bir öğrenciye ödünç verilmişse uyarı verecek

    printf("Sistemden silinecek kitabin ISBN numarasini giriniz: ");
    scanf("%s", silinecekISBN);
    while(curr != NULL && bulundu == 0) {
        if(strcmp(curr->ISBN, silinecekISBN) == 0) {
            bulundu = 1;
            for(i = 0; i < curr->kopya_adedi; i++) {
                if(curr->kopyalar[i].statusFlag == ODUNC_VERILDI) {
                    silinebilir = 0;
                }
            }
            
            if(silinebilir == 1) {
                if(prev == NULL) {
                    *bookHead = curr->next; // Bastaki siliniyorsa
                } else {
                    prev->next = curr->next; // Aradan siliniyorsa
                }
                
                free(curr->kopyalar); // Önce Kitabın içindeki dinamil diziyi free ettik
                free(curr);           // Sonra kitabın kendisi
                printf("-> Kitap ve tum kopyalari silindi!\n");
                
                i = 0; // Şimdi sıra eşleştrime tablosundaki temizlikte
                while(i < *eslesmeSayisi) {
                    if(strcmp((*eslestirmeTablosu)[i].bookISBN, silinecekISBN) == 0) {
                        for(j = i; j < (*eslesmeSayisi) - 1; j++){ // Kaydırma işlemi
                            (*eslestirmeTablosu)[j] = (*eslestirmeTablosu)[j+1];
                        }
                        (*eslesmeSayisi)--;
                    }else{
                        i++;
                    }
                }
                printf("-> Silinen kitaba ait Yazar-Kitap eslestirmeleri de tablodan temizlendi.\n");
                
            } else {
                printf("-> Bu kitabin bazi kopyalari ogrencilerdedir! Kitap silinmeden once kopyalar teslim alinmalidir.\n");
            }
            
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if(bulundu == 0) {
        printf("-> HATA: Kutuphanede '%s' ISBN numarali bir kitap bulunamadi.\n", silinecekISBN);
    }
    kitaplariDosyayaYaz(*bookHead);
    eslestirmeleriDosyayaYaz(*eslestirmeTablosu, *eslesmeSayisi);
}

void kitapGuncelle(Book *bookHead) {
    char arananISBN[14];
    Book *temp = bookHead;
    int bulundu = 0;
    printf("Guncellenecek kitabin ISBN numarasini giriniz: "); scanf("%s", arananISBN);

    while(temp != NULL && bulundu == 0) {
        if(strcmp(temp->ISBN, arananISBN) == 0) {
            bulundu = 1;
            printf("Mevcut Kitap Adi: %s\n", temp->title);
            printf("Yeni Kitap Adini Giriniz: ");
            scanf(" %[^\n]s", temp->title);
            
            printf("-> Kitap bilgileri  guncellendi!\n");
            kitaplariDosyayaYaz(bookHead);
        } else {
            temp = temp->next;
        }
    }

    if(bulundu == 0) {
        printf("-> HATA: %s ISBN numarali bir kitap sistemde bulunamadi!\n", arananISBN);
    }
    kitaplariDosyayaYaz(bookHead);
}


void kitapListele(Book *bookHead, BookAuthorMatch *eslestirmeTablosu, int eslesmeSayisi) {
    if (bookHead == NULL) {
        printf("-> Kutuphanede henuz kayitli kitap yok.\n");
    }else {
        Book *temp = bookHead;
        printf("\n=== KUTUPHANE ENVANTERI ===\n");
        while(temp != NULL) {
            printf("\nKitap Adi: %s | ISBN: %s | Toplam Kopya: %d\n", temp->title, temp->ISBN, temp->kopya_adedi);
            printf("Yazar ID'leri: ");
            int yazarBulundu = 0,i;
            for(i=0; i < eslesmeSayisi; i++) {
                // Yazarları bulmak için kitapa bilgi eklemek yerine yazarlarda kitabın numarasını arıyoruz, daha az yer ayırdık böylece
                if (strcmp(eslestirmeTablosu[i].bookISBN, temp->ISBN) == 0) {
                    printf("%d ", eslestirmeTablosu[i].authorID);
                    yazarBulundu = 1;
                }
            }
            if(yazarBulundu == 0) {
                printf("(Yazar Eslesmesi Yok)");
            }
            printf("\nKopya Durumlari:\n");
            for(i=0; i < temp->kopya_adedi; i++) {
                printf("  -> Etiket: %s | Durum: ", temp->kopyalar[i].tagNumber);
                if (temp->kopyalar[i].statusFlag == RAFTA) {
                    printf("%s\n", temp->kopyalar[i].currentState.rafBilgisi);
                } 
                else {
                    printf("Odunc Verildi (Ogrenci No: %d)\n", temp->kopyalar[i].currentState.studentID);
                }
            }
            printf("---------------------------------------\n");
            temp = temp->next;
        }
    }
}

void kitapBulVeGoster(Book *bookHead) {
    char arananAd[50];
    int bulundu = 0,i;
    Book *temp = bookHead;

    printf("Detaylarini gormek istediginiz kitabin adini giriniz: ");
    scanf(" %[^\n]s", arananAd); 

    while(temp != NULL && bulundu == 0) {
        if(strcmp(temp->title, arananAd) == 0) {
            bulundu = 1;
            printf("\n--- KITAP DETAYLARI ---\n");
            printf("Kitap Adi: %s | ISBN: %s | Kopya Adedi: %d\n", temp->title, temp->ISBN, temp->kopya_adedi);
            printf("Kopya Durumlari:\n");
            
            for(i=0; i<temp->kopya_adedi; i++) {
                printf("  -> Etiket: %s | Durum: ", temp->kopyalar[i].tagNumber);
                if(temp->kopyalar[i].statusFlag == RAFTA) {
                    printf("RAFTA\n");
                } else {
                    printf("ODUNC VERILDI (Ogrenci ID: %d)\n", temp->kopyalar[i].currentState.studentID);
                }
            }
            printf("-----------------------\n");
        } else {
            temp = temp->next;
        }
    }
    
    if(bulundu == 0) {
        printf("-> Kutuphanede '%s' adinda bir kitap bulunamadi.\n", arananAd);
    }
}

void kitapFiltreliListele(Book *bookHead, islemGecmisi *islemTablosu, int islemSayisi, char *bugun, int (*filtre_kurali)(BookCopy *, islemGecmisi *, int, char *)) {
    Book *temp = bookHead;
    int i, bulunan = 0;

    for(temp = bookHead; temp != NULL; temp = temp->next) {
        for(i = 0; i < temp->kopya_adedi; i++) {
            
            if(filtre_kurali(&(temp->kopyalar[i]), islemTablosu, islemSayisi, bugun) == 1 ) {
                printf("Kitap: %-15s | Etiket: %-15s | ", temp->title, temp->kopyalar[i].tagNumber);
                if(temp->kopyalar[i].statusFlag == RAFTA){
                    printf("Durum: RAFTA\n");
                }else{
                    printf("Ogrenci ID: %d | Durum: TESLIM EDILMEDI/GECIKMIS\n", temp->kopyalar[i].currentState.studentID);
                }
                bulunan++;
            }
        }
    }
    if(bulunan == 0) printf("-> Sisteme uygun kitap kopyasi bulunamadi.\n");
}

void yazarMenu(Author **authorHead, Book *bookHead, BookAuthorMatch **eslestirmeTablosu, int eslesmeSayisi){
    char secim;
    int menuAcik = 1;

    while(menuAcik == 1) {
        printf("\n--- YAZAR ISLEMLERI MENUSU ---\n");
        printf("1-> Yazar Ekle\n");
        printf("2-> Yazar Sil\n");
        printf("3-> Yazar Guncelle\n");
        printf("4-> Yazar Listele\n");
        printf("5-> Yazar Ara ve Kitaplarini Goster\n");
        printf("0-> Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf(" %c", &secim);

        if(secim == '1'){
            yazarEkle(authorHead);
        }else if(secim == '2'){
            yazarSil(authorHead, eslestirmeTablosu, eslesmeSayisi);
        }else if(secim == '3'){
            yazarGuncelle(*authorHead);
        }else if(secim == '4'){
            yazarListele(*authorHead);
        }else if(secim == '5') {
            yazarBulVeGoster(*authorHead, bookHead, *eslestirmeTablosu, eslesmeSayisi);
        }else if(secim == '0'){
            printf("Ana Menuye geri donuluyor\n");
            menuAcik = 0;
        }else {
            printf("-> Gecersiz secim yaptiniz!\n");
        }
    }
}

void yazarEkle(Author** head){
    Author* yeniYazar = (Author*)calloc(1, sizeof(Author));
    if(yeniYazar == NULL){
        printf("Bellek tahsis edilemedi!");
        return;
    }
    printf("Yazarin adini giriniz: \n"); scanf(" %[^\n]", yeniYazar->name);
    printf("Yazarin soyadini giriniz: \n"); scanf(" %[^\n]", yeniYazar->surname);
    yeniYazar->next = NULL;
    if(*head == NULL){ // Liste halihazırda var mı yoksa ilk kez mi oluşturuluyor
        yeniYazar->authorID = 1;
        *head = yeniYazar;
    }else{
        Author* temp = *head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = yeniYazar;
        yeniYazar->authorID = (temp->authorID) + 1; // Otomatik olarka arttırılması istenmişti
    }
    printf("-> Yazar basariyla eklendi! Sistemin atadigi Yazar ID: %d\n", yeniYazar->authorID);
    yazarlariDosyayaYaz(*head);
}
void yazarSil(Author **authorHead, BookAuthorMatch **eslestirmeTablosu, int eslesmeSayisi) {
    int silinecekID, i=0, bulundu=0;
    Author *curr = *authorHead,*prev = NULL ;

    printf("Silinecek Yazarin ID'sini giriniz: "); scanf("%d", &silinecekID);
    while(curr != NULL && bulundu == 0) {
        if(curr->authorID == silinecekID) {
            bulundu = 1;
            if(prev == NULL) {
                *authorHead = curr->next; // Baştakini siliyorsak head bir ileriye kaymalı
            }else{
                prev->next = curr->next;
            }
            free(curr);
            printf("-> %d ID'li yazar sistemden tamamen silindi!\n", silinecekID);
        }else{
            prev = curr;
            curr = curr->next;
        }
    }

    if(bulundu == 1){
        // Yazar silindiyse Id'sini -1 yapmamız isteniyordu PDF'te
        for(i=0; i<eslesmeSayisi; i++) {
            if((*eslestirmeTablosu)[i].authorID == silinecekID) {
                (*eslestirmeTablosu)[i].authorID = -1;
            }
        }
    }else {
        printf("-> %d ID'li yazar bulunamadi!\n", silinecekID);
    }
    yazarlariDosyayaYaz(*authorHead);
    eslestirmeleriDosyayaYaz(*eslestirmeTablosu, eslesmeSayisi);
}

void yazarBulVeGoster(Author *authorHead, Book *bookHead, BookAuthorMatch *eslestirmeTablosu, int eslesmeSayisi) {
    Author *tempAuthor = authorHead;
    Book *tempBook;
    char arananAd[30], arananSoyad[30];
    int bulundu = 0, yazarID = -1, yazarKitapVarMi = 0,i;
    printf("Detaylarini gormek istediginiz yazarin adini giriniz: "); scanf("%s", arananAd);
    printf("Soyadini giriniz: "); scanf("%s", arananSoyad);

    while(tempAuthor != NULL && bulundu == 0) {
        if(strcmp(tempAuthor->name, arananAd) == 0 && strcmp(tempAuthor->surname, arananSoyad) == 0) {
            bulundu = 1;
            yazarID = tempAuthor->authorID;
            printf("\n--- Yazar Detaylari ---\n");
            printf("Yazar ID: %d | Ad Soyad: %s %s\n", tempAuthor->authorID, tempAuthor->name, tempAuthor->surname);
        } else {
            tempAuthor = tempAuthor->next;
        }
    }

    if(bulundu == 1) {
        printf("\n=> Yazarin Butun Kitaplari \n");
        for(i=0; i<eslesmeSayisi; i++) {
            if(eslestirmeTablosu[i].authorID == yazarID) {
                tempBook = bookHead;
                while(tempBook != NULL){ // Verilen ISBN'ye göre kitabı eşleitiriyoruz
                    if(strcmp(tempBook->ISBN, eslestirmeTablosu[i].bookISBN) == 0) {
                        printf(" - %s (ISBN: %s)\n", tempBook->title, tempBook->ISBN);
                        yazarKitapVarMi = 1;
                    }
                    tempBook = tempBook->next;
                }
            }
        }
        
        if(yazarKitapVarMi == 0) {
            printf("-> Bu yazarin kutuphanemizde hic kitabi bulunmamaktadir.\n");
        }
        printf("-----------------------\n");
    }else{
        printf("-> Sistemde '%s %s' adinda bir yazar bulunamadi.\n", arananAd, arananSoyad);
    }
}

void yazarGuncelle(Author* head){ // Listenin head'i guncellemeler sonucu değişmeyeceği için tek * kullandık
    int arananID, bulundu=0;
    printf("Guncellenecek yazarin ID'sini giriniz: \n"); scanf("%d", &arananID);
    Author* temp = head;
    while(temp != NULL && bulundu == 0){
        if(temp->authorID == arananID){
            bulundu = 1;
            printf("Yazarin yeni ismini giriniz: \n"); scanf("%s", temp->name);
            printf("Yazarin yeni soyismini giriniz: \n"); scanf("%s", temp->surname);
            printf("%d ID'li yazar basariyla guncellendi\n", temp->authorID);
        }else{
            temp = temp->next;
        }
    }
    if(!bulundu) printf("%d ID'li yazar bulunamadi!\n", arananID);
    yazarlariDosyayaYaz(head);
}

void yazarListele(Author* head){
    if(head == NULL) printf("Henuz yazar eklenmemis. Liste bos!");
    else{
        Author* temp = head;
        while(temp){
            printf("ID: %d | Ad: %s | Soyad: %s\n", temp->authorID, temp->name, temp->surname);
            temp = temp->next;
        }
        printf("\n---------------------------------------------------------\n");
    }
}

void kitapYazarEslestir(Book *bookHead, Author *authorHead, BookAuthorMatch **eslestirmeTablosu, int *eslesmeSayisi) {
    char girilenISBN[14];
    int girilenAuthorID;
    Book *tempBook = bookHead;
    Author *tempAuthor = authorHead;
    int kitapBulundu = 0, yazarBulundu = 0;

    printf("Eslestirilecek kitabin ISBN numarasini giriniz: ");
    scanf("%13s", girilenISBN);

    while(tempBook != NULL && kitapBulundu == 0) {
        if(strcmp(tempBook->ISBN, girilenISBN) == 0) {
            kitapBulundu = 1;
        } else {
            tempBook = tempBook->next;
        }
    }
    if(kitapBulundu == 0) {
        printf("-> Bu ISBN numarasina sahip bir kitap sistemde kayitli degil!\n");
        return;
    }

    printf("Eslestirilecek yazarin ID'sini giriniz: ");
    scanf("%d", &girilenAuthorID);
    while(tempAuthor != NULL && yazarBulundu == 0) {
        if(tempAuthor->authorID == girilenAuthorID) {
            yazarBulundu = 1;
        } else {
            tempAuthor = tempAuthor->next;
        }
    }
    if(yazarBulundu == 0) {
        printf("-> Bu ID'ye sahip bir yazar sistemde kayitli degil!\n");
        return;
    }

    // Referans Bütünlüğü içim tabloyu realloc ile 1 birim büyütüp ekledik
    *eslestirmeTablosu = (BookAuthorMatch *)realloc(*eslestirmeTablosu, (*eslesmeSayisi + 1) * sizeof(BookAuthorMatch));
    strcpy((*eslestirmeTablosu)[*eslesmeSayisi].bookISBN, girilenISBN);
    (*eslestirmeTablosu)[*eslesmeSayisi].authorID = girilenAuthorID;
    (*eslesmeSayisi)++;

    printf("-> Kitap ve Yazar iliskisi eslestirme tablosuna eklendi!\n");
    eslestirmeleriDosyayaYaz(*eslestirmeTablosu, *eslesmeSayisi);
}

void kitapYazarGuncelle(Book *bookHead, Author *authorHead, BookAuthorMatch *eslestirmeTablosu, int eslesmeSayisi) {
    char girilenISBN[14];
    int eskiID, yeniID;
    Author *tempAuthor = authorHead;
    int i, tabloIndeks = -1, yeniYazarBulundu = 0;

    printf("Yazari guncellenecek kitabin ISBN numarasini giriniz: "); scanf("%s", girilenISBN);
    printf("Degistirilecek (Eski) Yazar ID: "); scanf("%d", &eskiID);

    for(i=0; i < eslesmeSayisi; i++){ // "İstenen eşleşme, oluşturulan Eşleştirme Tablonmuzda var mı" kontolü
        if(strcmp(eslestirmeTablosu[i].bookISBN, girilenISBN) == 0 && eslestirmeTablosu[i].authorID == eskiID) {
            tabloIndeks = i;
        }
    }

    if(tabloIndeks == -1) {
        printf("-> elirtilen Kitap-Yazar eslesmesi sistemde bulunamadi!\n");
        return;
    }

    printf("Yerine gelecek yeni Yazarin ID'sini giriniz: ");
    scanf("%d", &yeniID);
    while(tempAuthor != NULL && yeniYazarBulundu == 0) {
        if(tempAuthor->authorID == yeniID) {
            yeniYazarBulundu = 1;
        } else {
            tempAuthor = tempAuthor->next;
        }
    }
    if(yeniYazarBulundu == 0) {
        printf("-> Girmeye calistiginiz yeni Yazar ID sistemde kayitli degil!\n");
        return;
    }
    eslestirmeTablosu[tabloIndeks].authorID = yeniID;
    printf("-> Kitabin yazari basariyla guncellendi!\n");
    eslestirmeleriDosyayaYaz(eslestirmeTablosu, eslesmeSayisi);
}

void ogrenciMenu(Student **ogrenciDizisi, int *ogrenciSayisi, islemGecmisi **islemTablosu, int *islemSayisi, Book *bookHead, BookAuthorMatch* eslestirmeTablosu, int eslesmeSayisi){
    char secim;
    int menuAcik = 1;
    while(menuAcik == 1) {
        printf("\n--- OGRENCI ISLEMLERI MENUSU ---\n");
        printf("1-> Ogrenci Ekle\n");
        printf("2-> Ogrenci Sil\n");
        printf("3-> Ogrenci Guncelle\n");
        printf("4-> Ogrenci Listele \n"); // En detaylı Listeleme isteği bu
        printf("5-> Kitap Odunc Ver / Teslim Et\n");
        printf("6-> Sadece Cezali Ogrencileri Listele \n"); // Puan<100 şartlı
        printf("7-> Kitap Alma Hakki Bitenleri Listele\n"); // Puanı negatif olmalı
        printf("8-> Kitap Teslim Etmemis Ogrencileri Listele \n");
        printf("0-> Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf(" %c", &secim);

        if(secim == '1'){
            ogrenciEkle(ogrenciDizisi, ogrenciSayisi);
        }else if(secim == '2'){
            ogrenciSil(ogrenciDizisi, ogrenciSayisi);
        }else if(secim == '3'){
            ogrenciGuncelle(*ogrenciDizisi, *ogrenciSayisi);
        }else if(secim == '4'){
            ogrenciListeleDetayli(*ogrenciDizisi, *ogrenciSayisi, *islemTablosu, *islemSayisi);
        }else if(secim == '5') {
            int altSecim;
                printf("1-> Kitap Odunc Ver\n2-> Kitap Teslim Et\nSeciminiz: "); scanf("%d", &altSecim);
                if(altSecim == 1)
                    kitapOduncVer(bookHead, *ogrenciDizisi, *ogrenciSayisi, islemTablosu, islemSayisi);
                else if(altSecim == 2)
                    kitapTeslimEt(bookHead, *ogrenciDizisi, *ogrenciSayisi, islemTablosu, islemSayisi);
                else printf("Gecersiz secim\n");
        }else if(secim == '6'){
            printf("\n Cezali Ogrenciler\n");
            ogrenciFiltreliListele(*ogrenciDizisi, *ogrenciSayisi, bookHead, cezaliMi);
        }else if(secim == '7'){
            printf("\n Sistemden Banlanan Ogrenciler \n");
            ogrenciFiltreliListele(*ogrenciDizisi, *ogrenciSayisi, bookHead, banliMi);
        }else if(secim == '8') {
            printf("\n Kitap Teslim Etmemis Ogrenciler \n");
            ogrenciFiltreliListele(*ogrenciDizisi, *ogrenciSayisi, bookHead, isKitapTeslimEtmemis);
        }else if(secim == '0'){
            menuAcik = 0;
        }else{
            printf("-> HATA: Gecersiz secim yaptiniz!\n");
        }
    }
}

void ogrenciEkle(Student **ogrenciDizisi, int *ogrenciSayisi) {
    int i, yeniID;
    Student yeniOgrenci;
    printf("Ogrencinin 8 Haneli Numarasi: ");
    scanf("%d", &yeniID); yeniOgrenci.studentID = yeniID;
    for(i = 0; i < *ogrenciSayisi; i++) {
        if((*ogrenciDizisi)[i].studentID == yeniID) {
            printf("-> Bu ID zaten kayitli! Lutfen farkli bir numara girin.\n");
            return;
        }
    }
    printf("Ogrenci Adi: "); scanf("%s", yeniOgrenci.name);
    printf("Ogrenci Soyadi: "); scanf("%s", yeniOgrenci.surname);
    yeniOgrenci.score = 100;
    // Mevcut dizinin boyutunu 1 kişi daha sığacak kadar genişletiyoruz
    *ogrenciDizisi = (Student *)realloc(*ogrenciDizisi, (*ogrenciSayisi + 1) * sizeof(Student));
    (*ogrenciDizisi)[*ogrenciSayisi] = yeniOgrenci;
    (*ogrenciSayisi)++;
    printf("-> Ogrenci basariyla sisteme eklendi\n");
    ogrencileriDosyayaYaz(*ogrenciDizisi, *ogrenciSayisi);
}

void ogrenciSil(Student **ogrenciDizisi, int *ogrenciSayisi){ // Değişiklik kalıcı olsun diye ** gönderdik
    int silinecekID, i=0, j, bulundu=0;
    printf("Silinecek ogrencinin ID'sini giriniz: ");
    scanf("%d", &silinecekID);
    while(i<*ogrenciSayisi && bulundu==0){
        if((*ogrenciDizisi)[i].studentID == silinecekID){
            bulundu=1;
            for(j=i; j<(*ogrenciSayisi)-1; j++){ // Sağda kalanları bir geriye alalım, bütünlük korunsun
                (*ogrenciDizisi)[j] = (*ogrenciDizisi)[j+1];
            }
            (*ogrenciSayisi)--;
            if(*ogrenciSayisi > 0){ // Öğrenci silince dizi tamemen boşalmış da olaabilir!
                *ogrenciDizisi = (Student *)realloc(*ogrenciDizisi, (*ogrenciSayisi) * sizeof(Student));
            } else {
                free(*ogrenciDizisi);
                *ogrenciDizisi = NULL;
            }
            
            printf("-> %d ID'li ogrenci sistemden tamamen silindi!\n", silinecekID);
        } else {
            i++;
        }
    }
    
    if(bulundu==0) printf("-> HATA: %d ID'li ogrenci bulunamadi!\n", silinecekID);
    ogrencileriDosyayaYaz(*ogrenciDizisi, *ogrenciSayisi);
}

void ogrenciGuncelle(Student *ogrenciDizisi, int ogrenciSayisi){
    int arananID, i=0, bulundu=0;
    printf("Guncellenecek ogrencinin ID'sini giriniz: "); scanf("%d", &arananID);
    while(i<ogrenciSayisi && bulundu==0){
        if(ogrenciDizisi[i].studentID == arananID){
            bulundu=1;
            printf("Mevcut Ad: %s -> Yeni Ad: ", ogrenciDizisi[i].name); scanf("%s", ogrenciDizisi[i].name);
            printf("Mevcut Soyad: %s -> Yeni Soyad: ", ogrenciDizisi[i].surname); scanf("%s", ogrenciDizisi[i].surname);
            printf("-> %d ID'li ogrencinin bilgileri basariyla guncellendi!\n", arananID);
        } else {
            i++;
        }
    }
    
    if(bulundu==0) printf("-> %d ID'li ogrenci bulunamadi!\n", arananID);
    ogrencileriDosyayaYaz(ogrenciDizisi, ogrenciSayisi);
}

void ogrenciListeleDetayli(Student *dizi, int sayi, islemGecmisi *islemTablosu, int islemSayisi) {
    int i, j;
    if(sayi == 0){
        printf("-> Sistemde kayitli ogrenci yok!\n");
        return;
    }
    printf("\n--- DETAYLI OGRENCI LISTESI ---\n");

    for(i=0; i<sayi; i++){
        printf("\nOgrenci: %s %s (ID: %d) | Puan: %d\n", dizi[i].name, dizi[i].surname, dizi[i].studentID, dizi[i].score);
        printf("  [Islem Gecmisi]:\n");
        int islemVar = 0;
        
        for(j=0; j<islemSayisi; j++) {
            if(islemTablosu[j].studentID == dizi[i].studentID) {
                printf("   - Kitap Etiketi: %s | Islem: %s | Tarih: %s\n", 
                       islemTablosu[j].tagNumber, 
                       (islemTablosu[j].actionType == 0) ? "ALDI" : "IADE ETTI", 
                       islemTablosu[j].date);
                islemVar = 1;
            }
        }
        if(islemVar == 0) printf(" %d Numarali ogrencinin hic kitap gecmisi yok\n", dizi[i].studentID);
    }
}

void ogrenciFiltreliListele(Student *dizi, int sayi, Book *bookHead, int (*filtre_kurali)(Student *, Book *)) {
    int i, bulunan = 0;
    for(i=0; i<sayi; i++){
        if( filtre_kurali(&dizi[i], bookHead) == 1 ) {
            printf("ID: %d | Ad Soyad: %s %s | Puan: %d\n", dizi[i].studentID, dizi[i].name, dizi[i].surname, dizi[i].score);
            bulunan++;
        }
    }
    if(bulunan == 0) printf("-> Bu kritere uygun ogrenci bulunamadi.\n");
}

void kitapOduncVer(Book *head, Student *ogrenciDizisi, int ogrenciSayisi, islemGecmisi **islemTablosu, int *islemSayisi){
    char arananISBN[14];
    char islemTarihi[12];
    int bulundu=0, kopyaVerildi=0, ogrNo, ogrenciIndis=-1, i;
    Book *temp = head;
    
    printf("Odunc verilecek kitabin ISBN Numarasi: ");
    scanf("%s", arananISBN);
    
    while(temp!=NULL && bulundu==0){
        if(strcmp(temp->ISBN, arananISBN)==0){
            bulundu=1;
            printf("Kitabi alan ogrencinin 8 haneli numarasi: ");
            scanf("%d", &ogrNo);
            i=0;
            while(i<ogrenciSayisi && ogrenciDizisi[i].studentID != ogrNo) i++;
            ogrenciIndis = (i<ogrenciSayisi) ? i:-1;
            if(ogrenciIndis == -1){
                printf("-> Sistemde %d numarali bir ogrenci bulunamadi!\n", ogrNo);
                return;
            }
            if(ogrenciDizisi[ogrenciIndis].score < 0){
                printf("-> Ogrencinin puani negatif (%d). Kitap verilemez!\n", ogrenciDizisi[ogrenciIndis].score);
                return;
            }
            for(i=0; i<temp->kopya_adedi && !kopyaVerildi; i++){
                if(temp->kopyalar[i].statusFlag == RAFTA){
                    printf("Islem Tarihi (GG.AA.YYYY): ");
                    scanf("%s", islemTarihi);
                    temp->kopyalar[i].statusFlag = ODUNC_VERILDI;
                    temp->kopyalar[i].currentState.studentID = ogrNo;
                    // YEni bir işlem daha eklendiği için diziyi büyütmeliyiz ve değerleri geçerli olacak şekilde değiştirmeliyiz
                    *islemTablosu = (islemGecmisi *)realloc(*islemTablosu, (*islemSayisi + 1) * sizeof(islemGecmisi));
                    strcpy((*islemTablosu)[*islemSayisi].tagNumber, temp->kopyalar[i].tagNumber);
                    (*islemTablosu)[*islemSayisi].studentID = ogrNo;
                    (*islemTablosu)[*islemSayisi].actionType = 0; // Ödünç alma için 0
                    strcpy((*islemTablosu)[*islemSayisi].date, islemTarihi);
                    (*islemSayisi)++;
                    
                    printf("-> %s etiketli kopya %s adli ogrenciye verildi!\n", temp->kopyalar[i].tagNumber, ogrenciDizisi[ogrenciIndis].name);
                    kopyaVerildi = 1;
                }
            }
            if(kopyaVerildi == 0) printf("-> Bu kitabin tum kopyalari baska ogrencilere verilmis durumda!\n");
        }else{
            temp = temp->next;
        }
    }
    if(bulundu == 0) printf("-> Kutuphanede %s ISBN numarali bir kitap yok!\n", arananISBN);
    kitaplariDosyayaYaz(head);
    ogrencileriDosyayaYaz(ogrenciDizisi, ogrenciSayisi);
    islemGecmisiniDosyayaYaz(*islemTablosu, *islemSayisi);
}

int gunFarkiHesapla(char *verilisTarihi, char *teslimTarihi){
    int vGun, vAy, vYil;
    int tGun, tAy, tYil;
    int toplamVerilis, toplamTeslim;
    
    sscanf(verilisTarihi, "%d.%d.%d", &vGun, &vAy, &vYil); // sscanf sayesinde DD.MM.YYYY stringini parçalayabiliyoruz
    sscanf(teslimTarihi, "%d.%d.%d", &tGun, &tAy, &tYil);
    toplamVerilis = (vYil * 365) + (vAy * 30) + vGun;
    toplamTeslim = (tYil * 365) + (tAy * 30) + tGun;
    return (toplamTeslim - toplamVerilis);
}

void kitapTeslimEt(Book *head, Student *ogrenciDizisi, int ogrenciSayisi, islemGecmisi **islemTablosu, int *islemSayisi){
    char iadeEtiket[25];
    char teslimTarihi[12];
    int bulundu=0,tarihBulundu=0,i,j,k,ogrNo, ogrenciIndis=-1;
    int gunFarki;
    Book *temp = head;
    printf("Teslim edilecek kitabin Etiket Numarasini giriniz: ");
    scanf("%s", iadeEtiket);
    while(temp!=NULL && bulundu==0){
        for(i=0; i<temp->kopya_adedi; i++){
            if(strcmp(temp->kopyalar[i].tagNumber, iadeEtiket) == 0){
                bulundu=1;
                ogrNo = temp->kopyalar[i].currentState.studentID;
                printf("Teslim Tarihi (GG.AA.YYYY): ");
                scanf("%s", teslimTarihi);
                j = (*islemSayisi) - 1;
                while(j >= 0 && tarihBulundu == 0){
                    if(strcmp((*islemTablosu)[j].tagNumber, iadeEtiket) == 0 && (*islemTablosu)[j].actionType == 0 && (*islemTablosu)[j].studentID == ogrNo){
                        gunFarki = gunFarkiHesapla((*islemTablosu)[j].date, teslimTarihi);
                        k = 0;
                        ogrenciIndis = -1;
                        while(k < ogrenciSayisi && ogrenciIndis == -1){
                            if(ogrenciDizisi[k].studentID == ogrNo) {
                                ogrenciIndis = k;
                            }else {
                            k++;
                        }
                        }
        
                        if(gunFarki > 15){ 
                            ogrenciDizisi[ogrenciIndis].score -= 10;
                            printf("-> Kitap %d gun sonra teslim edildi! 15 gun siniri asildigi icin ogrenciden 10 puan dusuldu. Yeni Puan: %d\n", gunFarki, ogrenciDizisi[ogrenciIndis].score);
                        }
                        tarihBulundu = 1; 
                    }else{
                        j--;
                    }
                }
                temp->kopyalar[i].statusFlag = RAFTA; // Teslim sonrası değişimler yapıldıktan sonra kitap için bilgileri güncelleyelim
                strcpy(temp->kopyalar[i].currentState.rafBilgisi, "RAFTA");
                *islemTablosu = (islemGecmisi *)realloc(*islemTablosu, (*islemSayisi + 1) * sizeof(islemGecmisi));
                strcpy((*islemTablosu)[*islemSayisi].tagNumber, iadeEtiket);
                (*islemTablosu)[*islemSayisi].studentID = ogrNo;
                (*islemTablosu)[*islemSayisi].actionType = 1; /* 1: Teslim Etti */
                strcpy((*islemTablosu)[*islemSayisi].date, teslimTarihi);
                (*islemSayisi)++;
                printf("-> %s etiketli kitap rafa yerlestirildi.\n", iadeEtiket);
                kitaplariDosyayaYaz(head);
                ogrencileriDosyayaYaz(ogrenciDizisi, ogrenciSayisi);
                islemGecmisiniDosyayaYaz(*islemTablosu, *islemSayisi);
                return;
            }
        }
        temp = temp->next;
    }
    
    if(bulundu == 0) printf("-> Sistemde %s etiketli bir kitap kopyasi bulunamadi!\n", iadeEtiket);
    // Yukardaki return için ayrı burası için ayrı yazdık
    kitaplariDosyayaYaz(head);
    ogrencileriDosyayaYaz(ogrenciDizisi, ogrenciSayisi);
    islemGecmisiniDosyayaYaz(*islemTablosu, *islemSayisi);
}


void yazarlariDosyadanOku(Author **head){
    FILE *fp = fopen("yazarlar.csv", "r");
    char satir[150];
    Author *yeniYazar;
    Author *temp;

    if(fp == NULL){
        return; 
    }
    while (fgets(satir, sizeof(satir), fp) != NULL){ // feof yerine daha güvenli bir şart bloğu yazdık
        yeniYazar = (Author*)malloc(sizeof(Author));
        yeniYazar->next = NULL;

        // Virgüle kadar olan karakterleri alalım
        if(sscanf(satir, "%d,%[^,],%[^\n]", &yeniYazar->authorID, yeniYazar->name, yeniYazar->surname) == 3){
            if(*head == NULL){
                *head = yeniYazar;
            }else{
                temp = *head;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = yeniYazar;
            }
        }else{
            free(yeniYazar);
        }
    }
    fclose(fp);
}

void yazarlariDosyayaYaz(Author *head) {
    FILE *fp = fopen("yazarlar.csv", "w");
    Author *temp = head;
    if(fp == NULL) return;
    while(temp != NULL) {
        fprintf(fp, "%d,%s,%s\n", temp->authorID, temp->name, temp->surname);
        temp = temp->next;
    }
    fclose(fp);
}

void ogrencileriDosyadanOku(Student **dizi, int *elemanSayisi) {
    FILE *fp = fopen("Ogrenciler.csv", "r");
    char satir[200];
    if(fp == NULL){
        return; 
    }
    while(fgets(satir, sizeof(satir), fp) != NULL) {
        Student okunan;
        sscanf(satir, "%d,%[^,],%[^,],%d", &okunan.studentID, okunan.name, okunan.surname, &okunan.score);
        *dizi = (Student *)realloc(*dizi, (*elemanSayisi + 1) * sizeof(Student));
        (*dizi)[*elemanSayisi] = okunan;
        (*elemanSayisi)++;
    }
    fclose(fp);
}

void ogrencileriDosyayaYaz(Student *dizi, int elemanSayisi){
    FILE *fp = fopen("Ogrenciler.csv", "w");
    if(fp == NULL) {
        printf("HATA: Ogrenciler.csv olusturulamadi!\n");
        return; 
    }
    int i;
    for(i=0; i<elemanSayisi; i++){
        fprintf(fp, "%d,%s,%s,%d\n", dizi[i].studentID, dizi[i].name, dizi[i].surname, dizi[i].score);
    }
    fclose(fp);
}

void kitaplariDosyadanOku(Book **bookHead) {
    FILE *fp = fopen("Kitaplar.csv", "r");
    char satir[200];
    char tempUnionStr[20]; // Union'dan gelen veriyi önce string olarak tutmak için
    int i, tempStatus;
    Book *yeniKitap;
    Book *temp;
    if (fp == NULL) return;

    while (fgets(satir, sizeof(satir), fp) != NULL) {
        yeniKitap = (Book *)malloc(sizeof(Book));
        yeniKitap->next = NULL;

        sscanf(satir, "%[^,],%[^,],%d", yeniKitap->ISBN, yeniKitap->title, &yeniKitap->kopya_adedi);
        yeniKitap->kopyalar = (BookCopy *)malloc(yeniKitap->kopya_adedi * sizeof(BookCopy)); // Okunan kopya kadar yer ayırttık
        for(i=0; i < yeniKitap->kopya_adedi; i++) {
            
            if (fgets(satir, sizeof(satir), fp) != NULL) {
                /* statusFlag enum olduğu için doğrudan & ile okumak riskli olacaktı 
                   önce int bir "temp" değiskene alıp sonra enum'a attım.
                   Ayrıca union değeri için sayı mı yazı mı bilmediğimiz icin %s ile gecici stringe aldık */
                sscanf(satir, "%[^,],%d,%[^\n]", yeniKitap->kopyalar[i].tagNumber, &tempStatus, tempUnionStr);
                yeniKitap->kopyalar[i].statusFlag = tempStatus;
                if(yeniKitap->kopyalar[i].statusFlag == RAFTA) {
                    strcpy(yeniKitap->kopyalar[i].currentState.rafBilgisi, tempUnionStr);
                }else {
                    // atoi komutu, string icindeki sayiyi gercek bir int'e çevirecek
                    yeniKitap->kopyalar[i].currentState.studentID = atoi(tempUnionStr);
                }
            }
        }

        if (*bookHead == NULL){
            *bookHead = yeniKitap;
        }else{
            temp = *bookHead;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = yeniKitap;
        }
    }

    fclose(fp);
}

void kitaplariDosyayaYaz(Book *bookHead) {
    FILE *fp = fopen("Kitaplar.csv", "w");
    Book *temp = bookHead;
    int i;
    if (fp == NULL) return;

    while (temp != NULL){ // Önce kitabın ana bilgilerini sonra bütün detaylarını ekrana verelim
        fprintf(fp, "%s,%s,%d\n", temp->ISBN, temp->title, temp->kopya_adedi);
        
        for (i=0; i < temp->kopya_adedi; i++){
            if(temp->kopyalar[i].statusFlag == RAFTA){ // Raftaysa, uninondaki stringi; değilse öğrenci numarasını yazsın
                fprintf(fp, "%s,%d,%s\n", temp->kopyalar[i].tagNumber, temp->kopyalar[i].statusFlag, temp->kopyalar[i].currentState.rafBilgisi);
            }else{
                fprintf(fp, "%s,%d,%d\n", temp->kopyalar[i].tagNumber, temp->kopyalar[i].statusFlag, temp->kopyalar[i].currentState.studentID);
            }
        }
        
        temp = temp->next;
    }

    fclose(fp);
}

void eslestirmeleriDosyadanOku(BookAuthorMatch **tablo, int *eslesmeSayisi) {
    FILE *fp;
    BookAuthorMatch okunanKutu;
    fp = fopen("Kitap_Yazar.bin", "rb");
    if (fp == NULL) {
        return;
    }
    // fread komutu başarıyla 1 adet struct kalıbını okuduğu sürece genişletelim
    while (fread(&okunanKutu, sizeof(BookAuthorMatch), 1, fp) == 1){ 
        *tablo = (BookAuthorMatch *)realloc(*tablo, (*eslesmeSayisi + 1) * sizeof(BookAuthorMatch));
        (*tablo)[*eslesmeSayisi] = okunanKutu;
        (*eslesmeSayisi)++;
    }
    fclose(fp);
}

void eslestirmeleriDosyayaYaz(BookAuthorMatch *tablo, int eslesmeSayisi) {
    FILE *fp;
    fp = fopen("Kitap_Yazar.bin", "wb");
    if (fp == NULL) {
        return;
    }
    if (eslesmeSayisi > 0) {
        fwrite(tablo, sizeof(BookAuthorMatch), eslesmeSayisi, fp);
    }
    fclose(fp);
}

void islemGecmisiniDosyadanOku(islemGecmisi **tablo, int *islemSayisi) {
    FILE *fp = fopen("IslemGecmisi.csv", "r");
    if (fp == NULL) return;
    char satir[200];
    while (fgets(satir, sizeof(satir), fp) != NULL) {
        islemGecmisi yeni;
        sscanf(satir, "%[^,],%d,%d,%[^\n]", yeni.tagNumber, &yeni.studentID, &yeni.actionType, yeni.date);
        *tablo = (islemGecmisi*)realloc(*tablo, (*islemSayisi + 1) * sizeof(islemGecmisi));
        (*tablo)[*islemSayisi] = yeni;
        (*islemSayisi)++;
    }
    fclose(fp);
}

void islemGecmisiniDosyayaYaz(islemGecmisi *tablo, int islemSayisi) {
    FILE *fp = fopen("IslemGecmisi.csv", "w");
    int i;
    if(fp == NULL) return;
    for(i=0; i<islemSayisi; i++) {
        fprintf(fp, "%s,%d,%d,%s\n", tablo[i].tagNumber, tablo[i].studentID, tablo[i].actionType, tablo[i].date);
    }
    fclose(fp);
}