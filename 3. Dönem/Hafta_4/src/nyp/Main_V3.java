package nyp04;

public class Main_03 {
    public static void main(String args[]){
        Person oktay = new Person("Oktay Sinanoglu");
        Car rover = new Car("34 KS 001");
        //oktay.setCar(rover); Alttakini yazınca Buna gerek yok
        rover.setOwner(oktay);

        System.out.println(oktay.introduceSelf());
        System.out.println(rover.introduceSelf());
        /*=========== 4. Versiyon =============== */
        Person orcun = new Person("Oktay Sinano�lu");
		Car rolls = new Car("06 OS 1934");
		rolls.setOwner(orcun);

		Person aziz = new Person("Aziz Sancar");
		Car honda = new Car("47 AS 1946",aziz);

        System.out.println(honda.introduceSelf());
    }
}
