#include <stdio.h>
int main(){
float* fp;
*fp = 3.14; // Legal DEĞİL Çünkü değer değiştirme/atama için ÖNCEDEN AÇILAN bir değişken lazım. değişken adresini pointer'a bağlarsak eğer bu şekilde atama yapabiliriz
int s=5, *p_s; // Legal
*(&s) = 5; // Legal ama elverişli değil
int* p;
printf("%d",*(p+2)); // p = dizi[0] ise 2x4=8 byte sonrasını gösterir yani dizi[2]'yi
int dizi[5] = {1,2,3,4,5};
int* p= dizi; // p = &dizi[0] şu an
// dizi 1000-1004-1008-100C-1010 diye adreslerde tutulsun
int* p2 = p+4; // 1004 değil 1010 tutuldu. Yani dizi[4]=5 tutuluyor şu an
p = p2-2; // dizi[2]=3 tutuluyor şu an -->1010 - 2x4 
// sayi_p, 1200 adresinde 10 sayısını tutsun
int sayi=10;
int *sayi_p = &sayi;
*sayi_p+3; // * işareti daha öncelikli olduğu için 1200'e gider ve 3 ekler. Printflersek 13 yazdırır
*(sayi_p+3); // Burada işler değişti. 120C adresine gitti, burası sıkıntı
int evler[3] = {10, 20, 30};
int* home = evler;              // home tabelasını ilk evin (10'un) önüne diktik
printf("%d\n", *home);          // Çıktı: 10
home++;                         // LEGAL ve de çıktı : 20. Dizideki yeri sizeof kadar arttırdık
printf("%d\n", *home);
//----------------------------------------------------------------------------------------//
short i,j; //short integers
short *ptr;  //pointer to short
i = 123;   
j = 321;	 
ptr = &i;    //p now shows the memory address of i
j = *ptr;    // j = 123 oldu. * ile p'deki adresin değerini okuduk
printf("i:%d j:%d\n", i, j);	//	123 123
i += 2; j += 3; 
printf("i:%d j:%d *p:%d\n", i, j, *ptr+3); //	125	126 128 Önce *p çalıştı sonra +3 geldi
   
char *ptr1="10 spaces"; // Pointer'a böyle string yüklemek READ-ONLY yapar. Printf çalışır ama atamalar ÇALIŞMAZ
//ptr1[8] = 'r'; //does not work 
//*(ptr1+8) = 'r'; //does not work either 
printf("%s",ptr1);

int *ii=0,*jj=0;	//int *ii=NULL, *jj=NULL Yani pointer TANIMLARKEN ATAMA YAPMAK LAZIM ki garbage value dolmasın
//-----------------------------------------------------------------------------------------//
int i,n=5;
int *ptr;
int student[5]; 
printf("give 5 integer numbers\n");
for (i=0;i<n;i++){
    scanf("%d",&student[i]);
}
//Dizi elemanları memory'de art arda bulunur
for (i=0;i<n;i++){
	printf("the value of the element:%d the address of the element:%p\n",student[i],&student[i]);
}
ptr=student; // ptr=&student[0];
printf("the address of the first element:%p\n",ptr); // İlk elemanı bastık
printf("the address of the pointer ptr  :%p\n",&ptr); // İlk elemanın adresini bastık
for (i=0;i<n;i++){
	printf("the value of the element:%d the address of the element:%p\n",*(ptr+i),ptr+i);
}
return 0;
}

