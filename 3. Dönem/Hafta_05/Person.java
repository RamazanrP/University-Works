package Hafta_05;

public class Person {
    private String name;
    private Car car;

    public Person(String name){
        this.name = name;
    }

    public String getName(){
        return this.name;
    }

    public Car getCar(){
        return this.car;
    }
    public void setCar(Car car){
        this.car = car;
        car.setOwner(this); // En önemli kısım!!!
    }

    public String introduceSelf(){
        String intro = "Merhaba benim adim" + this.getName();
        if(this.getCar() == null) return intro;
        else{
            return intro + "Arabamin plakasi da" + this.getCar().getPlate(); // Hocamız burda + this.car.getPlate(); yazmış da acaba benimki hatalı mı? Ne farkımız var 
        }
    }
}
