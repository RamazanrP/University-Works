package nyp04;

public class Car{
    private String plate;
    public Car (String plakaNo){ // Bir Car ın exist olması için plaka zorunlu
        plate = plakaNo;
    }

    public String getPlate(){
        return plate;
    }
    /* ================== 2. Versiyon =================== */

    private String plaka;
    private Person sahip;

    public Car(String plakaNo){ // Sahibi olmayan araçlar da exist olsun diye
        this.plaka = plakaNo;
    }
    public Car(String plakaNo, Person owner){ // Sahibi varsa böyle exist olacak
        this.plaka = plakaNo;
        this.sahip = owner;
    }

    public void setOwner(Person sahip){
        this.sahip = sahip;
    }
    public Person getOwner(){ // String değil Person döndürüyor
        return sahip;
    }

    public void setPlaka(String plakaNo){
        this.plaka = plakaNo;
    }
    public String getPlaka(){
        return plaka;
    }

    public String introduceSelf(){
        String str;
        str = "CAR: Benim Plakam " + getPlaka();
        if(sahip != null){
            str += "Ve de benim sahibim " + getOwner();
        }
        return str;
    }
    /* ========== 3. Versiyon =================== */
    public void setOwner( Person owner ) { 
		this.sahip = owner;
		if( owner.getAraba() != this )
			owner.setAraba(this);
	}
    /* =============== 4. Versiyon ============= */
    public Car(String plakaNo, Person sahip){
        this.plaka = plakaNo;
        setOwner(sahip); // Yukardaki method a gitti, 3. Versiyondaki if kontrolünü boşa çıkardı daha temiz yazdı
    }

}
