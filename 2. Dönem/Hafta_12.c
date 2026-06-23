#include <stdio.h>
#include <stdlib.h>
#define EOF_FLAG 1 // Bit düzeyinde bayraklar
#define ERR_FLAG 2
#define NAME_LEN 20

typedef struct {
	char isim[20], soyisim[20];
	int numara;
	float puan;
}OGRENCI;

typedef struct vitalstat
{ 
 	char vs_name[NAME_LEN]; 
	char vs_ssnum[NAME_LEN]; 
	int vs_day;
	int vs_month;
	int vs_year;
} VITALSTAT; 

typedef struct
{ 
 	int dyil;
	int puan;
	char isim[NAME_LEN]; 
	char soyisim[NAME_LEN];
} OGR; 

typedef struct Atlet
{
    char ad[15];
    char soyad[15];
    int sure;
    struct Atlet *next;
} Atlet;

FILE *open_file(char* file_name, char* mode){
  FILE *fp;
  fp = fopen(file_name, mode);
  
  if (fp == NULL) {
    /* * freopen: Standart hata (stderr) akışını ekranda göstermek yerine 
     * "error.txt" dosyasına "a" (append - sonuna ekle) modunda yönlendirir.
     * Yani program çökerse ekranda hata görmezsin, hatayı log dosyasına yazar.
     */
	freopen("error.txt", "a", stderr);
    
    /* Hata mesajını stdout (standart ekran) yerine stderr (standart hata) akışına basar */
	fprintf(stderr, "Error opening file: %s\n", file_name);
    
    /* Programı anında sonlandırır. (Not: 0 başarı demektir, 1 olmalıydı. Aşağıda anlattım) */
    exit (0);
  }
  return fp;
}

/* * ferror ve feof komutları dosya akışında (stream) bir anormallik olup olmadığını söyler.
 * Stat değişkeni bit düzeyinde VEYA (|=) işlemi ile doldurulur.
 */
char check_file(FILE* fp) {
  char stat = 0; // Başlangıçta 0 (Binary: 00)
  
  if (ferror(fp))	// Örn: Sadece okuma ("r") modunda açılan dosyaya yazmaya çalışırsan tetiklenir
  	stat |= ERR_FLAG; // stat = stat | 2; (Binary: 10 olur)
    
  if (feof(fp))		// Dosyanın sonuna (End Of File) gelindiğinde tetiklenir
  	stat |= EOF_FLAG; // stat = stat | 1; (Binary: 01 veya 11 olur)
    
  /* Hata ve EOF bayraklarını sıfırlar ki sonraki okumalarda eski hatalar karşımıza çıkmasın */
  clearerr(fp); 
  
  return stat;
}

int main(){
  char file_name[100], mode[3], stat; 
  FILE *fp; 
  
  printf("Acilacak dosyanin adini girin: \n"); 
  scanf("%s", file_name);
  
  printf("Erisim modunu girin (r, w, a vb.): \n"); 
  scanf("%2s", mode);
  
  fp = open_file(file_name, mode);
  
  /* ... okuma/yazma işlemleri ... */
  
  stat = check_file(fp);
  
  if (stat == 0)
  	printf("Her sey yolunda, hata yok.\n"); 
  else
  	printf("Hata kodu: %d\n", stat); 
    /* Çıktı 1 ise: Sadece dosya sonu (EOF)
       Çıktı 2 ise: Sadece okuma/yazma hatası
       Çıktı 3 ise: Hem hata var hem de dosya sonuna gelinmiş (1 | 2 = 3)
    */
    
  fclose(fp); // İşin bitince dosyayı kapatmak ZORUNLUDUR!
  return 0; 
}
//-------------------------------------------------------------------------------------------------------------------------//
#define FAIL 0 
#define SUCCESS 1 
#define LINESIZE 100

    // YÖNTEM 1: SATIR SATIR KOPYALAMA (Daha Hızlı ve Güvenli)
