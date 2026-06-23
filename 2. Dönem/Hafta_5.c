// Fonksiyon içinde bir değişkeni i++ gibi değiştirmek veya swap etmek istersek ADRESİNİ fonl tanımlama parantezinde yazmalıyız
/* 1'den fazla şeyi return edemeyiz. Bir şeyi fonksiyon içinde return dışında da döndürmek istiyorsa fonk tanıtma parantezinde değişkenin ADRESİNİ girmeliyiz
Fonk içinde bulunan yeni değeri, adresin içine atarız, return'e gerek kalmaz*/
// Fonksiyon içinde tanımlanan şeyin ADRESİNİ return edemeyiz. Adres döndürmek için o değişken main'de tanımlanmalı ki adresi KALICI olsun
// Çağrılan fonksiyona dizi gönderirken ya "dizi,n" veya "&dizi[0],n" yazılıp gönderilmeli
// Fonk tanımlama parantezinde (int mat[][3], int satir) gibi SÜTUNLA BERABER yazılmalı, main içinde bunu çağırırıken fonk(mat,2) yazılabilir
/* Eğer matrisi DİZİ gibi okumak istersek fonk tanımlarken (int *p, int satir, int sutun) yazılmalı ve printf("%d ", *(p + i * sutun + j)) gibi yazılmalı
ve bunu mainde gönderirken zorla DİZİ gibi gönderiririz --> matrisHacker((int*)mat, 2, 3) */
// fonk tanımlarken (int* dizi) de olur (int dizi[]) de olur
#include <stdio.h>
#include <stdlib.h>
int* dinamikDiziOlusturVeBuyut(int ilkBoyut, int yeniBoyut) {
int *p = (int*)malloc(ilkBoyut * sizeof(int));
for(int i = 0; i < ilkBoyut; i++) {
    p[i] = (i + 1) * 10; // 10, 20...
}
int *yeni_p = (int*)realloc(p, yeniBoyut * sizeof(int));
for(int i = ilkBoyut; i < yeniBoyut; i++) {
    yeni_p[i] = (i + 1) * 10; // 30, 40...
}
return yeni_p; // Realloc sayesinde LOCAL değişken RETURN edebiliriz
}
int main() {
int *anahtar;
int elemanSayisi = 4;
anahtar = dinamikDiziOlusturVeBuyut(2, elemanSayisi);
printf("Fonksiyon bitti ama veriler burada:\n");
for(int i = 0; i < elemanSayisi; i++) {
    printf("Dizi[%d] = %d\n", i, anahtar[i]);
}
free(anahtar); 
//-----------------//
int** matrix,m;
// Diyelim ki matrisin 'm' tane satırı var
for (int i = 0; i < m; i++) {
    free(matrix[i]); // Önce her bir satırı (odaları) tek tek boşalt
}
free(matrix); // En son ana direği (pointer dizisini) imha et
//-------------------------------------------------------------//
return 0;
}
float toplaMatv1 (float **mat, int dim1, int dim2)
{
	float topla=0;
	int i,j;
	for (i=0;i<dim1;i++)
		for (j=0;j<dim2;j++)
			//topla=topla+*((float *)mat+i*dim2+j); //illegal kullanim, matris statik değil. Bloklar yan yana oluşmadı ** yüzünden. [2][3] diye yazılsaydı o zaman legal olurdu
			//topla=topla+*(*(mat+i)+j);  			//legal
			// Önceki niye illegal --> Başlangıç adresini veriyor. Şu kadar git, kesin bulursun diyor. Hayır art arda değiliz!!
			// İkinic neden legal --> mat+i diyerek yan yana dizilen değerlerin başlangıç adresine götürüyor. Başlangıç 0 0 dan değil yani
			topla=topla+mat[i][j];
	return topla;	
}