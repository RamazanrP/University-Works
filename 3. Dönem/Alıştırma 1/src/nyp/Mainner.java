package nyp;

public class Mainner { // Yorum satırı ibaresini kaldırarak outputu'u değiştirip işleyişi görebilirsiniz

    public static void main(String[] args) {

        // 1) NESNELERİ OLUŞTUR

        Universite uni = new Universite("ABC Üniversitesi");

        Ogrenci ali = new Ogrenci("Ali", "Yilmaz", 1001);
        Ogrenci ayse = new Ogrenci("Ayse", "Demir", 1002);
        Ogrenci mehmet = new Ogrenci("Mehmet", "Kaya", 1003);

        Ders java = new Ders("BLM101", "Java", 4, 2);
        Ders c = new Ders("BLM102", "C", 4, 3);
        Ders matematik = new Ders("MAT101", "Matematik", 5, 2);
        Ders fizik = new Ders("FIZ101", "Fizik", 3, 2);

        /* ========== ÜNİVERSİTEYE ÖĞRENCİ EKLE =============*/
        System.out.println(uni.ogrenciEkle(ali));
        System.out.println(uni.ogrenciEkle(ayse));
        System.out.println(uni.ogrenciEkle(mehmet));

        /* ============ ÜNİVERSİTEDEKİ ÖĞRENCİLER ============*/
        uni.ogrencileriListele();

        /* ============= ALİ'Yİ JAVA DERSİNE KAYDET ======== */
        System.out.println(ali.derseKaydol(java));

        /* ============ ALİ'NİN DERSLERİNİ GÖR ============== */
        //ali.dersleriListele();

        /* ========== JAVA DERSİNDEKİ ÖĞRENCİLERİ GÖR ========*/
        // java.ogrencileriListele();

        /* ================== AYŞE'Yİ JAVA'YA EKLE ======== */
        System.out.println(ayse.derseKaydol(java));

        /* JAVA'NIN KAPASİTESİNİ TEST ET (Java kapasitesi 2) */
        System.out.println(mehmet.derseKaydol(java));

        /* ============ ALİ'Yİ JAVA'DAN ÇIKAR ============== */
        // System.out.println(ali.derstenAyril(java));

        /* ========== JAVA'DAKİ ÖĞRENCİLERİ TEKRAR GÖR =======*/
        java.ogrencileriListele();

        /* =========== ALİ'NİN DERSLERİNİ TEKRAR GÖR ======== */
        // ali.dersleriListele();

        /* ============== FARKLI DERSLERİ TEST ET ============ */
        // System.out.println(ali.derseKaydol(c));
        // System.out.println(ali.derseKaydol(matematik));
        // System.out.println(ali.derseKaydol(fizik));

        /* ============== ALİ'NİN TÜM DERSLERİ ============ */
        // ali.dersleriListele();

        /* =========== ALİ'Yİ ÜNİVERSİTEDEN ÇIKAR ========== */
        // System.out.println(uni.ogrenciCikar(ali));

        /* =========== ÜNİVERSİTEDE KİMLER KALDI? ========== */
        // uni.ogrencileriListele();
    }
}
