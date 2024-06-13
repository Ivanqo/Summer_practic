// just_test.cpp : main project file.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <windows.h>

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79




struct z {
	char name[40];
	long price_komp;
	char size1[40];
	long prib_kvart;
	char size2[40];
	long price_akcii;
	char country[40];
	char data[11];
	char prognoz[40];
	};

struct sp {
	char name[40];
	long summa;
	struct sp* sled;
	struct sp* pred;
		};



int menu(int);
void maxim(struct z*, int);
void first(struct z*, int);
void text_data(char *,char *);
void kolvo(struct z *, int);
void alfalist(struct z*, int, struct sp**);
void vstavka(struct z*, char*, int, struct sp**);
void listing(struct z*, int);
void diagram(struct z*, int, struct sp**);
void countrys(struct z*, int);
void hard_question(struct z*, int);
void find_action(struct sp*);
void delete_element(struct sp*);


int main(array<System::String ^> ^args)
{
int i,n;
	char dan[][60]={
"Напиши самую дорогую акцию из сводки                   ",
"Покажи самое старое снятие показаний                   ",
"Все акции выбранной страны, стоимостью выше введённой  ",
"Покажи все акции в алфавитном и обратном порядке       ",
"Напиши количество акций введённой страны               ",
"Диаграмма. Процентное соотношение стоимостей акций     ",
"Покажи акции одинаковой стоимостью из разных стран     ",
"Выход                                                  "
};
char BlankLine[] = "                                                         ";
	int NC;
	FILE *in;
	struct z *Kompany;
		setlocale(LC_CTYPE,"Russian");
		Console::CursorVisible::set(false);
		Console::BufferHeight=Console::WindowHeight+300;
		Console::BufferWidth=Console::WindowWidth+300;
		if((in=fopen("MoskovBirzha.DAT","r"))==NULL)
			{
			printf("\nФайл MoskovBirzha.dat не открыт!");
			getch(); exit(1);
			}

		fscanf(in,"%d",&NC);
		Kompany=(struct z*)malloc(NC*sizeof(struct z));
		for(i=0;i<NC;i++)
			fscanf(in,"%s%ld%s%ld%s%ld%s%s%s",Kompany[i].name,
			&Kompany[i].price_komp, Kompany[i].size1,
			&Kompany[i].prib_kvart,Kompany[i].size2,
			&Kompany[i].price_akcii,Kompany[i].country, 
			Kompany[i].data, Kompany[i].prognoz);

		printf("%ld",NC);
		for(i=0;i<NC;i++)
			printf("\n%-17s %-5ld %-13s %-5ld %-15s %-5ld %-14s %-11s %-6s",
			Kompany[i].name,
			Kompany[i].price_komp, Kompany[i].size1,
			Kompany[i].prib_kvart,Kompany[i].size2,
			Kompany[i].price_akcii,Kompany[i].country, 
			Kompany[i].data, Kompany[i].prognoz);

getch();

struct sp* spisok = 0;

	while(1)
{
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Black;
Console::CursorLeft=10;
Console::CursorTop=4;
printf(BlankLine);
for(i=0;i<7;i++)
{
Console::CursorLeft=10;
Console::CursorTop=i+5;
printf(" %s ",dan[i]);
}
Console::CursorLeft=10;
Console::CursorTop=12;
printf(BlankLine);
n=menu(8);
switch(n) {
case 1: maxim(Kompany, NC); break;
case 2: first(Kompany, NC); break;
case 3: listing(Kompany, NC); break;
case 4: alfalist(Kompany, NC, &spisok); break;
case 5: kolvo(Kompany, NC);break;
case 6: diagram(Kompany, NC, &spisok);break;
case 7: hard_question(Kompany, NC);break;
case 8: exit(0);
}
} // конец while(1)...
    return 0;
}

int menu(int n)
{
char dan[8][60]={
"Напиши самую дорогую акцию из сводки                   ",
"Покажи самое старое снятие показаний                  ы ",
"Все акции выбранной страны, стоимостью выше введённой  ",
"Покажи все акции в алфавитном и обратном порядке       ",
"Напиши количество акций введённой страны               ",
"Диаграмма. Процентное соотношение стоимостей акций     ",
"Покажи акции одинаковой стоимостью из разных стран     ",
"Выход                                                  "
};

int y1=0,y2=n-1;
char c=1;
while (c!=ESC)
	{
	switch(c) {
		case DOWN: y2=y1; y1++; break;
		case UP: y2=y1; y1--; break;
		case ENTER: return y1+1;
		case HOME:y2=y1;y1=0;break;
		case END:y2=y1;y1=6;break;
}
	if(y1>n-1){y2=n-1;y1=0;}
	if(y1<0) {y2=0;y1=n-1;}
		Console::ForegroundColor=ConsoleColor::White;
		Console::BackgroundColor=ConsoleColor::Green;
		Console::CursorLeft=11;
		Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
		Console::ForegroundColor=ConsoleColor::Green;
		Console::BackgroundColor=ConsoleColor::Black;
		Console::CursorLeft=11;
		Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
} // конец while(c!=ESC)...
exit(0);
}

