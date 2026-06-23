#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
char courseName[50];
char courseCode[10];
int credit;
int midtermGrade;
int finalGrade;
float average;
} Course;
typedef struct {
char name[50];
int StudentNo;
Course *courses;
int courseCount;
float overallAverage;
} STUDENT;

void initStudent(STUDENT *stu, char *name, int no);
void addCourse(STUDENT *stu, char *name, char *code, int credit);
void deleteCourse(STUDENT *stu, char *code);
void freeSystem(STUDENT *stu);

void enterGrades(STUDENT *stu, char *code, int midterm, int final);
void calculateOverallAverage(STUDENT *stu);
void updateCourse(STUDENT *stu, char *code, char *newName, int newCredit);

int searchCourse(STUDENT *stu, char *code);
void findHighestGradeCourse(STUDENT stu);
void listFailedCourses(STUDENT stu);

void printReportCard(STUDENT stu);
void creditLoadReport(STUDENT stu);
void sortCoursesAlphabetically(STUDENT *stu);

void updateStudentInfo(STUDENT *stu, char *newName, int newNo);
void copyCourses(STUDENT *target, STUDENT source);

int main() {
    STUDENT *Students = NULL;
    int StudentCount = 0;
    int mainChoice = -1;

    while (mainChoice != 0) {
        printf("\n--- ANA MENU ---\n");
        printf("1-> Yeni Ogrenci Kaydet \n");
        printf("2-> Ogrenci Islem Merkezi \n");
        printf("3-> Ogrenci Derslerini Kopyala\n");
        printf("0-> CIKIS \n");
        printf("Seciminiz: ");
        scanf("%d", &mainChoice);
        
        if (mainChoice == 1) {
            STUDENT *temp = NULL;
            if (StudentCount == 0) { // İlk defa kaydedilecekse önce ind_i açalım (kontolü aşağıda), ilk değilse bir tam boyut kadar genişletelim
                temp = (STUDENT*)malloc(1 * sizeof(STUDENT));
            } else {
                temp = (STUDENT*)realloc(Students, (StudentCount + 1) * sizeof(STUDENT));
            }

            if (temp != NULL) {
                Students = temp;
                char name[50];
                int no;
                printf("\nOgrencinin Adi: ");
                scanf(" %[^\n]", name);
                printf("Ogrenci Numarasi: ");
                scanf("%d", &no);
                
                initStudent(&Students[StudentCount], name, no);
                StudentCount++;
                printf("Kayit Basarili, Ana Menuye geri donuluyor...\n");
            } else {
                printf("Bellek tahsis edilemedi!\n");
            }
        } 
        else if (mainChoice == 2) {
            int targetNo, foundIdx = -1, i = 0;
            printf("Islem yapilacak ogrencinin numarasi: \n");
            scanf("%d", &targetNo);

            while (i < StudentCount && foundIdx == -1) {
                if (Students[i].StudentNo == targetNo) {
                    foundIdx = i;
                }
                i++;
            }

            if (foundIdx != -1) { // Öğrenci numarasını bulduk, işlemi soralım kullanıcıya
                int subChoice = -1;
                while (subChoice != 0) {
                    printf("\n SECİLEN OGRENCI: %s \n", Students[foundIdx].name);
                    printf("1->  Ders Ekle \n");
                    printf("2->  Ders Sil \n");
                    printf("3->  Not Girisi Yap \n");
                    printf("4->  Genel Not Ortalamasini Goster \n");
                    printf("5->  Ders Bilgisini Guncelle \n");
                    printf("6->  Ders Ara \n");
                    printf("7->  En Yuksek Notlu Dersi Bul \n");
                    printf("8->  Kalinan Dersleri Listele \n");
                    printf("9->  Transkript Yazdir \n");
                    printf("10-> Toplam Kredi Yukunu Gor \n");
                    printf("11-> Dersleri Alfabetik Sirala \n");
                    printf("12-> Ogrenci Kisisel Bilgilerini Guncelle \n");
                    printf("0->  Ana Menuye Don\n");
                    printf("Islem Seciniz: ");
                    scanf("%d", &subChoice);

                    char tempName[50], tempCode[10];
                    int tempCredit, mid, final, idx;

                    if (subChoice == 1) {
                        int adet, k = 0;
                        char tName[50], tCode[10];
                        int tCred;
                        printf("\nKac adet ders eklemek istiyorsunuz? ");
                        scanf("%d", &adet);
                        while (k < adet) {
                        printf("\n--- %d. Ders Bilgileri ---\n", k + 1);
                        printf("Ders Adi: "); 
                        scanf(" %[^\n]", tName);
                        printf("Ders Kodu: "); 
                        scanf("%s", tCode);
                        printf("Kredisi: "); 
                        scanf("%d", &tCred);
                        addCourse(&Students[foundIdx], tName, tCode, tCred);
                        k++;
                    }
                    printf("\n%d adet ders basariyla sisteme islendi!\n", adet);
                    }
                    else if (subChoice == 2) {
                        printf("Silinecek Ders Kodu: ");
                        scanf("%s", tempCode);
                        deleteCourse(&Students[foundIdx], tempCode);
                        printf("\n%s kodlu ders basariyla silindi. Guncel Ders Listesi:\n", tempCode);
                        creditLoadReport(Students[foundIdx]);
                    } 
                    else if (subChoice == 3) {
                        printf("Ders Kodu: ");
                        scanf("%s", tempCode);
                        printf("Vize Notu: ");
                        scanf("%d", &mid);
                        printf("Final Notu: ");
                        scanf("%d", &final);
                        enterGrades(&Students[foundIdx], tempCode, mid, final);
                    } 
                    else if (subChoice == 4) {
                        calculateOverallAverage(&Students[foundIdx]);
                        printf("Agirlikli  Not Ortalamasi: %.2f\n", Students[foundIdx].overallAverage);
                    } 
                    else if (subChoice == 5) {
                        printf("Guncellenecek Ders Kodu: ");
                        scanf("%s", tempCode);
                        printf("Yeni Ders Adi: ");
                        scanf(" %[^\n]", tempName);
                        printf("Yeni Kredi: ");
                        scanf("%d", &tempCredit);
                        updateCourse(&Students[foundIdx], tempCode, tempName, tempCredit);
                        printf("Guncel Ders Listesi:\n");
                        creditLoadReport(Students[foundIdx]);
                    } 
                    else if (subChoice == 6) {
                        printf("Aranacak Ders Kodu: ");
                        scanf("%s", tempCode);
                        idx = searchCourse(&Students[foundIdx], tempCode);
                        if (idx != -1) printf("Ders %d. sirada bulundu\n", idx + 1);
                        else printf("Ders bulunamadi\n");
                    } 
                    else if (subChoice == 7) {
                        findHighestGradeCourse(Students[foundIdx]);
                    } 
                    else if (subChoice == 8) {
                        listFailedCourses(Students[foundIdx]);
                    } 
                    else if (subChoice == 9) {
                        printReportCard(Students[foundIdx]);
                    } 
                    else if (subChoice == 10) {
                        creditLoadReport(Students[foundIdx]);
                    } 
                    else if (subChoice == 11) {
                        sortCoursesAlphabetically(&Students[foundIdx]);
                        printReportCard(Students[foundIdx]);
                    } 
                    else if (subChoice == 12) {
                        int newNo;
                        printf("Yeni Ogrencinin Adi: ");
                        scanf(" %s", tempName);
                        printf("Yeni Numarasi: ");
                        scanf("%d", &newNo);
                        updateStudentInfo(&Students[foundIdx], tempName, newNo);
                    }
                }
            } else {
                printf("%d numarali ogrenci bulunamadi!\n", targetNo);
            }
        } 
        else if (mainChoice == 3) {
            int srcNo, tgtNo, srcIdx = -1, tgtIdx = -1, i = 0;
            printf("\nKaynak (Kopyalanacak) Ogrenci No: ");
            scanf("%d", &srcNo);
            printf("Hedef (Yapistirilacak) Ogrenci No: ");
            scanf("%d", &tgtNo);

           while (i < StudentCount && (srcIdx == -1 || tgtIdx == -1)) {
                if (Students[i].StudentNo == srcNo) srcIdx = i;
                if (Students[i].StudentNo == tgtNo) tgtIdx = i;
                i++;
            }

            if (srcIdx != -1 && tgtIdx != -1) {
               copyCourses(&Students[tgtIdx], Students[srcIdx]); 
                printf("Dersler basariyla kopyalandi\n");
            } else {
                printf("Girdiginiz numaralardan biri veya ikisi hatali!\n");
            }
        }
    }

    printf("\n Hafiza temizleniyor...\n");
    int j=0;
    while (j < StudentCount) {
        freeSystem(&Students[j]); // PDF'te bize tek öğrenciyi temizleme imkanı verildiği için bu şekilde döngü ile çağırdık fonksiyonu
        j++;
    }
    if (Students != NULL) {
        free(Students); 
    }
    
    return 0;
}

