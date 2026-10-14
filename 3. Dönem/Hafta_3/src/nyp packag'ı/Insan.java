package nyp;

import java.util.Date;

public class Insan {
    private String ad;
    private String soyad;
    private String tcKimlikNo;
    private Date dogumTarihi;
    private Araba arabalar[]; // başlangıçta adedi yok
    private int arabaSayisi;

    public Insan(String ad, String soyad, String tcKimlikNo){
        this.ad = ad;
        this.soyad = soyad;
        this.tcKimlikNo = tcKimlikNo;
        arabaSayisi = 0;
        arabalar = new Araba[9]; // Şu an 9 tane araba objesi oluşmadı, referans verebileceğimiz array oluştu. Şu an içi null dolu
    }

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

    public String getTcKimlikNo(){
        return tcKimlikNo;
    }

    public void setTcKimlikNo(String tcKimlikNo){
        this.tcKimlikNo = tcKimlikNo;
    }

    public Date getDogumTarihi(){
        return dogumTarihi;
    }

    public void setDogumTarihi(Date dogumTarihi){
        this.dogumTarihi = dogumTarihi;
    }

    public String arabalariListele(){
        String temp = "Merhaba ben " + this.ad + ".";
        if(this.arabaSayisi != 0){ // if kontrolü için this'i kontrol ediyoruz!
            temp = temp + "Arabalarimin listesi asagidaki gibidir: \n";
            for(int i=0; i<arabaSayisi; i++){
                temp = temp + (i+1) + ")" + arabalar[i].getMarka() + " " + arabalar[i].getModel() + "\n";
            }
        }
        return temp;
    }

    public boolean setAraba(Araba gelenAraba){
        if(!gelenAraba.sahibiVarMi() && arabalar.length != arabaSayisi){
            arabalar[arabaSayisi++] = gelenAraba; // this.arabalar[this.arabaSayisi] = gelenAraba da denebilir. Daha sonra ++ yazarız
            return true;
        }else return false;
    }

    public boolean arabaSat(Araba beklenen, Insan alici){
        int  i = 0;
        while(i < arabalar.length && beklenen != arabalar[i]) i++;

        if(i == arabalar.length){
            return false; // Demek ki satılmak istenen, listede yokmuş
        }else{
            arabaSayisi--;
            arabalar[i] = null;
            while(i < arabaSayisi-1){
                arabalar[i] = arabalar[i+1];
                i++;
            }
            alici.setAraba(beklenen); // Şu an Insan class'ı içindeyiz. alici, setAraba Methodundaki this kısmı yerine geçiyor
            return true;
        }
    }

    public String toString(){
        return arabalariListele();
    }
}