int copyfileLinebyLine(char * infile, char * outfile) { 
	FILE *fp1, *fp2; 
	char line [LINESIZE]; /* Arabellek (Buffer) - Veriyi RAM'de tutacağımız geçici oda */
	int lineNum=0;
	
    if ((fp1 = fopen( infile, "r" )) == NULL) return FAIL; 
	if ((fp2 = fopen( outfile, "w" )) == NULL) { 
		fclose (fp1); // Buraya gelip de içeri girdiyse demek ki fp1 açılmış ama fp2 açılamamış. Sadece açılanı kapatıyoruz
		return FAIL; 
	}
	
	/* * fgets(), dosyadan "\n" (alt satır) görene kadar VEYA 99 karakter (LINESIZE-1)
     * okuyana kadar veriyi çeker ve sonuna gizlice '\0' (NULL) ekler.
     * Dosya bittiğinde NULL döner ve döngü tertemiz biter.
	 */
	while (fgets(line, LINESIZE-1, fp1) != NULL) {
		fputs(line, fp2); /* Okunan satırı diğer dosyaya basar */
		lineNum++;
	}
	
    fprintf(fp2, "dosyada %d line var\n", lineNum);
	fclose(fp1); 
	fclose(fp2); 
	return SUCCESS; 
}

/* =================================================================*/
/*   YÖNTEM 2: KARAKTER KARAKTER KOPYALAMA (Amelelik Yöntemi)       */
/*================================================================= */
int copyfileCharbyChar(char * infile, char * outfile) { 
	FILE *fp1, *fp2; 
	char ch, ch2; 
	int charNum=0;
	
    if ((fp1 = fopen( infile, "r" )) == NULL) return FAIL; 
	
    /* DİKKAT: "w" (Write) yerine "a" (Append) kullanılmış. 
     * Bu sayede Yöntem 1'in yazdıklarını silmez, dosyanın sonundan eklemeye devam eder. */
    if ((fp2 = fopen( outfile, "a" )) == NULL) { 
		fclose (fp1); 
		return FAIL; 
	}
	
    /* HOCA BURADA BİLEREK/BİLMEYEREK İLK KARAKTERİ YAKIYOR! 
     * fscanf ile ilk harfi okuyup 'ch2'ye atıyor ama hiçbir yere yazmıyor. */
	fscanf(fp1, "%c", &ch2); 
	
	ch = getc(fp1);	/* Gerçek okuma buradan başlıyor */					
	while (!feof(fp1)) {
		putc(ch, fp2);   
		ch = getc(fp1);  
		charNum++;
	}

	fprintf(fp2, "dosyada %d char var\n", charNum);
    fclose(fp1); 
	fclose(fp2); 
	return SUCCESS; 
}
//-------------------------------------------------------------------------------------------------------------------------//
void dosyaOlustur(char* ); //verilen bir isimdeki dosyayı wb modda acar. Kayit sayisini ogrenir. Kayitlar icin yer alloce eder, bilgileri alir 
void dosyayaYaz(FILE*,int,OGRENCI*); //kendisine gönderilen file*'a yine kendisine g�nderilen bilgileri yazar
FILE * dosyaAc(char*,char*); //verilen isimdeki bir dosyayi istenen formatta açar ve file döndürür
void dosyaListele(FILE *);  //kendisine gönderilen file 'daki kayıtları listeler