void maxim(struct z* Kompan, int NC)
{
	int i=0; struct z best;
	strcpy(best.name,Kompan[0].name);
	best.price_akcii=Kompan[0].price_akcii;
	for(i=1;i<NC;i++)
	if (Kompan[i].price_akcii>best.price_akcii)
	{
	strcpy(best.name,Kompan[i].name);
	best.price_akcii=Kompan[i].price_akcii;
	best.price_komp = Kompan[i].price_komp;
	strcpy(best.size1,Kompan[i].size1);
	}
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Green;
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Самая дорогая акция стоит %ld доллара",best.price_akcii);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Это акция компании %s, оценённой в %ld %s",best.name, best.price_komp, best.size1);
	getch();
}


void text_data(char *s,char *sd)
{
char s0[3],month[12][9]={
"января","февраля","марта","апреля","мая","июня",
"июля","августа","сентября","октября","ноября","декабря"};
strcpy(s,sd+8);
strcat(s," ");
strncpy(s0,sd+5,2); s0[2]=0;
strcat(s,month[ atoi(s0)-1]);
strcat(s," ");
strncat(s,sd,4);
return;
}

void first(struct z* Kompan, int NC)
{
	int i;
	char s[30];
	struct z* best=Kompan;
	for(i=1;i<NC;i++)
		if (strcmp(Kompan[i].data,best->data)<0)
		best=&Kompan[i];
		text_data(s,best->data);
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Green;
		Console::CursorLeft=10;
		Console::CursorTop=15;
		SetConsoleCP(866);
		printf("Самое \"старое\" показание с компании %s. Цена была %ld$ за акцию",
		best->name,best->price_akcii);
		Console::CursorLeft=10;
		Console::CursorTop=16;
		printf("Страна компании %s цена компании %ld %s",best->country,best->price_komp,best->size1);
	getch();
}

void kolvo(struct z *Kompan, int NC)
{
int i,k=0;
char CONTRY[30];
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf("Введите название страны: ");
SetConsoleCP(1251);
gets(CONTRY);
SetConsoleCP(866);
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
for(i=0;i<NC;i++)
if (strcmp(Kompan[i].country,CONTRY)==0)
k++;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Green;
Console::CursorLeft=10;
Console::CursorTop=15;
printf("Акции %s",CONTRY);
Console::CursorLeft=10;
Console::CursorTop=17;
printf("Всего: %d",k);
Console::CursorLeft=10;
Console::CursorTop=19;
printf("Список:");
for(i=0;i<NC;i++)
	if (strcmp(Kompan[i].country,CONTRY)==0)
	{
	Console::CursorTop+=1;
	Console::CursorLeft=10;
	printf("%s",Kompan[i].name);
	}
getch();
}

