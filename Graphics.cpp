#include<iostream>
#include<cstring>               
#include<conio.h>               
#include<stdlib.h>             
#include<windows.h>
#include"Graphics.h"
using namespace std;

void Intro()
{
	string str1 = " Movie Recommendation System ";
	string str2 = " CS218 Data Structures Project ";
	string str3 = " Developed By";
	string name1 = " Sara Sameer";
	string name2 = " Arzaan ul Mairaj";
	string name3 = " Bassam Tariq";
	system("color 0F");
	gotoxy(33, 3);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j <= 15; j++);
		cout << "\xC4";
	}

	gotoxy(38, 3);
	for (int i = 0; i < str1.length(); i++)
	{
		cout << str1[i];
		Sleep(90);
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j <= 15; j++);
		cout << "\xC4";
	}
	/*gotoxy(30,4);
	for(int i=0;i<50;i++)
	{	for(int j=0;j<=300000;j++);
		cout << "\xC4";
	}*/
	cout << endl;
	gotoxy(37, 4);
	for (int i = 0; i < str2.length(); i++)
	{
		cout << str2[i];
		Sleep(90);
	}
	cout << endl << endl << endl;


	gotoxy(37, 7);
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j <= 300; j++);
		cout << "\xB2";
		Sleep(90);
	}

	cout << endl;

	gotoxy(44, 10);
	for (int i = 0; i < str3.length(); i++)
	{
		cout << str3[i];
		Sleep(90);
	}

	gotoxy(43, 12);
	cout << "\xAF";
	for (int i = 0; i < name1.length(); i++)
	{
		cout << name1[i];
		Sleep(90);
	}
	gotoxy(43, 13);
	cout << "\xAF";
	for (int i = 0; i < name2.length(); i++)
	{
		cout << name2[i];
		Sleep(90);
	}
	gotoxy(43, 14);
	cout << "\xAF";
	for (int i = 0; i < name3.length(); i++)
	{
		cout << name3[i];
		Sleep(90);
	}
	gotoxy(40, 16);
	system("pause");
}


void gotoxy(int x, int y)
{
    COORD coordinates;     
    coordinates.X = x;     
    coordinates.Y = y;    
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void CleaningPhase()
{
	gotoxy(45, 3);
	string train = "Data Cleaning Phase";
	for (int i = 0; i < train.length(); i++)
	{
		cout << train[i];
		Sleep(90);
	}
	gotoxy(42, 4);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j <= 40; j++);
		cout << "\xB2";
		Sleep(90);
	}
	gotoxy(0, 6);
}

void MenuGraphics()
{
	gotoxy(43, 3);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j <= 40; j++);
		cout << "\xB2";
		Sleep(90);
	}
	gotoxy(43, 5);
	cout << "Choose an option:";
	gotoxy(43, 7);
	cout << "1. Train model";
	gotoxy(43, 8);
	cout << "2. Get recommendations";
	gotoxy(43, 9);
	cout << "3. Exit";
	gotoxy(43, 11);
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j <= 40; j++);
		cout << "\xB2";
		Sleep(90);
	}
	gotoxy(43, 13);
	cout << "Your Choice ";
}