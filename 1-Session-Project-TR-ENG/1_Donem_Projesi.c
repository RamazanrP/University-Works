
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Tum Fonksiyonların erişebileceği degişkenlerimiz
char tahta[20][20];
int N, M;
int yer_degis_puani = 0;
int patlatma_puani = 0;
char elementler[] = {'*', '/', '+', '%', 'O'};
//Taş Üretme 
char rastgele_tas() {
    return elementler[rand() % 5]; //Break continue gibi okumayı zorlaştıran türden olmayan bir return
}

void yazdir_tahta() {
    printf("\n   ");
    int i,j;
    // Göze daha iyi hitap etmesi için satir ve sutun haneleri ekledim
    for ( j = 0; j < M; j++) printf("%2d ", j + 1);
    printf("\n");
    
    printf("   ");
    for ( j = 0; j < M; j++) printf("---");
    printf("\n");

    for ( i = 0; i < N; i++) {
        printf("%2d| ", i + 1); // Görüntüde tek hane-cift hane ayrimi olmamasi icin %2d kullandik
        for ( j = 0; j < M; j++) {
            printf("%c  ", tahta[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------\n");
    printf("Toplam Yer Degisikligi: %d\n", yer_degis_puani);
    printf("Toplam Patlatilan Element: %d\n", patlatma_puani);
    printf("------------------------------\n");
}

void hamle_yer_degistir(int satir1, int sutun1, int satir2, int sutun2) {
    // Öğrendiğimiz temp atamasını kullandık
    char temp = tahta[satir1][sutun1];
    tahta[satir1][sutun1] = tahta[satir2][sutun2];
    tahta[satir2][sutun2] = temp;
    int i,j;
    yer_degis_puani++;
    system("cls"); 
    yazdir_tahta(); 
    printf("\n Hamlenizi gorebilirsiniz! Yeni satir olusturuluyor...\n");
    
    Sleep(2000); //Değişimin görünür olmasi icin

    for ( i = 0; i < N-1; i++) {
        for ( j = 0; j < M; j++) {
            tahta[i][j] = tahta[i + 1][j]; //Satırlarımız yukarı çıkıyor
        }
    }

    // En alt satıra (N-1) rastgele fonksiyonu ile tas ekledim
    for ( j = 0; j < M; j++) {
        tahta[N - 1][j] = rastgele_tas();
    }
    
    printf("\n>>> Taslar 1 satir yukari kaydi ve en alt satir yenilendi\n");
}

void hucre_degis(int s1, int stn1, int s2, int stn2) {
	char temp = tahta[s1][stn1];
	tahta[s1][stn1] = tahta[s2][stn2];
	tahta[s2][stn2] = temp;
}
void yer_cekimi_uygula() {
	int hareket_var;
	do { // Taşların düşüp düşmeyeceğini baştan bilemeyiz. Mutlaka tahtayı en az bir kere taramamız gerekir.
		hareket_var = 0;
		int i,j;
		
		for(j=0; j<M; j++) {
			for(i= N-1; i>0; i--) {
				if(tahta[i][j] == ' ' && tahta[i-1][j] != ' ') {
					hücre_degis(i,j,i-1,j);
					hareket_var = 1;
				}
			}
		}
		if(hareket_var) {
			system("cls");
			yazdir_tahta();
			printf("\n Yer Cekimi Uygulanıyor...\n");
			Sleep(150); //Oyuncu ekranda "o kaymayı" görsün diye
		}
	} while(hareket_var == 1); // Bir hareket olduğu sürece taramaya devam edelim
		system("cls"); // Nihai sonucu yazdıralım
		yazdir_tahta();
		printf("\n Taslar yerine oturdu. Son halini görebilirsiniz");
}
//Patlatmanın İşleyişi
void hamle_patlat(int satir, int sutun) {
    char hedef_tas = tahta[satir][sutun];
    
    // Hedef, boşluk olursa uyarı versin
    if (hedef_tas == ' ') {
        printf("Boslugu patlatamazsiniz!!\n");
	} else {
	int yatay_sayac = 0;
    int k=sutun;
    while(k<M && tahta[satir][k]== hedef_tas){
        yatay_sayac++;
        k++;
    }
    
    int dikey_sayac = 0;
    k=satir;
    while(k<N && tahta[k][sutun]== hedef_tas){
        dikey_sayac++;
        k++;
    }
    // Önce uygunluğu kontrol edelim
    if (yatay_sayac < 3 && dikey_sayac < 3) {
        printf("\n>>> Hata: Burada en az 3'lu bir grup yok!\n");
        
    }
	/*Eğer patlama modunu en çok puan getiren değil de birleşen türden (Candy Crush'daki gibi) yapmak isteseydik az önceki if
	bloğundan sonra sadece else koyardık. Demek ki yatay veya dikeyde 3+ var derdik. O zaman yatay + dikey -1 tane taş patlasın derdik. Puan da bu kadar artardı.
	Çünkü hedef taşı iki saymış olurduk. -1 yazarsak puan doğru şekilde artar. Bu gibi "Süper Patlatmada" oyuncuya görsel şeyler hazırlanabilir vs :)*/
    // Ben gene de projeye sadık kalayım: En çok puan getiren patlasın (" " olanlar) 
    else if (yatay_sayac >= dikey_sayac && yatay_sayac >= 3) {
    	 int k;
         for ( k = 0; k < yatay_sayac; k++) {
            tahta[satir][sutun + k] = ' '; 
         }
        patlatma_puani += yatay_sayac;
        printf("\n>>> Bilgi: Yatayda %d tas patlatildi.\n", yatay_sayac);
    }
    else if (dikey_sayac > yatay_sayac && dikey_sayac >= 3) {
        for ( k = 0; k < dikey_sayac; k++) {
            tahta[satir + k][sutun] = ' ';
        }
        patlatma_puani += dikey_sayac;
        printf("\n>>> Bilgi: Dikeyde %d tas patlatildi.\n", dikey_sayac);
    }

    yer_cekimi_uygula();
	}
}


// MAİN FONSKİYONUMUZ
int main() {
    srand(time(NULL));

    printf("-Oyun alaninin boyutlarini giriniz (NxM): ");
    scanf("%d %d", &N, &M);
	int i,j;
   for( i=0; i<N; i++) for( j=0; j<M; j++) tahta[i][j] = ' ';

    int mod;
    printf("-Oyun Modu icin 1, Kontrol Modu icin 2: ");
    scanf("%d", &mod);
	
    if (mod == 1) { 
        for ( i = N/2; i < N; i++) {
            for ( j = 0; j < M; j++) {
                tahta[i][j] = rastgele_tas();
            }
        }
    } else {
        printf("Oyun tahtasini karakter karakter giriniz:\n");
        for ( i = 0; i < N; i++) {
            for ( j = 0; j < M; j++) {
                // Boşlukları atlamak icin " %c" koydum
                char temp;
                scanf(" %c", &temp); 
                tahta[i][j] = temp;
            }
        }
    }

    int secim = 0;
    while (secim != -1) { //Break olmaması için while
        yazdir_tahta(); 

        printf("\n-Yer Degisikligi Icin 1\n-Patlama Icin 2\n-Cikis Icin -1\nSeciminiz: ");
        scanf("%d", &secim);

        if (secim == 1) {
            int satir1, sutun1, satir2, sutun2;
            printf("-Koordinatlar (Satir1 Sutun1 Satir2 Sutun2): ");
            scanf("%d %d %d %d", &satir1, &sutun1, &satir2, &sutun2);
            hamle_yer_degistir(satir1-1, sutun1-1, satir2-1, sutun2-1);
        }
        else if (secim == 2) {
            int satir,sutun;
            printf("-Koordinatlar (Satir Sutun): ");
            scanf("%d %d", &satir, &sutun);
            // Koordinati C'ye gore girdik, 1 eksiğini
            hamle_patlat(satir-1, sutun-1);
        }
        else if (secim == -1) {
            printf("Oyun Sonlandi.\n");
        }
    }

    return 0;
}
