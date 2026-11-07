package Hafta_06_A;

public class Manager extends Employee {
   private int bonus = 0;

   public Manager(String var1, int var2) { // Employee'nin name'i ve salary'si vardı. Direkt üzerine aldık.
      super(var1, var2);
   }

   public void setBonus(int bonus) {
      this.bonus = bonus;
   }

   public int getSalary() {
      return super.getSalary() + this.bonus; // ====> super böyle de kullanılabilir
   }
   
   public String toString() {
      String intro = "Ben bir manager'ım. Benim adımı zaten biliyorsun. Maaşım ve bonusum toplam : " + this.getSalary();
      return intro;
   }
}

