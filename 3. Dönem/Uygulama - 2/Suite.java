package Uygulama_2;

import java.util.Locale;

public final class Suite extends Room{
    private String viewType;

    public Suite(int floor, double nightlyPrice, String viewType, int serial){
        super(floor, nightlyPrice); // bunu unutuyon hep
        this.viewType = viewType;
        this.uniqueId = generateUniqueIdBody(serial);
    }

    public String getTypeName(){
        return getClass().getSimpleName();
    }
    public String getViewType(){return this.viewType;}
    public void setViewType(String viedType){this.viewType = viedType;}

    public String generateUniqueIdBody(int serial){
        return getTypeName().substring(0, 3).toUpperCase(Locale.ENGLISH)
        + "-" + getViewType().substring(0,3).toUpperCase(Locale.ENGLISH)
        + "-" + getFloor() + "-" + serial;
    }

}
