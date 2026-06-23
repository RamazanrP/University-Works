#include <stdio.h>

int main() {
    FILE *fp_1 = fopen("istiklal.txt", "r");
    char line[100]; // fgets ya \n ya da 99 karakter kadar okuyacak
    long savedPos; //  Imlecin dosyada kacinci baytta (karakterde) oldugunu unutmamak icin kaydedecegimiz degisken
    fgets(line, sizeof(line), fp_1); // 3 parametre => Nereye yazayim?, En fazla kac harf okuyayim?, Hangi dosyadan okuyayim?
    savedPos = ftell(fp_1); // Su an imlec kacinci baytta?" diye sorar (2. satırın başını veya 1. satırın uzunluğunu döndürecek)
    printf("After first line:\n%s\n", line);
    fgets(line, sizeof(line), fp_1); // Imlec zaten 2. satirin basinda bekledigi icin bu sefer 2. satiri ("Dusun altindaki...") okur.
    printf("Second line:\n%s\n", line);
    // === FSEEK === //
    /*  Dosya (fp), Hedef Konum (savedPos), Referans Noktasi (SEEK_SET - Dosyanin basi)
        Bu komut, su an 3. satira gecmis olan imleci zorla tutup 'savedPos' icindeki o eski degere isinlar!
        Yani imlec tekrar 2. satirin en basina geri doner   */

    // 1 -> Hangi dosyanın imlecini taşıyayım? (fp)
    // 2 -> Kaç adım (bayt) gideyim? (Örn: savedPos veya 10, -5)

    /*  fseek fonksiyonunun 3. parametresi:
        SEEK_SET: Dosyanın en başından say.
        SEEK_CUR: İmlecin şu an bulunduğu yerden say.
        SEEK_END: Dosyanın en sonundan geriye doğru say   */
    fseek(fp_1, savedPos, SEEK_SET); // savedPos ilk satırın uzunluğunu tutmuştu, baştan bu kadar ilerlersek 2. satıra geliriz :)
    fgets(line, sizeof(line), fp_1);
    printf("Read again from saved position:\n%s\n", line);

    fclose(fp_1);
}
//-------------------------------------------------------------------------------------------------------------------------------//
int main(){
//C'nin standart makrolarıdır. Kodu çalıştırdığında, o kodun dosya adını ve o an kaçıncı satırda çalıştığını ekrana basarlar.
printf("Current line :%d\nFilename : %s\n\n", __LINE__, __FILE__);
// Derleyici #line'dan itibaren kendini "new name" isimli bir dosyanın 200. satırında sanır ve bir sonraki satırı 201 olarak sayar
#line 200  "new name"
printf("Current line :%d\nFilename : %s\n\n", __LINE__, __FILE__);
}
//-------------------------------------------------------------------------------------------------------------------------------//
int main()
{
	int y,a;
	float z;
    // #define MUL_BY_TWO(a) ((a)+(a)) DIŞ PARANTEZ ZORUNLULUK!!!
	y = MUL_BY_TWO(2.4); //4
	z = MUL_BY_TWO(2.4);	//4.8
	#define false 0 // false gördüğün yere 0 yaz
	#ifndef false // if not defined diye sorgular ama defined old. için alttaki satırlar direkt boşa çıkar
	#define false 1
    #endif
    //Alttaki durumda false değeri 0 olduğundan  DOĞRU döndürür ve alta iner, false 1 olarak redefine edilir
    //#if !false
    //#define false 1
	printf("false:%d\n",false);
	#define TEST 5
	#ifdef TEST // SADECE DEFİNE EDİLMİŞ DEĞERİ SORGULAYABİLİRİZ. MAİN'DEN OKUMA + SORGULAMA YAPILMAZ
	printf("this is a test\n");
	#else
	printfv("this is not a test\n"); // Böyle bir fonksiyon yok ama zaten bu satıra inmediği için sorun da yok :)
	#endif
	// KISACA: #ifndef makronun kimliğiyle (varlığıyla) ilgilenir, #if ise makronun cüzdanıyla (değeriyle) ilgilenir!
	#define MUL_BY_TWO_V2(a) (a)+(a)
	#define SQUARE(a) (a*a)
	a=10*MUL_BY_TWO_V2(2); //10*(2)+(2) = 22
	a=SQUARE(2+3); //(2+3*2+3) = 11
}
//-------------------------------------------------------------------------------------------------------------------------------//
#define CHECK(a, b) \
if((a)!=(b)) \
fail(a, b, __FILE__, __LINE__)
/*Benim beklentim ile gerçekteki değer birbirini tutmuyorsa;bana sadece 'Hata var' deme.
Hatanın hangi dosyada, kaçıncı satırda olduğunu ve hangi değerlerin çakıştığını nokta atışı söyle!*/
void fail(int a, int b, char* p, int line){
printf("Check failed in file %s at line %d: received %d, expected %d\n", p, line, a, b);
}
int main (){
    CHECK(3,4);
}
//-------------------------------------------------------------------------------------------------------------------------------//
int main (){
    char file1[20],file2[20]; // Verilen iki isimde dosyayı oluşturacağız
    FILE *fp1;
    int x=4,i; // x=124567 olsaydı txt için her digit(char) bir bayt olduğundan normalde 10.000(10 kB) dosya 60.000(60 kB) olurdu
	if ((fp1 = fopen( file1, "w" )) == NULL)
		return 0; 
	for (i=0;i<10000;i++)
		fprintf(fp1,"%d",x);
	fclose(fp1);
	
	if ((fp1 = fopen( file2, "wb" )) == NULL) // Binary için int boyutu SABİT 4 baytdır. x=4 de olsa 124567 de olsa 40 kB olurdu
		return 0; 
	for (i=0;i<10000;i++)
		fwrite(&x,sizeof(int),1,fp1);
	fclose(fp1);
}