int main()
{
	FILE *fa,*fb,*fs;
	OGRENCI ogr1,ogr2;
	char dosyaA[30],dosyaB[30],dosyaC[30];
	printf("sirasiyla giris dosyalarinin ve cikis dosyanin adlarini veriniz\n");
	scanf("%s %s %s",dosyaA,dosyaB,dosyaC);
	dosyaOlustur(dosyaA);
	dosyaOlustur(dosyaB);
	fa=dosyaAc(dosyaA,"rb");
	fb=dosyaAc(dosyaB,"rb");
	fs=dosyaAc(dosyaC,"wb");
	fread(&ogr1,sizeof(OGRENCI),1,fa); //BINARY (İKİLİ) OKUMA: fgets veya fscanf kullanılmaz!
	fread(&ogr2,sizeof(OGRENCI),1,fb);
	
	while (!feof(fa) && !feof(fb))
	{
		if (ogr1.puan<ogr2.puan) // ogr2 büyükse
		{
			fwrite(&ogr2, sizeof(OGRENCI),1,fs); // çıkş dosyasına mevcut ogr2'yi yaz
			fread(&ogr2, sizeof(OGRENCI),1,fb);	// Sıradali ogr22ye geç, onu karşılaştırmaya alcaz
		}
		else
		{
			fwrite (&ogr1,sizeof(OGRENCI),1,fs);
			fread(&ogr1, sizeof(OGRENCI),1,fa);   			
		}
	}
	
	if (feof(fa)) // fa'da o kadar büyük vardı ki dosya bitti, fb'yi "dosya sonuna gelene kadar" oku ve geçir
	{
		while (!feof(fb))
		{
			fwrite (&ogr2,sizeof(OGRENCI),1,fs);
			fread(&ogr2,sizeof(OGRENCI),1,fb);
		}
	}
	else
	{
		while (!feof(fa))
		{
			fwrite (&ogr1,sizeof(OGRENCI),1,fs);
			fread(&ogr1,sizeof(OGRENCI),1,fa);
		}
	}

	fclose(fa);
	fclose(fb);
	fclose(fs); // Yukarda wb modunda açmıştık, iki işlemi tek seferde yapamayız önce kapatmalıyız
	fs=dosyaAc(dosyaC,"rb"); // Şimdi tekrar açtık, işimizi gördük
	dosyaListele(fs); 
	fclose(fs); // 2. defa kapatıyoruz
}

FILE* dosyaAc(char *dosya_ad, char mode[3])
{
	FILE *fs;
	fs=fopen (dosya_ad,mode);
	if (fs==NULL)
	{
		printf("dosya acilamadi\n");
		exit(0);
	}
	return fs;
}
void dosyayaYaz(FILE* fs, int n, OGRENCI* data)
{
	fwrite (data,sizeof(OGRENCI),n,fs);
}

void dosyaOlustur(char* dosya_ad)
{
	int n,i;
	OGRENCI ogr, *ogrDizi;
	FILE *fs;
	fs=dosyaAc(dosya_ad,"wb");
	printf("kitapcikta kac ogrenci var\n");
	scanf("%d",&n);
	ogrDizi=(OGRENCI*) calloc (n, sizeof(OGRENCI));
	printf("azalan puan sirasi ile ogrenci bilgilerini veriniz (isim,soyisim,numara,puan)\n");
	for (i=0;i<n;i++)
		scanf("%s %s %d %f",ogrDizi[i].isim,ogrDizi[i].soyisim,&ogrDizi[i].numara,&ogrDizi[i].puan);

	dosyayaYaz(fs,n,ogrDizi);
	fclose(fs);
	free(ogrDizi);
}
	
void dosyaListele(FILE *fs)
{
	OGRENCI ogr;
	fread(&ogr,sizeof(OGRENCI),1,fs);
	while (!feof (fs))
	{
		printf("%s %s %d %f\n",ogr.isim,ogr.soyisim,ogr.numara,ogr.puan);
		fread(&ogr,sizeof(OGRENCI),1,fs);
	}
}

//-------------------------------------------------------------------------------------------------------------------------//

