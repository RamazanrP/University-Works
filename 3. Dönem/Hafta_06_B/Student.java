package Hafta_06_B;

public class Student extends Person{

    public Student(){
        super();
    }

    public String introduceSelf(){
        String intro2 = super.introduceSelf();
        String intro = intro2 +  " Ayni zamanda da ben bir ogrenciyim";
        return  intro;
    }

    public String kendineAitMethod(){
        return "Kendime aidim";
    }
}
