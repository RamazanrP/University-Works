#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
//Our Variables for Every Funtion can access
char table[20][20];
int N,M;
int changing_placement_point=0;
int bomb_point=0;
char elements[]= {'*','/','+','%','0'};
// Creating Items
char random_item(){
    return elements[rand() % 5];
}
void print_table(){
    printf("\n   ");
    int i,j;
    for(j = 0; j<M; j++) printf("%2d ", j+1);
    printf("\n");

    printf("   ");
    for(j=0; j<M; j++) printf("---");
    printf("\n");
    
    for( i=0; i<N; i++){
        printf("%2d| ", i+1); //We used %2d for that no single digit- double digit distinction
        for( j=0; j<M ; j++){
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------\n");
    printf("Total Changing Placement: %d\n", changing_placement_point);
    printf("Total Bombed Placement: %d\n", bomb_point);
}
void move_changing_placement(int row1, int column1, int row2, int column2){
    //I used the temp installation I learned.
    char temp = table[row1][column1];
    table[row1][column1] = table[row2][column2];
    table[row2][column2] = temp;
    int i,j;
    changing_placement_point++;
    system("cls");
    print_table();
    printf("You can see ur move. New line is loading...\n");

    Sleep(2000); //for the change to be visible by player

    for( i=0; i<N; i++){
        for( j=0; j<M; j++){
            table[i][j]= table[i+1][j]; // Our lines going up
        }
    }

    //I added placements to bottom line w/random_item func
    for( j=0; j<M; j++){
        table[N-1][j]= random_item();
    }
    printf("\n Our Placements moved one row up and bottom line has been updated")
}
void gravity() {
    // We'll firstly place lower lines bc upper stones comes up from above
    int i,j;
    for( j=0; j<M; j++){
        int written_index = N-1;
        for( i=N-1; i>=0; i--){
            if(table[i][j] != ' '){ // If stones are not bombed move down
                table[written_index][j] = table[i][j];
                if(written_index != i){
                    table[i][j]= ' ';
                }
                written_index--;
            }
        }
    }
}
//Progress of Bombing
void move_bombing(int row, int column){
    char target_place = table[row][column];

    //Give a notice if target is space
    if(target_place == ' '){
        printf("Error: You can not bomb space!\n");
        return;
    }
    int horizontal_counter = 0;
    int k=column;
    while(k<M && table[row][k] == target_place){
        horizontal_counter++;
        k++;
    }
    int vertical_counter = 0;
    k = row;
    while(k<N && table[k][column] == target_place){
        vertical_counter++;
        k++;
    }
    //Firstly check the suitability
    if(horizontal_counter<3 && vertical_counter<3){
        printf("\n Error: There is no any triple group");
        return;
    }
    /*If we wanted to make the explosion mode a merging type (like in Candy Crush) instead of the one that gives the most points,
    we would just put else after the if block. So we would say there are 3+ stones horizontally or vertically. 
    Then we would say horizontal + vertical -1 stone should explode.
    The score would increase by that much. Because we would count the target stone as two. If we write -1, the score increases correctly.
    Visuals can be prepared for the player in "Super Explosion" or smt :)*/
// I'll stick to the project anyway: Explode the one that gives the most points (" " those)
if(horizontal_counter >= vertical_counter && horizontal_counter>= 3){
    int k;
    for( k=0; k<horizontal_counter; k++){
        table[row][column + k] = ' ';
    }
    bomb_point += horizontal_counter;
    printf("%d explosions were carried out horizontally.\n", horizontal_counter);
} else if(vertical_counter > horizontal_counter && vertical_counter>=3){
    for( k=0; k<vertical_counter; k++){
        table[row + k][column] = ' ';
    }
    bomb_point += vertical_counter;
    printf("%d explosions were carried out vertically.\n", vertical_counter);
}
gravity();
} 
// MAIN FUNCTION
int main() {
    srand(time(NULL));

    printf("-Enter the dimensions of the playing area.(NxM): ");
    scanf("%d %d", &N, &M);
    int i,j;
    for( i=0; i<N;i++) for(j=0; j<M; j++) = ' ';

    int mod;
    printf("For game mode-> for control mode-> 2: ");
    scanf("%d", &mod);
    
    if(mod == 1){
        for(i= N/2; i<N; i++){
            for(j=0; j<M; j++){
                table[i][j] = random_item();
            }
        }
    } else{
        printf("Enter characters:\n");
        for( i=0; i<N; i++){
            for( j=0, j<M; j++){
                //I used " %c" for ignoring spaces
                char temp;
                scanf(" %c", &temp);
                table[i][j] = temp;
            }
        }
    }
    int choice=0;
    while(choice != -1){ // We'll do without Break
        print_table();

        printf("\n for changing -> 1\n For explosion-> 2\n For exit-> -1\n Your Choice: ");
        scanf("%d", &choice);
        if( choice == 1){
            int row1, column1, row2; column2;
            printf("- Coordinates (r1 c1 r2 c2):");
            scanf("%d %d %d %d", &row1, &column1, &row2, &column2);
            move_changing_placement(row1-1, column1-1, row2-1, column2-1);
        } else if (choice == 2){
            int row,column;
            printf("-Coordinates (row and column): ");
            scanf("%d %d", &row, &column);
            //We wrote -1 so that it corresponds to C
            move_bombing(row-1, column-1);
        } else if( choice == -1){
            printf("Game Over\n");
        }
    }
    return 0;
}
