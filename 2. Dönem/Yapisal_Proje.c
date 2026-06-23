#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 10
#define MAX_USERS 50
#define MAX_NAME  64
#define MAX_GAMES 200
#define MAX_MOVES 500
#define SAVE_FILE "game_save.dat"
#define SCORES_FILE "scores.csv"
#define EMPTY 0

typedef struct{ // Tek bir hamleyi temsil eder. UNDO/REDO için bize yardım edecek
    int srcRow;
    int srcCol;
    int dstRow;
    int dstCol;
    int matrix[MAX_N][MAX_N];// Hamle öncesi anlık görüntü
} oneMove;

typedef struct { // Bütün hamleleri tutacak
    oneMove Moves[MAX_MOVES];
    int top;                   
} MoveStack;

typedef struct {
    int gameID;
    char username[MAX_NAME];
    int matrixSize;
    int isAutoMode; //1: otomatik, 0: manuel
    int isRandomMatrix; // 1: rastgele, 0: dosyadan
    int undoCount;
    double completionTimeSec;
    double score;
} GameRecord;

typedef struct{
    char username[MAX_NAME];
    int gamesPlayed;
    double totalScore;
    GameRecord games[MAX_GAMES];
} UserRecord;

typedef struct {
    int matrix[MAX_N][MAX_N];  // mevcut matris 
    int original[MAX_N][MAX_N]; // baslangic matrisi (sifirlama icin)
    int N;                         
    int pairSrc[MAX_N+1][2]; // her sayi icin 1. konum 
    int pairDst[MAX_N+1][2];  // her sayi icin 2. konum 
    int pathFound[MAX_N+1]; // DFS sonucunda yol bulundu mu 
} GameState;

void stackInit(MoveStack*);
int stackIsEmpty(MoveStack*);
int stackIsFull(MoveStack*);
void stackPush(MoveStack*, oneMove);
oneMove stackPop(MoveStack*);
oneMove stackPeek(MoveStack*);

void  initGameState(GameState* , int);
void  copyMatrix(int dst[MAX_N][MAX_N], int src[MAX_N][MAX_N], int n);
void  printMatrix(int mat[MAX_N][MAX_N], int n);
void  locatePairs(GameState*);
int isMatrixFull(int mat[MAX_N][MAX_N], int n);
void  resetMatrix(GameState*);

void createRandomMatrix(GameState*, int);
int createMatrixFromFile(GameState*, const char*);
int generateSolvableRandomMatrix(GameState*, int);

// Manuel Mod
int   isValidManualoneMove(GameState*, int, int, int, int);
void  applyManualoneMove(GameState*, MoveStack*, int, int, int, int);
void  undoLastoneMove(GameState*, MoveStack*);
void  playManualMode(GameState*, MoveStack*, MoveStack*, GameRecord*, time_t);

//Otomatik mod 
int dfsSolve(GameState*, int, MoveStack*, int);
void playAutoMode(GameState*, MoveStack*, GameRecord*);

double calculateScore(GameRecord*, int);

int findUser(UserRecord*, int, const char*);
void  addGameRecord(UserRecord*, int*,const char*, GameRecord*);
void  saveScores(UserRecord*, int);
int loadScores(UserRecord*, int*);
void showAllScores(UserRecord*, int);
void showSingleUserScores(UserRecord*, int);

void  saveGameState(GameState*, MoveStack*, MoveStack*, char*);
int   loadGameState(GameState*, MoveStack*, MoveStack*, char*);

void  clearInputBuffer(void);
int   getIntInput(const char*, int, int);

/*  Girdi: MoveStack* s - başlatılacak yığın işaretçisi
    Çıktı: void olduğundan yok
    İşlev: Yığını başlangıç durumuna getirir, top = -1 yapar.   */
void stackInit(MoveStack *s){
    s->top = -1;
}

/*  stackIsEmpty: Yığın boş mu kontrol eder.
    Girdi: Hamelelr Yığını => *s
    Çıktı: int (1: boş, 0: dolu)     */
int stackIsEmpty(MoveStack *s){
    return s->top == -1;
}

/*  stackIsFull: Yığın dolu mu kontrol eder.
 * Girdi: Hameleler Yığını => *s
 * Çıktı: int (1: tamamen dolu, 0: boş)    */
int stackIsFull(MoveStack *s){
    return s->top == MAX_MOVES - 1;
}

/*  stackPush: Yığına yeni bir hamle ekler.
 * Girdi: Hameleler Yığını => *s, 1 Hareket =>  m
 * Çıktı: void   */
void stackPush(MoveStack *s, oneMove m){
    if (stackIsFull(s)) {
        printf("[UYARI] Hamle yigini dolu!\n");
        return;
    }
    s->Moves[++(s->top)] = m;
}

/*   stackPop: Yığının en üstündeki hamleyi çıkarır ve döndürür.
     Girdi: Hamelelr Yığını => *s
     Çıktı: oneMove (çıkarılan hamle; boşsa içi 0)    */
oneMove stackPop(MoveStack *s){
    oneMove empty;
    memset(&empty, 0, sizeof(oneMove));
    if (stackIsEmpty(s)) return empty;
    return s->Moves[(s->top)--];
}

/* stackPeek: Yığının en üstündeki hamleyi silmeden döndürür.
 * Girdi: Hameleler Yığını => *s
 * Çıktı: oneMove */
oneMove stackPeek(MoveStack *s){ 
    oneMove empty;
    memset(&empty, 0, sizeof(oneMove));
    if (stackIsEmpty(s)) return empty;
    return s->Moves[s->top];
}

