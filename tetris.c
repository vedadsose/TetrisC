//
//  Created by Vedad Sose on 02/12/14.
//  Copyright (c) 2014 Vedad Sose. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int pieces[999][10][2];


int nextpiece = 1;

bool testRender() {
    int matrix[21][21];
    for (int i = 1; i <= 20; i++) { for(int j = 1; j <= 20; j++) { matrix[i][j] = 0; } }
    // Prvobitno setovanje matrice
    for(int i = 1; i <= 19; i++) {
        matrix[i][1] = 1;
        matrix[i][20] = 1;
        matrix[20][i] = 1;
    }
    matrix[20][20] = 1;
    
    for(int i = 1; i < nextpiece; i++) {
        for (int j = 0; j < 4; j++) {
            if(matrix[pieces[i][j][0]][pieces[i][j][1]] == 1) return false;
            else matrix[pieces[i][j][0]][pieces[i][j][1]] = 1;
        }
    }
    
    return true;
}

int getRandom(int max)
{
    return rand() % max + 1;
}


// Function that renders the matrix
int render() {
    int matrix[21][21];
    for (int i = 1; i <= 20; i++) { for(int j = 1; j <= 20; j++) { matrix[i][j] = 0; } }
    // Prvobitno setovanje matrice
    for(int i = 1; i <= 19; i++) {
        matrix[i][1] = 1;
        matrix[i][20] = 1;
        matrix[20][i] = 1;
    }
    matrix[20][20] = 1;
    
    for(int i = 1; i < nextpiece; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[pieces[i][j][0]][pieces[i][j][1]] = 1;
        }
    }
    
    for(int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 20; j++) {
            if(matrix[i][j]==1) printf("*");
            else printf(" ");
        }
        printf("\n");
    }
    
    return 0;
}

// Function for inserting a new piece in the game
int createPiece(int type) {
    int i = 2+getRandom(16);
    // Array of pieces
    
    switch(type) {
        case 1:
            // ****
            pieces[nextpiece][0][0] = 1;
            pieces[nextpiece][0][1] = i;
            
            pieces[nextpiece][1][0] = 1;
            pieces[nextpiece][1][1] = i+1;
            
            pieces[nextpiece][2][0] = 1;
            pieces[nextpiece][2][1] = i+2;
            
            pieces[nextpiece][3][0] = 1;
            pieces[nextpiece][3][1] = i+3;
            
            break;
        case 2:
            // *
            // *
            // * *
            
            pieces[nextpiece][0][0] = -1;
            pieces[nextpiece][0][1] = i;
            
            pieces[nextpiece][1][0] = 0;
            pieces[nextpiece][1][1] = i;
            
            pieces[nextpiece][2][0] = 1;
            pieces[nextpiece][2][1] = i;
            
            pieces[nextpiece][3][0] = 1;
            pieces[nextpiece][3][1] = i+1;
            
            break;
        case 3:
            //   *
            //   *
            // * *
            
            pieces[nextpiece][0][0] = -1;
            pieces[nextpiece][0][1] = i;
            
            pieces[nextpiece][1][0] = 0;
            pieces[nextpiece][1][1] = i;
            
            pieces[nextpiece][2][0] = 1;
            pieces[nextpiece][2][1] = i;
            
            pieces[nextpiece][3][0] = 1;
            pieces[nextpiece][3][1] = i-1;
            
            break;
            
        case 4:
            //   *
            // * *
            // *
            
            pieces[nextpiece][0][0] = -1;
            pieces[nextpiece][0][1] = i;
            
            pieces[nextpiece][1][0] = 0;
            pieces[nextpiece][1][1] = i;
            
            pieces[nextpiece][2][0] = 0;
            pieces[nextpiece][2][1] = i-1;
            
            pieces[nextpiece][3][0] = 1;
            pieces[nextpiece][3][1] = i-1;
            
            break;
        case 5:
            // * *
            // * *
            
            pieces[nextpiece][0][0] = 0;
            pieces[nextpiece][0][1] = i;
            
            pieces[nextpiece][1][0] = 0;
            pieces[nextpiece][1][1] = i+1;
            
            pieces[nextpiece][2][0] = 1;
            pieces[nextpiece][2][1] = i;
            
            pieces[nextpiece][3][0] = 1;
            pieces[nextpiece][3][1] = i+1;
            
            break;
    }
    nextpiece++;
    return 0;
}

