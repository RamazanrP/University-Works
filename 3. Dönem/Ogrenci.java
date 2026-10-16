package nyp;

public class Ogrenci {
    private String ad;
    private String soyad;
    private int ogrNo;
    private Ders[] dersler;
    private int dersSayisi;

    public String getAd(){
        return ad;
    }

    public void setAd(String ad){
        this.ad = ad;
    }

    public String getSoyad(){
        return soyad;
    }

    public void setSoyad(String soyad){
        this.soyad = soyad;
    }

    public int getOgrNo(){
        return ogrNo;
    }

    public void setOgrNo(int ogrNo){
        this.ogrNo = ogrNo;
    }

    public Ogrenci(String ad, String soyad, int ogrNo){
        this.ad = ad;
        this.soyad = soyad;
        this.ogrNo = ogrNo;
        // Ders[] dersler = new Ders[5]; -> BU HATALIII
        this.dersler = new Ders[5]; 
        this.dersSayisi = 0;
    }
    public boolean derseKaydol(Ders ders){
        if(dersSayisi >= 5 || !(ders.ogrenciEkle(this))) return false; // Öğrencinin kapasitesini düşündüğümüz gibi dersininkini de düşünmeliydik
        dersler[dersSayisi++] = ders;
        return true;
    }

    public boolean derstenAyril(Ders ders){
        // Burada ya söylenen ders listede olmayacak ya da listeden silip geri kalanları kaydırcaz
        int i=0;
        while(i<dersSayisi && dersler[i] != ders) i++; // i<5 değil i< dersSayisi
        if(i == dersSayisi) return false; // demek ki liste bulamadan bitmiş
        if(ders.ogrenciCikar(this)){
            dersSayisi--;
            while(i< dersSayisi){
                dersler[i] = dersler[i+1];
                i++;
            }
            dersler[dersSayisi] = null;
            return true;
        }
        return false; // ogrenciCikar başarısız olursa diye
    }

    public void dersleriListele(){
        String temp;
        temp = "Merhaba ben " + this.ogrNo + " numarali ogrenci "+ this.ad + " " + this.soyad + ". Ve de bunlar benim sectigim derslerim:\n";
        System.out.println(temp);
        for(int i=0; i<dersSayisi; i++){
            System.out.println((i+1) + ") " + dersler[i].getDersAdi());
        }
    }
}
