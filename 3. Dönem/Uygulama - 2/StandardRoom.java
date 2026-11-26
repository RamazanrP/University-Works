package Uygulama_2;

import java.util.Locale;

public class StandardRoom extends Room{
    private int bedCount;

    public StandardRoom(int floor, double nightlyPrice, int bedCount, int serial){
        super(floor, nightlyPrice);
        this.bedCount = bedCount;
        this.uniqueId = generateUniqueIdBody(serial);
    }

    public int getBedCount(){return this.bedCount;}
    public void setBedCount(int bedCount){this.bedCount = bedCount;}

    public String getTypeName(){
        return getClass().getSimpleName();
    }

    public String generateUniqueIdBody(int serial){
        return getTypeName().substring(0, 3).toUpperCase(Locale.ENGLISH)
        + "-" + getFloor() + "-" + getBedCount() + "-" + serial;
    }


    
}