int main() {
    char potez;
    bool play = true;
    bool bottomTest = true;
    bool leftTest = true;
    bool rightTest = true;
    int pbackup[10][2];
    int px, py;

    int i = 0;
    bool canDo = true;
    createPiece(getRandom(5));
    
    while(play) {
        render();
        scanf(" %c", &potez);
        
        i = nextpiece-1;
        canDo = true;
        
        switch (potez) {
            case 'a':
                for (int j = 0; j < 4; j++) {
                    pieces[i][j][0] += 1;
                    pieces[i][j][1] -= 1;
                }
                
                canDo = testRender();
                
                if(!canDo) {
                    for (int j = 0; j < 4; j++) {
                        pieces[i][j][0] -= 1;
                        pieces[i][j][1] += 1;
                    }
                }
                
                break;
            case 'd':
                // Check if we can go right
                for (int j = 0; j < 4; j++) {
                    pieces[i][j][0] += 1;
                    pieces[i][j][1] += 1;
                }
                
                canDo = testRender();
                
                if(!canDo) {
                    for (int j = 0; j < 4; j++) {
                        pieces[i][j][0] -= 1;
                        pieces[i][j][1] -= 1;
                    }
                }
                
                break;
            case 's':
                // Check if we can turn around
                px = pieces[i][2][0];
                py = pieces[i][2][1];
                
                for (int j = 0; j < 4; j++) {
                    int x1 = pieces[i][j][0];
                    int y1 = pieces[i][j][1];
                    
                    pieces[i][j][0] = (y1 + px - py)+1;
                    pieces[i][j][1] = (px + py - x1);
                    
                    pbackup[j][0] = x1;
                    pbackup[j][1] = y1;
                }
                
                canDo = testRender();
                
                if(!canDo) {
                    for (int j = 0; j < 4; j++) {
                        pieces[i][j][0] = pbackup[j][0];
                        pieces[i][j][1] = pbackup[j][1];
                    }
                }
                
                break;
            
            case 'w':
                // Check if we can turn around
                px = pieces[i][2][0];
                py = pieces[i][2][1];
                
                for (int j = 0; j < 4; j++) {
                    int x1 = pieces[i][j][0];
                    int y1 = pieces[i][j][1];
                    
                    pieces[i][j][0] = (px + py - y1)+1;
                    pieces[i][j][1] = (x1 + py - px);
                    
                    pbackup[j][0] = x1;
                    pbackup[j][1] = y1;
                }
                
                canDo = testRender();
                
                if(!canDo) {
                    for (int j = 0; j < 4; j++) {
                        pieces[i][j][0] = pbackup[j][0];
                        pieces[i][j][1] = pbackup[j][1];
                    }
                }
                
                break;

                
        }
        
        if(!canDo) printf("Invalid move.\n");
        else {
            // If any part can move bottom then go for it
            
            // Bottom
            for (int j = 0; j < 4; j++) {
                pieces[i][j][0] += 1;
            }
            bottomTest = testRender();
            for (int j = 0; j < 4; j++) {
                pieces[i][j][0] -= 1;
            }

            // Left
            for (int j = 0; j < 4; j++) {
                pieces[i][j][0] += 1;
                pieces[i][j][1] += 1;
            }
            leftTest = testRender();
            for (int j = 0; j < 4; j++) {
                pieces[i][j][0] -= 1;
                pieces[i][j][1] -= 1;
            }

            // Right
            for (int j = 0; j < 4; j++) {
                pieces[i][j][0] += 1;
                pieces[i][j][1] -= 1;
            }
            rightTest = testRender();
            for (int j = 0; j < 4; j++) {
                pieces[i][j][0] -= 1;
                pieces[i][j][1] += 1;
            }

            
            if(!bottomTest || (!leftTest && !rightTest)) {
                createPiece(getRandom(5));
                
                i++;
                // Bottom
                for (int j = 0; j < 4; j++) {
                    pieces[i][j][0] += 1;
                }
                bottomTest = testRender();
                for (int j = 0; j < 4; j++) {
                    pieces[i][j][0] -= 1;
                }

                if(!bottomTest) {
                    printf("Game over.");
                    play = false;
                }
            }
            
        }
    }
    return 0;
}