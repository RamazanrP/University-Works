public class Hafta_1 {
    // Class, Nesnelerin nasıl olacağını tanımlayan şablondur. Mesela
    class Car {

    String brand; // field - attribute
    int speed;    // field - attribute

    void accelerate() { // method
        speed++;
        }
    } // Car nesnesinin bilgi ve davranışlarını tanımladık ama henüz bir Car oluşturmadık
    
    // Peki Object nasıl olur
    Car car1 = new Car();
    
    // Method: Bir class'ın içerisinde tanımlanan ve bir davranışı gerçekleştiren kod bloğudur. Mesela accelerate()
    // Instance: car1, Car Class'ının bir instance'ı
    // Inheritance: Bir Class'ın başka bir Class'ın özellikelrini alabilmesi. BNW, Car'ın özelliklerini taşır
    /*
    ┌──────────────────────┐
    │         Car          │ Class'ın adı
    ├──────────────────────┤
    │ - plate : String     │ attribute :(Bu türde) Type 
    │ - speed : int        │
    ├──────────────────────┤
    │ + getPlate() : String│ Method - : - Dönüş Tipi
    │ + brake() : void     │
    └──────────────────────┘
    
    + public
    - private
    # protected -> Kalıtım/erişim bağlamında korunan üye
    ~ package -> Package seviyesinde erişim. Özel olarak package keywrod'üne gerek yok. Erişim belirleyicisi hiç yazılmazsa package kabul edilir

    */
   //public String accelerate() {...} Olarak yazılır
   // + setPlate(p : String) : void => public ve void dönüş tipli setPlate method'u String tipinde p değişkeni alıyormus demek
   //public void setPlate(String p) {...} Olarak yazılır 
   /*
    client             kitt : Car
  │                         │
  │──── getPlate() ────────>│ clienti kitt isimli Car sınıfına ait objeye getPlate istemi gönderiyor
  │                         │
  │<────── plate ───────────│ kitt'in bu isteme cevabı
  │                         │
   */
  // UML de önce değişken sonra type, Java'da önce type sonra parametre/değişken
}
class Student {

    static int count; // Static: Shared Usage yani class'a ait olarak tanımlanır. (Method da static tanımlanabilir)
    final int MAX = 100; // Artık teni bir değer atanamaz
    /*
    final variable → tekrar atanamaz

    final method → yeniden tanımlanması engellenir

    final class → kalıtım için kullanılamaz
    */
   static final int MAXIMUM = 100; // İkisi aynı anda kullanılabilir
   
   // Constructor => Bir object oluşturulduğunda onu başlangıç durumuna getirmek için kullanılan özel yapıdır.
   String name;
    int age;

    Student(String name, int age) { // CONSTRUCTOR'IN ADI CLASS İLE AYNI OLMA ZORUNDA VE DÖNÜŞ TYPE'I OLMAZ
        this.name = name;
        this.age = age;
    }
}
/*
 * ============================
 * JAVA HAZIR SINIFLARI
 * ============================
 *
 * WRAPPER
 *
 * int       -> Integer
 * double    -> Double
 * float     -> Float
 * boolean   -> Boolean
 * char      -> Character
 *
 *
 * INTEGER
 *
 * intValue()
 * Integer -> int
 *
 * parseInt(String)
 * String -> int
 *
 * valueOf(String)
 * String -> Integer
 *
 * toString()
 * Integer -> String
 *
 *
 * STRING
 *
 * length()
 * -> uzunluk
 *
 * equals()
 * -> içerik eşitliği
 *
 * equalsIgnoreCase()
 * -> büyük/küçük harf önemsemeden eşitlik
 *
 * contains()
 * -> içerisinde geçiyor mu?
 *
 * toUpperCase()
 * -> büyük harf
 *
 * toLowerCase()
 * -> küçük harf
 *
 * compareTo()
 * -> String sıralama karşılaştırması
 *
 *
 * MATH
 *
 * abs()    -> mutlak değer
 * max()    -> büyük olan
 * min()    -> küçük olan
 * ceil()   -> yukarı
 * floor()  -> aşağı
 * round()  -> en yakın
 * sqrt()   -> karekök
 *
 *
 * RANDOM
 *
 * nextBoolean()
 * -> true / false
 *
 * nextDouble()
 * -> [0.0, 1.0)
 *
 * nextInt(bound)
 * -> [0, bound)
 *
 * Örnek:
 * nextInt(10)
 * -> 0..9
 *
 * 1..10 için:
 * nextInt(10) + 1
 */
