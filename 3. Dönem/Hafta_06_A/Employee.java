package Hafta_06_A;

public class Employee extends Person { // ÇOK ÇOK ÖNEMLİ EXTENDS KEYWORD Ü İNHERİTANCE İÇİN
   private int salary;

   public Employee(String name, int salary) {
      super(name);                   // Üst Sınıfın Constructor'ı SUPER ile çağırılır. this yok!!!
      this.salary = salary;
   }

   public int getSalary() {
      return this.salary;
   }

   public void setSalary(int salary) {
      this.salary = salary;
   }

   public String toString() {
      String var10000 = this.getName();
      String intro = "Benim adım: " + var10000 + ". Maaşım: " + this.salary;
      return intro;
   }
}
