/*******************************************************************************************************************************
********************************************************************************************************************************
********************************************************************************************************************************
********************************************************************************************************************************
**************************************************< Chess Game >****************************************************************
********************************************************************************************************************************
****************************************************  Made By   ****************************************************************
********************<Mohammed Deifallah>**************************************************<Muhammed Essam Khamis>****************
********************************************************************************************************************************
*******************************************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Muhammeds.h"
reundo* Head = NULL ;
reundo* Cru = NULL ;

void fillEmpty(char ar[][10])
{
    //determine the main lines of the program
    int i ,j;
    for(i=0; i<10; i++)
        for(j=0; j<10; j++)
        {
            if((i==0&&j==0)||(i==9&&j==9)||(i==0&&j==9)||(i==9&&j==0))
                ar[i][j]='#';
            else if ((i==0||i==9)&&j>0)
                ar[i][j]=64+j;
            else if((j==0||j==9)&&i>0)
                ar[i][j]= 57-i ;
            else if ((i+j)%2==0)
                ar[i][j]='-';
            else
                ar[i][j]='.';
        }
}
void putPieces(char ar[][10])
{
    //to put pieces
    int j;
    for(j=1; j<9; j++)
    {
        ar[2][j]='p';
        ar[7][j]='P';
        switch(j)
        {
        case 1 :
            ar[1][j]='r';
            ar[8][j]='R';
            break;
        case 2 :
            ar[1][j]='n';
            ar[8][j]='N';
            break;
        case 3 :
            ar[1][j]='b';
            ar[8][j]='B';
            break;
        case 4 :
            ar[1][j]='q';
            ar[8][j]='Q';
            break;
        case 5 :
            ar[1][j]='k';
            ar[8][j]='K';
            break;
        case 6 :
            ar[1][j]='b';
            ar[8][j]='B';
            break;
        case 7 :
            ar[1][j]='n';
            ar[8][j]='N';
            break;
        case 8 :
            ar[1][j]='r';
            ar[8][j]='R';
            break;
        }
    }

}
void printChess(char ar[][10])
{
    //print all the board and pieces with formatting
    int x ,y ;
    for(x=0; x<10; x++)
    {
        for(y=0; y<10; y++)
        {
            // Formatting
            printf("|");
            printf(" %c ",ar[x][y]);
        }
        printf("|");
        printf("\n");
        for(y=0; y<11; y++)
        {
            printf("|");
            if(y!=10)
                printf("___");
        }
        printf("\n");
    }
}
void printList(char ar[], int n)
{
    int i ;
    printf("\nList :\n");
    for (i=0; i<=n; i++)
    {
        if(ar[i]>'A'&&ar[i]<'Z')
            printf("%c ",ar[i]);

    }
    printf("\t\t\t");
    for (i=0; i<=n; i++)
    {
        if(ar[i]>'a'&&ar[i]<'z')
            printf("%c ",ar[i]);

    }
    printf("\n");
}

int checkPiece(char* piece )
{
    if(*piece=='p'||*piece=='P')
        return 1 ;
    if(*piece=='r'||*piece=='R')
        return 2 ;
    if(*piece=='n'||*piece=='N')
        return 3 ;
    if(*piece=='b'||*piece=='B')
        return 4 ;
    if(*piece=='q'||*piece=='Q')
        return 5 ;
    if(*piece=='k'||*piece=='K')
        return 6 ;

    return 0 ;

}

int checkMove(int x,int i , int j , int k ,int l,char ar[][10])
{
    int y =0;
    if(l>0&&l<9&&k<9&&k>0)
    {
        switch(x)
        {
        case 1 :
            y=checkPawn(i,j,k,l,ar);
            break ;
        case 2 :
            y=checkRook(i,j,k,l,ar);
            break ;
        case 4 :
            y=checkBishop(i,j,k,l,ar);
            break ;
        case 3 :
            y=checkKnight(i,j,k,l,ar);
            break ;
        case 5 :
            y=checkQueen(i,j,k,l,ar);
            break ;
        case 6 :
            y=checkKing(i,j,k,l,ar);
            break ;
        }
    }
    return y ;
}
int checkPawn(int i , int j , int k ,int l,char ar[][10])
{
    // if Can move or not
    if(abs(j-l)<=1&&l>0&&l<9&&k>0&&k<9)
    {
        int black1=0,black2=0,white1=0,white2=0;
        char tmp = ar[i][j],tmp2= ar[k][l] ;
        if(isupper(ar[i][j]))
            black1=1;
        else
            white1 = 1 ;
        if(isupper(ar[k][l]))
            black2=1;
        else if (islower(ar[k][l]))
            white2=1;
        if((black1&&black2)||(white1&&white2))
        {
            return 0;
        }
        else if (white1&&!white2)
        {
            if ((i-k)<0&&ar[i][j]=='p')
            {
                // as it moves
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(white.c,white.d,ar)==0)
                {
                    ar[i][j]=tmp;
                    ar[k][l]= tmp2;
                    // to eat the Enemy
                    if(i-k==-1&&abs(j-l)==1&&ar[k][l]!='.'&&ar[k][l]!='-')
                        return 1 ;
                    // to move 2 steps at start
                    if(i==2&&j==l&&i-k==-2)
                        return 1 ;
                    //to move normally
                    if(i-k==-1&&j==l&&(ar[k][l]=='.'||ar[k][l]=='-'))
                        return 1 ;
                }
                ar[i][j]=tmp;
                ar[k][l]= tmp2;
            }
        }
        else if (black1&&!black2)
        {
            if((i-k)>0&&ar[i][j]=='P')
            {
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(black.c,black.d,ar)==0)
                {
                    // return its values
                    ar[i][j]=tmp;
                    ar[k][l]= tmp2;
                    if(i-k==1&&abs(j-l)==1&&ar[k][l]!='.'&&ar[k][l]!='-')
                        return 1 ;
                    //move 2 steps at start
                    if(i==7&&j==l&&i-k==2)
                        return 1 ;
                    // to move normally
                    if(i-k==1&&j==l&&(ar[k][l]=='.'||ar[k][l]=='-'))
                        return 1 ;

                }
                ar[i][j]=tmp;
                ar[k][l]= tmp2;
            }
        }
    }

    return 0;
}
int checkRook(int i,int j , int k , int l,char ar[][10])
{
    int black1=0,black2=0,white1=0,white2=0;
    char tmp = ar[i][j] ,tmp2= ar[k][l];
    if(isupper(ar[i][j]))
        black1=1;
    else
        white1 = 1 ;
    if(isupper(ar[k][l]))
        black2=1;
    else if (islower(ar[k][l]))
        white2=1;
    if(((i==k&&j!=l)||(l==j&&i!=k))&&k>0&&k<9&&l<9&&l>0)
    {

        if((black1&&black2)||(white1&&white2))
        {
            return 0;
        }
        else if (black1&&!black2)
        {
            if(checkTrapRook(i,j,k,l,ar))
            {
                //i want to know if this move will kill the threat or not
                // so i remove it temporary and see the effect of this move if it's not here and the new place makes the king safe
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(black.c,black.d,ar)==0)
                {
                    // return its values
                    ar[i][j]=tmp;
                    ar[k][l]= tmp2;
                    return 2 ;
                }
                //return its values
                ar[i][j]=tmp;
                ar[k][l]= tmp2;
            }
        }
        else if (white1&&!white2)
        {
            if(checkTrapRook(i,j,k,l,ar))
            {
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(white.c,white.d,ar)==0)
                {
                    ar[i][j]=tmp;
                    ar[k][l]= tmp2;
                    return 2 ;
                }
                ar[i][j]=tmp;
                ar[k][l]= tmp2;
            }


        }

    }

    return 0 ;
}
int checkBishop(int i,int j,int k,int l,char ar[][10])
{
    int black1=0,black2=0,white1=0,white2=0;
    char tmp = ar[i][j], tmp2= ar[k][l];
    if(isupper(ar[i][j]))
        black1=1;
    else
        white1 = 1 ;
    if(isupper(ar[k][l]))
        black2=1;
    else if (islower(ar[k][l]))
        white2=1;
    if((i+j)%2==(k+l)%2 && abs(i-k)==abs(j-l)&&k>0&&k<9&&l>0&&l<9)
    {
        if((black1&&black2)||(white1&&white2))
        {
            return 0;
        }
        else if (white1&&!white2)
        {
            if(checkTrapBishop(i,j,k,l,ar))
            {
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(white.c,white.d,ar)==0)
                {
                    ar[i][j]=tmp;
                    ar[k][l]= tmp2;
                    return 4 ;
                }
                ar[i][j]=tmp;
                ar[k][l]= tmp2;

            }

        }
        // same as rook :D
        else if (black1&&!black2)
        {
            if(checkTrapBishop(i,j,k,l,ar))
            {
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(black.c,black.d,ar)==0)
                {
                    ar[i][j]=tmp;
                    ar[k][l]= tmp2;
                    return 4 ;
                }
                ar[i][j]=tmp;
                ar[k][l]= tmp2;

            }

        }
    }

    return 0;
}
int checkKnight(int i,int j, int k, int l,char ar[][10])
{
    int black1=0,black2=0,white1=0,white2=0;
    char tmp = ar[i][j] ,tmp2=ar[k][l];
    if(isupper(ar[i][j]))
        black1=1;
    else
        white1 = 1 ;
    if(isupper(ar[k][l]))
        black2=1;
    else if (islower(ar[k][l]))
        white2=1;
    if((i+j)%2!=(k+l)%2&&k<9&&k>0&&l>0&&l<9)
    {
        if(abs(i-k)+abs(j-l)==3&&i!=k&&j!=l)
        {
            //don't know why code this !!
            if(black1&&!black2)
            {
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(black.c,black.d,ar)==0)
                {
                    ar[i][j]=tmp;
                    ar[k][l]=tmp2;
                    return 3;
                }
                ar[i][j]=tmp;
                ar[k][l]=tmp2;
            }
            else if (white1&&!white2)
            {
                ar[i][j]='.';
                ar[k][l]=tmp;
                if(openTrack(white.c,white.d,ar)==0)
                {
                    ar[i][j]=tmp;
                    ar[k][l]=tmp2;
                    return 3;
                }
                ar[i][j]=tmp;
                ar[k][l]=tmp2;
            }
        }
    }
    return 0 ;
}

int checkQueen(int i , int j , int k , int l,char ar[][10])
{
    if((i==k&&j!=l)||(l==j&&i!=k))
    {
        if(checkRook(i,j,k,l,ar))
            return 5;
    }
    else if((i+j)%2==(k+l)%2 && abs(i-k)==abs(j-l))
    {
        if (checkBishop(i,j,k,l,ar))
            return 5 ;
    }

    return 0 ;
}
int checkKing(int i , int j , int k , int l,char ar[][10] )
{
    char tmp2= ar[k][l],tmp=ar[i][j];
    int black1=0,black2=0,white1=1,white2=1;
    if(isupper(ar[i][j]))
    {
        black1=1;
        white1=0;
    }
    if (isupper(ar[k][l]))
    {
     black2=1;
     white2 = 0;
    }

    if(abs(i-k)<=1&&abs(j-l)<=1)
    {
        if((black1&&black2)||(white1&&white2))
            return 0;
        if(black1&&!black2)
        {
            ar[k][l]='K';
            ar[i][j]= tmp2;
        }
        else if (white1&&!white2)
        {
            ar[k][l]='k';
            ar[i][j]= tmp2;
        }
        if(openTrack(k,l,ar)==0)
        {
            ar[k][l]=tmp2;
            ar[i][j]=tmp;
            if(black1)
            {
                black.c = k;
                black.d = l;
            }
            else
            {
                white.c = k;
                white.d = l;
            }
            return 6 ;
        }

    }
            ar[k][l]=tmp2;
            ar[i][j]=tmp;
    return 0 ;
}
int checkTrapRook(int i , int j , int k , int l,char ar[][10])
{
    int trap = 2 ;
    int big,small ;
    //check if moving vertical
    if(j==l)
    {
        //determine who is bigger
        if (i>k)
        {
            small =k+1;
            big = i;
        }
        else
        {
            big = k ;
            small = i+1;
        }
        //looping from the small to the big
        for(; small<big; small++)
        {
            //if not empty then the move invalid
            if(ar[small][j]!='.'&&ar[small][j]!='-')
            {
                trap = 0 ;
                break ;
            }
        }
    }
    else
    {
        if(j>l)
        {
            big = j ;
            small = l+1;
        }
        else
        {
            big =l ;
            small= j+1;

        }
        // move from the start to end or vice versa
        for(; small<big; small++)
        {
            //if not empty then the move invalid
            if(ar[k][small]!='.'&&ar[k][small]!='-')
            {
                trap= 0 ;
                break ;
            }
        }
    }
    //return 0 or 2 only
    return trap ;
}
int checkTrapBishop(int i , int j , int k,int l , char ar[][10])
{
    // check if friend or not
    int x,y,n, trap = 3;
    if((ar[i][j]<91&&ar[i][j]>64&&ar[k][l]<91&&ar[k][l]>64)||(ar[i][j]<123&&ar[i][j]>96&&ar[k][l]<123&&ar[k][l]>96))
    {
        trap = 0;
        return trap ;
    }
    if(j!=l)
    {
        if((i-k)/(j-l)>0)
        {
            if(i>k)
            {
                x=k+1;
                y=l+1;
                n=i-k;
            }
            else
            {
                x=i+1;
                y=j+1;
                n=k-i;
            }
            for(; n>1; n--,x++,y++)
            {
                if(ar[x][y]!='.'&&ar[x][y]!='-')
                {
                    trap = 0 ;
                    break ;
                }
            }
        }
        else
        {
            if(i>k)
            {
                x=k+1;
                y=l-1;
                n=i-k;
            }
            else
            {
                y=j-1;
                x=i+1;
                n=k-i;
            }
            for(; n>1; n--,x++,y--)
            {
                if(ar[x][y]!='.'&&ar[x][y]!='-')
                {
                    trap = 0;
                    break ;
                }
            }


        }
    }
    return trap ;

}
int checkTrapQueen(int i,int j , int k , int l,char ar[][10])
{
    int trap = 5 ;
    if(i==k||j==l)
    {
        if(checkTrapRook(i,j,k,l,ar))
            return trap;
    }
    if(abs(i-k)==abs(j-l))
    {
        if (checkTrapBishop(i,j,k,l,ar))
            return trap;
    }
    return 0 ;
}
void save (char ar[],char c )
{
    reundo* mv = malloc(sizeof(reundo));
    if(mv!=NULL)
    {
        if(Head==NULL)
        {
            reundo* last = malloc(sizeof(reundo));
            last-> moves = "last" ;
            last->place = '0' ;
            last->pre=Head;
            last->next=NULL;
            Head=last;
            Cru=Head;
            mv->moves= ar ;
            mv->place= c;
            Cru->next =mv;
            mv->pre=Cru;
            mv->next = NULL;
            Head=mv;
            Cru=Head;
        }
        else
        {
            //strcpy(mv->moves,ar);
            mv->moves= ar ;
            mv->place= c;
            Cru->next =mv;
            mv->pre=Cru;
            mv->next = NULL;
            Head=mv;
            Cru=Head;
        }

    }

}
char unRedo (char ch,char ar[][10])
{
    char n='0' ;
    if(Cru==NULL)
        return n ;
    //to undo press z
    if(ch=='z')
    {
        //
        if(Cru==NULL||strcmp(Cru->moves,"last")==0)
            return n;
        char mv[6];
        strcpy(mv,Cru->moves);
        char place = Cru->place;
        if(place!='.'&&place!='-')
            n=place;
        undoMove(mv,place,ar);
        if(Cru->pre!=NULL)
            Cru=Cru->pre;
    }
    if(ch=='y')
    {
        if(Cru==NULL||Cru->next==NULL)
            return n ;
        Cru=Cru->next;
        char mv[6];
        strcpy(mv,Cru->moves);
        //char place = Cru->place;
        n = movePiece(mv,ar);

    }
    return n ;
}
// check Who is playing
int checkPlayer(int x , char* piece)
{
    if(x%2==0&&*piece>96&&*piece<122)
        return 1 ;
    if(x%2==1&&*piece>64&&*piece<90)
        return 1 ;
    return 0 ;
}
// load the file
piece load (char ar[][10],char loseList[])
{
    int i,j,k,l,promoted;
    piece nAndCounter = {0,0};  //In case of loading it returns the player's turn and the loselist
    piece checking ; //To identify the piece which puts the king in check
    char* piec ;    //To identify the piece type
    FILE* fp = fopen("Tmp.txt","r");
    if(fp==NULL){
        printf("File Not found\n");
        nAndCounter.d=-1;
        return nAndCounter;
    }
    char mv[6];
    while(!feof(fp))
    {
        fscanf(fp," %s ",mv);
        promoted=0;
        // movepiece(mv,ar);
        j=mv[0]%64;
        i=-1*mv[1]+57;
        l=mv[2]%64;
        k=-1*mv[3]+57;
        piec= &(ar[i][j]);
        int check1 = checkPiece(piec);
        int check2 = checkMove(check1,i,j,k,l,ar);
        int check3 = checkPlayer(nAndCounter.d,piec);
        if(check1==check2&&check1!=0&&check3)
        {
            //save(mv,ar[k][l]);
            if(ar[k][l]!='.' && ar[k][l]!='-')
            {
                loseList[nAndCounter.c]= ar[k][l];
                nAndCounter.c++;
            }
            movePiece(mv,ar);
            promoted=checkPromotion(mv,ar);
            if(promoted)
            {
                printf("Promotion\n");
                getch();
            }
            system("cls");
            printChess(ar);
            if(nAndCounter.d%2==0)
            {
                int opened = openTrack(black.c,black.d,ar);
                if(opened==2)
                {
                    if(!runKingRun(black.c,black.d,ar))
                    {
                        printf("Check mate\n");
                        nAndCounter.d=-1;
                        return nAndCounter ;
                    }
                }
                else if (opened==1)
                {
                    checking= DetectTheFuckingPiece(black.c,black.d,ar);
                    if(runKingRun(black.c,black.d,ar)==0&&preventThreat(ar,checking)==0)
                    {
                        printf("Check mate\n");
                        nAndCounter.d=-1;
                        return nAndCounter;
                    }
                    else
                        printf("Check\n");
                }
                else if (opened==0)
                {
                    int counter = numOfPieces(ar,'b'),o=0,t,r;
                    if(runKingRun(black.c,black.d,ar)==0)
                    {
                        for(t=1; t<9; t++)
                            for(r=1; r<9; r++)
                            {
                                if(isupper(ar[t][r])&&ar[t][r]!='K')
                                {
                                    if(stalmateValidation1(t,r,ar)||stalmateValidation2(t,r,ar))
                                        o++;
                                }
                            }
                        if(o==counter-1)
                        {
                            printf("Stalemate\n");
                            nAndCounter.d=-1;
                            return nAndCounter;
                        }
                    }
                }
            }
            else
            {
                int opened = openTrack(white.c,white.d,ar);
                if(opened==2)
                {
                    if(!runKingRun(white.c,white.d,ar))
                    {
                        printf("Check mate\n");
                        nAndCounter.d=-1;
                        return nAndCounter ;
                    }
                }
                else if (opened==1)
                {
                    checking= DetectTheFuckingPiece(white.c,white.d,ar);
                    if(!runKingRun(white.c,white.d,ar)&&!preventThreat(ar,checking))
                    {
                        printf("Check mate\n");
                        nAndCounter.d=-1;
                        return  nAndCounter;
                    }
                    else
                        printf("Check\n");
                }
                else if ( opened==0 )
                {
                    int counter = numOfPieces(ar,'w'),o=0,t,r;
                    if(runKingRun(white.c,white.d,ar)==0)
                    {
                        for(t=1; t<9; t++)
                            for(r=1; r<9; r++)
                            {
                                if(islower(ar[t][r])&&ar[t][r]!='k')
                                {
                                    if(stalmateValidation1(t,r,ar)||stalmateValidation2(t,r,ar))
                                        o++;
                                }

                            }
                        if(o==counter-1)
                        {
                            printf("Stalemate\n");
                            nAndCounter.d=-1;
                            return nAndCounter;
                        }


                    }
                }
            }
            nAndCounter.d++;

        }
//        if(strlen(mv)==5)
//        {
//            checkpromotion(mv,ar);
//        }
//        system("cls");
//        printchess(ar);
//        counter++;
    }
    fclose(fp);
    return nAndCounter;
}

//save the file
void saveFile(int x )
{
    FILE* fp = fopen("Tmp.txt","w");
    if(fp==NULL){
        printf("Couldn't Save the game\n");
        return;
    }
    int y = 1;
    reundo* save = Head;
    if (save!=NULL)
    {
        for(; y<x; save=save->pre,y++);
        for(; save!=NULL; save=save->next)
        {
            fputs(save->moves,fp);
            fputs("\n",fp);
        }

    }
    fclose(fp);
}

void undoMove(char mv[],char place,char ar[][10])
{
    int j=mv[0]%64;
    int i=-1*mv[1]+57;
    int l=mv[2]%64;
    int k=-1*mv[3]+57;
    if(strlen(mv)==4)
    {
        ar[i][j]=ar[k][l];
    }
    if(strlen(mv)==5)
    {
        if(isupper(ar[k][l]))
            ar[i][j]='P';
        else
            ar[i][j]='p';
    }
    ar[k][l]=place;
}
char movePiece(char* mv ,char ar[][10])
{
    char n='0';
    int j=mv[0]%64;
    int i=-1*mv[1]+57;
    int l=mv[2]%64;
    int k=-1*mv[3]+57;
    if(ar[k][l]!='.'&&ar[k][l]!='-')
        n=ar[k][l];
    ar[k][l]=ar[i][j];
    if((i+j)%2==1)
        ar[i][j]='.';
    else
        ar[i][j]='-';

    return n ;
}
int checkPromotion(char mv[],char ar[][10])
{
    int l=mv[2]%64;
    int k=-1*mv[3]+57;
    if(checkPiece(&(ar[k][l]))==1)
    {
        if(mv[4]=='n'||mv[4]=='N'||mv[4]=='b'||mv[4]=='B'||mv[4]=='q'||mv[4]=='Q'||mv[4]=='R'||mv[4]=='r')
        {
            if(isupper(ar[k][l])&&k==1)
               ar[k][l]=toupper(mv[4]);
            if(islower(ar[k][l])&&k==8)
               ar[k][l]=tolower(mv[4]);
             return 1;
        }
    }
    return 0;

}
int check (int k , int l ,int x , int y,char ar[][10])
{
    switch(ar[k][l])
    {
    case 'p' :
    case 'P' :
        if(checkPawn(k,l,x,y,ar))
            return 1 ;
        break;
    case 'b' :
    case 'B' :
        if(checkBishop(k,l,x,y,ar))
            return 1 ;
        break;
    case 'q' :
    case 'Q' :
        if(checkQueen(k,l,x,y,ar))
            return 1 ;
        break;
    case 'r' :
    case 'R' :
        if (checkRook(k,l,x,y,ar))
            return 1 ;
        break;
    case 'n' :
    case 'N' :
        if(checkKnight(k,l,x,y,ar))
            return 1 ;
        break;
    }

    return 0 ;
}
int openTrack(int x , int y,char ar[][10])
{
    int i,j,white=1,find=0;
    if (isupper(ar[x][y]))
        white=0;
    for (i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            if(!white)
            {
                if(ar[i][j]=='b'||ar[i][j]=='r'||ar[i][j]=='q'||ar[i][j]=='p'||ar[i][j]=='n')
                    if(check(i,j,x,y,ar))
                        find++;
            }
            if(white)
            {
                if(ar[i][j]=='B'||ar[i][j]=='R'||ar[i][j]=='Q'||ar[i][j]=='P'||ar[i][j]=='N')
                    if(check(i,j,x,y,ar))
                        find++ ;
            }

        }
    }
    return find;
}
int runKingRun(int x, int y,char ar[][10])
{
    int i,j,find =0;
    for(i=x-1; i<x+2&&find==0; i++)
    {
        for(j=y-1; j<y+2&&find==0; j++)
        {
            if (ar[i][j]=='.'||ar[i][j]=='-')
            {
                if(isupper(ar[x][y])&&ar[i][j]!='K')
                {
                    int tmp=ar[i][j];
                    ar[i][j]='K';
                    ar[x][y]=tmp;
                    if(openTrack(i,j,ar)==0)
                    {
                        find = 1 ;

                    }
                    ar[i][j]=tmp;
                    ar[x][y]='K';
                }
                else if (islower(ar[x][y])&&ar[i][j]!='k')
                {
                    int tmp=ar[i][j];
                    ar[i][j]='k';
                    ar[x][y]=tmp ;
                    if(openTrack(i,j,ar)==0)
                    {
                        find = 1 ;

                    }
                    ar[i][j]=tmp;
                    ar[x][y]='k';
                }

            }
        }
    }
    return find ;
}
int preventThreat(char ar[][10],piece check)
{
    int p=0;
    if(isupper(ar[check.c][check.d]))
    {
        if(ar[check.c][check.d]=='R')
            p=preventThreatRook(check.c,check.d,white.c,white.d,ar);
        else if (ar[check.c][check.d]=='B')
            p=preventThreatBishop(check.c ,check.d,white.c , white.d,ar);
        else if (ar[check.c][check.d]=='Q')
        {
            if(check.c==white.c||check.d==white.d)
                p=preventThreatRook(check.c,check.d,white.c,white.d,ar);
            else
                p=preventThreatBishop(check.c ,check.d,white.c , white.d,ar);
        }
        else if (ar[check.c][check.d]=='N'||ar[check.c][check.d]=='P')
            p=preventThreatKnightAndPawn(check.c,check.d,white.c,white.d,ar);
    }
    else
    {
        if(ar[check.c][check.d]=='r')
            p=preventThreatRook(check.c,check.d,black.c,black.d,ar);
        else if (ar[check.c][check.d]=='b')
            p=preventThreatBishop(check.c ,check.d,black.c , black.d,ar);
        else if (ar[check.c][check.d]=='q')
        {
            if(check.c==black.c||check.d==black.d)
                p=preventThreatRook(check.c,check.d,black.c,black.d,ar);
            else
                p=preventThreatBishop(check.c ,check.d,black.c , black.d,ar);
        }
        else if (ar[check.c][check.d]=='n'||ar[check.c][check.d]=='p')
            p=preventThreatKnightAndPawn(check.c,check.d,black.c,black.d,ar);
    }
    return p ;
}
//
int preventThreatRook(int i, int j ,int k , int l ,char ar[][10])
{
    int big , small ,u,v, upper1=0,lower1=0;
    if(j==l)
    {
        if(i>k)
        {
            small = k+1;
            big=i;
        }
        else
        {
            big=k;
            small=i;
        }
        for(; small<big; small++)
        {
            for(u=1; u<9; u++)
            {
                for(v=1; v<9; v++)
                {
                    int check = checkPiece(&ar[u][v]);
                    if(check&&checkMove(check,u,v,small,l,ar))
                    {
                        if(isupper(ar[u][v]))
                            upper1++ ;
                        else
                            lower1++ ;
                    }
                }
            }
        }
    }
    else
    {
        if(j>l)
        {
            big = j ;
            small = l+1;
        }
        else
        {
            big =l ;
            small= j;

        }
        // move from the start to end or vice versa
        for(; small<big; small++)
        {
            //if not empty then the move invalid
            for(u=0; u<9; u++)
            {
                for(v=0; v<9; v++)
                {
                    int check = checkPiece(&ar[u][v]);
                    if(check&&checkMove(check,u,v,k,small,ar))
                    {
                        if(isupper(ar[u][v]))
                            upper1++;
                        else
                            lower1++;
                    }
                }

            }
        }
    }
    if(isupper(ar[k][l]))
        return upper1;
    else
        return lower1;
}

int preventThreatBishop(int i , int j , int k , int l, char ar[][10])
{
    int x,y,n,lower=0 , upper=0 ,u,v;
    if((i-k)/(j-l)>0)
    {
        if(i>k)
        {
            x=k+1;
            y=l+1;
            n=i-k;
        }
        else
        {
            x=i;
            y=j;
            n=k-i;
        }
        for(; n>0; n--,x++,y++)
        {
            for(u=1; u<9; u++)
            {
                for(v=1; v<9; v++)
                {
                    int check = checkPiece(&ar[u][v]);
                    if(check&&checkMove(check,u,v,x,y,ar))
                    {
                        if(isupper(ar[u][v]))
                            upper++;
                        else
                            lower++;
                    }
                }
            }
        }
    }
    else
    {
        if(i>k)
        {
            x=k+1;
            y=l-1;
            n=i-k;
        }
        else
        {
            y=j;
            x=i;
            n=k-i;
        }
        for(; n>0; n--,x++,y--)
        {
            for(u=1; u<9; u++)
            {
                for(v=1; v<9; v++)
                {
                    int check = checkPiece(&ar[u][v]);
                    if(check&&checkMove(check,u,v,x,y,ar))
                    {
                        if(isupper(ar[u][v]))
                            upper++;
                        else
                            lower++;
                    }
                }

            }


        }
    }
    if(isupper(ar[k][l]))
        return upper;
    else
        return lower;
}
int preventThreatKnightAndPawn(int i, int j, int k, int l, char ar[][10])
{
    int x,y,upper1=0,lower1=0;
    for(x=1;x<9;x++)
    {
        for(y=1;y<9;y++)
        {
         int check=checkPiece(&ar[x][y]);
         if(check&&checkMove(check,x,y,i,j,ar))
         {
            if(isupper(ar[x][y]))
                upper1++;
            else
                lower1++;
         }
        }
    }
    if(isupper(ar[k][l]))
        return upper1;
    else
        return lower1;
}
// to see if we remove the piece the king will be in danger
int stalmateValidation1(int x, int y ,char ar[][10])
{
    int white1=1,counter=0;
    char tmp ;
    if(isupper(ar[x][y]))
        white1=0;
    if(white1)
    {
        tmp = ar[x][y];
        ar[x][y]=(x+y)%2 ? '.' : '-' ;
        if(openTrack(white.c,white.d,ar))
        {
            counter++;
        }
        ar[x][y]= tmp ;
    }
    else
    {
        tmp = ar[x][y];
        ar[x][y]=(x+y)%2 ? '.' : '-' ;
        if(openTrack(black.c,black.d,ar))
        {
            counter++;
        }
        ar[x][y]= tmp ;

    }
    return counter ;
}
// to see if the piece can move or not
int stalmateValidation2(int x , int y , char ar[][10])
{
    int i=x,j=y;
    int white1=1;
    if(isupper(ar[x][y]))
        white1=0;
    if(white1)
    {
        int check1 = checkPiece(&ar[x][y]);
        switch(check1)
        {
        case 1 :
            if(!checkPawn(i,j,i+1,j,ar)&&!checkPawn(i,j,i+1,j+1,ar)&&!checkPawn(i,j,i+1,j-1,ar))
                return 1;
            break ;
        case 2 :
            if(!checkRook(i,j,i,j+1,ar)&&!checkRook(i,j,i,j-1,ar)&&!checkRook(i,j,i+1,j,ar)&&!checkRook(i,j,i-1,j,ar))
                return 1 ;
            break ;
        case 3 :
            if(!checkKnight(i,j,i-2,j+1,ar)&&!checkKnight(i,j,i-2,j-1,ar)&&!checkKnight(i,j,i-1,j-2,ar)&&!checkKnight(i,j,i-1,j+2,ar)&&!checkKnight(i,j,i+1,j-2,ar)&&!checkKnight(i,j,i+1,j+2,ar)&&!checkKnight(i,j,i+2,j-1,ar)&&!checkKnight(i,j,i+2,j+1,ar))
                return 1;
            break ;
        case 4 :
            if(!checkBishop(i,j,i-1,j-1,ar)&&!checkBishop(i,j,i-1,j+1,ar)&&!checkBishop(i,j,i+1,j-1,ar)&&!checkBishop(i,j,i+1,j+1,ar))
                return 1 ;
            break ;
        case 5 :
            if(!checkQueen(i,j,i,j+1,ar)&&!checkQueen(i,j,i,j-1,ar)&&!checkQueen(i,j,i+1,j,ar)&&!checkQueen(i,j,i-1,j,ar)&&!checkQueen(i,j,i-1,j-1,ar)&&!checkQueen(i,j,i-1,j+1,ar)&&!checkQueen(i,j,i+1,j-1,ar)&&!checkQueen(i,j,i+1,j+1,ar))
                return 1 ;
            break ;
        }

    }
    else
    {
        int check1 = checkPiece(&ar[x][y]);
        switch(check1)
        {
        case 1 :
            if(!checkPawn(i,j,i-1,j,ar)&&!checkPawn(i,j,i-1,j+1,ar)&&!checkPawn(i,j,i-1,j-1,ar))
                return 1;
            break ;
        case 2 :
            if(!checkRook(i,j,i-1,j,ar)&&!checkRook(i,j,i,j-1,ar)&&!checkRook(i,j,i+1,j+1,ar)&&!checkRook(i,j,i+1,j,ar))
                return 1 ;
            break ;
        case 3 :
            if(!checkKnight(i,j,i-2,j-1,ar)&&!checkKnight(i,j,i-2,j+1,ar)&&!checkKnight(i,j,i-1,j-2,ar)&&!checkKnight(i,j,i-1,j+2,ar)&&!checkKnight(i,j,i+1,j-2,ar)&&!checkKnight(i,j,i+1,j+2,ar)&&!checkKnight(i,j,i+2,j-1,ar)&&!checkKnight(i,j,i+2,j+1,ar))
                return 1;
            break ;
        case 4 :
            if(!checkBishop(i,j,i-1,j-1,ar)&&!checkBishop(i,j,i-1,j+1,ar)&&!checkBishop(i,j,i+1,j-1,ar)&&!checkBishop(i,j,i+1,j+1,ar))
                return 1 ;
            break ;
        case 5 :
            if(!checkQueen(i,j,i-1,j-1,ar)&&!checkQueen(i,j,i-1,j,ar)&&!checkQueen(i,j,i-1,j+1,ar)&&!checkQueen(i,j,i,j-1,ar)&&!checkQueen(i,j,i,j+1,ar)&&!checkQueen(i,j,i+1,j-1,ar)&&!checkQueen(i,j,i+1,j,ar)&&!checkQueen(i,j,i+1,j+1,ar))
                return 1 ;
            break ;
        }
    }
    return 0 ;
}
int numOfPieces(char ar[][10],char c)
{
    int i , j,counter=0;
    if(c=='b')
    {
        for(i=1; i<9; i++)
        {
            for(j=1; j<9; j++)
                if(isupper(ar[i][j]))
                    counter++;
        }
    }
    else
    {
        for(i=1; i<9; i++)
        {
            for(j=1; j<9; j++)
                if(islower(ar[i][j]))
                    counter++;
        }
    }
    return counter;
}

piece DetectTheFuckingPiece(int k, int l , char ar[][10])
{
    piece checking= {0,0};
    int i,j,white1=1;
    if(isupper(ar[k][l]))
        white1=0;
    for(i=1; i<9; i++)
    {
        for(j=1; j<9; j++)
        {
            if(white1)
            {
                if(ar[i][j]=='B'||ar[i][j]=='N'||ar[i][j]=='P'||ar[i][j]=='Q'||ar[i][j]=='R')
                    if(check(i,j,k,l,ar))
                    {
                        checking.c= i;
                        checking.d=j;
                        return checking;
                    }
            }
            else
            {
                if(ar[i][j]=='b'||ar[i][j]=='n'||ar[i][j]=='p'||ar[i][j]=='q'||ar[i][j]=='r')
                    if(check(i,j,k,l,ar))
                    {
                        checking.c= i;
                        checking.d=j;
                        return checking;
                    }
            }
        }
    }
    return checking ;
}
