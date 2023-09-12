#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    int col=8,rig=4,x,y;
    char mat[4][8];

    for(y=0;y<rig;y++){
        for(x=0;x<col;x++){
            mat[y][x]=' -';
        }

    }
    mat[1][1]='O';
    for(y=0;y<rig;y++){
        for(x=0;x<col;x++){
            printf(" %c",mat[y][x]);
        }
        printf("\n");

    }
}
