// ========== 2021 Lab 1 ================= //
public abstract class Calisan{ // Yazım doğru, böyle olmalı
    private String name;
    private int calisilanYil;
    private double maas;

    public abstract void zamYap(); // void unutma ve de {} YOK 
    // getter setter yazdık farz edelim
    public String kendiniTanit(){
        String intro = "Merhaba. Benim ismim " + getName()
        + "Calistigim yil miktari" + getCalisilanYil()
        + "Maasim da " + getMaas();
        return intro;
    }
}

public class Analist extends Calisan{

    public void zamYap(){
        setMaas(1.1 * getMaas());
        setCalisilanYil(getCalisilanYil() + 1);
    }
    
    
}

public class Yazilimci extends Calisan{
    private int certCount;
    public void zamYap(){
        setMaas(1.15 * maas); // =======> HATALI
        setMaas(1.10 * getMaas());
        setCalisilanYil(++calisilanYil); // =======> HATALI
        setCalisilanYil(getCalisilanYil() + 1);
    }

    public String kendiniTanit(){
        String intro = super.kendiniTanit();
        return intro + " ve " getCertCount() + " adet de sertifikam var";         
    }

}

// Departmanda da çalışan sayısı olmasını beklerim

public class Departman{
    private Calisan[] ekip;
    public static final int maxCalisanSayisi = 3;
    private int calisanSayisi; // Bunu constructor da 0 yaptığımı düşün
}

public class Sirket{
    public static final int departmantSayisi = 4;
    private Departman[] deps;
}

// boolean olmasını tercih ettim ben
public boolean calisanEkle(Calisan eklenecek){
    for(int i=0; i< departmantSayisi; i++){
        if(deps[i].calisanSayisi < 3){
            for(int j=0; j< maxCalisanSayisi; j++){
                if(deps[i].ekip[j] == null){
                    deps[i].ekip[j] = eklenecek;
                    deps[i].calisanSayisi++; // Bunu unutmuşum
                    return true;
                }
            }
        }
    }
    return false;
}

public double depOrtMaas(int depNo){
    if(depNo < 0 || depNo > 3) return 0.0;
    int count = 0;
    double sum = 0.0;
    for(int i=0; i< deps[depNo].calisanSayisi; i++){
        if(deps[depNo].ekip[i] != null){
            count++;
            sum += deps[depNo].ekip[i].getMaas();
        }
    }
    return count == 0 ? 0.0 : sum / count;
}

public void maxGorevYili(){
    // Tüm şirkette aricam
    int max = 0;
    for(int i=0; i< departmantSayisi; i++){
        for(int j=0; j< maxCalisanSayisi; j++){
            if(deps[i].ekip[j] != null && deps[i].ekip[j].getCalisilanYil() > max){
                max = deps[i].ekip[j].getCalisilanYil();
            }
        }
        
    }

    for(int i=0; i< departmantSayisi; i++){
        for(int j=0; j< maxCalisanSayisi; j++){
            if(deps[i].ekip[j] != null && deps[i].ekip[j].getCalisilanYil() == max){
                System.out.println(deps[i].ekip[j].kendiniTanit());
            }
        }
        
    }
}

public void sirketiTanit(){
    // Bu koda çok emek verdim o yüzden düzeltme yapmayacağım :)
    int aSayac=0, ySayac=0;
    int[][] depSayac = new int[2][4]; // Bunu yapmak istedim son mesaj için
    for(int i=0; i< departmantSayisi; i++){
        for(int j=0; j< maxCalisanSayisi; j++){
            if(deps[i].ekip[j] != null && deps[i].ekip[j] instanceof Analist){
                aSayac++;
                System.out.println("Ben Analist-" + aSayac 
                + deps[i].ekip[j].getCalisilanYil() + " yildir calisiyorum"
                + deps[i].ekip[j].getMaas() + " lira maas aliyorum");
                depSayac[0][i]++;
            }else if(deps[i].ekip[j] != null && deps[i].ekip[j] instanceof Yazilimci){
                ySayac++;
                System.out.println("Ben Yazilimci-" + ySayac 
                + deps[i].ekip[j].getCalisilanYil() + " yildir calisiyorum"
                + deps[i].ekip[j].getMaas() + " lira maas aliyorum"
                + ((Yazilimci)deps[i].ekip[j].getCertCount()) + " adet sertifikam var");
                depSayac[1][i]++;
            }
        }
    }
    for(int i=0; i<departmantSayisi; i++){
        System.out.println(i + "numarali Departmanda"
        + depSayac[0][i] + "adet Analist,"
        + depSayac[1][i] + " adet Yazilimci vardir.");
    }
    return;
}
