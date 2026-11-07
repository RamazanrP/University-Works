package Uygulama_1;

public class Book {
    private String title;
    private String author;
    private int pageCount;
    private boolean available;

    public Book(String title, String author, int pageCount){
        this.title = title;
        this.author = author;
        this.pageCount = pageCount;
        available = true; // Başlangıçta rafta olup ulaşılabilir kabul ettik
    }

    public String getTitle(){
        return title;
    }
    public void setTitle(String title){
        this.title = title;
    }

    public String getAuthor(){
        return author;
    }
    public void setAuthor(String author){
        this.author = author;
    }

    public int getPageCount(){
        return pageCount;
    }
    public void setPageCount(int pageCount){
        this.pageCount = pageCount;
    }

    public boolean isAvailable(){
        return available;
    }
    public void setAvailable(boolean available){
        this.available = available;
    }

    public String toString(){ // toString PARAMETRE ALMAZ
        String intro = "Merhaba ben " + getAuthor() + " tarafindan yazilmis " + getPageCount() 
        + " sayfali" + getTitle() + " kitabiyim. Ve su an";
        if(available) return intro + "Raftayim";
        else return intro + "Odunc alindim";
    }
}  
