package Hafta_06_A;

import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

public class Company {
   public Company() {
   }

   public static void main(String[] args) {
      Employee emp1 = new Employee("Kübra Uzungil", 1000000);
      Employee emp2 = new Employee("Hasan Kisaca", 123456);
      Manager mngr1 = new Manager("Cem Tutakligil", 900000);
      mngr1.setBonus(50000);
      List<Employee> emps = new ArrayList<>();
      emps.add(emp1);
      emps.add(emp2);
      emps.add(mngr1);

      for(Employee employee : emps) {
         if (employee instanceof Manager) { // Manager type ında bir nesne görürsen eğer
            PrintStream var10000 = System.out;
            int var1 = employee.getSalary();
            var10000.println("Bu manager'in bonussuz maasi:" + (var1 - 10)); // Bu 10'un pek mantığı yok çünkü getSalary'de bonusu baştan eledik
         }
      }

   }
}
