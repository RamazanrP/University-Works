package Hafta_06_A;

public class Person {
   private String name;

   public Person(String name) {
      this.name = name;
   }

   public String getName() {
      return this.name;
   }

   public String toString() {
      String intro = "Benim adım: " + this.name;
      return intro;
   }
}
