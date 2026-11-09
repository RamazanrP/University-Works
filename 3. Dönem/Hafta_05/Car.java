package Hafta_05;

public class Car {
    private String plate;
    private  Person owner;

    public Car(String plate, Person owner){ // parametre aldığını unutma
        this.plate = plate;
        this.owner = owner;
    }

    public String getPlate(){
        return this.plate;
    }
    public void setPlate(String plate){
        this.plate = plate;
    }

    public Person getOwner(){
        return this.owner;
    }
    public void setOwner(Person owner){
        this.owner = owner;
    }

    public String introduceSelf(){ // Bu örnek için parametre almamış!!!
        String intro = "Ben bir arabayim. Plaka numaram:" + getPlate();
        if(this.getOwner() == null) return intro;
        else{
            return intro + "Sahibim de" + this.getOwner().getName();
        }
    }
}
