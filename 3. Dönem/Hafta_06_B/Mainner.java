package Hafta_06_B;

import java.util.ArrayList;

public class Mainner {
    public static void main(String[] args){
        Person kisi1 = new Person();
        Student kisi2 = new Student();
        Person kisi3 = new Student();
        Employee kisi4 = new Employee();
        Retired kisi5 = new Retired();
        
        ArrayList<Person> people = new ArrayList<>();
        people.add(kisi1);
        people.add(kisi2);
        people.add(kisi3);
        people.add(kisi4);
        people.add(kisi5);
        
        for(Person human : people){
            if(human instanceof Student){
                System.out.println(((Student) human).kendineAitMethod());
            }
        }
        /*Bunun yerine şöyle de yazılabilirdi
        for (Person human : people) {
            if (human instanceof Student) {
                Student student = (Student) human; Downcasting ile
                System.out.println(student.kendineAitMethod());
            }
        } 
        */
    }
}
