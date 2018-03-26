#ifndef MUHAMMEDS_H_INCLUDED
#define MUHAMMEDS_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//making linked list to save the moves
typedef struct reundo
{
    // to store the move
    char* moves;
    //to point to previous move ;
    struct reundo* pre ;
    //to point to next move
    struct reundo* next ;
    //in case of un or re do
    char place ;

}   reundo ;

typedef struct piece
{
    int c ;
    int d ;
}
piece;

piece black ;
piece white ;

void fillEmpty(char ar[][10]);   //To print the borders of the chess board

void putPieces(char ar[][10]);   //To put every piece in its place

void printChess(char ar[][10]);  //To make borders for showing tiles

void printList(char ar[], int n);   //To show the token out pieces

int checkPiece(char* piece );     //To check the type of piece

int checkMove(int x,int i , int j , int k ,int l,char ar[][10]);

int checkPawn(int i , int j , int k ,int l,char ar[][10]);   //To validate the pawn's move

int checkRook(int i,int j , int k , int l,char ar[][10]);    //To validate the rook's move

int checkBishop(int i,int j,int k,int l,char ar[][10]);      //To validate the bishop's move

int checkKnight(int i,int j, int k, int l,char ar[][10]);    //To validate the knight's move

int checkQueen(int i , int j , int k , int l,char ar[][10]);  //To validate the queen's move

int checkKing(int i , int j , int k , int l,char ar[][10] );  //To validate the king's move

int checkTrapRook(int i , int j , int k , int l,char ar[][10]);  //To assure that the destination of the rook is valid

int checkTrapBishop(int i , int j , int k,int l , char ar[][10]); //To assure that the destination of the bishop is valid

int checkTrapQueen(int i,int j , int k , int l,char ar[][10]);    //To assure that the destination of the queen is valid

char unRedo (char ch,char ar[][10]); //To control the process of undo & redo

void save (char ar[],char c);  //To provide the feature of Save

int checkPlayer(int x , char* piece); //To check if it's the player turn or not

void saveFile(int x );

char movePiece (char* mv ,char ar[][10]);     //To control the process of moving &taking pieces out (if happened)

void undoMove(char* mv,char place,char ar[][10]);

piece load (char ar[][10],char loselist[]);  //To load the saved game

int checkPromotion(char mv[],char ar[][10]);  //To control the process of promotion

int preventThreatRook(int i, int j ,int k , int l ,char ar[][10]);  //To check if the rook could stop the 'Check' or not

int preventThreatBishop(int i , int j , int k , int l, char ar[][10]); //To check if the bishop could stop the 'Check' or not

int preventThreatKnightAndPawn(int i, int j, int k, int l, char ar[][10]);  //To check if the knight or the pawn could stop the 'Check' or not

int preventThreat(char ar[][10],piece check);

int stalmateValidation1(int x , int y,char ar[][10]); //To check if the king will be in danger or not in case a piece of its team wants to move

int openTrack(int x , int y,char ar[][10]);  //To check if the piece's move will put its king in check or not

int numOfPieces(char ar[][10],char c);  //To count the number of pieces

int stalmateValidation2(int x , int y , char ar[][10]);   //To check if the piece of the checked king's team could move or not

piece DetectTheFuckingPiece(int k, int l , char ar[][10]);  //To identify the piece which checks the king

#endif // MUHAMMEDS_H_INCLUDED
