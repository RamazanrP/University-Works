/*
src -> Kaynak kodlarım burada 
 ↓
nyp -> Sınıflar nyp package'nda olacak
 ↓
Araba.java Ve de 3 class'ımız
Insan.java
Mainner.java
*/
package nyp;


public class Araba { // public class dediğin anda dosya adı Araba.java olur
    private String marka;
    private String model;
    private String renk;
    public int sasiNo;
    private boolean otomatikMi;
    private boolean sahibiVarMi;

    public Araba(){
        sahibiVarMi = false; // Araba üretilir üretilmez sahibi yok diyoruz
    }

    public Araba(String marka, String model, int sasiNo){ // Constructor'un return type'ı yoktur. public Araba() diye yazılır
        this.marka = marka; // this.xxxx -> class'ın field'ı / = xxxx constructor'ın parametresi
        this.model = model;
        this.sasiNo = sasiNo;
        sahibiVarMi = false;
    }

    public boolean sahibiVarMi(){
        return sahibiVarMi;
    }

    public void setSahibiVarMi(boolean sahibiVarMi){
        this.sahibiVarMi = sahibiVarMi;
    }

    // Getter -> Dışardan okuyabilme && Setter -> Değiştirebilme
    // Set ve Get genelde private değişkenler için kullanılır. Çünkü dışardan erişim sağlar bize
    public String getMarka(){   //getter lar da parametre döndürüyor!
        return marka;
    }

    public void setMarka(String marka){ // Setterlar void !
        this.marka = marka;
    }

    public String getModel(){
        return  model;
    }
    
    public void setModel(String model){
        this.model = model;
    }

    public int getSasiNo(){
        return sasiNo;
    }

    public void setSasiNo(int sasiNo){
        this.sasiNo = sasiNo;
    }

    public String getRenk(){
        return renk;
    }

    public void setRenk(String renk){
        this.renk = renk;
    }

    public boolean isOtomatikMi(){ // boolean'ların get'inde is kullanılıyor dikkat!!!
        return otomatikMi;
    }

    public void setOtomatikMi(boolean otomatikMi){
        this.otomatikMi = otomatikMi;
    }

    public String toString(){
        String temp;
        temp = "Merhaba ben bir arabayim.";
        temp = temp + "Markam: " + this.marka + "modelim: " + this.model;
        return temp;
    }

}
