package nyp04;
import java.util.*;

public class Main_02 {
    public static void main(String args[]){
        Scanner girdi = new Scanner(System.in); // Klavyeden inout alacak demek ve MUTLAKA PROGRAM SONUNDA KAPATILMALI
        Person oktay;
        String name = "";
        while( name.length() < 5){
            System.out.println("Kisinin ismini giriniz: ");
            name = girdi.nextLine(); // Kullanıcın yazdığı bütün satırı al demek
        }
        oktay = new Person(name); // Atama böyle Dikkat !!!
        String secim;
        System.out.println("Kisinin arabasi var mi?");
        secim = girdi.nextLine();
        if(secim.contains("e") || secim.contains("E")){
            Car rover;
            System.out.println("Arabanin plakasini giriniz");
            rover = new Car(girdi.nextLine()); // Güzel kullanım. Ekstra dan plate String i yaratmadık
            oktay.setAraba(rover);
        }
        System.out.println(oktay.introduceSelf());
        girdi.close();
        /*============== 2. Versiyon ================= */
		Person kerem = new Person("Kerem Balci");
        Car rolls = new Car("23 KRM 01");
        kerem.setAraba(rolls);
        rolls.setOwner(kerem);
        System.out.println(kerem.introduceSelf());
        System.out.println(rolls.introduceSelf());
    }
}
