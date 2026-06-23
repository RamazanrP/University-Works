#include <stdio.h>
int main(){
int m,n,sayi;
float x,y;
m += n+x-y; // m = m + ((n+x)-y)
m /= x*n+y; // m = m / ((x*n)+y)
n %= (int)(y+m);   // n = n % (y+m)
x += y -= m;// x = (x+(y = (y-m))) Sağdan sola += -='ler
//-----------------------------------------------------//
int a;
a++; // Burada önce get value a der
++a; // Önce a'yı arttırır sonra get value der
int j=5,i=5;
printf("%d %d",j++,++i ); // 5 ve 6 yazdırır
printf("%d %d", j, i); // Şimdi 6 6 yazdırır !
int m=1,j=-1,s; 
s = m++ - --j; // Önce get value m diyecek (), sonra j'yi bir azaltıp get diyecek (-2) yani s=3 olacak
//----------------------------------------------------//
// & ->iki taraf da 1 ise -> 1 & 1 = 1
// | -> birinde 1 varsa yeter -> 1 | 0 = 1
// ^ -> Farklıysa 1 aynıysa 0 -> 0 ^ 1 = 1
// ~ -> Sayını 1 ve 0'larını değişir, Matematiksel olarak işaretini değiştirip 1 eksiğini verir. ~0101 = 1010 = -6
// sayı << n --> Sayıyı 2^n ile çarpmaktır. 5 << 1 = 0101 << 1 = 1010 yani 10 olur.
// sayı >> n --> Sayıyı 2^n'ye böler (Tam sayı bölmesi) 5 >> 1 = 2'dir.
// z = ((x>y) ? x:y); x, y'den büyükse z=x değilse z=y
char ch;
int numofSpace=0;
int charCounts[128];
// İf yasak, boşluk karakterlerini sayalım
do
{
	scanf("%c",&ch);	//ch=getchar(); is useful too
	charCounts[ch]++;
			
}while (ch!='\n');		// Enter'a basana kadar karakter alıyoruz. While'ın içi do'nun devam etme şartı, While'da istenmeyen şey olunca çıkar.
printf("Number of spaces (do-while):%d\n",charCounts[' ']);
//-------------------------------------------------------//
char ch;
int a=3,b=5,c;
printf("Bir karakter giriniz\n");
scanf("%c",&x);
switch (ch)		//switch ile verilen ifade char, int, short tipinde olabilir
{
	case 'a':	// küçük a'da break olmaması Kullanıcı a da A da girdiğinde Addition olması için :)
	case 'A':c=a+b; printf("Addition      :%d",c); break;	
	case 's':
	case 'S':c=a-b; printf("Substraction  :%d",c); break;
	case 'm':
	case 'M':c=a*b; printf("Multiplication:%d",c); break;
	default : 		printf("Invalid operand"); 	
}
//------------------------------------------------------------//
unsigned short correctanswers = 0,answer2=0,testanswer,result; 
short int j,score=0; 
char c; 
printf("sizeof short %d\n",sizeof(j));
/* eger ilk soru en sol bitte tutuluyorsa*/
/*for (j=0; j <= 15; j++)
{ 
	scanf ("%c", &c); 
	if (c == 'y' || c == 'Y') 
	{
		answer2=1<<(15-j);
		correctanswers = answer2 | correctanswers;
		answer2=0;
	}
}
*/
/* eger ilk soru en sağ bitte tutuluyorsa*/
// correctanswers : testin cevap anahtari
// answer2 : i. soru için sadece i. biti 1 olan bir sayi
answer2=1;
for (j=0; j <= 15; j++)
{ 
	c=getch(); // Klavyeye basıldığı anda hafızaya atar, enter'ı beklemez. Ama biz ekranda da görelim diye putch(c) dedik
	putch(c);
	if (c == 'y' || c == 'Y') 
		correctanswers = answer2 | correctanswers; // correctanswer 0'dı (16 tane 0). answer2 de 1'di. Kullanıcı y girerse VEYA çalışır. 0 VEYA 1 = 1 olur. Yanlışlarını görmüş oluruz
	answer2<<=1;
}
	
	
printf( "Correct answers :%d\n",correctanswers);
printf("Kullanicinin verdigi cevaplari giriniz:\n");
scanf("%d",&testanswer);
result=testanswer^correctanswers;  //aynıysa 0 farklıysa 1, yani sadece YANLIŞLAR 1 diye gözükecek
printf("result:%d",result);
answer2=1; // 00000000 00000001 diye başlattık ve bu 1 hep sağa gidip result'a bakacak. 1 varsa 1&1 olacak, score artacak
for (j=0; j <= 15; j++)
{ 
	if (answer2&result)
		score++;					// yanlış cevap sayisini tutar
	answer2=answer2<<1;
}
printf("score:%d\n",16-score);
return 0;
}