/* initGameState: Oyun durumunu sıfırlar, tüm hücreleri EMPTY yapar.
 * Girdi: Mevcut durum => *gs, boyut
 * Çıktı: void   */
void initGameState(GameState *gs, int n){
    int i, j;
    gs->N = n;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            gs->matrix[i][j] = EMPTY;
    for (i = 0; i <= n; i++)
        gs->pathFound[i] = 0;
}

/* copyMatrix: Kaynak matristen hedef matrise kopyalama.
 * Girdi: Kaynak ve Hedef matrisleri ve de boyut
 * Çıktı: void */
void copyMatrix(int dst[MAX_N][MAX_N], int src[MAX_N][MAX_N], int n){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < n; j++){
            dst[i][j] = src[i][j];
        }
    }
}

/* printMatrix: Matrisi tablo şeklinde ekrana basar, boş hücreleri '.' gösterir.
 * Girdi: Matris ve Boyut
 * Çıktı: void  */
void printMatrix(int mat[MAX_N][MAX_N], int n){ 
    int i, j;
    printf("\n   ");
    for (j = 0; j < n; j++) printf("%3d", j);
    printf("\n   ");
    for (j = 0; j < n; j++) printf("---");
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("%2d|", i);
        for (j = 0; j < n; j++) {
            if (mat[i][j] == EMPTY) printf("  .");
            else printf("%3d", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* locatePairs: original matrisindeki her sayının iki konumunu pairSrc/pairDst dizilerine kaydeder.
 * Girdi: Mevcut durum => *gs
 * Çıktı: void  */
void locatePairs(GameState *gs){
    int i, j, num;
    int found[MAX_N+1];
    memset(found, 0, sizeof(found));
    for (i = 0; i < gs->N; i++) {
        for (j = 0; j < gs->N; j++) {
            num = gs->original[i][j];
            if (num != EMPTY) {
                if(!found[num]){
                    gs->pairSrc[num][0] = i;
                    gs->pairSrc[num][1] = j;
                    found[num] = 1;
                }else{
                    gs->pairDst[num][0] = i;
                    gs->pairDst[num][1] = j;
                }
            }
            
        }
    }
}

/* 
 * isMatrixFull: Matristeki tüm hücreler dolu mu kontrol eder.
 * Girdi: Matris ve Boyut
 * Çıktı: int (1: tamamen dolu, 0: boş hücre var) */
int isMatrixFull(int mat[MAX_N][MAX_N], int n) {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (mat[i][j] == EMPTY) return 0;
    return 1;
}

/* resetMatrix: Geçerli matrisi orijinal matrise sıfırlar.
 * Girdi: Mevcut durum => *gs
 * Çıktı: void  */
void resetMatrix(GameState *gs) {
    copyMatrix(gs->matrix, gs->original, gs->N);
}

/* createRandomMatrix: 1..n arası sayıları rastgele ikişer kez yerleştirir.
 * Girdi: Mevcut durum => *gs ve boyut
 * Çıktı: void (matris gs->matrix'e yazılır)    */
void createRandomMatrix(GameState *gs, int n) {
    int total = n * n;
    int cells[MAX_N * MAX_N];
    int placed[MAX_N * MAX_N];
    int i, r, tmp, count;

    initGameState(gs, n);

    for (i = 0; i < total; i++) cells[i] = i;
    for (i = total - 1; i > 0; i--) {
        r = rand() % (i + 1);
        tmp = cells[i];
        cells[i] = cells[r];
        cells[r] = tmp;
    }

    count = 0;
    memset(placed, 0, sizeof(placed));
    for (i = 1; i <= n && count + 1 < 2*n; i++) {
        placed[count]   = cells[count];
        placed[count+1] = cells[count+1];
        gs->matrix[ cells[count]   / n ][ cells[count]   % n ] = i;
        gs->matrix[ cells[count+1] / n ][ cells[count+1] % n ] = i;
        count += 2;
    }

    copyMatrix(gs->original, gs->matrix, n);
    locatePairs(gs);
}

// createRandomMatirx fonksiyonunun ürettiği Matris çözülmeye elverişli mi değil mi onu kontrol eder, ta ki matris çözülebilir olana kadar.
/* Girdi: Mevcut durum => *gs ve de boyut
   Çıktı: int; Çözülebilir bulursa 1 bulamazsa 0    */
int generateSolvableRandomMatrix(GameState *gs, int n) {
    int maxAttempts = 200;
    int attempt;
    GameState tmpGs;
    MoveStack tmpStack;

    for (attempt = 1; attempt <= maxAttempts; attempt++) {
        initGameState(&tmpGs, n);
        createRandomMatrix(&tmpGs, n);

        stackInit(&tmpStack);
        resetMatrix(&tmpGs);
        locatePairs(&tmpGs);

        if (dfsSolve(&tmpGs, 1, &tmpStack, 1)) {
            copyMatrix(gs->matrix, tmpGs.original, n);
            copyMatrix(gs->original, tmpGs.original, n);
            gs->N = n;
            locatePairs(gs);
            return 1;
        }
    }
    printf("[HATA] %d deneme yapildi ancak cozulebilir matris bulunamadi.\n", maxAttempts);
    return 0;
}
/* createMatrixFromFile: CSV dosyasından matris okur, geçersiz formatta hata döner.
 * Girdi: Mevcut durum => gs ve Dosya Adı *filename
 * Çıktı: int (1: başarılı, 0: hata)    */
int createMatrixFromFile(GameState *gs, const char *filename){
    FILE *fp;
    char line[512];
    char *token;
    int row = 0, col, n = 0, val;
    int tmpMat[MAX_N][MAX_N];

    fp = fopen(filename, "r");
    if (!fp) {
        printf("[HATA] Dosya acilamadi: %s\n", filename);
        return 0;
    }

    while (fgets(line, sizeof(line), fp) && row < MAX_N) {
        col = 0;
        token = strtok(line, " ,\t\n\r");
        while (token && col < MAX_N) {
            val = atoi(token);
            tmpMat[row][col] = val;
            col++;
            token = strtok(NULL, ",\n\r");
        }
        if (n == 0) n = col;
        row++;
    }
    fclose(fp);

    if (row != n || n < 2) {
        printf("[HATA] Gecersiz CSV formati (kare matris olmali).\n");
        return 0;
    }

    initGameState(gs, n);
    copyMatrix(gs->matrix, tmpMat, n);
    copyMatrix(gs->original, tmpMat, n);
    locatePairs(gs);

    printf("\nDosyadan matris yuklendi (%dx%d): %s\n", n, n, filename);
    printMatrix(gs->matrix, n);
    return 1;
}

/* ========================== MANUEL MOD ========================== */

/*  Girdi: Kaynak ve Hedef koordinatları alır
    İşlev: Hamlenin gecerliligini kontrol eder:
   - Kaynak ve hedef ayni satir VEYA ayni sutun olmali
   - Aradaki tum hucreler bos olmali
   - Hedef ya bos ya da ayni sayiyla dolu olmali */
int isValidManualoneMove(GameState *gs, int sr, int sc, int dr, int dc) {
    int srcVal, dstVal, i;
    if (sr < 0 || sr >= gs->N || sc < 0 || sc >= gs->N) return 0;
    if (dr < 0 || dr >= gs->N || dc < 0 || dc >= gs->N) return 0;
    if (sr == dr && sc == dc) return 0;
    if (sr != dr && sc != dc) return 0; // Ayni satir VEYA ayni sutun olmali - ikisi birden degisemez

    srcVal = gs->matrix[sr][sc];
    dstVal = gs->matrix[dr][dc];

    if (srcVal == EMPTY) return 0;
    if (dstVal != EMPTY && dstVal != srcVal) return 0;

    // Aradaki hucrelerin hepsi bos olmali
    if (sr == dr) { // Yatay mı hareket edilecek
        int minC = sc < dc ? sc : dc;
        int maxC = sc > dc ? sc : dc;
        for (i = minC + 1; i < maxC; i++)
            if (gs->matrix[sr][i] != EMPTY) return 0;
    } else { // Dikey mi hareket edilecek
        int minR = sr < dr ? sr : dr;
        int maxR = sr > dr ? sr : dr;
        for (i = minR + 1; i < maxR; i++)
            if (gs->matrix[i][sc] != EMPTY) return 0;
    }

    return 1;
}

/* Geçerli hamleyi uygular, önceki durumu UNDO yığınına kaydeder.
Girdi: Hareket yığınlarını, oyun durumunu, kaynak ve hedef hücre koordinatlarını alır */
void applyManualoneMove(GameState *gs, MoveStack *s, int sr, int sc, int dr, int dc) {
    int srcVal = gs->matrix[sr][sc];
    oneMove m;
    int i;
    
    // Hamle öncesi matrisin tamamını snapshot olarak kaydet
    copyMatrix(m.matrix, gs->matrix, gs->N);
    m.srcRow = sr; m.srcCol = sc;
    m.dstRow = dr; m.dstCol = dc;
    stackPush(s, m);
    
    // Yolu doldur (aradaki tüm hücreleri + hedef; kaynak hariç)
    if (sr == dr) { // Yatay hareket
        int step = (sc < dc) ? 1 : -1;
        for (i = sc + step; i != dc + step; i += step) {
            gs->matrix[sr][i] = srcVal;
        }
    } else { // Dikey hareket
        int step = (sr < dr) ? 1 : -1;
        for (i = sr + step; i != dr + step; i += step) {
            gs->matrix[i][sc] = srcVal;
        }
    }
}
/* undoLastoneMove: Son hamleyi geri alır.
 * Girdi: Oyun durumu *gs ve Hareket dizilerini *s alır
 * Çıktı: void */
void undoLastoneMove(GameState *gs, MoveStack *s) {
    oneMove m;
    if (stackIsEmpty(s)) {
        printf("[UNDO] Geri alinacak hamle yok.\n");
        return;
    }
    m = stackPop(s);
    copyMatrix(gs->matrix, m.matrix, gs->N);
    printf("[UNDO] Son hamle geri alindi. (%d,%d) -> (%d,%d)\n", m.srcRow, m.srcCol, m.dstRow, m.dstCol);
    printMatrix(gs->matrix, gs->N);
}

/* İşlev: Manuel oyun modunu çalıştırır, kullanıcı hamlelerini alır.
 * Girdi: Mevcut durum => gs, Yapılan hamleler yığını => uStack, UNDO hamleleri => rStack, Skor,süre gibi bilgiler => rec, Oyun süresi => startTime
 * Çıktı: void (rec üzerinden sonuç doldurulur)*/
void playManualMode(GameState *gs, MoveStack *uStack, MoveStack *rStack, GameRecord *rec, time_t startTime) {
    int sr, sc, dr, dc, choice = -1;
    int undoCount = 0, devamEdiyor = 1;

    printf("\n=== MANUEL MOD ===\n");
    printf("Hamle girmek icin 1, UNDO icin 2, REDO icin 3, cikis icin 0 girin.\n");
    printMatrix(gs->matrix, gs->N);

    while (!isMatrixFull(gs->matrix, gs->N) && devamEdiyor == 1) {
        choice = getIntInput("Secim (1=Hamle, 2=UNDO, 3=REDO, 0=Cikis): ", 0, 3);

        if (choice == 0) {
            printf("Manuel moddan cikiliyor...\n");
            devamEdiyor = 0; 
        } 
        else if (choice == 2) { // UNDO
            if (!stackIsEmpty(uStack)) {
                oneMove u = stackPop(uStack);
                oneMove current; // Geleceği yani şu anki halini REDO'ya atalım
                current.srcRow = u.dstRow; current.srcCol = u.dstCol;
                current.dstRow = u.srcRow; current.dstCol = u.srcCol;
                copyMatrix(current.matrix, gs->matrix, gs->N);
                stackPush(rStack, current);
                
                copyMatrix(gs->matrix, u.matrix, gs->N); // GEçmişe dönmek içim
                undoCount++;
                printf("[UNDO] Hamle geri aliniyor: (%d,%d) -> (%d,%d)\n", u.srcRow, u.srcCol, u.dstRow, u.dstCol);
                printMatrix(gs->matrix, gs->N);
            } else {
                printf("[HATA] Geri alinacak hamle yok!\n");
            }
        } 
        else if (choice == 3) { // REDO
            if(!stackIsEmpty(rStack)){
                oneMove r = stackPop(rStack);
                oneMove current; // Geri dönebilmek için şu anki durumu UNDO'da attık
                copyMatrix(current.matrix, gs->matrix, gs->N);
                stackPush(uStack, current);
                
                copyMatrix(gs->matrix, r.matrix, gs->N); // Geleceğe geri dönüyoruz
                printf("REDO basarili. Bir adim ileri gidildi.\n");
                printMatrix(gs->matrix, gs->N);
            }else{
                printf("[HATA] Ileri alinacak hamle yok!\n");
            }
        }
        else if (choice == 1) { // Yeni hamle istemi
            printf("Kaynak satir ve sutun girin (aralarinda 1 boslukla): ");
            if (scanf("%d %d", &sr, &sc) != 2) { 
                clearInputBuffer(); 
                printf("[HATA] Hatali giris!\n");
            } else {
                printf("Hedef satir ve sutun girin (aralarinda 1 boslukla): ");
                if (scanf("%d %d", &dr, &dc) != 2) { 
                    clearInputBuffer(); 
                    printf("[HATA] Hatali giris!\n");
                } else {
                    clearInputBuffer();

                    if(!isValidManualoneMove(gs, sr, sc, dr, dc)) {
                        printf("[HATA] Gecersiz hamle! Tekrar deneyin.\n");
                    }else{
                        applyManualoneMove(gs, uStack, sr, sc, dr, dc);
                        stackInit(rStack); // Yeni hamle yapıldığında REDO sıfırlanır
                        printf("Hamle uygulandi: (%d,%d) -> (%d,%d)\n", sr, sc, dr, dc);
                        printMatrix(gs->matrix, gs->N);
                        if (isMatrixFull(gs->matrix, gs->N)) {
                            printf("*** TEBRIKLER! Tum hucreler dolduruldu! ***\n");
                        }
                    }
                }
            }
        }
    }

    rec->undoCount = undoCount;
    rec->completionTimeSec = difftime(time(NULL), startTime);
    rec->isAutoMode = 0;
}

/* Algoritmamız:
-Her sayı için DFS ile kaynak'tan hedef'e yol aranır.
-Hücre doldurulurken komşu boş hücrelere recursive gidilir.
-Çıkmazsa geri izleme (backtrack) yapılır.
Girdi: GameState* gs, int numIdx, MoveStack* s
Çıktı: int (1: çözüm bulundu, 0: bulunamadı)
 */
int dfsSolve(GameState *gs, int numIdx, MoveStack *s, int isSilent){
    int num, r, c;
    int dRow[4] = {-1, 1, 0, 0};
    int dCol[4] = { 0, 0,-1, 1};
    int d, nr, nc;
    oneMove m;
    int cozumBulundu = 0;
    if (numIdx > gs->N) {
        return isMatrixFull(gs->matrix, gs->N);
    }

    num = numIdx;
    r = gs->pairSrc[num][0];
    c = gs->pairSrc[num][1];
    if (r == gs->pairDst[num][0] && c == gs->pairDst[num][1]) {
        gs->pathFound[num] = 1;
        if(!isSilent) printf("[AUTO] Sayi %d eslesti.\n", num);
        if (dfsSolve(gs, numIdx + 1, s, isSilent)) return 1;
        gs->pathFound[num] = 0;
        return 0;
    }

    for (d = 0; d < 4 && cozumBulundu == 0; d++) {
        nr = r + dRow[d];
        nc = c + dCol[d];

        if(nr >= 0 && nr < gs->N && nc >= 0 && nc < gs->N) {
            if(nr == gs->pairDst[num][0] && nc == gs->pairDst[num][1]) {
                m.srcRow = r; m.srcCol = c;
                m.dstRow = nr; m.dstCol = nc;
                copyMatrix(m.matrix, gs->matrix, gs->N);
                stackPush(s, m);

                gs->pairSrc[num][0] = nr;
                gs->pairSrc[num][1] = nc;
                if(!isSilent) printf("[AUTO] Hamle: (%d,%d)->(%d,%d) [Sayi %d eslesti]\n", r, c, nr, nc, num);

                if(dfsSolve(gs, numIdx+1, s, isSilent)){
                    cozumBulundu = 1;
                }else{
                    gs->pairSrc[num][0] = r;
                    gs->pairSrc[num][1] = c;
                    stackPop(s);
                }
            }
            else if (gs->matrix[nr][nc] == EMPTY && cozumBulundu == 0) {
                m.srcRow = r; m.srcCol = c;
                m.dstRow = nr; m.dstCol = nc;
                copyMatrix(m.matrix, gs->matrix, gs->N);
                stackPush(s, m);

                gs->matrix[nr][nc] = num;
                gs->pairSrc[num][0] = nr;
                gs->pairSrc[num][1] = nc;
                if(!isSilent) printf(" Hamle: (%d,%d)->(%d,%d) [Sayi %d]\n", r, c, nr, nc, num);

                if(dfsSolve(gs, numIdx, s, isSilent)){
                    cozumBulundu = 1;
                }else{
                    gs->matrix[nr][nc] = EMPTY;
                    gs->pairSrc[num][0] = r;
                    gs->pairSrc[num][1] = c;
                    if(!isSilent) printf("[AUTO UNDO] Sayi %d icin hamle geri aliniyor: (%d,%d) bosaltiliyor.\n", num, nr, nc);
                    stackPop(s);
                }
            }
        }
    }

    return cozumBulundu;
}
/* İşlev: Otomatik modu başlatır, çözüm arar ve süreyi hesaplar.
 * Girdi: Mevcut durum => *gs, Yapılan Hamleler Yığını *s, Skor,süre gibi bilgiler *rec
 * Çıktı: void  */
void playAutoMode(GameState *gs, MoveStack *s, GameRecord *rec) { // Otomatik modu başlatır, dfsSolve ile çözüm arar ve süreyi hesaplar.
    time_t start;
    int solved;

    printf("\n=== OTOMATIK MOD ===\n");
    printMatrix(gs->matrix, gs->N);

    start  = time(NULL);
    solved = dfsSolve(gs, 1, s, 0);

    rec->completionTimeSec = difftime(time(NULL), start);
    rec->isAutoMode        = 1;
    rec->undoCount         = 0;

    if (solved) {
        printf("\n*** COZUM BULUNDU! ***\n");
        printMatrix(gs->matrix, gs->N);
    } else {
        printf("\n[!] Bu matris icin cozum bulunamadi.\n");
    }
}

/* ========================== SKOR HESAPLAMA ========================== */

/*
 * Girdi: GameRecord pointer 
 * Cikti: Hesaplanan skor döndürülür
 * Formul:
 *   temelPuan = matrisSize * 100
 *   zamanCezasi = tamamlama_suresi * 0.5
 *   undoCezasi  = undoCount * 10
 *   moduBonusu  = otomatik ? 0 : 50 (manuel oynayanda bonus)
 *   dosyaBonusu = rastgele ? 20 : 0
 *   oyunSayiBonusu = rec->gameID * 5
 *   skor = temelPuan - zamanCezasi - undoCezasi + moduBonusu + dosyaBonusu + oyunSayiBonusu
 *   (skor < 0 olursa 0'a yuvarlanir)
 */
double calculateScore(GameRecord *rec, int gamesPlayed){
    double base = (double)(rec->matrixSize * 100);
    double tPen = rec->completionTimeSec * 0.5;
    double undoPen = (double)(rec->undoCount * 10);
    double modBonus  = rec->isAutoMode    ? 0.0  : 50.0;
    double fileBonus = rec->isRandomMatrix ? 20.0 : 0.0;
    double gameBonus = (double)(rec->gameID * 5);
    double score = base - tPen - undoPen + modBonus + fileBonus + gameBonus;

    return score < 0.0 ? 0.0 : score;
}

// Girdi: UserRecord users[], int userCount, const char* name
// Çıktı: int -> Bulunursa index bulunmazsa -1
int findUser(UserRecord users[], int userCount, const char *name){
    int i;
    for (i = 0; i < userCount; i++)
        if (strcmp(users[i].username, name) == 0) return i;
    return -1;
}

/* İşlev: Kullanıcıya yeni oyun kaydı ekler, yoksa yeni kullanıcı oluşturur.
 * Girdi: users dizisi, user adedi, isim, oyun kayıtları
 * Çıktı: void  */
void addGameRecord(UserRecord users[], int *userCount, const char *name, GameRecord *rec){
    int idx = findUser(users, *userCount, name);
    UserRecord *u;

    if (idx == -1) {
        if (*userCount >= MAX_USERS) {
            printf("[UYARI] Maksimum kullanici sayisina ulasildi.\n");
            return;
        }
        idx = *userCount;
        strncpy(users[idx].username, name, MAX_NAME - 1);
        users[idx].gamesPlayed = 0;
        users[idx].totalScore  = 0.0;
        (*userCount)++;
    }

    u = &users[idx];
    rec->gameID = u->gamesPlayed + 1;
    rec->score  = calculateScore(rec, u->gamesPlayed);

    if (u->gamesPlayed < MAX_GAMES) {
        u->games[u->gamesPlayed] = *rec;
        u->gamesPlayed++;
        u->totalScore += rec->score;
    }

    printf("\n--- Oyun Bitti ---\n");
    printf("Oyuncu : %s\n", rec->username);
    printf("Boyut  : %dx%d\n", rec->matrixSize, rec->matrixSize);
    printf("Mod    : %s\n", rec->isAutoMode ? "Otomatik" : "Manuel"); // 11. Haftadaki ders anlatımında görmüştük bu kullanımı
    printf("Sure   : %.1f sn\n", rec->completionTimeSec);
    printf("UNDO   : %d\n", rec->undoCount);
    printf("SKOR   : %.1f\n", rec->score);
}

/* İşlev: Tüm kullanıcı ve oyun bilgilerini CSV dosyasına yazar.
 * Girdi: users dizisi ve boyutu
 * Çıktı: void  */
void saveScores(UserRecord users[], int userCount) {
    FILE *fp = fopen(SCORES_FILE, "w");
    int i, j;
    if (!fp) {
        printf("[HATA] Skor dosyasi (%s) olusturulamadi!\n", SCORES_FILE);
        return;
    }
    fprintf(fp, "OyuncuAdi,ToplamOyun,ToplamSkor,OyunID,MatrisBoyutu,Mod,MatrisTuru,UndoSayisi,SureSaniye,OyunSkoru\n");

    for (i = 0; i < userCount; i++) {
        // Eğer kullanıcının henüz hiç kayıtlı oyunu yoksa sadece temel profilini yazıyoruz
        if (users[i].gamesPlayed == 0) {
            fprintf(fp, "%s,%d,%.1f,-1,-1,-1,-1,-1,-1.0,-1.0\n",
                    users[i].username, users[i].gamesPlayed, users[i].totalScore);
        } else {
            // Kullanıcının oynadığı her oyun için CSV'ye yeni bir satır ekliyoruz
            for (j = 0; j < users[i].gamesPlayed; j++) {
                GameRecord *gr = &users[i].games[j];
                fprintf(fp, "%s,%d,%.1f,%d,%d,%d,%d,%d,%.1f,%.1f\n",
                        users[i].username,
                        users[i].gamesPlayed,
                        users[i].totalScore,
                        gr->gameID,
                        gr->matrixSize,
                        gr->isAutoMode,
                        gr->isRandomMatrix,
                        gr->undoCount,
                        gr->completionTimeSec,
                        gr->score);
            }
        }
    }

    fclose(fp);
    printf("[BILGI] Tum skorlar ve performans kayitlari '%s' dosyasina CSV olarak kaydedildi.\n", SCORES_FILE);
}

/* İşlev: CSV dosyasından skorları okur, kullanıcıları doldurur.
 * Girdi: users dizisi ve de boyutu
 * Çıktı: int (okunan kullanıcı sayısı, 0 ise hata) */
int loadScores(UserRecord users[], int *userCount) {
    FILE *fp;
    char line[512];
    char name[MAX_NAME];
    int gp, gid, ms, iam, irm, uc;
    double ts, sc, tot;
    int count, i, idx;

    fp = fopen(SCORES_FILE, "r");
    if (!fp) { *userCount = 0; return 0; }

    // Önceden oyun varsa başlık olacaktır. Başlık satırını atlamak için:
    if (!fgets(line, sizeof(line), fp)) { fclose(fp); *userCount = 0; return 0; }

    count = 0;
    while (fgets(line, sizeof(line), fp)) {
        // Eğer en az 3 değişken okunabildiyse işle, yoksa satırı atla 
        if (sscanf(line, "%[^,],%d,%lf,%d,%d,%d,%d,%d,%lf,%lf", name, &gp, &tot, &gid, &ms, &iam, &irm, &uc, &ts, &sc) >= 3) {
            // Kullanıcı listede var mı kontrolü:
            idx = -1;
            for (i = 0; i < count && idx == -1; i++) {
                if (strcmp(users[i].username, name) == 0) idx = i;
            }
            // Yoksa yeni kullanıcı oluştur
            if (idx == -1 && count < MAX_USERS) {
                idx = count;
                strncpy(users[idx].username, name, MAX_NAME - 1);
                users[idx].gamesPlayed = 0;
                users[idx].totalScore  = tot;
                count++;
            }
            // Eğer kullanıcı bulunduysa ve geçerli oyun verisi varsa ekleyelim
            if (idx != -1 && gid != -1 && users[idx].gamesPlayed < MAX_GAMES) {
                int g = users[idx].gamesPlayed;
                users[idx].games[g].gameID = gid;
                users[idx].games[g].matrixSize = ms;
                users[idx].games[g].isAutoMode = iam;
                users[idx].games[g].isRandomMatrix = irm;
                users[idx].games[g].undoCount = uc;
                users[idx].games[g].completionTimeSec = ts;
                users[idx].games[g].score = sc;
                strncpy(users[idx].games[g].username, name, MAX_NAME - 1);
                users[idx].gamesPlayed++;
            }
        }
    }

    fclose(fp);
    *userCount = count;
    return 1;
}

/* showAllScores: Tüm kullanıcıların skorlarını ekrana yazdırır.
 * Girdi: users dizisi ve de boyutu
 * Çıktı: void  */
void showAllScores(UserRecord users[], int userCount) {
    int i, j;
    GameRecord *gr;

    if (userCount == 0) {
        printf("\nHenuz kayitli skor yok.\n");
        return;
    }

    printf("\n========== KULLANICI SKORLARI ==========\n");
    for (i = 0; i < userCount; i++) {
        printf("\nOyuncu: %-20s | Toplam Oyun: %d | Toplam Skor: %.1f\n",
               users[i].username,
               users[i].gamesPlayed,
               users[i].totalScore);
        printf("  %-4s %-6s %-10s %-8s %-5s %-8s %-8s\n",
               "ID","Boyut","Mod","Matris","UNDO","Sure","Skor");
        for (j = 0; j < users[i].gamesPlayed; j++) {
            gr = &users[i].games[j];
            printf("  %-4d %-6d %-10s %-8s %-5d %-8.1f %-8.1f\n",
                   gr->gameID,
                   gr->matrixSize,
                   gr->isAutoMode ? "Otomatik" : "Manuel",
                   gr->isRandomMatrix? "Rastgele" : "Dosya",
                   gr->undoCount,
                   gr->completionTimeSec,
                   gr->score);
        }
    }
    printf("=========================================\n");
}

/* showSingleUserScores: Belirli bir kullanıcının detaylı karnesini gösterir.
 * Girdi: users dizisi ve de boyutu
 * Çıktı: void  */
void showSingleUserScores(UserRecord users[], int userCount) {
    char searchName[MAX_NAME];
    int idx, j;
    GameRecord *gr;

    if (userCount == 0) {
        printf("\n-> Henuz sisteme kayitli hicbir skor yok.\n");
        return;
    }
    printf("\nSkorlarini gormek istediginiz kullanicinin adini girin: "); scanf("%s", searchName);
    clearInputBuffer();

    idx = findUser(users, userCount, searchName);

    if (idx == -1) {
        printf("\n[HATA] '%s' adinda bir kullanici bulunamadi!\n", searchName);
        return;
    }

    printf("\n========== KULLANICI SKORLARI ==========\n");
    printf("Oyuncu: %-20s | Toplam Oyun: %d | Toplam Skor: %.1f\n",
           users[idx].username,
           users[idx].gamesPlayed,
           users[idx].totalScore);
    printf("  %-4s %-6s %-10s %-8s %-5s %-8s %-8s\n",
           "ID","Boyut","Mod","Matris","UNDO","Sure","Skor");
           
    for (j = 0; j < users[idx].gamesPlayed; j++) {
        gr = &users[idx].games[j];
        printf("  %-4d %-6d %-10s %-8s %-5d %-8.1f %-8.1f\n",
               gr->gameID,
               gr->matrixSize,
               gr->isAutoMode ? "Otomatik" : "Manuel",
               gr->isRandomMatrix ? "Rastgele" : "Dosya",
               gr->undoCount,
               gr->completionTimeSec,
               gr->score);
    }
    printf("=========================================\n");
}

/* İşlev: Oyun durumunu binary dosyaya kaydeder.
 * Girdi: Mevcut durum => *gs, Yapılan Hamleler Yığını => *uStack, UNDO için hamleler => *rStack, kullanıcı adı *username
 * Çıktı: void  */
void saveGameState(GameState *gs, MoveStack *uStack, MoveStack *rStack, char *username) {
    FILE *fp;
    fp = fopen(SAVE_FILE, "wb");
    if (!fp){
        printf("[HATA] Kayit dosyasi olusturulamadi.\n");
        return;
    }
    fwrite(username, MAX_NAME, 1, fp);
    fwrite(gs, sizeof(GameState), 1, fp);
    fwrite(uStack, sizeof(MoveStack), 1, fp);
    fwrite(rStack, sizeof(MoveStack), 1, fp);
    fclose(fp);
    printf("[BILGI] Oyun kaydedildi: %s\n", SAVE_FILE);
}
/* İşlev: Kaydedilmiş oyunu dosyadan yükler.
 * Girdi: Mevcut durum => *gs, Yapılan hamleler yığını => uStack, UNDO hamleleri => rStack, kullanıcı adı *username
 * Çıktı: int (1: başarılı, 0: dosya yok/hata) */
int loadGameState(GameState *gs, MoveStack *uStack, MoveStack *rStack, char *username){
    FILE *fp;
    fp = fopen(SAVE_FILE, "rb");
    if (!fp) return 0;
    if (fread(username, MAX_NAME, 1, fp) != 1) { fclose(fp); return 0; }
    if (fread(gs, sizeof(GameState), 1, fp) != 1) { fclose(fp); return 0; }
    if (fread(uStack, sizeof(MoveStack), 1, fp) != 1) { fclose(fp); return 0; }
    if (fread(rStack, sizeof(MoveStack), 1, fp) != 1) { fclose(fp); return 0; }
    fclose(fp);
    return 1;
}

// Birkaç yardımcı fonksiyon da ekledim

/*clearInputBuffer: Giriş tamponunu temizler.
Girdi ve de Çıktı: void */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* 
 * getIntInput: Kullanıcıdan belirli aralıkta tamsayı girişi alır.
 * Girdi:  char* prompt, min ve max değerler
 * Çıktı: int (geçerli değer)*/
int getIntInput(const char *prompt, int minVal, int maxVal) { // Kullanıcıdan min-max aralığında bir tamsayı girişi alır, geçerli girişe kadar döner.
    int val;
    do {
        printf("%s", prompt);
        if (scanf("%d", &val) != 1) { clearInputBuffer(); val = minVal - 1; }
        else clearInputBuffer();
    } while (val < minVal || val > maxVal);
    return val;
}

/* ========================== ANA PROGRAM ========================== */

int main(void) {
    UserRecord *users;
    int userCount = 0;
    users = (UserRecord*)malloc(MAX_USERS * sizeof(UserRecord));
    
    if (!users) { 
        printf("[HATA] Bellek ayrilamadi.\n"); 
        return 1; 
    }
    memset(users, 0, MAX_USERS * sizeof(UserRecord));
    srand((unsigned int)time(NULL));
    
    GameState  gs;
    MoveStack  mStack, rStack;
    GameRecord rec;
    char username[MAX_NAME];
    char filename[256];
    int mainChoice, gameChoice, scoreChoice, n;
    int hasMatrix = 0;
    time_t gameStart;
    char savedUser[MAX_NAME];

    loadScores(users, &userCount);
    
    { // Skorları yüklüyoruz ve oyun var mı kontrol ediyoruz
        GameState  tmpGs;
        MoveStack  tmpMs, tmpRs;
        if (loadGameState(&tmpGs, &tmpMs, &tmpRs, savedUser)) {
            printf("\nKayitli oyun bulundu (Oyuncu: %s). Devam etmek ister misiniz? (1=Evet, 0=Hayir): ", savedUser);
            if (getIntInput("", 0, 1) == 1) {
                gs = tmpGs;
                mStack = tmpMs;
                rStack = tmpRs;
                strncpy(username, savedUser, MAX_NAME - 1);
                hasMatrix = 1;
                printf("Kayitli oyun yuklendi.\n");
                printMatrix(gs.matrix, gs.N);
            }
        }
    }

    do {
        printf("\n========== ANA MENU ==========\n");
        printf("1-> Rastgele Matris Olustur\n");
        printf("2-> Dosyadan Matris Olustur\n");
        printf("3-> Kullanici Skorlarini Goster\n");
        printf("0-> Cikis\n");
        printf("==============================\n");
        mainChoice = getIntInput("Seciminiz: ", 0, 3);

        switch (mainChoice) {
        case 1:
        case 2:
            printf("Kullanici adinizi girin: ");
            if (scanf("%s", username) == 1) { 
                clearInputBuffer();
                
                if (mainChoice == 1) {
                    int found = 0;
                    int retry = 1; 
                    n = getIntInput("Matris boyutunu girin (2-10): ", 2, 10);
                    
                    while(retry == 1 && found == 0) {
                        printf("\nLutfen bekleyin, arka planda cozulebilir matris arastiriliyor...\n");
                        if (generateSolvableRandomMatrix(&gs, n)) {
                            found = 1;
                            hasMatrix = 1;
                            memset(&rec, 0, sizeof(rec));
                            rec.matrixSize = n;
                            rec.isRandomMatrix = 1;
                            strncpy(rec.username, username, MAX_NAME - 1);
                            printf("\n%dx%d Cozulebilir matris olusturuldu :\n", n, n);
                            printMatrix(gs.matrix, n);
                        } else {
                            printf("\n[HATA] Cozulebilir matris olusturulamadi.\n");
                            retry = getIntInput("Isteginizi tekrarlamak ister misiniz? (1=Evet, 0=Hayir): ", 0, 1);
                        }
                    }
                } 
                else if(mainChoice == 2) {
                    printf("Dosya adini girin: ");
                    if (scanf("%s", filename) == 1) {
                        clearInputBuffer();
                        if (createMatrixFromFile(&gs, filename)) {
                            hasMatrix = 1;
                            memset(&rec, 0, sizeof(rec));
                            rec.matrixSize    = gs.N;
                            rec.isRandomMatrix = 0;
                            strncpy(rec.username, username, MAX_NAME - 1);
                        }
                    } else {
                        clearInputBuffer();
                    }
                }
                // Sadece geçerli bir matris oluşturulduysa Oyun Menüsü döngüsüne gir
                if (hasMatrix == 1) {
                    stackInit(&mStack);
                    stackInit(&rStack);

                    do {
                        printf("\n--- OYUN MENUSU (%s) ---\n", username);
                        printf("1-> Manuel Modda Oyna\n");
                        printf("2-> Otomatik Modda Oyna\n");
                        printf("3-> Oyunu Kaydet\n");
                        printf("0-> Ana Menuye Don\n");
                        printf("------------------------\n");
                        
                        gameChoice = getIntInput("Seciminiz: ", 0, 3);

                        if (gameChoice == 1) {
                            resetMatrix(&gs);
                            stackInit(&mStack);
                            stackInit(&rStack);
                            gameStart = time(NULL);
                            playManualMode(&gs, &mStack, &rStack, &rec, gameStart);
                            addGameRecord(users, &userCount, username, &rec);
                            saveScores(users, userCount);
                        } 
                        else if (gameChoice == 2) {
                            resetMatrix(&gs);
                            locatePairs(&gs);
                            stackInit(&mStack);
                            stackInit(&rStack);
                            playAutoMode(&gs, &mStack, &rec);
                            addGameRecord(users, &userCount, username, &rec);
                            saveScores(users, userCount);
                        } 
                        else if (gameChoice == 3) {
                            saveGameState(&gs, &mStack, &rStack, username);
                        }

                    } while (gameChoice != 0);
                    
                    hasMatrix = 0; // Ana menüye dönerken bir sonraki tur için matris durumunu sıfırla
                }
            } 
            else {
                clearInputBuffer(); // Kullanıcı adı okunamadıysa sadece buffer'ı temizle
            }
            break; // Case 1 ve Case 2'nin bitiş noktası
            
        case 3: {
            printf("\n--- SKOR SORGULAMA MENUSU ---\n");
            printf("1-> Tum Oyunculari ve Ozet Skorlarini Listele\n");
            printf("2-> Tek Bir Oyuncunun Detayli Karnesini Goster\n");
            printf("Seciminiz: ");
            scanf("%d", &scoreChoice);
            clearInputBuffer();
            
            if (scoreChoice == 1) {
                showAllScores(users, userCount);
            } else if (scoreChoice == 2) {
                showSingleUserScores(users, userCount);
            } else {
                printf("\n[HATA] Gecersiz secim yaptiniz!\n");
            }
            break;
        }
        
        case 0:
            printf("Programdan cikiliyor...\n");
            break;

        default:
            break;
        }

    } while (mainChoice != 0);

    saveScores(users, userCount);
    free(users);
    return 0;
}