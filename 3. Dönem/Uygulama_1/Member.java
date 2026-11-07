package Uygulama_1;

public class Member {
    public static final int MAX_BORROW = 3;
    private String name;
    private int memberID;
    private Book[] borrowedBooks;

    public Member(String name, int memberID){
        this.name = name;
        this.memberID = memberID;
        borrowedBooks = new Book[MAX_BORROW];
    }

    public String getName(){
        return name;
    }
    public void setName(String name){
        this.name = name;
    }


    public int getMemberID(){
        return memberID;
    }
    public void setMemberId(int memberID){
        this.memberID = memberID;
    }

    public Book[] getBorrowedBooks(){
        return borrowedBooks;
    }

    public boolean borrowBook(Book b){
        if(b.isAvailable() == false) return false;
        for(int i=0; i< MAX_BORROW; i++){
            if(borrowedBooks[i] == null){
                borrowedBooks[i] = b;
                b.setAvailable(false); // bunu UNUTMA
                return true;
            }
        }
        return false;
    }

    public boolean returnBook(Book b){
        for(int i=0; i<MAX_BORROW; i++){
            if(borrowedBooks[i] != null){
                if(borrowedBooks[i].getTitle().equalsIgnoreCase(b.getTitle())){
                    borrowedBooks[i] = null;
                    b.setAvailable(true);
                    return true;
                }
            }
        }
        return false;
    }

    public void listBorrowedBooks(){
        for(Book b : borrowedBooks){
            if(b != null) System.out.println(b.toString());
        }
    }

}
