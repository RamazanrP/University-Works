#include <stdio.h>
#include <string.h>
#define MAX 10
struct student{
    int id;
    char name[30];
    float percentage;
};
struct Kisi {
    char* ad;
    int id;
    int yas;
};
void swap4(int **a, int **b);
void swap3(int *a, int *b);
void yaz(int array[MAX]);
void yaz2(int *pA);
void f(int array[MAX]);
void f2(int *array);
void f3(int *array);
int main(){
    int i;
    struct student record1 = {1, "Raju", 90.5};
    struct student record2, record3, *ptr1, record4;

    printf("Records of STUDENT1 - record1 structure \n");
    printf("  Id : %d \n  Name : %s\n  Percentage : %f\n", record1.id, record1.name, record1.percentage);
    // 1st method to copy whole structure to another structure
    record2=record1;  
	
	record1.name[1]='X';  // Burada ismi "RXju" yapıyoruz. [] diyerek isme değil DİZİYE ulaşır ve HARFİ değiştirebiliriz
                          // Eğer direkt ismi "X" yapmak isteseydik --> strcpy(record1.name, "X");
	printf("Records of STUDENT1 - record1 structure \n");
    printf("  Id : %d \n  Name : %s\n  Percentage : %f\n",
    record1.id, record1.name, record1.percentage);

    printf("\nRecords of STUDENT1 - Direct copy from " \
           "record1 \n");
    printf("  Id : %d \n  Name : %s\n  Percentage : %f\n", 
    record2.id, record2.name, record2.percentage);

    // 2nd method to copy using memcpy function
    /*memcpy() function is used to copy a block of memory from one location to another
    int a = 20;
    int b = 10;
    Use memcpy to copy the value of 'a' into 'b'
    memcpy(&b, &a, sizeof(int)); memcpy, değer değil ADRES ister. O kaynağa git. sizeof(int) kadar kutuyu al, hedef adrese yapıştır
	*/
    ptr1 = &record1; 
    memcpy(&record3, ptr1, sizeof(record1)); // sizeof()'un içine direkt sayı YAZAMAYIZ. Boyut belirten değişken yazmalıyız
    ptr1 = &record3;
    printf("\nRecords of STUDENT1 - copied from record1pppp " \
           "using memcpy \n");
    printf("  Id : %d \n  Name : %s\n  Percentage : %f\n", 
           ptr1->id, ptr1->name, ptr1->percentage);

    // 3rd method to copy by individual members
    printf("\nRecords of STUDENT1 - Copied individual " \
           "members from record1 \n");
    record4.id=record1.id; // Manuel olarak atadık
    strcpy(record4.name, record1.name);
    record4.percentage = record1.percentage;

    printf("  Id : %d \n  Name : %s\n  Percentage : %f\n",record4.id, record4.name, record4.percentage);
//----------------------------------------------//
char metin[30]="ince memed. yasar Kemal"; // Şu an metin üzerinde değişiklik yapılabilir ama tek seferde TAMAMI değiştirilemez. metin="yeni" OLMAZ
char *str="beyaz gemi Cengiz Aytmatov";   // str şu an READ-ONLY alandadır. Sadece ekrana yazdırabiliriz. %s diyip str+5 mesela
//---------------------------------------------//
int *pX,*pY;
//--------------------------------------------//
int array[MAX]={1,2,3}; // Yukarda MAX için 10 dedik ama biz 3 indise değer verdik geri kalanı SIFIR KABUL EDİLİR
	yaz(array);	//1 2 3 0 0 0 0 0 0 0
	int *x=array;
	x=&array; // Alttaki ile aynı şeydir
	x=&array[0];
	yaz2(array); //1 2 3 0 0 0 0 0 0 0
	yaz2(&array);//1 2 3 0 0 0 0 0 0 0
	yaz2(&array[0]);//1 2 3 0 0 0 0 0 0 0
	f(array); // f fonksiyonunda array[i] dememiz bize ADRESİ verir. Normal değişkenler gibi değildir dizide işlem yapmak. İşlemler kalıcıdır
	yaz2(array);//2 3 4 1 1 1 1 1 1 1   int array[MAX] = int array[] = int *array -> Üçünü de fonksiyonda yazabiliriz
	f2(array);
	yaz2(array);//3 4 5 2 2 2 2 2 2 2
	f3(array);
	yaz2(array);//4 5 6 3 3 3 3 3 3 3
	int j=0;
	printf("\n%d %d %d",array[j], *(array+j), j[array]); //4 4 4 Burda j[array] legaldir çünkü C *(j+array) diye okur her zaman
	printf("\n%d %d %d",&array[j], (array+j), &j[array]);//6487568 6487568 6487568
//----------------------------------------//
struct Kisi s1,s2;
s1.ad = (char*)malloc(100);
    // Bellekten yer ayır
    strcpy(s1.ad, "Mehmet");
    s1.id = 5;
    s1.yas = 55;

    s2 = s1; // Burada s2'ye gidip Mehmet'i koymuyoruz. ADRESİ KOYUYORUZ. s2'de değişiklik S1'İ DE ETKİLER
    // Böyle olmaması için strcut ta İSİM'i pointer olarak değil DİZİ olarak açsaydık işte o zaman rahatça değişiklik yapardık. s1 değişmezdi
return 0;
}
void yaz(int array[MAX]){
	int i;
	for(i=0;i<MAX;++i){
		printf("%d ",array[i]);
	}
	printf("\n");
}

void yaz2(int *pA){
	int i;
	for(i=0;i<MAX;++i){
		printf("%d ",*(pA+i));
	}
	printf("\n");
}

void f(int array[MAX]){
	int i;
	for(i=0;i<MAX;++i){
		array[i]+=1;
	}
}
void f2(int array[]){
	int i;
	for(i=0;i<MAX;++i){
		*(array+i)+=1;
	}
}

void f3(int *array){
	int i;
	for(i=0;i<MAX;++i){
		array[i]+=1;
	}
}
//---------------------------------------------//
// x ve y' ye bir değer verelim. Sonra pX ve pY diye iki pointera bunların adresini koyalım.
// swap3'e px ve pY'yi gönderiyoruz ama değişiklik OLMAZ. Çünkü pointer da olsa adres üzerinden değil değer üzerinden atama yapmış swap3
//swap3(pX,pY); diye gönderdik
void swap3(int *a, int *b){ //call by value
	int *t;
	t=a;
	a=b;
	b=t; // Fonksiyon bittiği gibi bu değerler uçar
}
//swap4(&pX,&pY); adresi gönderdik bak
void swap4(int **a, int **b){ //call by referans
	int *t; // Bir pointer açtık
	t=*a;   // a'yı bir kere açtık. Artık a, pointer derecesinde. Değişikliği böyle yapacağız.
	*a=*b;
	*b=t;
}