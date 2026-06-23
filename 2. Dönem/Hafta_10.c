#include <stdio.h>
union Register {
    unsigned char value;

    struct {
        unsigned char bit0 : 1; //reg.value = 0; Bütün bitleri temizledi
        unsigned char bit1 : 1; //reg.bits.bit0 = 1; 2^0 + 2^3 = 9 yazdırır ekrana reg.value
        unsigned char bit2 : 1; //reg.bits.bit3 = 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    } bits;
};

union doub
{
	unsigned char c[2];
	unsigned int val; //  unsigned int sebebiyle 8 digit alan kaplıyor
};

union u
{
	struct{
	char f1,f2; // ussigned diye belirtmezse en baştaki 1 bit işarete gider. O yüzden -128 ile 127 arası sayı tutabilir
	short f3;	
	}s;
	unsigned char f4[6]; // 6 alan kapsıyor
	
};

union IPAddress {
    unsigned int addr;
    unsigned char bytes[4];
};

typedef struct Employee {
    char name[20], surname [20];
    int  ID; 
    float salary; 
    struct Employee *next;
} EMPLOYEE;

int main()
{
	int j,i;
	char ch;
	union doub d;
	// int ii:4; Main içinde böyle bir yazım olmaz, struct'tayken yazmalıydı
	
	// c[0]=1		c[1]=1 olsun
	// 00000001		00000001
	for (j=0;j<2;j++)
		scanf("%d",&d.c[j]);		
	
	printf("val1:%d\n",d.val); //257
	printf("c1_1:%d c2_1:%d\n",d.c[0],d.c[1]);// 1 1
	
	d.c[0]=0;
	// c[0]=0		c[1]=1 olsun
	// 00000000		00000001

	printf("val2:%d\n",d.val); //256 niye 1 değil? intel islemciler little-endian
	
	printf("c1_2:%d c2_2:%d\n",d.c[0],d.c[1]);
	printf("ad1:%p ad2:%p\n",&d.c[0],&d.c[1]);
	
	//union u test={1,2,3,4,5,6};	// Böyle bir süslü parantez kullanımında SADECE TANIMLANAN İLK YAPI (3 değişkenli struct) dolar -> 1 2 3 0 0 0
	//dizinin diğer elemanlarini dolduramadigi icin bu satir warning sebebi 
	union u test={.f4={1,2,3,4,5,6}}; //struct dolar, aynı adresten başlıyordu. test.s.f1=1, s.f2=2 .f3'e ise 3 ve 4 yazılır. f4'ün struct karşılığı budur
	
	printf("%d %d %d\n",test.s.f1,test.s.f2,test.s.f3); // 1 2 1027 yazar, s.f1 ve f2 tek byte o yüzden sayıyı gösterir ama short f3 için 8 bit (256) hesabı yapcaz
	printf("%d %d %d %d %d %d\n",test.f4[0],test.f4[1],test.f4[2],test.f4[3],test.f4[4],test.f4[5]);

    //----------------------------------------------------------------------------------------------------//
    union IPAddress ip;

    ip.addr = 0xC0A80101; // 192.168.1.1 in decimal

    printf("IP as integer: %u\n", ip.addr);

    printf("IP as bytes: %u.%u.%u.%u\n", // Little-Endian yani en küçük adresi en başa alacak şekilde yazar. 1.1.168.192
           ip.bytes[0], ip.bytes[1],
           ip.bytes[2], ip.bytes[3]);

    //printf("no:%d \n", findOldestWoman(personArray,n,&maxAge)); En yaşlı kadının yaşını bir yere kaydetmemiş, direkt yazıyor
	return 0;
}

int powRv2(int x, unsigned int y){ // 2^10 düşünelim. ilk başta sadece y değerleri yarıya iner. 10->5->2->1->0 => 0 oldu temp=1 dedi. Artıüste çıkıyoruz
    int temp;
    if( y == 0)
        return 1;
    temp = powRv2(x, y/2);
    
    if (y%2 == 0)           // 1'den geldik 2 üssüne. çift, buraya girdi. temp*temp yani 2*2 dedi. Bir yukarıya 5 çıktı. 2.t.t = 2.4.4 = 32
        return temp*temp;
    else                    // 0'dan sonra 1 geldi, tek, buraya girdi. 2.1.1 dedi. Yukarıya çıktık
        return x*temp*temp;
}

int TopRecurse(int a, int b){ // a ve b sayıları için terazinin bir kefesine ekleiyp diğerinden çıkarıyor
    if(b == 0){ // Amacımıza ulaştık artık toplam a'da yazılı
        return a;
    } 
    else if(b > 0) { //b pozitifse (Sıfıra inmek için b'yi küçültecez)
        return TopRecurse(a + 1, b - 1);
    } 
    else{ // b negatifse (Sıfıra çıkmak için b'yi büyütecez)
        return TopRecurse(a - 1, b + 1);
    }
} 

int DiziTopRecurse(int* dizi, int b)	//bir dizinin elemanlarini toplayalim
{ 
	if (b==0) return dizi[b]; 
	else 
		return dizi[b]+DiziTopRecurse(dizi,b-1); // En sola, 0. indise kadar gidiyoruz. Sonra gerisini topluyor bu kısım
} 

int ElemanAraRecurse(int* dizi, int b, int x){ // Yollanan indisten geriye doğru geliyor. 0'da bile yoksa -1 döndürüyor
	if (b<0) return -1; 
	else 
		if (dizi[b]==x)	return b; // Bulunca indisi yolluyor
		else 			return ElemanAraRecurse(dizi,b-1,x); 
}

// int findOldestWoman(PERSON *array, int n, int* max) Böyle bir fonksiyon yazdık diyelim. Max'ın adresini göndeririz
// Fonksiyon içinde de .age > (*max) bulursa *max = .age deriz. Önemli

//-----------------------------------------------------------------------------------------------------------------------------//
void printElementP( EMPLOYEE *emp ) {
    printf("Employee %d %s has a salary of %f\n", emp->ID, emp->name, emp->salary);
}
void printList(EMPLOYEE *head) {
    int j; EMPLOYEE *p;
	for(j=0, p=head; p != NULL; p=p->next, j++)
	    printf("%d-th person: %d\t%s\t%f\n",j+1, p->ID, p->name, p->salary);
}
EMPLOYEE* create_list_element(  ) {
    EMPLOYEE *emp; int i; float s;
    emp = (EMPLOYEE*)malloc(sizeof(EMPLOYEE));
    if(emp == NULL ){ // Sadece 1 tane çalışanlık yer oluşturdu, ayırdığı alan boşsa çıkıs yaptı
        printf("create_employee: out of memory."); exit(1);
    }
    printf("Enter name of the person: "); scanf("%s", emp->name); // Öyle strcpy falan yok :D
    printf("Enter ID of the person: ");
    scanf("%d", &i); emp->ID = i;
    printf("Enter salary of the person: ");
    scanf("%f", &s); emp->salary = s;
    emp->next=NULL; return emp; // Sonrakini NULL yapmak önemli!
}
void add_element(EMPLOYEE **head, EMPLOYEE *e){
    EMPLOYEE *p;
    if(*head == NULL){ *head=e; return; }
    // otherwise, find the last element in the list:
    for (p=*head; p->next != NULL; p=p->next); // Çok güzel, tek satırda sadece sonuna gitmek için for yazmış
    p->next=e;
}
void delete_element(EMPLOYEE **head,EMPLOYEE *goner){
    EMPLOYEE *p;
    if(goner == *head)
	*head=goner->next;
    else // Head dışında bir eleman silinmek isteniyorsa
	for(p=*head; (p!=NULL) && (p->next != goner); p=p->next); // p != değil p->next !! Çünkü bize arkasındaki düğüm lazım
    	if(p == NULL){
	    printf("delete_element(): could not find the element \n"); return;
    }
    p->next=p->next->next; // arada goner kalmıştı. Aradan kalktı
	free(goner); //if you forgot to free : memory leak !!!
}
EMPLOYEE* find(EMPLOYEE * head,char *name) {
    EMPLOYEE *p;
    for(p=head; p!= NULL; p=p->next){
        if(strcmp(p->name, name) == 0) // returns 0, if 2 strings are same
	      return p;
    return NULL;
    }
}
void insert_after(EMPLOYEE *p, EMPLOYEE *q){
    // if p and q are same or NULL, or if p already follows q, report that:
    if(p==NULL || q==NULL || p==q || q->next == p){
	   printf("insert_after(): Bad arguments \n");
	   return;
    }
    // x q z	+	p 	=	x q p z
    p->next = q->next; // Önce q'nun sağ kolunu kesti, sonra oraya p'yi bağladı
    q->next = p;
}

/*
typedef struct
{
	char ad[15];
	int sure:4; Bunu input olarak alırken &oyuncular[i].sure diyemeyiz. Önce bi int a; deriz sonra &a'ya alırız. dizi[i].sure=a; deriz
	union
	{
	   unsigned int puan;  		// 32 bit  Önce ödül sayılarını ekrana basalım. Sonra skoru hesaplayım yazalım 
	   char odul[3];	 	 	// 8*3=24 bit Ama böyle olursa ödüllerin bilgisi gidecektir :)
	} SKOR;
}ATLET;
*/