/**
void find_action(struct sp* nt)
{
char findName[40];
printf("\n\t Введите название компании, акции которой нужно найти \n\t");
SetConsoleCP(1251);
gets(findName);
SetConsoleCP(866);
for(nt=spisok; nt!=0 && strcmp(nt->name,findName); nt=nt->sled);
if (nt!=0)
{
	printf("\n\t Да, такая компания есть: %s", nt->name);
}
else
{
	printf("\n\t Нет такой");
}
}

void delete_element(struct sp* nt)
{
char kompName[40];
char flag[40];
printf("\n\t Введите название компании, акции которой нужно удалить из списка \n\t");
SetConsoleCP(1251);
gets(kompName);
SetConsoleCP(866);

Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Gray;
Console::Clear();

printf("\n\t Обновлённый список \n\t");

for(nt=spisok; nt!=0; nt=nt->sled)
{
strcpy(flag,nt->name);
if (strcmp(flag,kompName) == 0) break;
printf("\n\t%-30s %ld",nt->name,nt->summa);
}

struct sp *z=0;
for(nt=spisok; nt!=0 && strcmp(nt->name,kompName); nt=nt->sled);
if(nt)
{
	if(z) {z->sled = nt->sled;}
	else {spisok = nt->sled;}
	free(nt);
}
else
{
	printf("Элемент не обнаружен!");
	getch();
	exit(0);
}


for(nt=spisok; nt!=0; nt=nt->sled)
printf("\n\t%-30s %ld",nt->name,nt->summa);

}

**/
void alfalist(struct z* Kompan, int NC, struct sp** spisok)
{
int i,n;
struct sp *nt, *mt;
n = NC;
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Gray;
Console::Clear();
if(!*spisok)
for(i=0;i<NC;i++)
vstavka(Kompan,Kompan[i].name, NC, spisok);
printf("\n\t Алфавитный список акций последней сводки");
/**printf("\n ===============================\n");**/
printf("\t\tОбратный алфавитный список акций последней сводки");
/**printf("\t \t \t \t ===============================\n");**/
for(nt=*spisok; nt!=0; nt=nt->sled)
printf("\n\t%-30s %ld",nt->name,nt->summa);
for (nt=*spisok, mt=0; nt!=0; mt=nt, nt = nt->sled);

Console::CursorTop=2;
for (nt=mt,i=0;nt!=0; i++, nt=nt->pred)
{
	Console::CursorLeft=70;
	printf("%-20s %ld",nt->name,nt->summa);
	Console::CursorTop+=1;
}

getch();
/**
find_action(nt);

getch();

delete_element(nt);

getch();**/


}
void vstavka(struct z* Kompan,char* name, int NC, struct sp** spisok)
{
	int i;
	struct sp *nov,*nt,*z=0;
	for(nt=*spisok; nt!=0 && strcmp(nt->name,name)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->name,name)==0) return;
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->name,name);
	nov->pred=z;
	nov->sled=nt;
	nov->summa=0;
	for(i=0;i<NC;i++)
	if(strcmp(Kompan[i].name,name)==0)
	nov->summa+=Kompan[i].price_akcii;
	if (!z) *spisok=nov;
	if (nt) nt->pred=nov;
	if (z) z->sled=nov;
	return;
}

void diagram(struct z *Kompan, int NC, struct sp** spisok)
{
	struct sp *nt;

	int len,i,NColor;
	long sum = 0 ;
	char str1[40];
	char str2[40];

	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();

	for(i=0;i<NC;i++) sum = sum+Kompan[i].price_akcii;
	if(!*spisok)
	for(i=0;i<NC;i++)
	vstavka(Kompan,Kompan[i].name, NC, spisok);
	Color=ConsoleColor::Black; NColor=0;
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		sprintf(str1,"%s",nt->name);
		sprintf(str2,"%3.2f%%",(nt->summa*100./sum));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::White;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=20;
		printf("%s",str2);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for(len=0; len<nt->summa*100/sum; len++) printf(" ");
		if(NColor==14)
		{ Color=ConsoleColor::Black; NColor=0; }
	}
	getch();
	return ;
}

void listing(struct z* Kompan, int NC)
{
int i;
struct z* nt;
char CONTRY[30];
int porog;
Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Black;
Console::Clear();
printf("Введите название страны: ");
SetConsoleCP(1251);
gets(CONTRY);
SetConsoleCP(866);
printf("Введите больше какой суммы: ");
scanf("%ld",&porog);

Console::ForegroundColor=ConsoleColor::Green;
Console::BackgroundColor=ConsoleColor::Gray;
Console::Clear();
printf("\n\r Список акций %s, стоимость которых выше %ld$",&CONTRY,porog);
printf("\n\r ===================================================== \n\r");
for(i=0,nt=Kompan;i<NC;nt++,i++)
if (nt->price_akcii>porog && strcmp(nt->country,CONTRY)==0)
printf("\n\r %-20s %ld $",nt->name,nt->price_akcii);
getch();
}

void hard_question(struct z* Kompan, int NC)
{
	int i,j;
	int flag = 0;
	Console::ForegroundColor=ConsoleColor::Green;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();

	for(i=0;i<NC;i++)
	{
		for (j = i+1; j < NC; j++)
		{
			if (Kompan[i].price_akcii == Kompan[j].price_akcii)
			{
			printf("\nСтоимость акций компании %s страны %s равна стоимости акций компании %s страны %s",Kompan[i].name,Kompan[i].country,Kompan[j].name, Kompan[j].country);
			printf("\nЦена %ld \n", Kompan[i].price_akcii);
			flag = 1;
			break;
			}
		}
		if (flag == 1) {break;}
	}
	if (flag == 0)
	{printf("Совпадений нет");}
	getch();
}
