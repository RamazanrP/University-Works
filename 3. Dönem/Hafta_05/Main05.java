package Hafta_05;

public class Main05 {
    public static void main(String[] args){
        Person kisi1 = new Person("Selam ya");
        Person kisi2 = new Person("Naber Canim");
        Person kisi3 = new Person("İyiyim, ya sen");

        Car araba1 = new Car("34 YTÜ 31", kisi1);
        Car araba2 = new Car("23 ELZ 23", kisi2);

        System.out.println(araba1.introduceSelf());

        Gallery galerim = new Gallery("Esenler OTO", kisi1);

        galerim.addCar(araba1);
        galerim.addCar(araba2);

        System.out.println(galerim.introduceSelf());

        System.out.println(kisi3.introduceSelf());

        System.out.println(araba1.introduceSelf());
    }
}
