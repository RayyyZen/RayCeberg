#include "file.h"

//This function saves the array that contains the icebergs of the grid
void saveIcebergs(Grid grid){
    FILE *file=NULL;
    int i=0;

    file=fopen("icebergGrid.bin","wb");
    //If the file does not exist it will be created because of the use of the "wb" mode
    if(file==NULL){
        exit(100);
    }
    for(i=0;i<grid.M;i++){
        fwrite(grid.tab[i],sizeof(Iceberg),grid.N,file);
    }
    fclose(file);
}

//This function saves the array that contains all the players of the game
void savePlayers(PlayersInfo info){
    FILE *file=NULL;

    file=fopen("playersInfos.bin","wb");
    //If the file does not exist it will be created because of the use of the "wb" mode
    if(file==NULL){
        exit(110);
    }
    fwrite(info.player,sizeof(Player),info.players,file);
    fclose(file);
}

//This function frees the array that contains the grid
void destroyGrid(Grid *grid){
    int i=0;

    for(i=0;i<grid->M;i++){
        free(grid->tab[i]);
    }
    free(grid->tab);
    grid->tab=NULL;
}

//This function saves the game
void saveGame(Grid grid, PlayersInfo info){
    FILE *file=NULL;
    Game game={grid,info};

    file=fopen("structureGame.bin","wb");
    //If the file does not exist it will be created because of the use of the "wb" mode
    if(file==NULL){
        exit(120);
    }
    fwrite(&game,sizeof(Game),1,file);
    fclose(file);
}

//This function recovers the array containing the icebergs of the grid that is previously saved
void recoverIcebergs(Grid *grid){
    FILE *file=NULL;
    int i=0;

    file=fopen("icebergGrid.bin","rb");
    if(file==NULL){
        exit(130);
    }
    grid->tab=malloc((grid->M)*sizeof(Iceberg*));
    if(grid->tab==NULL){
        exit(30);
    }
    for(i=0;i<grid->M;i++){
        grid->tab[i]=malloc((grid->N)*sizeof(Iceberg));
        if(grid->tab[i]==NULL){
            exit(31+i);
        }
        fread(grid->tab[i],sizeof(Iceberg),grid->N,file);
    }
    fclose(file);
}

//This function recovers the array that contains all the players that were previously saved
void recoverPlayers(PlayersInfo *info){
    FILE *file=NULL;

    file=fopen("playersInfos.bin","rb");
    if(file==NULL){
        exit(140);
    }
    info->player=malloc(info->players*sizeof(Player));
    if(info->player==NULL){
        exit(40);
    }
    fread(info->player,sizeof(Player),info->players,file);
    fclose(file);
}

//This function recovers the game that is previously saved
void recoverGame(Grid *grid, PlayersInfo *info){
    FILE *file=NULL;
    Game game;

    file=fopen("structureGame.bin","rb");
    if(file==NULL){
        exit(150);
    }
    fread(&game,sizeof(Game),1,file);
    *grid=game.grid;
    *info=game.info;
    fclose(file);
}

//This function removes the files that contains the saves of the previous game
void removeSave(){
    FILE *file1=NULL,*file2=NULL,*file3=NULL;

    //The remove() function must be used after the fclose() function
    file1=fopen("structureGame.bin","rb");
    if(file1!=NULL){
        fclose(file1);
        if(remove("structureGame.bin")!=0){exit(55);};
    }
    file2=fopen("icebergGrid.bin","rb");
    if(file2!=NULL){
        fclose(file2);
        if(remove("icebergGrid.bin")!=0){exit(56);};
    }
    file3=fopen("playersInfos.bin","rb");
    if(file3!=NULL){
        fclose(file3);
        if(remove("playersInfos.bin")!=0){exit(57);};
    }
}