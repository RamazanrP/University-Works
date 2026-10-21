package nyp04;

public class Person {
    private String name;
    private Car araba;

    public Person(String name){
        this.name  = name;
    }
    public String getName(){
        return name;
    }
    public Car getAraba(){
        return araba;
    }
    public void setAraba(Car araba){
        this.araba = araba;
    }

    public String introduceSelf(){
        String intro;
        intro = "Hi, my name is " + getName(); // += olmuyor ilk atamada, = koy
        if(araba != null){
            intro += " and my car's plate is" + araba.getPlate(); // Burada plakayı çağırmak için araba. demek lazımmış !!!
        }
        intro += ".";
        return intro;
    }
    /* ========== 3. Versiyon ============== */
    public void setCar( Car car ) { 
		this.araba = car;
		if( araba.getOwner() != this ) // Burada araba mı kontrol edeyim car mı?
			araba.setOwner(this);
	}
}
