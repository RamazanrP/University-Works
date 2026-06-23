#include <stdio.h>
enum SiparisDurumu { 
    HAZIRLANIYOR, 
    KARGODA, 
    TESLIM_EDILDI, 
    IPTAL_EDILDI 
};
void durumuYazdir(enum SiparisDurumu durum) {
    switch(durum) {
        case HAZIRLANIYOR: printf("Durum: Hazirlaniyor...\n"); break;
        case KARGODA: printf("Durum: Kargoda...\n"); break;
        case TESLIM_EDILDI: printf("Durum: Teslim edildi!\n"); break;
        case IPTAL_EDILDI: printf("Durum: Iptal edildi!\n"); break;
        default: printf("Durum: Bilinmeyen hata!\n");
    }
}
int main(){
printf("%d", 010);
printf("%o", 8);
printf("%x", 16);

/* * ENUM NEDIR?
 * enum, belirli değişkenlere isim vererek onları gruplamamızı sağlar.
 * C dili varsayılan olarak ilk elemana 0 verir, sonrakileri birer birer artırır.
 * Yani: SUNDAY=0, MONDAY=1, TUESDAY=2, WEDNESDAY=3 ... şeklinde devam eder.*/

enum SiparisDurumu siparis1 = KARGODA; // Doğru ve Kullanıcı dostu yazım
durumuYazdir(siparis1);
enum SiparisDurumu siparis2 = 0; // 2. KULLANICI DOSTU DEĞİL (Magic Number)
durumuYazdir(siparis2);
durumuYazdir(siparis2 + 1); // 3. UYGUN KULLANIM DEĞİL (Enum ile matematik yapmak)
// -------------------------------------------------------//
typedef long int INT32; // Değişken adımızı kendimizin belirlemesine imkan tanır
INT32 sayi;
//-------------------------------------------------------//
float j = 3/2;
printf("%f", j); // 1.5 değil 1 diye çıkar çünkü 3 ve 2 integer!! Bundan kurtulmak için ya 3.0/2 veya j = float(...); yazılmalıydı
return 0;
}