void printf_file(char filename[])
{
	int nb,i,day,month,year;
	VITALSTAT vs;
	FILE *fs=fopen (filename,"wb");
	if (fs==NULL)
	{
		printf("not opened\n");
		exit(0);
	}
	
	printf("kac kayit var\n");
	scanf("%d",&nb);
	printf("bilgilerini veriniz\n");
	for (i=0;i<nb;i++)
	{
		scanf("%s %s %d %d %d",vs.vs_name,vs.vs_ssnum, &vs.vs_day, &vs.vs_month, &vs.vs_year);
		fwrite (&vs,sizeof(VITALSTAT),1,fs);	
	}
	
	fclose(fs);
}
void list_file(FILE *fs)
{
	VITALSTAT vs;
	printf("kisi listesi:\n");
	fseek( fs, 0, SEEK_SET);
	fread(&vs,sizeof(VITALSTAT),1,fs);
	while(!feof(fs))	
	{
	printf("%s %s %d %d %d\n",vs.vs_name,vs.vs_ssnum, vs.vs_day, vs.vs_month, vs.vs_year);
	fread(&vs,sizeof(VITALSTAT),1,fs);
    }
}
int main()
{
	char filename[20];
	FILE *data_file; 
	int k=0,stat=0;
	long offset=0,boyut;
	VITALSTAT vs;
	printf("olusturulacak dosya ismini veriniz\n");
	scanf( "%s", filename ); 
	printf_file(filename);
	data_file = fopen( filename, "r+b" ); 
	if (data_file == NULL) 
	{ 
		printf( "Error opening file %s.\n", filename ); 
		exit ( 1 ); 
	}
 	
	list_file(data_file);
    
	printf("kacinci kisiye ulasmak istiyorsunuz?\n");
    scanf("%d",&k);
    offset=k*sizeof(VITALSTAT);
    stat=fseek( data_file, offset, SEEK_SET);
    fread(&vs,sizeof(VITALSTAT),1,data_file);
    printf("ilgili kisinin bilgileri:\n");
    printf("%s %s %d %d %d\n",vs.vs_name,vs.vs_ssnum, vs.vs_day, vs.vs_month, vs.vs_year);
    printf("yeni dogum yili?\n");
    scanf("%d",&vs.vs_year);
    //stat=fseek( data_file, offset, SEEK_SET); Alttakini yapmak yerine bu da olurdu
	stat=fseek( data_file, -sizeof(VITALSTAT), SEEK_CUR); // fonksiyonun yapısı gereği bir ilerler. -size yazarak bir paket geriye alıp üzerine yazıyoruz
    fwrite(&vs,sizeof(VITALSTAT),1,data_file);
    list_file(data_file);
	
}
//-------------------------------------------------------------------------------------------------------------------------//
int main()
{
	char filename[20];
	FILE *data_file; 
	int k=0,nb,yil,puan;
	long offset=0,boyut;
	OGR ogr;
	printf("dosya ismi veriniz\n");
	scanf( "%s", filename ); 
	printf_file(filename);
	data_file = fopen( filename, "rb+" ); 
	if (data_file == NULL) 
	{ 
		printf( "Error opening file %s.\n", filename ); 
		exit ( 1 ); 
	}
	list_file(data_file);
	fseek( data_file, 0, SEEK_END);
 	nb=ftell(data_file)/sizeof(OGR); // ftell: Baştan sona kaç byte olduğunu söyler, Bunu struct boyutuna bölersen adedi bulursun
 	fseek( data_file, 0, SEEK_SET);
	/*
	Aşağıdaki while bloğu tehlikeli. Neden? Aslında şu an sorun yok çünkü OGR yapısının ilk iki field'ı int (yıl ve puan)
	Eğer bunda eminsek yapmak belki güvenli ama farklı field'lar olsaydı Compiler arada padding eklerdi ve 
	biz yıl'dan hemen sonra puan okumaya kalkışsaydık yanlış byte dizisini okumaya kalkardık. O yüzden güvenli olan:
	Struct'ı bütün bir kalıp olarak RAM'e çek, RAM'de değiştir ve kalıp olarak geri bas.
	*/
	
	while(k<nb)
    {
		fread (&yil,sizeof(int),1,data_file);	
		if (yil>2000)
		{
			fread (&puan,sizeof(int),1,data_file);	
			puan=puan+10;
			fseek( data_file, -sizeof(int), SEEK_CUR);
			fwrite (&puan,sizeof(int),1,data_file);	
		}
		// offset ilk başta 0'dı. Yukarda if'e girip girmediği belli değil. İmlecimiz kaybolmasın diye tam bir OGR kadar ilerliyor(zorla)
		offset=offset+sizeof(OGR);
		fseek( data_file, offset, SEEK_SET);
		k++;
	}
	
	
	//yerleşiminden emin olmadığımız bir structure varsa her structure elemanı bütün olarak okumak gerekir
	/*	
	fread (&ogr,sizeof(OGR),1,data_file);
	while(k<nb)		
    {
		printf("%d\n",ogr.dyil);
		if (ogr.dyil>2000)
		{
			ogr.puan=ogr.puan+10; Struct'tan arttırdı
			fseek( data_file, -sizeof(OGR), SEEK_CUR); ==> if'e girdiği için azaltma yapmalıydık
			fwrite (&ogr,sizeof(OGR),1,data_file);	
		}
		==> Burada offset'e gerek yok çünkü zaten hep bir OGR kadar ilerliyor, fazla ilerlerse geri çekiyor
		fread (&ogr,sizeof(OGR),1,data_file);	
		k++;
	}
	*/
	list_file(data_file);
	return 0;
}
//----------------------------------    LİNKED & FİLE	 --------------------------------------------------------//
void dosyaya_yaz(Atlet *head){
    FILE *fp = fopen("atletler.csv", "w");
	Atlet *temp = head;
	while (temp != NULL){
        fprintf(fp, "%s,%s,%d\n",temp->ad,temp->soyad,temp->sure);
		temp = temp->next;
    }
	fclose(fp);
}
Atlet* ekle(Atlet *head){
    Atlet *yeni = (Atlet*)malloc(sizeof(Atlet));
	printf("ad: "); scanf("%s", yeni->ad);
	printf("soyad: "); scanf("%s", yeni->soyad);
	printf("sure: "); scanf("%d", &yeni->sure);

    yeni->next = NULL;
	if (head == NULL)
        head = yeni;
    else{
        Atlet *temp = head;
        while (temp->next != NULL) temp = temp->next;

        temp->next = yeni;
    }

    return head;
}
void listele(Atlet *head){
    Atlet *temp = head;
	while (temp != NULL){
        printf("Ad: %s | Soyad: %s | Sure: %d\n",temp->ad,temp->soyad,temp->sure);
		temp = temp->next;
    }
}
void guncelle(Atlet *head){
    char ad[15], soyad[15];
    int bulundu = 0;

    printf("guncellenecek atlet ad: "); scanf("%s", ad);
	printf("soyad: "); scanf("%s", soyad);
	Atlet *temp = head;
	while (temp != NULL && bulundu == 0){
        if (strcmp(temp->ad, ad) == 0 && strcmp(temp->soyad, soyad) == 0){
            printf("yeni sure: ");
            scanf("%d", &temp->sure);

            bulundu = 1;
        }

        temp = temp->next;
    }

    if (bulundu == 0)
    {
        printf("atlet bulunamadi\n");
    }
    else
    {
        dosyaya_yaz(head);
        printf("dosya guncellendi\n");
    }
}
void dosyadan_oku_ve_listele()
{
    FILE *fp = fopen("atletler.csv", "r");

    if (fp == NULL)
    {
        printf("dosya acilamadi\n");
        return;
    }

    char satir[100];

    printf("\n--- DOSYADAKI ATLETLER ---\n");

    while (fgets(satir, sizeof(satir), fp) != NULL) // "fp'ye git, size kadar oku ve satir'a ata" diyor
    {
        char ad[15], soyad[15];
        int sure;
		//sscanf() C'de bir string (char dizisi) içinden formatlı veri okumaya yarar.
		//alternatifi strtok => AMELE USÜLÜ
		/*
		token = strtok(satir, ",");			strcpy(ad, token); ilk kısım ad, sonraki soyad, sonraki de sure olarak ayırdı

		token = strtok(NULL, ",");			strcpy(soyad, token);

		token = strtok(NULL, ",");			sure = atoi(token);
		*/
		// Buradaki %[^,] ifadesi bilgisayara şunu söyler: "Virgül görene kadar ne var ne yoksa string olarak oku ve değişkene at"
        sscanf(satir, "%[^,],%[^,],%d", ad, soyad, &sure);

        printf("Ad: %s | Soyad: %s | Sure: %d\n", ad, soyad, sure);
    }
	fclose(fp);
}

int main(){
    Atlet *head = NULL;
    int n, i, secim=1;

    printf("kac atlet gireceksiniz: ");
    scanf("%d", &n);
	for (i = 0; i < n; i++) head = ekle(head);

    dosyaya_yaz(head);

    while (secim!=4)
    {
        printf("\n1-Listele (Linked List)\n");
        printf("2-Guncelle (Linkli liste ve dosyada guncelle)\n");
        printf("3-Dosyadan Oku ve Listele\n");
        printf("4-Cikis\n");
        printf("Secim: ");

        scanf("%d", &secim);

        if (secim == 1)
            listele(head);

        else if (secim == 2)
            guncelle(head);

        else if (secim == 3)
            dosyadan_oku_ve_listele();
        
    }
	free(head);
    return 0;
}