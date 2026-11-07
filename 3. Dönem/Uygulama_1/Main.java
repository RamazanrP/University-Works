package Uygulama_1;

public class Main {

	public static void main(String[] args) {
		Library lib = new Library("YTU_KTP", 3);
		Member member1 = new Member("Yasin", 001);
		Book book1 = new Book("Babam ve Ben", "Baban", 313);
		Book book2 = new Book("Ethical Hacking", "Ben", 310);
        Book book3 = new Book("Naber Canim :)", "Sen", 777);

		lib.addBook(book1);
        lib.addBook(book2);
        lib.addBook(book3);

		lib.printAllBooks();
		
		lib.lendBook(member1, "Naber Canim :)");
		
		lib.printAllBooks();
		member1.listBorrowedBooks();
	}

}
