#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node *next;
};

void list(struct node *);
//------------------------------// 2. Kaynak kodunun fonskiyonları
void push(struct node *, int); // Listenin sonuna ekler
struct node * pushFront(struct node *, int);  // Listenin başını yaratır. O yüzden struct node* döndürüyor
void list(struct node *);
void deleteNode(struct node *, int); // Verilen değerin öncesindeki kutuyu bulucaz. O kutunun next'ini bu verilen kutunun next'ine bağlicaz
//------------------------------// 2. Kaynak kodunun fonskiyonları bitti
void pushV2(struct node **); // Haftanın son kaynak kodu. push'a göndermeden önce head'i mallocla oluşturuyorduk. Buna ADRES göndercez
//forward referencing
struct s1{
 	int a;
  	struct s2 *ps2;
}; 
struct s2{
 	int b;
  	struct s1 *ps1;
}; 
struct s
{
	int a,b;
	float c;
	struct s* pointer_to_S;
};
/*
typedef struct;
{
	int a,b;
	float c;
	Sr* pointer_to_Sr; Typedef ile yapamayız çünkü şu an işlemci Sr nedir bilmiyor ?
}Sr;
*/
int main(){
	struct s S1={1,2,1.2,NULL};
	struct s S2={3,4,5.6,NULL};
	
	S1.pointer_to_S=&S2;
	S2.pointer_to_S=&S1;
	
	printf("%d-%d\n",(S1.pointer_to_S)->a,(S1.pointer_to_S)->b); //3 4
	printf("%d-%d\n",(S2.pointer_to_S)->a,(S2.pointer_to_S)->b); //1 2 
	//	printf("%d-%d\n",(*(S2.pointer_to_S)).a,(S2.pointer_to_S)->b);
	struct s z,t;
	z.pointer_to_S=&t; // Linkedlist'in başlangıcı. z, head; t,next
	//----------------------------------------------------------------------------------------------------//
    struct node *head, *node2;
	int num;
	head = malloc(sizeof(struct node)); // Aslında burada head = (struct node*) malloc(sizeof(struct node)); diyor 
	if (head == NULL) {                 // Baştaki (struct node*) demek malloc'dan gelen ADRESİ node adresine çevir demektir
    	return 0;
	}	
    num=10;
	head->val = num;
	head->next = NULL; // Benden sonra kimse yok diyor
	node2 = malloc(sizeof(struct node));
	if (node2 == NULL) {
    	return 0;
	}	
    num=20;
	node2 ->val = num;
	node2 ->next = NULL; // Kendisinden sonra kimseyi göstermeyen struct'larımız var
	head->next = node2; // Burada artık BAĞLADIK
    list(head); // Gezmek için bir fonksiyon tanımlamışız
    //----------------------------------      2. Kod Yapımız   ------------------------------------------------------------------//
    struct node *head, *newHead, *dummy;
	int num;
	head = malloc(sizeof(struct node));
	if (head == NULL) {
    	return 0;
	}	
	
	printf("listenin sonuna eklenmek uzere eleman veriniz\n");
    scanf("%d",&num);
	head->val = num;
	head->next = NULL;
	
	printf("listenin sonuna eklenmek uzere eleman veriniz\n");
    scanf("%d",&num);
	push(head,num);
	
	printf("listenin sonuna eklenmek uzere eleman veriniz\n");
    scanf("%d",&num);
	push(head,num);
	
	printf("listenin sonuna eklenmek uzere eleman veriniz\n");
    scanf("%d",&num);
	push(head,num);
	
	list(head);
	
	printf("listenin basina eklenmek uzere eleman veriniz\n");
    scanf("%d",&num);
	newHead=pushFront(head,num);
	list(newHead);
	
	printf("listeden silinecek elemani veriniz\n");
	scanf("%d",&num);
	if (num==newHead->val) // Listenin başını silmek isterse ikinciyi garantiye alır, head'i free eder ve 2.yi yeni baş ilan eder
	{
		dummy=newHead->next;
		free(newHead);
		newHead=dummy;
	}
	else
		deleteNode(newHead,num);
	list(newHead);
    //-----------------------------------------------------------//
    struct node *dummy2=NULL; // NULL oluşturduk ama bu dummy'yi direkt gönderirsek MAİN'DE ETKİSİ OLMAZ. Bunun ADRESİNİ göndericez
	pushV2(&dummy2);
	pushV2(&dummy2);
	pushV2(&dummy2);
	list(dummy2);

	return 0;
}

void list(struct node *head){ // Gördüğün gibi buraya adres geliyor
	struct node* current = head;
    while (current->next != NULL) { // Benden sonra struct varsa beni yazdır ve beni, benden sonraki olarak güncelle diyor
    	printf("-%d-",current->val);
        current = current->next;
    }
    printf("-%d-",current->val); // Sonuncuya geldiğimize çıktık, o yüzden yazdırmadı. Burada sonuncunun değeri yazdırıyoruz
}
//----------------------------------      2. Fonksiyon Yapımız     ------------------------------------------------------------------//
void push(struct node *head, int val) {
    struct node* current = head; // Başı kaybetmemek için current değişkenine atadık, current'ı ilerletiyoruz ki head'e bişi olmasın
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = malloc(sizeof(struct node)); // En sona geldik. Hemen sonrasını oluşturalım ve değeri verelim.
    current->next->val = val;					
    current->next->next = NULL;	// Sonrayı oluşturmuştuk. Sonranın sonunu getirelimn				
}
void list(struct node *head){
	struct node* current = head;
    printf("liste elemanlari:\n");
	while (current->next != NULL) {
    	printf("-%d-",current->val);
        current = current->next;
    }
    printf("-%d-\n",current->val);
}
struct node* pushFront(struct node *head, int val){
    struct node* newN;
	newN=malloc(sizeof(struct node)); 
	newN->next =head; // Önceki başı bu node'un sonrası yaptı. Artık başımız NewN
	newN->val =val;
    return newN;
}
void deleteNode(struct node *head, int val){
	struct node* current = head, *before=NULL;
    while ((current->val != val)&&(current->next != NULL)){
	    before=current;
		current = current->next;
	}
    // Buradan çıkınca current'ımız silmek istediğimiz değer olacak ve before onun öncesini tutacak ki geri kutuları kaybetmeyelim
    if (current->next == NULL) // Bu demektir ki hiç == val olmadan son kutuya gelmiş. Son kutuda bile yoksa listede yoktur :)
    	printf("silinmek istenen eleman listede yok\n");
    else{
    	before->next=current->next; // Öncekinin elini next'in eliyle birleştirdik
    	free (current);
	}
}

void pushV2(struct node **head){
    struct node* current;
    int val;
    current = malloc(sizeof(struct node));  	
    printf("listenin sonuna eklenmek uzere eleman veriniz");
    scanf("%d",&val);
	current->val = val;
	current->next = NULL;
	if (*head == NULL){ // Gönderilen adreste bir next yoksa ilerleyemeyiz. O yüzden önce o NULL'a az önce oluşturulan kutuyu verelim
		*head = current;
        return;
    }
    struct node* temp = *head; // Yukarıda return olmadıysa buraya gelecek ve en sona gidecek. Temp bizim gezicimiz
    while (temp->next != NULL) {
        temp = temp->next;
        printf("1:%d",temp->val);
    }
    temp->next = current; // En sona geldik ve de bize verileni yerleştirdik
}