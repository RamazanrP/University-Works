#include <stdio.h>
#include <stdlib.h>
typedef union{
    unsigned short raw; // Tuttuğu 16-bit alan sayesinde aşağıdaki density,red gibi şeylere TEK SEFERDE bakabiliyoruz
    struct {
        unsigned char density; // 0-255 Yoğunluk ölçüsü

        struct {
            unsigned char red     : 1;
            unsigned char yellow  : 1;
            unsigned char green   : 1;
            unsigned char error   : 1;
            unsigned char reserved: 4;
        } signal;

    } structured;

} Intersection;

typedef struct Node {
    int row, col;
    Intersection data;
    struct Node* next;
} Node;

Intersection** createMatrix(int n, int m) {
	Intersection** mat = malloc(n * sizeof(Intersection*));
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(m * sizeof(Intersection));
    }
    return mat;
}

void fillMatrix(Intersection** mat, int n, int m) {
	int i,j;
	for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
			mat[i][j].raw = 0; // İlk başta bütün bir alan 0'lansın
            mat[i][j].structured.density = rand() % 256;
            mat[i][j].structured.signal.red = rand() % 2;
            mat[i][j].structured.signal.yellow = rand() % 2;
            mat[i][j].structured.signal.green = rand() % 2;
            mat[i][j].structured.signal.error = 0;
            mat[i][j].structured.signal.reserved = 0;
        }
    }
}

Node* addNode(Node* head, int i, int j, Intersection data){ // intersection tipinde yazdık, sadece matristeki elementi alıyoruz burada, kordinatları zaten geldi
    Node* newNode = malloc(sizeof(Node));
    newNode->row = i;
    newNode->col = j;
    newNode->data = data;
    newNode->next = head; // En sona değil de en başa ekliyor gelen bilgiyi
    return newNode;
}

Node* detectCongestion(Intersection** mat, int n, int m, int threshold) {
    Node* head = NULL; // Fonksiyonu çağıracağız evet ama ='in sol tarafına ne yazacağız? head :) 
	int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {

            if (mat[i][j].structured.density > threshold) {
                head = addNode(head, i, j, mat[i][j]); // Burada mat[i][j] gönderdik, matrisin elementi İnterseciton boyutunda, addNode'da ** olmayacak :)
            }
        }
    }

    return head;
}

void printList(Node* head) {
    while (head) {
        printf("(%d,%d) Density=%d | R:%d Y:%d G:%d\n",
               head->row, head->col,
               head->data.structured.density,
               head->data.structured.signal.red,
               head->data.structured.signal.yellow,
               head->data.structured.signal.green);

        head = head->next;
    }
}

void printMatrix(Intersection** mat, int n, int m) {
	int i,j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {

            printf("[%3d | R:%d Y:%d G:%d E:%d] ",
                mat[i][j].structured.density,
                mat[i][j].structured.signal.red,
                mat[i][j].structured.signal.yellow,
                mat[i][j].structured.signal.green,
                mat[i][j].structured.signal.error
            );
        }
        printf("\n");
    }
}

void findIntersection(Intersection** mat, int n, int m) {
   	int i,j,x,y;
   	printf("Give coordinates of an intersection");
	scanf("%d %d",&x,&y);
    
    int found = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
			    if (mat[i][j].raw == mat[x][y].raw){ // Yine aynı mantık, matchleşme oldu mu diye konrol için sadece raw
                printf("Match found at (%d, %d)\n", i, j);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No matching intersection found.\n");
    }
}

int main() {
    int n = 4, m = 4;

    Intersection** grid = createMatrix(n, m);

    fillMatrix(grid, n, m);
    
    printMatrix(grid,n,m);
    
    findIntersection(grid,n,m); 

    Node* critical = detectCongestion(grid, n, m, 200);

    printList(critical);

    return 0;
}