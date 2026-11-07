package Hafta_06_B;

public class Person {
    protected int sayi1;
    protected final int sayi2; 
    // Final denilene 1 KERE ATAMA YAPILIR YAPILMADAN BIRAKILAMAZ. 
    // AŞAĞIDAKİNİ YAPANA KADAR HATA VERİYORDU !!! 
    public Person(){
        this.sayi1 = 1;
        this.sayi2 = 2;
    }

    public String introduceSelf(){
        String intro;
        intro = "Ben bir insanim";
        return  intro;
    }

    public  final String introduceSelf2(){ // İlerde Kullanacağız
        String intro;
        intro = "Ben bir insandim";
        return  intro;
    }
}