void initStudent(STUDENT *stu, char *name, int no){
    strcpy(stu->name,name);
    stu->StudentNo = no; // Geri kalan ind_ilerin temiz bırakılması istenmiş PDF'te
    stu->courses = NULL;
    stu->courseCount = 0;
    stu->overallAverage = 0.0;
}

void addCourse(STUDENT *stu, char *name, char *code, int credit){
    stu->courses = (Course*)realloc(stu->courses, (stu->courseCount + 1) * sizeof(Course)); // İnitStudent'ta burayı NULL'a eşitlemiştik. O yüzden öncelikle ind_i ayırıyoruz
    strcpy(stu->courses[stu->courseCount].courseName, name);
    strcpy(stu->courses[stu->courseCount].courseCode, code);
    stu->courses[stu->courseCount].credit = credit;
    stu->courses[stu->courseCount].midtermGrade=0;
    stu->courses[stu->courseCount].finalGrade=0;
    stu->courses[stu->courseCount].average=0.0;
    stu->courseCount++; // initStudent'ta sıfır vermiştik buna
}

void deleteCourse(STUDENT *stu, char *code){
    int idx=-1, i=0;
    while(i<stu->courseCount && strcmp(stu->courses[i].courseCode, code) != 0) i++;
    if(i<stu->courseCount){
        idx = i;
        for(i=idx;i<stu->courseCount-1;i++){
        stu->courses[i] = stu->courses[i+1];
        }
        stu->courseCount--;
        if(stu->courseCount > 0){
            stu->courses = (Course*)realloc(stu->courses, stu->courseCount*sizeof(Course));
        }else{ // Yani Öğrencinin ders listesi boşaltılmışsa
            free(stu->courses);
            stu->courses = NULL;
        }
        
    }
}

