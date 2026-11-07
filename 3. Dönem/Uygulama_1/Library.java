package Uygulama_1;

public class Library {
    private String name;
    private int maxBooks;
    private Book[] books;

    public Library(String name, int maxBooks){
        this.name = name;
        this.maxBooks = maxBooks; // Bunu Unutmuşum
        this.books = new Book[maxBooks]; // ÖNEMLİ
    }

    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }

    public Book[] getBooks(){ // [] Açmayı unutma
        return books;
    }

    public int getMaxBooks(){
        return maxBooks;
    }

    public void printAllBooks(){
        for(Book b : books){
            if(b != null)
                System.out.println(b);
        }
    }

    public boolean addBook(Book b){
        if(books.length == maxBooks) return false;
        for(int i=0; i<maxBooks; i++){
            if(books[i] == null){
                books[i] = b;
                return true;
            }
        }
        return false;
    }
    
    public Book findByTitle(String title){
        for(Book b : books){
            if(b != null && b.getTitle().equalsIgnoreCase(title)){ // Kullanıma dikkat
                return b;
            }
        }
        return null;
    }

    public boolean lendBook(Member m, String title){
        Book b = findByTitle(title);
        if(b == null)
            return false;
        return m.borrowBook(b);
    }

    public double getAveragePageCount(){
        int sayac = 0, sumPC = 0;
        for(Book b : books){
            if(b != null){
                sayac++;
                sumPC += b.getPageCount();
            }
        }
        if(sayac != 0) return (double) sumPC/sayac;
        return 0.0;
    }

    public Book getLongestBook(){
        int longest = 0;
        Book longestB = null; // null yapmayınca hata veriyordu return'da
        for(Book b : books){
            if(b != null && b.getPageCount() > longest){ // null kontrolü ekledik
                longest = b.getPageCount();
                longestB = b;
            }
        }
        return longestB;
    }

    public Book getShortestBook(){
        int shortest = 0;
        Book shortestB = null;
        for(Book b : books){
            if(b != null && b.getPageCount() < shortest){
                shortest = b.getPageCount();
                shortestB = b;
            }
        }
        return shortestB;
    }

    public int getAvailableCount(){
        int sayac = 0;
        for(Book b : books){
            if(b != null && b.isAvailable()) sayac++;
        }
        return sayac;
    }

    public double getAveragePageCountOfAvailable(){
        int sayacA = 0, sumAPC = 0;
        for(Book b : books){
            if(b != null && b.isAvailable()){
                sayacA++;
                sumAPC+=b.getPageCount();
            }
        }
        if(sayacA == 0) return 0.0;
        return (double)sumAPC/sayacA;
    }
}
