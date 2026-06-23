#include <stdio.h>
#include <stdlib.h>
/*
m:              label:      (4 tarafa bakıyoruz, 8 yöne bakan hali aşağıda)
1 1 1 0 0 0     1 1 1 0 0 0 
1 0 0 0 1 1     1 0 0 0 2 2
0 0 0 0 1 0     0 0 0 0 2 0
0 0 0 0 0 0     0 0 0 0 0 0 
1 0 1 1 1 1     3 0 4 4 4 4
*/
void ccl(int, int, int ,int **,int ,int ,int **);
void main() {
    int **m, **label, row_count, col_count, component=1, i,j;
    for (i = 0; i < row_count; i++) // Burdan önce matris için yer ayırdık ve elemanları aldık diyelim, kodu uzatmıyorum
        for (j = 0; j < col_count; j++) // Eğer matriste 1 varsa label'da burası marklanmamışsa fonksiyona yönlendir
            if (!label[i][j] && m[i][j]) ccl(i, j, component++, m,row_count,col_count,label);
}

void ccl(int x, int y, int current_label,int **m,int row_count,int col_count,int **label) {

  	if (x < 0 || x == row_count) return; // out of bounds
  	if (y < 0 || y == col_count) return; // out of bounds
  	if (label[x][y] || !m[x][y]) return; // already labeled or not marked with 1 in m

	label[x][y] = current_label; // Component bizim adacık sayımızı tutuyordu, şimdi 4 tarafına bakmak için çağıralım
	ccl(x + 1, y + 0, current_label,m,row_count,col_count,label); 	ccl(x + 0, y + 1, current_label,m,row_count,col_count,label);
	ccl(x - 1, y + 0, current_label,m,row_count,col_count,label);   ccl(x + 0, y - 1, current_label,m,row_count,col_count,label);	
	
	//*((int *)label+x*col_count+y)=current_label; //dynamic memory alloc ile ayr�lan yerde elemanalar iteratif yerle�mediginden bu kullan�m runtime hatasi verir
	
	/*int direction; 
	int dx[] = {+1, 0, -1, 0};               8 yön için =>  int dx[] = {-1, -1, -1,  0,  0,  1,  1,  1}; 0-0 yok :)
	int dy[] = {0, +1, 0, -1};               8 yön için =>  int dy[] = {-1,  0,  1, -1,  1, -1,  0,  1};
	for (direction = 0; direction < 4; ++direction) 8 yön için burada 8 kere dönecekti
		ccl(x + dx[direction], y + dy[direction], current_label,m,row_count,col_count,label);*/

}