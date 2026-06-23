#include <stdio.h>
#include <stdlib.h>
//poly1: 5.X^2 + 2.X^3 + 4.X^1
//poly1.N=3
//poly1.term[0].derece=2	poly1.term[0].katsayi=5
//poly1.term[1].derece=3	poly1.term[1].katsayi=2
//poly1.term[2].derece=1	poly1.term[2].katsayi=4
//poly2: 3.X^2 + 2.X^2
//dizi:	0	1	2		3 => x'in dereceleri
//			4	5+3+2	2 => toplam katsayıları
//poly3: 2X^3+10X^2+4X^1

typedef struct term{ // Hem term hem de TERM denmiş. Kısacası kodda iki çeşitte de kullanabiliriz
	int derece;
	int katsayi;
}TERM;

typedef struct poly{
	TERM *terms; //terimler
	int N; //terim sayısı
}POLY;

void getTerms(POLY* p);
void writeTerms(POLY p);
//topla() iki polinomu toplar ve p3'de tutar
//ilgili derecelere ait katsayı toplamlarını hesaplamak için bir dizi kullanalım
//bu dizi için ne kadar alan gerekli? dereceBul() ve getMax() ile hesaplayalim
// v1'e *p3'ü göndereceğiz. Bu yüzden void ama v2'de p4'ü oluşturacağız. O yüzden POLY* return ediyor
void topla(POLY p1, POLY p2, POLY *p3); 
int getMax(int x, int y); //iki sayıdan maximum olani bulur
int dereceBul(POLY p); //Bir polinomun derecesini döndürür
POLY* toplav2(POLY p1, POLY p2);

int main(){
	srand(time(NULL));
	POLY p1, p2, p3, *p4; // Aslında burada p4 diye oluşturup toplav2'yi POLY döndürecek şekilde yapardık.
	printf(" Ilk polinomun N sayisi"); //toplav2'de gene max kadar term açıp bir sonuc(POLY tipinde) değişkenine koyar ve de sonucu döndürürdük
    scanf("%d",&p1.N); // Her polinomun kendine göre N'si olduğu içn direkt &N diyemeyiz!!! Polinoma özel olmalı
	p1.terms = (TERM*)malloc(p1.N*sizeof(TERM));
	getTerms(&p1);
	writeTerms(p1);
	
	printf("\n Diger polinomun N sayisi");
    scanf("%d",&p2.N);
	p2.terms = (TERM*)malloc(p2.N*sizeof(TERM));
	getTerms(&p2);
	writeTerms(p2);
	
	topla(p1,p2,&p3); 
	printf("\ntoplaV1\n");
	writeTerms(p3);
	
	p4 = toplav2(p1,p2); 
	printf("\ntoplaV2\n");
	writeTerms(*p4);
	
	return 0;
}
void topla(POLY p1, POLY p2, POLY *p3){
	int N, M, MAX;
	int i,counter=0;
	int *dizi;
	N = dereceBul(p1);
	M = dereceBul(p2); 
	//p1 2.dereceden, p2 3.dereceden olsun. Toplam polinom 3.dereceden olur. 
	MAX = getMax(N,M) +1 ; // x^0'lı terimi de baz alınca derece+1 tane terim kutusu lazım
	dizi = (int*)calloc(MAX,sizeof(int)); // Calloc ile açtık ki 0 olmayanı değerlendirelim
	for(i=0;i<p1.N;i++){
		dizi[p1.terms[i].derece] += p1.terms[i].katsayi; // İlk terim diyelim 2. dereceden. Dizinin 2. indisine KATSAYIYI ekler
	}
	for(i=0;i<p2.N;i++){
		dizi[p2.terms[i].derece] += p2.terms[i].katsayi;
	}
	for(i=0;i<MAX;i++) {    // Boşa terms açmamak için sadece var olan dereceleri not alıyoruz. Sonrasında if ile kaydedeceğiz
		if(dizi[i]!=0) 
			counter++;
	}
	p3->N = counter; // Gerekli yeri açtık. Pointer ile göndermiştik buraya!
	p3->terms = (TERM*)malloc(counter*sizeof(TERM));
	int j=0;
	for(i=0;i<MAX;i++) {
		if(dizi[i]!=0) {
			p3->terms[j].derece = i;
			p3->terms[j].katsayi = dizi[i];
			j++;	// j'yi manuel arttırdık. i, tüm diziyi gezecek. j, bizi eksik kalmayacak şekilde yerlerimize götürecek
		}
	}
}

POLY* toplav2(POLY p1, POLY p2){
	int N, M, MAX;
	POLY *p4; // Pointer olarak burada oluşturduk ama bu da olurdu : POLY *p4 = (POLY*) malloc(sizeof(POLY));
	int i,j=0, counter=0;
	int *dizi;
	N = dereceBul(p1);
	M = dereceBul(p2); 
	MAX = getMax(N,M) +1 ; 
	dizi = (int*) calloc(MAX,sizeof(int));
	for(i=0;i<p1.N;i++){
		dizi[p1.terms[i].derece] += p1.terms[i].katsayi;
	}
	for(i=0;i<p2.N;i++){
		dizi[p2.terms[i].derece] += p2.terms[i].katsayi;
	}
	
	for(i=0;i<MAX;i++) {
		if(dizi[i]!=0) 
			counter++;
	}
	p4 = (POLY*) malloc(1*sizeof(POLY)); // veya (sizeof(POLY)) Üstekki POLY *p4 satırını SİLEMEYİZ. Önce p4 diye bir şey old. tanıtmalıyız
	
	p4->N = counter;
	p4->terms = (TERM*)malloc(counter*sizeof(TERM));
	
	for(i=0;i<MAX;i++) {
		if(dizi[i]!=0) {
			p4->terms[j].derece = i; // i,bizim derecemiz; dizi[i]'miz ise katsayımız
			p4->terms[j].katsayi = dizi[i];
			j++;	
		}
	}
	return p4;
}


int getMax(int x, int y){
	return x>=y ? x:y; 
}

int dereceBul(POLY p){
	int i;
	int max=0;
	for(i=0;i<p.N;i++){
		if(p.terms[i].derece>max)
			max = p.terms[i].derece;
	}
	
	return max;
}

void getTerms(POLY* p){ // Pointer gönderildiği için -> kullanımına dikkat
	int i;
	for(i=0;i<p->N;i++){
		
		/*printf("%d. terim icin katsayi",i+1); 
		scanf("%d",&p->terms[i].katsayi);
		printf("%d. terim icin derece",i+1); 
		scanf("%d",&p->terms[i].derece);*/
		p->terms[i].katsayi = rand() % 5 + 1 ; 
		(*p).terms[i].derece = rand() % p->N + 1  ; 
		
	}
	
}
void writeTerms(POLY p){
	int i;
	/*for(i=0;i<p.N-1;i++){          Böyle olunca en sonda + işareti kalmıyor. Estetik olarak doğrusu böyle
		printf("%d.X^%d + ",p.terms[i].katsayi,p.terms[i].derece);
	}
	printf("%d.X^%d",p.terms[i].katsayi,p.terms[i].derece);
	*/
	for(i=0;i<p.N;i++){
		printf("%d.X^%d + ",p.terms[i].katsayi,p.terms[i].derece); // En sonda + işareti kaldı :)
	}
}