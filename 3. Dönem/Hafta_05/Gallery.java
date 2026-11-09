package Hafta_05;

import java.util.ArrayList;

public class Gallery {
    private String galleryName;
    private Person galleryOwner;
    private int carCount;
    private ArrayList<Car> cars; // Kullanıma dikkat

    public Gallery(String galleryName, Person galleryOwner){
        this.galleryName = galleryName;
        this.galleryOwner = galleryOwner;
        cars = new ArrayList<Car>(); // KULLANIMA DİKKAT
        carCount = 10;
    }

    public String getGalleryName(){
        return this.galleryName;
    }
    public void setGalleryName(String galleryName){
        this.galleryName = galleryName;
    }

    public Car searchCarWithPlate(String plate) { // İÇ İÇE 2 FOR KULLANMAKTAN KURTARDI BİZİ
		for(Car i:cars){
            if(i.getPlate().equals(plate)){
                return i;
            }else{
                return null;
            }
        }
        return null;
	}

    public boolean searchCar(Car aCar) {
		return this.cars.contains(aCar); // Bunu biraz açıkla
	}

    public boolean addCar(Car eklenecek){
        if(cars.size() < carCount){ // .size() için this değil CARS
            eklenecek.setOwner(galleryOwner); // Gene çok öenmliydi
            cars.add(eklenecek);
            return true;
        }else{
            System.out.println("Galeri dolu");
            return false;
        }
    }

    public Car removeCar(String plate){
        Car aranan = searchCarWithPlate(plate);
        if(aranan != null){
            this.cars.remove(aranan); // Ben şimfi bu arabayı silince ArrayList teki geri indislerde kalanlar bir araba öne gelecek mi?
            aranan.setOwner(new Person("Sari Cizmeli Mehmet Aga"));
            return aranan;
        }else{
            return null;
        }
    }

    public boolean sellCar(String plate, Person newOwner){
        Car satilacak = searchCarWithPlate(plate);
        if(satilacak != null){
            this.cars.remove(satilacak);
            satilacak.setOwner(newOwner);
            return true;
        }else{
            return false;
        }
    }
    
    public String introduceSelf(){
        String intro = "MErhaba ben bir galeriyim. İsmim: " + getGalleryName() + "Sahibim: " + this.galleryOwner.getName();
        if(cars.size() > 0){
            intro += "Sahip oldugum arabalar: ";
            for(Car i : cars){
                intro += i.getPlate() + "\n";
            }
        }
        return intro;
    }
}
