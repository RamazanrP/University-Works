#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int i=15;	//Program Scope -> Gölgeleme yapılmadığı sürece bu i değeri baz alınır ve bu global i değişmez
static int j=3;	//File Scope -> File yani diğer .c dosyaları bunu göremez
// Ama  gidip de bir blok için i tanımlanmışsa o Block Scope i, bu globali EZER
void printfi()
{
	printf("i with program scope:%d\n",i); // Paranteze yazmadan gönderirsek bloktaki i görülmez ve global baz alınır.

}

void printfiBlock(int i) // Block içinde tanımlanan local i'yi o blok içinde bir fonksiyonun parantezinde gönderirsek o blokta tanımlanan local i gider. Global DEĞİŞMEZ

{
	printf("i with block scope:%d\n",i);
}
//---------------------------------//
void funkA ()
{
	int k=10,i;					//Block Scope
	for (i=0;i<3;i++)
	{	
		int a=4;
		printf("funka-k:%d -a:%d  -i:%d\n",k,a,i);
		printfi();
		printfiBlock(i);
	}
	// illegal
	/*				
	if (a==4)	                    Buradaki a, Süslü parantez bitince yok oldu. İf diyip ÇAĞIRAMAYIZ	
		printf("esit");
	*/
}
//----------------------------------------------//
void fixDuration()
{
	static int fix=2; // Bu fix'i bir kere daha çağırınca 2'den başlamaz 3'ten devam eder. Eski halini HATIRLAR
	fix++;
	printf("fix:%d\n",fix);
}
//-----------------------------------------------------------//
int main(int argc, char *argv[]) // argc -> kaç tane parametre yazdın, argv -> char matrisidir. Dizinin adı dahil stringleri tutar
{
	int say1,say2;
	if (argc!=4) // hesapla.exe topla 10 20 gibi bir şey yazmalı düzgünce çalışması için
	{
		printf("eksik parametre");
		exit(0);
	}
	
	say1=atoi(argv[2]); // ASCII to integer
	say2=atoi(argv[3]);
	
	if (!strcmp("topla",argv[1]))  	// İki metin de aynıysa 0 döndürür. Başına ! koyduk, yani 1 olunca bu if'e girecek
		printf("%d\n",say1+say2);
	else
		printf("%d\n",say1-say2);
	
//------------------------------------------------STRUCT------------------------------------------------------------//
struct {
    char ogr_isim[15];
    short OGR_yas;
} ogrenci1;
// Tek kullanımlıktır
struct OGR {				// Bunda en başta OGR dedik ve 
    char ogrenci_isim[15];
    short ogrenci_yas;
}; 
struct OGR ogrenci1;
// istediğimiz değişkeni oluşturabiliriz ama sıkıntısı her zaman struct yazmalıyız
typedef struct {		  // Bunda OGR kısmı en sonda
    char OGR_isim[15];
    short OGR_yas;
} OGR; 
OGR ogrenci1;
// Bunda struct yazmaktan kurtulduk ama bunu gören kişi bunu struct olduğunu hemen anlayamayabilir :)
//---------------------------------------------------------//
struct OGRN
{
 char OGR_isim[15] , OGR_soyisim[20]; 
 short OGR_yas;
 float OGR_puan; 
};
int i,max=0,maxYer;
static struct OGRN *ogrenci,ogrenciler[3];  
struct OGRN *maxYerStr;
// Diyelim ki diziyi ogrenciler[i].ogr_puan ile geziyoruz ve i. öğrencide en yüksek puanı bulduk diyelim
printf("%s %d\n",ogrenciler[maxYer].OGR_isim,max);
	ogrenci=&ogrenciler[maxYer];  
	printf("v1:%s\n",ogrenci->OGR_soyisim);
	printf("v2:%s\n",(*ogrenci).OGR_soyisim);
//maxyer=i dedik ama bunu POİNTER ile yapabilir miyiz?
max=0;
	ogrenci=ogrenciler;  // Başlangıç adresini eşitledik pointerımıza
	for (i=0;i<3;i++)
	{
		if (ogrenci->OGR_puan>max) // veya *(ogrenci).OGR_puan
		{
			max=ogrenci->OGR_puan;
			maxYerStr=ogrenci; // ogrenci struct boyutu atlayarak ilerliyor. Her zaman bir bloğun baş adresini tutuyor. O ADRESİ maxYerStr'ye atadık
		}
		ogrenci++;
	}
	
	printf("v3:%s\n",maxYerStr->OGR_soyisim); //  maxYerStr bir adres, yani pointer. Koca bir struct'ı tutuyor. Gidip de -> kullanabiliriz
	printf("boyut:%d\n",sizeof(struct OGR));
//-----------------------------------------//
// typedef struct{} OGR; ile OGR tipini oluşturalım. OGR *ogrenciler ile dizi açalım n tane. 3 tane legal erişim vardır
/* asagidaki uc erisim de legal*/
	//ogrenciler[0].OGR_yas=19;
	(*ogrenciler).OGR_yas=19;
	//ogrenciler->OGR_yas=19; // Burada ogrenciler++ diyerek ilerleyip yazdırırız
	printf("%d",ogrenciler->OGR_yas);
	free (ogrenciler);
//----------------------------Nested Structs---------------------------------------//
typedef struct{
 char gun;
 char ay;
 char yil;	
} TARIH;
typedef struct{
 char isim[30];
 int maas; 
 TARIH tarih;
}CALISAN;
// Bunun yerine SADECE çalışan değişkeninde kullanabileceğimiz şekilde struct içinde de struct açabiliriz ve xxx.xxx.xxx diye iki nokta ile erişiriz
typedef struct {
 char isim[30];
 int maas; 
 struct {
 	char gun;
 	char ay;
 	char yil;
 }tarih;
} CALISAN; // Doldururken de struct CALISAN calisan2={"ali",7000,{11,10,90}}; deriz
//---------------------------------------------------------------------------------//
/* Main fonksiyonundan önce böyle tanımladık diyelim. Parantez içine OGR yazmaya dikkat, ve de main de değişiklik kalıcı olsun diye ADRESİ YOLLADIK
void FindMax (OGR *,int);
void NotGuncelle (OGR *);
OGR NotGuncellev2 (OGR);
OGR* YerAc (int);
*/
// OGR ogrenciler[3]; diyip yan yana 3 tane büyük oda açtık

/* Her dizi aslında bir pointer olduğu için FindMax (ogrenciler,n); diye gönderebildik
void FindMax (OGR *ogrenciDizi,int n)  BUNUN YERİNE void findmax (OGR ogrenciDizi[],int n) de diyebilirdik
{
	int i,max=0;
	for (i=0;i<n;i++)
	{
		if (ogrenciDizi[i].puan>max)
			max=ogrenciDizi[i].puan;
	}
	printf("%d\n",max);
}
*/

/*
void NotGuncelle (OGR *ogrenci)  //void NotGuncelle (OGR ogrenci) deseydik sadece kopyasını değiştirirdik !!!
{
	if (ogrenci->yas < 18) 		Ayrıca ogrenci dedikten sonra yas veya puan diye paranteze yazmaya gerek YOK. Onlar zaten BLOK
		ogrenci->puan++;
}
*/

/*
Main içinde ogrPtr = YerAc(3); diye bir POİNTER'a fonksiyon atamıştık. Bu fonksiyon bize BLOK döndürüyor. ogrPtr[0,1,2] diye kullanabiliriz
OGR* YerAc (int n)				// 3 tane BLOK açtık. 3 farklı kişiyi art arda açtık o yüzden OGR* dedik
{
	return (OGR*) calloc (n, sizeof(OGR)); kalıcı olarak Heap'te yaklaşık 3x41 lik alan açtık, ogrPtr'nin başlangıcına eşitledik
}	// Ayrıca return de direkt böyle dyn. all. kullanılarak açılan yerleri döndürmek LEGALDİR!!!
*/
}