void enterGrades(STUDENT *stu, char *code, int midterm, int final){
    int i=0;
    while(i<stu->courseCount && strcmp(stu->courses[i].courseCode,code) != 0){
        i++;
    }
    if(i<stu->courseCount){
        stu->courses[i].midtermGrade = midterm;
        stu->courses[i].finalGrade = final;
        stu->courses[i].average = (midterm*0.4) + (final*0.6);
        printf("%s kodlu dersin notlari guncellendi\n", code);
    }else{
        printf("Bu ogrenciye ait %s kodlu ders kaydi bulunmamaktadir!\n", code);
    }
}

void calculateOverallAverage(STUDENT *stu){
    float AllAvg=0;
    int i=0,TotalCredit=0;
    while(i<stu->courseCount){
        AllAvg += stu->courses[i].average * stu->courses[i].credit;
        TotalCredit += stu->courses[i].credit;
        i++;
    }
    if (TotalCredit>0){ // Sıfıra bölme kontrolü
        stu->overallAverage = AllAvg/TotalCredit;
    } else {
        stu->overallAverage = 0.0;
    }
}

void updateCourse(STUDENT *stu, char *code, char *newName, int newCredit){
    int i=0;
    while(i<stu->courseCount && strcmp(code,stu->courses[i].courseCode) != 0){
        i++;
    }
    if(i<stu->courseCount){
        strcpy(stu->courses[i].courseName,newName);
        stu->courses[i].credit = newCredit;
        calculateOverallAverage(stu); // Dersin kredisi değişince GPA'ya etkisi de değişecektir
    }else{
        printf("Yenilemek istediginiz ders kodu bu ogrencinin listesinde yok!\n");
    }
}

