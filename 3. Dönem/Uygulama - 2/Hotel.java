package Uygulama_2;

import java.util.ArrayList;
import java.util.LinkedList;

public class Hotel {
    private ArrayList<Room> rooms;
    private LinkedList<String> history;
    private int capacity;
    private int serialCounter;
    
    public Hotel(int capacity){
        this.capacity = capacity;
        this.serialCounter = 500;
        this.history = new LinkedList<>();
        this.rooms = new ArrayList<>();
    }

    public int getCapacity(){return this.capacity;}
    public void setCapacity(int c){this.capacity = c;}

    public void addRoom(Room r){
        if(rooms.size() == capacity){
            System.out.println("WARNING: Hotel is full! Room not added: " + r.getUniqueId());
            return; // bunu unutma
        }
        rooms.add(r); // Veya bunu else'ye koy
    }

    public StandardRoom createStandardRoom(int floor, double nightlyPrice, int bedCount){
        return new StandardRoom(floor, nightlyPrice, bedCount, serialCounter++);
        // serialcCounter'ı parametre oalrak almaz ama constructor'da uniqueId verirken kullanır
        // new StandardRoom() derken içine verip arttırırız
    }
    public Suite createSuite(int floor, double nightlyPrice, String viewType){
        return new Suite(floor, nightlyPrice, viewType, serialCounter++);
        // ID verirken seri numarası burada artacak, AZALMA YOK
    }
    public void printAllRooms(){
        for(Room r : rooms){
            System.out.println(r.toString());
        }
    }

    public Room findById(String id){
        for(Room r : rooms){
            if(r.getUniqueId().equals(id)) return r; // String i de == ile kontrol etme be kanka
        }
        return null;
    }

    public void checkIn(String id){
        if(findById(id) == null){
            System.out.println("ERROR: Room X-000 not found.");
            return;
        }else if(findById(id).isOccupied()){
            System.out.println("WARNING" + findById(id).getUniqueId() + " is already occupied!");
        }else{
            Room r = findById(id);
            r.setOccupied(true); 
            // rooms.add(r); Oda zaten var, eklemeye gerek yok, sadece True yapacağız
            history.addFirst("Check-in: " + r.getUniqueId());
        }
    }

    public void checkOut(String id, int nights){
        if(findById(id) == null){
            System.out.println("ERROR: Room X-000 not found.");
            return;
        }else if(!findById(id).isOccupied()){
            System.out.println("WARNİNG" + findById(id).getUniqueId() + " is empty!");
        }else{
            Room r = findById(id);
            r.setOccupied(false); 
            rooms.remove(r);
            System.out.println("Check out " + r.getUniqueId()
            + nights + " nights" + r.calculateCost(nights));
            history.addFirst("Check out: " +  r.getUniqueId() +
            "(" + r.calculateCost(nights) + " TL )");
        }
    }

    public void printHistory(){
        System.out.println("History (newest first):");
        for(String s : history){ // for-each LinkedList'te çalışır
            System.out.println(s);
        }
    }
}
