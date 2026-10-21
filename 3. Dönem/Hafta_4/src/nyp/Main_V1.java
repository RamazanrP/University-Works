package nyp04;

public class Main_01 {
    public static void main(String args[]){
        Person oktay;
        oktay = new Person("Oktay Sinanoglu");
        Car rover = new Car("34 AN 987");
        oktay.setAraba(rover);
        System.out.println(oktay.introduceSelf()); // main de introduce methodu yok. oktay'ın altında var. oktay.Method(İÇİNİ BOŞ BIRAK);
        Person aziz = new Person("Aziz Sancar");
        System.out.println(aziz.introduceSelf());
    }
    
}
