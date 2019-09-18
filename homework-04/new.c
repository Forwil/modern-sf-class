#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAXNUM 100
#define MAXLEN 26
#define MAXMAT 100
#define MAXRANDOM 100000
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};
int board[MAXMAT][MAXMAT];
char words[MAXNUM][MAXLEN];
int N,M;
FILE *fin,*fout;
void work(int n);
int randpos(char *word, int *posx, int *posy, int *posd);
int howgood(char *word, int x, int y, int drct);
void placeword(char *word, int x, int y, int drct);
void swap(char a[],char b[]);
void fillallby(char c);
int charcmp(char a,char b);
int main(int argc,char *argv[])
{
	int n,i,j;
	fin=fopen("words.txt","r");
	fout=fopen("result.txt","w");
	fscanf(fin,"%d",&n);
	fprintf(fout,"%d\n",n);
	for(i=1;i<=n;i++)
	{
		fscanf(fin,"%s",words[i]);
		fprintf(fout,"%s\n",words[i]);
	}
	for(i=1;i<=n;i++)
		for(j=i+1;j<=n;j++)
		if(strlen(words[i])<strlen(words[j]))	
			swap(words[i],words[j]);
	N=atoi(argv[1]);
	M=atoi(argv[2]);
	work(n);
	fillallby('X');
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=M;j++)
			{
			printf("%c", board[i][j]);
			fprintf(fout,"%c",board[i][j]);
			}
		printf("\n");
		fprintf(fout,"\n");
	}
	return 0;
}
void fillallby(char c)
{
	int i,j;
	for(i=1;i<=N;i++)
		for(j=1;j<=M;j++)
		if(board[i][j]==' ') 
			board[i][j]=c;
}
void swap(char a[],char b[])
{
	int i; 
	char c;
	for(i = 0;i<MAXLEN;i++)
		{
		c=a[i];
		a[i]=b[i];
		b[i]=c;
		}
}
void work(int n)
{
	int i,j,posx,posy,posd,can;
	for(i=1;i<=N;i++)for(j=1;j<=M;j++)board[i][j]=' ';
	srand((int)time(0));
	for(i=1;i<=n;i++)
	{
		can=randpos(words[i],&posx,&posy,&posd);
		if(can==-1)
		{
			printf("cannot!\n");
		//	getchar();
		}
		placeword(words[i],posx,posy,posd);
	}
}
int randpos(char *word, int *posx, int *posy, int *posd)
{
	int max,i,x,y,d,temp;
	max=-1;
	for(i=1;i<=MAXRANDOM;i++)
	{
		x=rand()%N+1;
		y=rand()%M+1;
		d=rand()%8;
		temp=howgood(word,x,y,d);
		if(temp>max)
		{
			max=temp;
			*posx=x;
			*posy=y;
			*posd=d;
		}
	}
	return max;
}
int charcmp(char a,char b)
{
	if(a<='z'&&a>='a') a -='a';
	if(a<='Z'&&a>='A') a -='A';
	if(b<='z'&&b>='a') b -='a';
	if(b<='Z'&&b>='A') b -='A';	
	return (a==b);
}
int howgood(char *word, int x, int y, int drct)
{
	int xx,yy,score,i;
	xx=x;
	yy=y;
	score=0;
	for(i=0;i<strlen(word);i++)
	{
		if((xx<1 || xx>N || yy<1 || yy>M) || (board[xx][yy]!=' ' && board[xx][yy]!=word[i]))
			return -1;
		if(charcmp(board[xx][yy],word[i]))
			score++;
		xx+=dx[drct];
		yy+=dy[drct];
	}
	return score;	
}
void placeword(char *word, int x, int y, int drct)
{
	int xx,yy,i;
	xx=x;
	yy=y;
	for(i=0;i<strlen(word);i++)
	{
		board[xx][yy]=word[i];
		xx+=dx[drct];
		yy+=dy[drct];
	}
} 
