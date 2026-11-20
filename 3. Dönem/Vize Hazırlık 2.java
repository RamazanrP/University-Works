// ============ 2024 Vize ============/

public class Customer extends Person { // PERSONDAN SONRA () YOK
    private String tel, eMail;
    private Purchase[] purchases;
    private int purchaseCount;

    private void enlargePurchaseArray(){
        // Kapasiteyi 2 katına çıkaralım
        Purchase[] newP = new Purchase[2*purchases.length];
        // Direkt eşitlemek olmaz. Önce elemanları aktaracağız
        for(int i=0; i<purchaseCount; i++){ // length yerine count kullandım
            newP[i] = purchases[i];
        }
        purchases = newP;
    }

    public void purchaseProduct(Product p, int n){
        if(purchases.length == purchaseCount){
            enlargePurchaseArray();
            purchases[purchaseCount++] = new Purchase(p ,n);
            return;
        }
        purchases[purchaseCount++] = new Product(p, n);
        return;
    }

    public double findTotalSpent(){
        double sum = 0.0;
        for(Purchase p : purchases){
            if(p != null) sum += p.getCost();
        }
        return sum;
    }

    public String toString(){
        String intro = super.toString();
        for(Purchase p : purchases){
            if(p != null){
                intro += "\n" + p.toString();
            }
        }
        return result;
    }
}

// ============ Şimdi bizden indirimli müşteri kısmını istemiş =========  //

public class PreferredCustomer extends Customer{
    private double discountRatio;

    public double findTotalSpent(){
        double spent = super.findTotalSpent();
        spent *= discountRatio;
        return spent;
    }
    public String toString(){
        String intro = super.toString();
        return intro +  "Benim indirim oranim: " + discountRatio;
    }
}

// ============ 3. soruya geçelim ==========//
public void listTaskOf(int employeeID){
    Employee e = searcStaff(employeeID);
    if(e != null){
        e.listAllTasks();
    }
}

public Task findTask(int TaskID){
    for(int i=0; i<staff.length; i++){
        if(staff[i] != null){
            Task t = staff[i].searcTask(TaskID); // staff[i]. unutmuşum. Ayrıca da Task t olcak Employee değil
            if(t != null){
                System.out.println(t.toString());
                return t;
            }
        }
    }
    return null;
}

public class EstateAgent{
    private String name;
    private Home[] h;

    public EstateAgent(){
        this.h = new Home[100];
    }
    public void hasHome(Home eklenecekH){
        for(int i=0; i< h.length; i++){
            if(h[i] == null){
                h[i] = eklenecekH;
                return;
            }
        }
    }
}

public  void sellHome(Home satilacak, Customer alici){
    if(satilacak == null || alici == null) return;
    boolean bulundu = false;
    for(int i=0; i<h.length; i++){
        if(h[i] == satilacak){
            bulundu = true;
            alici.buyHome(satilacak);
            for(int j=i; j<h.length-1; j++){
                h[j] = h[j+1];
            }
            h[length-1] = null; // Bunu unutmuşum
            System.out.println("Ev" + alici.getName() + "isimli alıcıya satıldı.");
            return;
        }
    }
    if(bulundu == false){
        System.out.println("Bu ev, satılacaklar listesinde mevcut değil!");
    }
    return;
}
