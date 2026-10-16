package nyp;

public class Ders {
    private String dersKodu;
    private String dersAdi;
    private int kredi;
    private int kapasite;

    private Ogrenci[] ogrenciler;
    private int ogrenciSayisi;

    public String getDersKodu(){
        return dersKodu;
    }
    public void setDersKodu(String dersKodu){
        this.dersKodu = dersKodu;
    }

    public String getDersAdi(){
        return dersAdi;
    }
    public void setDersAdi(String dersAdi){
        this.dersAdi = dersAdi;
    }

    public int getKredi(){
        return kredi;
    }
    public void setKredi(int kredi){
        this.kredi = kredi;
    }

    public int getKapasite(){
        return kapasite;
    }
    public void setKapasite(int kapasite){
        this.kapasite = kapasite;
    }

    public Ders(String dersKodu, String dersAdi, int kredi, int kapasite){
        this.dersKodu = dersKodu;
        this.dersAdi = dersAdi;
        this.kredi = kredi;
        this.kapasite = kapasite;
        this.ogrenciler = new Ogrenci[kapasite];
        this.ogrenciSayisi = 0;
    }
    public boolean ogrenciEkle(Ogrenci eklenen){
        if(ogrenciSayisi >= kapasite) return false;
        ogrenciler[ogrenciSayisi++] = eklenen;
        return true;
    }

    public boolean ogrenciCikar(Ogrenci cikarilacak){
        int i=0;
        while(i<ogrenciSayisi && ogrenciler[i] != cikarilacak) i++;
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
        String temp;
        temp = this.dersKodu + " koduna sahip " + this.dersAdi + " dersini alan ogrenciler asagidaki gibidir: \n";
        System.out.println(temp);
        for(int i=0; i<ogrenciSayisi; i++){
            System.out.println((i+1) + ") " + ogrenciler[i].getAd() + " " + ogrenciler[i].getSoyad());
        }
    }
}
