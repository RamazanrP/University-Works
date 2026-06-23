#include <stdio.h>
int main(){
int i;
char* aylar[12];
for (i=0;i<12;i++) // %p ile &aylar[0] gösterilirse bize POİNTER'IN ADRESİ görünür, %p ile aylar[0] gösterilirse OCAK'IN 'O'SUNUN ADRESİ GÖRÜNÜR. %s dersek i=0 da ocak yazdırılır
	printf("%p adresinde %s var icinde %p\n",&aylar[i],aylar[i],aylar[i]);
i=0;
while (aylar[0][i]){ 
	printf("%p adresinde %c %c %c var\n",&aylar[0][i],aylar[0][i],*(aylar[0]+i),*(*(aylar+0)+i)); // bu üçü de aynı şeyi gösteriyor
	i++;
} // aylar[0] bize o harfinin adresini verir, & İSTEMEZ, ZATEN ADRESTİR. Ama aylar[0][i] dersek & ŞART, direkt veriden bahsettiğimiz için adresini eklemek lazım
//-------------------------------------------------------------------------------------------------------//
int j = 8, k = 3.7, m = -6, x;
unsigned int i = -2;
float y = 12, z;
char a = '2', b = '7';
printf("%c\n", (b - a) + '3');  //7      
z = -6 / y + k;
printf("%f\n", z);	//2.500000 -> Önce bölme yapıldı -6/12 = -0.5 çıktı(bir tane float varsa hepsini float olarak alır). -0.5 + 3(k'yı int olarak tanımşlamış) = 2.50000
x = y - 15 / m;		
printf("%d\n", x);	//14 Önce bölme yaptı. Her ikisi de int diye sonuç -2 çıktı. Sonu. 14.0 olmalıydı ama X İNTEGER. .0 gitti 14 kaldı. İçerisi float çıksaydı bile gene x, int kalırdı
printf("%d\n", i > j + m);  //+' precedence is higher then >    1
printf("%d\n", (m--) + (++j)); //3
printf("%u\n", i); // 4294967294
printf("%d\n", i); // -2  (interpreting the bits as signed)
//-------------------------------------------------------------------------------------------------------//
char ptr[5][20] = {"apple", "banana", "cherry", "orange", "grape"};
printf("%s\n", *ptr);            // apple
printf("%s\n", *(ptr + 1));      // banana
printf("%s\n", *(ptr + 3));      // orange
printf("%c\n", *(*(ptr + 2) + 1)); // second letter of "cherry" -> 'h'
printf("%s\n", *(ptr + 2) + 1);  // herry -> Ekstra * koymadık. Direkt adres belirtmiyoruz. String ise başlangıç adresini verip NULL'a kadar okur
char *ptr2;
ptr2=ptr[0]; // Şu an 'a' harfinin adresini gösteriyor
printf("%s\n", ptr2); 			//apple 'a'dan başladı, NULL'a kadar okudu
printf("%s\n", ptr2+1); 		//pple  Adres olarak bir sonrakine geçti
printf("%c\n", *(ptr2+1));		//p     Bu sefer * var çünkü char istiyor. Nokta atışı adres lazım
printf("%c\n", *ptr2+1);		//b     *ptr2 ile adresi açtı değeri okudu. İçinde 'a' var. onu bir arttırdı. 'b' oldu !!!!!
//-------------------------------------------------------------------------------------------------------//
char *dict[10][20] = {{ "abhor", "able", "abort", "about", NULL } , 
					{ "absurde" , "accepter", "accord", "achat" , NULL } }; 
char **z; // z burada String gösteren bir pointer. Oysa bizim dict'imiz 3 boyutlu. Satırları, sütünları ve de bu karelerde harfleri var. Biz z'yi İngilizce'nin ilk kelimesine koyduysak, kelime kelime ilerler
//	DENEYIN BAKALIM
/*	z=&(dict[language][0]);  -> z, şu an abhor'un başlangıcının adresini tutuyor
	printf("%c\n",**z);			//a
	printf("%s\n",*(z+1));		//able -> Önce z'yi ilerletiyor, sonra açıyoruz. 
	printf("%c\n",*(*(z+1)+1));	//b -> burası z[1][1 veya dict[0][1][1] diyebiliriz. Önce z'yi bir ilerlet. "able". Bunun içine gir ve bir ilerle. 'b' harfinin adresi. Bu adresi oku
*/

return 0;
}