int searchCourse(STUDENT *stu, char *code){
    int i=0;
    while(i<stu->courseCount && strcmp(stu->courses[i].courseCode, code) != 0){
        i++;
    }
    if(i<stu->courseCount) return i;
    else return -1;
}

void findHighestGradeCourse(STUDENT stu){
    float highest = 0;
    int i,ind_i;
    for(i=0;i<stu.courseCount;i++){
        if(stu.courses[i].average > highest){
            highest=stu.courses[i].average;
            ind_i=i;
        }
    }
    printf("Ogrencinin en yuksek notu ve dersin kodu: %.2f - %s\n", highest, stu.courses[ind_i].courseCode);
}

void listFailedCourses(STUDENT stu){
    int kaldi=0,i;
    for(i=0;i<stu.courseCount;i++){
        if(stu.courses[i].average < 50){
            printf("Ogrenci %s kodlu %s dersinden kalmistir\n", stu.courses[i].courseCode, stu.courses[i].courseName);
            kaldi=1;
        }
    }
    if(kaldi == 0) printf("Tebrikler! Ogrenciniz her dersten gecti\n");
}

void printReportCard(STUDENT stu) {
    printf("============================================\n");
    printf("Ogrenci Adi : %s\n", stu.name);
    printf("Ogrenci No  : %d\n", stu.StudentNo);
    printf("Ders Listesi:\n");
    printf("--------------------------------------------\n");
    int i=0;
    while (i < stu.courseCount) {
        printf("Ders Adi  : %s\n", stu.courses[i].courseName);
        printf("Ders Kodu : %s\n", stu.courses[i].courseCode);
        printf("Kredisi   : %d\n", stu.courses[i].credit);
        printf("Vize Notu : %d\n", stu.courses[i].midtermGrade);
        printf("Final Notu: %d\n", stu.courses[i].finalGrade);
        printf("Ortalama  : %.2f\n", stu.courses[i].average);
        printf("--------------------------------------------\n");
        i++;
    }
    printf("Toplam Ders   : %d\n", stu.courseCount);
    printf("Genel Ortalama: %.2f\n", stu.overallAverage);
    printf("============================================\n");
}

void creditLoadReport(STUDENT stu){
    int total = 0,i;
    for(i=0;i<stu.courseCount;i++){
        printf("%s kodlu %s dersinin kredi yuku: %d\n", stu.courses[i].courseCode, stu.courses[i].courseName, stu.courses[i].credit);
        total += stu.courses[i].credit;
    }
    printf("Toplam alinan kredi yuku: %d\n", total);
}

void sortCoursesAlphabetically(STUDENT *stu){
    Course temp;
    int i,j;
    for(i=0;i<stu->courseCount-1;i++){
        for(j=i+1;j<stu->courseCount;j++){
            if(strcmp(stu->courses[j].courseName, stu->courses[i].courseName) < 0){
                temp = stu->courses[j];
                stu->courses[j] = stu->courses[i];
                stu->courses[i] = temp;
            }
        }
    }
    printf("Alinan dersler alfabetik olarak siralandi\n");
    printf("Ders Listesinin Yeni Hali:\n");
}

void updateStudentInfo(STUDENT *stu, char *newName, int newNo){
    strcpy(stu->name,newName);
    stu->StudentNo = newNo;
    printf("Ogrencinin ismi ve numarasi yenilendi");
}

void copyCourses(STUDENT *target, STUDENT source){
    int i;
    if(target->courses != NULL) free(target->courses);
    target->courseCount = source.courseCount;
    target->courses = (Course*)malloc(target->courseCount*sizeof(Course));
    for(i=0;i<source.courseCount;i++){
        target->courses[i] = source.courses[i];
    }
}

void freeSystem(STUDENT *stu){
    if(stu->courses != NULL){
        free(stu->courses);
        stu->courses = NULL;
    }
    stu->courseCount = 0; // Ders dizisi kalmadıysa 0'a eşitlemeyi unutmayalım
}