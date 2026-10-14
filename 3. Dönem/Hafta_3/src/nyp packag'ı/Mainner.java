package nyp;

public class Mainner {
    public static void main(String[] args){
        Araba yeniAraba = new Araba();
        yeniAraba.setMarka("Renault");
        yeniAraba.setModel("Clio");
        //System.out.println(yeniAraba);

        Araba yeniAraba2 = new Araba("Volvo", "XC90", 12345);
        //System.out.println(yeniAraba2);

        Insan insan1 = new Insan("haydar", "Yenice", "34234");
        Insan insan2 = new Insan("Buse", "Arici", "11063");

        insan1.setAraba(yeniAraba);
        insan2.setAraba(yeniAraba2);

        System.out.println(yeniAraba);
        System.out.println(yeniAraba2);

        System.out.println(insan1);
        System.out.println(insan2);

        insan1.arabaSat(yeniAraba, insan2);
		
		System.out.println(insan1);
		System.out.println(insan2);

    }
}
