package Uygulama_2;

public abstract class Room {
    protected int floor;
    protected double nightlyPrice;
    protected String uniqueId;
    protected boolean occupied;

    public Room(int floor, double nightlyPrice){
        this.floor = floor;
        this.nightlyPrice = nightlyPrice;
        this.occupied = false; // Başlangıçta hepsi boş
    }

    protected abstract String generateUniqueIdBody(int serial);

    public abstract String getTypeName();

    public int getFloor(){return this.floor;}
    public void setFloor(int f){this.floor = f;}
    public double getNightlyPrice(){return this.nightlyPrice;}
    public void setNightlyPrice(double nightlyPrice){this.nightlyPrice = nightlyPrice;}
    public boolean isOccupied(){return this.occupied;}
    public void setOccupied(boolean occupied){this.occupied = occupied;}
    public String getUniqueId(){return this.uniqueId;}
    public double calculateCost(int nights){return this.nightlyPrice*nights;}
    public String toString(){
        String occ = isOccupied() ? "Occupied" : "Available";
        return getTypeName() +" => Floor " + getFloor()+  "| " + getNightlyPrice()
        + "TL/night" + "ID: " + getUniqueId() + "| Status" + occ;
    }
}
