#include <stdio.h>
#include <string.h>
#include "cs50.h"
#include "Muhammeds.h"
//piece black = {8,5};
//piece white = {1,5};
int main()
{
    black.c = 8;
    black.d=5;
    white.c = 1;
    white.d =5;
    int n=0,l,i,j,k,len,counter=0,promoted;
    piece nAndCounter = {0,0};
    piece checking ;
    char* piece ;
    char ar[10][10];
    char loseList[40]= {'0'};
    char saveAfterGame;
    fillEmpty(ar);
    putPieces(ar);
    printChess(ar);
    printList(loseList,n);
    printf("Enter the Move or \"quit\" to exit or \"l\" to load : ");
    char* mv = GetString();
    while(strcmp(mv,"quit")!=0)
    {
        promoted=0;
        fflush(stdin);
        len = strlen(mv);
        if(len<=3)
        {
            if(mv[0]=='l'&&counter==0)
            {

                nAndCounter=load(ar,loseList);
                n = nAndCounter.c ;
                counter=nAndCounter.d;
                if(counter==-1&&n==0){
                    getch();
                    return 0;}
                else if(counter==-1)
                {
                        printList(loseList,n);
                        getch();
                        return 0;
                }
                printf("Enter the Move or \"quit\" to exit or \"s\" to save : ");
                //mv = GetString();

            }
            else if (mv[0]=='s'&&counter>0)
            {
                saveFile(counter);
                system("cls");
                printChess(ar);
                printList(loseList,n);
                printf("Enter the Move or \"quit\" to exit or \"s\" to save : ");
             //   mv= GetString();

            }
            else if(counter==0&&mv[0]!='y'&&mv[0]!='z')
            {
                system("cls");
                printChess(ar);
                printList(loseList,n);
                printf("Enter the Move or \"quit\" to exit or \"l\" to load : ");
              //  mv = GetString();
            }
            else if ((mv[0]=='z'||mv[0]=='y')&&counter>0)
            {
                char x = unRedo(mv[0],ar);
                if(mv[0]=='z')
                {
                    if(x!='0')
                    {
                        n--;
                        loseList[n]='0';
                    }
                    counter--;
                }
                else
                {
                    // Error
                    if(x!='0')
                    {
                        loseList[n]=x;
                        n++;
                    }
                    counter++;
                }
                system("cls");
                printChess(ar);
                printList(loseList,n);
                printf("Enter the Move or \"quit\" to exit or \"s\" to save : ");
               // mv = GetString();
            }
            else if (counter>0)
            {
                system("cls");
                printChess(ar);
                printList(loseList,n);
                printf("Enter Move or \"quit\" to Exit or \'s\' to save : ");
              //  mv = GetString();
            }
                 mv = GetString();
        }
        else if(len==4||len==5)
        {
            j=atoi(mv);
            i=atoi((mv+1));
            l=atoi((mv+2));
            k=atoi((mv+3));

            if(j!=0||l!=0||i==0||k==0)
            {
                if (counter>0)
                {
                    system("cls");
                    printChess(ar);
                    printList(loseList,n);
                    printf("Enter Move or \"quit\" to Exit or \'s\' to save : ");
                }

                else
                {
                    system("cls");
                    printChess(ar);
                    printList(loseList,n);
                    printf("Enter Move or \"quit\" to Exit or \"l\" to load: ");
                }

                mv = GetString();
            }

            else
            {
                j=mv[0]%64;
                i=-1*mv[1]+57;
                l=mv[2]%64;
                k=-1*mv[3]+57;
                piece= &(ar[i][j]);
                int check1 = checkPiece(piece);
                int check2 = checkMove(check1,i,j,k,l,ar);
                int check3 = checkPlayer(counter,piece);
                if(check1==check2&&check1!=0&&check3)
                {
                    save(mv,ar[k][l]);
                    if(ar[k][l]!='.' && ar[k][l]!='-')
                    {
                        loseList[n]= ar[k][l];
                        n++;
                    }
                    movePiece(mv,ar);
                    if(len==5)
                    {
                        promoted=checkPromotion(mv,ar);
                    }
                    system("cls");
                    printChess(ar);
                   if(counter%2==0)
            {
                int opened = openTrack(black.c,black.d,ar);
                if(opened==2)
                {
                    if(!runKingRun(black.c,black.d,ar))
                    {
                        if(promoted)
                        {
                            printf("Promotion!");
                        }
                        printf("Check mate\n");
                        printList(loseList,n);
                        printf("If you want to save press 's', else press any button: ");
                        scanf(" %c",&saveAfterGame);
                        if(saveAfterGame=='s')
                            saveFile(counter);
                        getch();
                        return 0 ;
                    }
                }
                else if (opened==1)
                {
                    checking= DetectTheFuckingPiece(black.c,black.d,ar);
                    if(runKingRun(black.c,black.d,ar)==0&&preventThreat(ar,checking)==0)
                    {
                        if(promoted)
                        {
                            printf("Promotion!");
                        }
                        printf("Check mate\n");
                        printList(loseList,n);
                        printf("If you want to save press 's', else press any button: ");
                        scanf(" %c",&saveAfterGame);
                        if(saveAfterGame=='s')
                            saveFile(counter);
                        getch();
                        return 0;
                    }
                    else{
                            if(promoted)
                        {
                            printf("Promotion!");
                        }
                        printf("Check\n");
                        printList(loseList,n);
                        getch();
                    }
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
                            if(promoted)
                        {
                            printf("Promotion!");
                        }
                            printf("Stalemate\n");
                            printList(loseList,n);
                            printf("If you want to save press 's', else press any button: ");
                            scanf(" %c",&saveAfterGame);
                            if(saveAfterGame=='s')
                             saveFile(counter);
                            getch();
                            return 0;
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
                        if(promoted)
                        {
                            printf("Promotion!");
                        }
                        printf("Check mate\n");
                        printList(loseList,n);
                        printf("If you want to save press 's', else press any button: ");
                        scanf(" %c",&saveAfterGame);
                        if(saveAfterGame=='s')
                            saveFile(counter);
                        getch();
                        return 0 ;
                    }
                }
                else if (opened==1)
                {
                    checking= DetectTheFuckingPiece(white.c,white.d,ar);
                    if(!runKingRun(white.c,white.d,ar)&&!preventThreat(ar,checking))
                    {
                        if(promoted)
                        {
                            printf("Promotion!");
                        }
                        printf("Check mate\n");
                        printList(loseList,n);
                        printf("If you want to save press 's', else press any button: ");
                        scanf(" %c",&saveAfterGame);
                        if(saveAfterGame=='s')
                            saveFile(counter);
                        getch();
                        return 0;
                    }
                    else
                    {
                        if(promoted)
                        {
                            printf("Promotion!");
                        }
                        printf("Check\n");
                        printList(loseList,n);
                        getch();
                    }
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
                            if(promoted)
                             {
                            printf("Promotion!");
                             }
                            printf("Stalemate\n");
                            printList(loseList,n);
                            printf("If you want to save press 's', else press any button: ");
                            scanf(" %c",&saveAfterGame);
                            if(saveAfterGame=='s')
                             saveFile(counter);
                            getch();
                            return 0;
                        }


                    }
                }
            }
                counter++;

                }
                system("cls");
                printChess(ar);
                if(promoted)
                {
                    printf("Promotion");
                }
                printList(loseList,n);
                printf("\nEnter Move or \"quit\" to Exit or \'s\' to save : ");
                mv = GetString();


            }

        }
        else
        {
            system("cls");
            printChess(ar);
            printList(loseList,n);
            printf("Enter Move or \"quit\" to Exit or \'s\' to save : ");
            mv= GetString();
        }

    }
    getch();
    return 0;
}
