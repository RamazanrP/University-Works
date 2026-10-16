package nyp;

public class Universite {
    private String ad;
    private Ogrenci[] ogrenciler;
    private int ogrenciSayisi;

    public String getAd(){
        return ad;
    }
    public void setAd(String ad){
        this.ad = ad;
    }
    public Universite(String ad){
        this.ad = ad;
        this.ogrenciler = new Ogrenci[30];
        this.ogrenciSayisi = 0;
    }

    public boolean ogrenciEkle(Ogrenci ogrenci){
        if(ogrenciSayisi >= 30 ) return false;
        ogrenciler[ogrenciSayisi++] = ogrenci;
        return true;
    }
    public boolean ogrenciCikar(Ogrenci ogrenci){
        int i=0;
        while(i < ogrenciSayisi && ogrenciler[i] != ogrenci) i++;
        if(i == ogrenciSayisi) return false;
        ogrenciSayisi--;
        while(i < ogrenciSayisi) {
            ogrenciler[i] = ogrenciler[i+1];
            i++;
        }
        ogrenciler[ogrenciSayisi] = null;
        return true;
    }
    public void ogrencileriListele(){
        for(int i=0; i<ogrenciSayisi; i++){
            System.out.println((i+1) + ") " + ogrenciler[i].getAd() + " " + ogrenciler[i].getSoyad());
        }
    }
}
