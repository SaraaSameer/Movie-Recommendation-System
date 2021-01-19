#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<vector>
#include<Windows.h>
#include <algorithm>
#include<conio.h>
#include "training and word vectors.h"
#include "Graphics.h"

using namespace std;

template <typename T>
struct one_dimensional_LL_node {
	T n;
	one_dimensional_LL_node* next;
};

template<class T>
class one_dimensional_LL {
public:

	one_dimensional_LL_node<T>* head;
	one_dimensional_LL_node<T>* tail;
	one_dimensional_LL() {



		head = NULL;
		tail = NULL;
	}


	void swapdata(int index1, int index2) {
		if (index1 >= size() || index2 >= size()) {
			cout << "Out of bounds" << endl;
			return;

		}
		T n1 = getnode(index1)->n;
		T n2 = getnode(index2)->n;
		setnode(index1, n2);
		setnode(index2, n1);



	}

	void addtoTail(T n) {

		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp->n = n;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			tail = temp;
		}

	}



	void deletetail() {
		if (size() <= 0) {
			cout << "Empty" << endl;
			return;
		}
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp = head;
		while (temp->next->next != NULL) {
			temp = temp->next;
		}
		temp->next = NULL;
	}

	void deletehead() {
		if (size() <= 0) {
			cout << "Empty" << endl;
			return;
		}
		if (head == tail) {
			head = NULL;
			tail = NULL;
		}
		else {
			head = head->next;
		}

	}



	void addtoHead(T n) {
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp->n = n;
		temp->next = NULL;
		if (head == NULL) {
			head = temp;
			tail = temp;
		}
		else {
			temp->next = head;
			head = temp;
		}
	}

	void print() {
		if (size() > 0) {

			one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
			temp = head;
			while (temp != NULL) {
				cout << temp->n << " ";
				temp = temp->next;
			}
			cout << endl;

		}

		else {
			cout << "Empty" << endl;
		}

	}

	void deletenodebydata(T n) {
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		if (!(exists(n))) {
			cout << "Data does not exist" << endl;
			return;
		}
		temp = head;
		if (head->n == n) {
			deletehead();
		}
		else {
			while (temp->next->n != n) {
				temp = temp->next;
			}
			if (temp->next == tail) {
				deletetail();
			}
			else {
				temp->next = temp->next->next;
			}

		}

	}

	bool exists(T n) {

		if (head == NULL && tail == NULL) {
			return false;
		}
		else {
			bool found = false;
			one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
			temp = head;
			for (int i = 0; i < size(); i++) {
				if (getnode(i)->n == n) {
					found = true;
					break;
				}
			}
			return found;

		}





	}

	int search(T n) {
		if (!(exists(n))) {
			cout << "Does not exist" << endl;
			return -1;
		}
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp = head;
		int count = 0;
		while (temp->n != n) {
			count++;
			temp = temp->next;
		}
		return count;
	}


	int size() {
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp = head;
		int count = 0;
		while (temp != NULL) {
			count++;
			temp = temp->next;
		}
		return count;
	}

	void add(T n, int index) {
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp = head;

		if (index == 0) {
			addtoHead(n);
		}
		else {
			for (int i = 0; i < index - 1; i++) {
				temp = temp->next;
			}
			one_dimensional_LL_node<T>* newnode = new one_dimensional_LL_node<T>;
			newnode->n = n;
			newnode->next = temp->next;
			temp->next = newnode;
		}






	}

	one_dimensional_LL_node<T>* getnode(int index) {

		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		if (index >= size()) {
			cout << "Out of bounds" << endl;
			return temp;
		}
		temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		return temp;
	}

	void setnode(int index, T n) {
		if (index >= size()) {
			cout << "Out of bounds" << endl;
			return;
		}
		one_dimensional_LL_node<T>* temp = new one_dimensional_LL_node<T>;
		temp = head;
		for (int i = 0; i < index; i++) {
			temp = temp->next;
		}
		temp->n = n;
	}



	void clear() {
		head = NULL;
		tail = NULL;
	}

	void sort() {
		T temp;
		for (int i = 0; i < size() - 1; i++) {
			for (int j = 0; j < size() - 1 - i; j++) {
				if (getnode(j)->n > getnode(j + 1)->n) {
					temp = getnode(j)->n;
					setnode(j, getnode(j + 1)->n);
					setnode(j + 1, temp);
				}
			}

		}
	}
};

struct movie_title_and_similarity {
	string title;
	int ID;
	double similarity;
};


class Movie {

private:
	int id;
	string title;
	string year;
	one_dimensional_LL<string> genre;
public:

	Movie() {
		id = 0;
		title = "";
		year = "";

	}

	void settitle(string title) {
		this->title = title;
	}

	string gettitle() {
		return title;
	}

	void setYear(string year)
	{
		this->year = year;
	}

	string getYear()
	{
		return year;
	}

	int getid() {
		return id;
	}

	void setid(int id) {
		this->id = id;
	}

	void addgenre(string genre) {
		this->genre.addtoTail(genre);
		this->genre.sort();
	}

	void deletegenre(string genre) {
		this->genre.deletenodebydata(genre);
	}

	bool does_this_genre_exist(string genre) {
		return this->genre.exists(genre);
	}



	void print_genres() {
		genre.print();
	}



	bool matchid(int id) {

		if (this->id == id) {
			return true;
		}
		return false;

	}

	void print_details() {
		cout << "ID: " << id << endl;
		cout << "Title: " << title << endl;
		cout << "Genre(s): ";

		genre.print();

		cout << endl;
	}

	void File_Output()
	{
		ofstream fout("movielist.txt",ios::app);
		string temp = title;
		temp.erase(remove(temp.begin(), temp.end(), ' '), temp.end());

		//Case Senstivity
		for(int i=0;i<temp.length();i++)
		temp[i] = toupper(temp[i]);
		fout << temp;
		if (genre.size() > 0) {

			one_dimensional_LL_node<string>* temp = new one_dimensional_LL_node<string>;
			temp = genre.head;
			while (temp != NULL) {
				fout << temp->n;
				temp = temp->next;
			}

			fout << year;
			fout << endl;
		}
		fout.close();
	}


};


void cleanData(one_dimensional_LL<Movie>*obj)
{
	//Duplicates and Case senstivity 
	cout << "Removing Duplicate data. Please wait..." << endl;
	Movie temp;
	one_dimensional_LL_node<Movie>* Start = NULL;
	one_dimensional_LL_node<Movie>* Last = NULL;
	one_dimensional_LL_node<Movie>* Out = NULL;
	one_dimensional_LL_node<Movie>* In = NULL;
	string compare1, compare2;
	int count = 1;
	for (Out = obj->head; Out != NULL; Out = Out->next)
	{
	
		compare1 = Out->n.gettitle();
		for (int i = 0; i < compare1.length(); i++)
		{
			compare1[i] = toupper(compare1[i]);
		}

		cout << (int)((float)count / 10197 * 100) << " %";

		
		for (In = obj->head; In != Out; In = In->next)
		{
			compare2 = In->n.gettitle();
			for (int i = 0; i < compare2.length(); i++)
			{
				compare2[i] = toupper(compare2[i]);
			}

			if (compare1==compare2)
			{
				break;
			}
		}

		if (In == Out)
		{
			if (Start == NULL)
			{
				Start = Last = In;
			}
			else
			{
				Last->next = In;
				Last = In;
			}
		}
	
		count++;
		cout << "\r";
	}
	obj->head = Start;
	Last->next = NULL;
	cout << endl;
	cout << "Duplicates removed" << endl<<endl;


}


void trainnewmodel() {
    trainmodel();
}

void loadwordvectorsintofile() {
    loadwordvectors();
}

double cosine_similarity(vector<float> A, vector<float> B, unsigned int Vector_Length)
{
	double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
	for (unsigned int i = 0u; i < Vector_Length; ++i) {
		dot += A[i] * B[i];
		denom_a += A[i] * A[i];
		denom_b += B[i] * B[i];
	}
	return dot / (sqrt(denom_a) * sqrt(denom_b));
}


void loadwordvectorsintoLL(one_dimensional_LL<one_dimensional_LL<float> >& obj,int _size)
{
	//obj = new one_dimensional_LL<one_dimensional_LL<float>>;
	ifstream fin("listofmoviewordvectors.txt");
	float Vect;
	for (int j = 0; j < _size; j++)
	{
		one_dimensional_LL<float> SingleLine;
		for (int i = 0; i < 100; i++)
		{
			fin >> Vect;
			SingleLine.addtoTail(Vect);
		}
		obj.addtoTail(SingleLine);
	}

	fin.close();
}

vector <float> LLintoVectorForm(one_dimensional_LL<float> VectorList)
{
	vector<float> VectForm;
	for (int i = 0; i < VectorList.size(); i++)
	{
		VectForm.push_back(VectorList.getnode(i)->n);
	}
	return VectForm;
}


void ShellSortOne(vector<movie_title_and_similarity>& obj, int size)
{
	for (int gap = size / 2; gap > 0; gap = gap / 2)
	{
		for (int i = gap; i < size; i++)
		{
			for (int j = i; j >= gap; j = j - gap)
			{
				if (obj[j - gap].similarity <obj[j].similarity)
				{
					swap(obj[j - gap], obj[j]);
				}
			}
		}
	}
}



void SortCosineSimilarities(vector<movie_title_and_similarity>& obj)
{
	ShellSortOne(obj, obj.size());
}


int Partition(one_dimensional_LL<Movie>*MovieObj, int s, int e)
{
	Movie tempObj;
	string pivot = MovieObj->getnode(e)->n.gettitle();
	int pindex = s;
	for (int i = s; i < e; i++)
	{
		if (MovieObj->getnode(i)->n.gettitle().compare(pivot)<0)
		{
			//swap(MovieObj->getnode(i), MovieObj->getnode(pindex));
			tempObj = MovieObj->getnode(i)->n;
			MovieObj->getnode(i)->n = MovieObj->getnode(pindex)->n;
			MovieObj->getnode(pindex)->n=tempObj;
			pindex++;
		}
	}
	//swap(MovieObj->getnode(pindex), MovieObj->getnode(e));
	tempObj = MovieObj->getnode(pindex)->n;
	MovieObj->getnode(pindex)->n = MovieObj->getnode(e)->n;
	MovieObj->getnode(e)->n = tempObj;
	return pindex;
}

void QuickSort(one_dimensional_LL<Movie>* MovieObj, int l, int h)
{
	if (l < h)
	{
		int p = Partition(MovieObj, l, h);
		QuickSort(MovieObj, l, p - 1);
		QuickSort(MovieObj, p + 1, h);
	}
}

void SortMoviesData(one_dimensional_LL<Movie>* MovieObj)
{

	int size1 = MovieObj->size();
	QuickSort(MovieObj, 0, size1 - 1);
	//Display Sorted Data
	//for (int i = 0; i < MovieObj->size(); i++)
		//cout << MovieObj->getnode(i)->n.gettitle()<<endl;
}

one_dimensional_LL_node<Movie>* getMiddle(one_dimensional_LL_node<Movie>* start, one_dimensional_LL_node<Movie>* last)
{
	one_dimensional_LL_node<Movie>* slow = start;
	one_dimensional_LL_node<Movie>* fast = start->next;
	while (fast != last)
	{
		fast = fast->next;
		if (fast != last)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	return slow;
}

int BinarySearch(one_dimensional_LL<Movie>MovieObj,string UpperCaseStr)
{
	static one_dimensional_LL_node<Movie>* start = MovieObj.head;
	static one_dimensional_LL_node<Movie>* last = NULL;
	one_dimensional_LL_node<Movie>* mid;
	static int startingindex = 0;
	static int endingindex = MovieObj.size()-1;
	int midValue;
	string MovieObjUppercase;

	if (start == last)
	{
		cout << endl << endl << "Searched Movie is not in the List " << endl;
		return NULL;
	}
	else
	{
		mid = getMiddle(start, last);
		midValue = (startingindex + endingindex) / 2;
		MovieObjUppercase = mid->n.gettitle();
		for (int i = 0; i < MovieObjUppercase.length(); i++)
		{
			MovieObjUppercase[i] = toupper(MovieObjUppercase[i]);
		}
		if (MovieObjUppercase == UpperCaseStr)
		{
			return mid->n.getid();
			return midValue;

		}
		else if (MovieObjUppercase < UpperCaseStr)
		{
			start = mid->next;
			startingindex = midValue + 1;
			BinarySearch(MovieObj, UpperCaseStr);
		}
		else
		{
			last = mid;
			endingindex = midValue-1;
			BinarySearch(MovieObj,UpperCaseStr);
		}
	}
}


void findCosineSimilarityOfVectors(one_dimensional_LL<one_dimensional_LL<float>>VectorObj,one_dimensional_LL<Movie>MovieObj)
{
	int i;
	string MovieTitle,UpperCaseStr,MovieObjUppercase;
	//movie_title_and_similarity MovieSearched;
	vector<float>movieSearchedVectors;
	
	vector<movie_title_and_similarity> Similarities;
	movie_title_and_similarity temp;
	double CosineSimilarity;
	int indexValue;
	
	cout << endl;
	gotoxy(33, 7);
	cout << "Enter the Title of Movie you'd like to watch" << endl;
	cin.ignore();
	getline(cin, MovieTitle);
	MovieTitle = MovieTitle + " ";

	UpperCaseStr = MovieTitle;
	for (int i = 0; i < UpperCaseStr.length(); i++)
	{
		UpperCaseStr[i] = toupper(UpperCaseStr[i]);
	}

	for (i = 0; i < MovieObj.size(); i++)
	{
		MovieObjUppercase = MovieObj.getnode(i)->n.gettitle();
		for (int i = 0; i < MovieObjUppercase.length(); i++)
		{
			MovieObjUppercase[i] = toupper(MovieObjUppercase[i]);
		}

		if (UpperCaseStr==MovieObjUppercase)
		{
			for (int j = 0; j < 100; j++)
			{
				//cout << VectorObj.getnode(i)->n.getnode(j)->n << " ";
				movieSearchedVectors.push_back(VectorObj.getnode(i)->n.getnode(j)->n);
			}
			break;
		}
	}
	if (i == MovieObj.size())
	{
		cout << endl<<endl<<"Searched Movie is not in the List " << endl;
		return;
	}

	//indexValue = BinarySearch(MovieObj, UpperCaseStr);
	/*if (indexValue == NULL)
		return;       //Value Not Found
	else
	{
		for (int j = 0; j < 100; j++)
		{
			movieSearchedVectors.push_back(VectorObj.getnode(indexValue)->n.getnode(j)->n);
		}
	}*/

	for (int j = 0; j < MovieObj.size(); j++)
	{
		temp.title = MovieObj.getnode(j)->n.gettitle();
		temp.ID = MovieObj.getnode(j)->n.getid();
		CosineSimilarity = cosine_similarity(movieSearchedVectors, LLintoVectorForm(VectorObj.getnode(j)->n), 100);
		temp.similarity = CosineSimilarity;
		Similarities.push_back(temp);
		
	}

	SortCosineSimilarities(Similarities);
	//Sort Them in Descending Order (similarities)
	cout <<endl<< "If you like \"" << MovieTitle << "\", then you may also like to watch: " << endl;
	cout << endl;
	for (int k = 1; k < 8; k++)
	{
		cout << setfill(' ')<<setw(5);
		cout << "\xFE" << " ";
		cout << Similarities[k].title << "    ";
		cout << endl;
		//For Demonstration Purpose
		//cout << Similarities[k].ID << "  ";
		//cout << Similarities[k].similarity << endl;
	}
}

int main() {
    int choice;
	Intro();
	system("cls");
	CleaningPhase();
	cout << "Extracting relevant data from file. Please wait..." << endl;
	int id;
	string title, temp;
	ifstream f1("movies.dat");
	Movie m[10197];
	getline(f1, temp);
	for (int i = 0; i < 10197; i++) { //10197


		f1 >> id;
		f1 >> temp;

		while (!(temp >= "0" && temp <= "9999999999")) {

			title += temp + " ";
			f1 >> temp;
		}
		m[i].setid(id);
		m[i].settitle(title);
		
		title = "";
		f1 >> temp;
		while(!(temp >= "0" && temp <= "9999999999")||temp.size()!=4) {
			f1 >> temp;
		}
		//cout << temp<<endl;
		m[i].setYear(temp);
		getline(f1, temp);
	}
	f1.close();
	f1.open("movie_genres.dat");

	string genre;
	getline(f1, temp);

	for (int i = 0; i < 20809; i++) {
		f1 >> id >> genre;
		for (int j = 0; j < 10197; j++) {

			if (m[j].matchid(id)) {

				m[j].addgenre(genre);
				break;

			}

		}
	}

	f1.close();





	one_dimensional_LL<Movie> movies;
	for (int i = 0; i < 10197; i++) {

		movies.addtoTail(m[i]);
	}

	ofstream fout("movielist.txt");
	fout.close();
	cleanData(&movies);
	cout << "Cleaned data is being written to file. Please wait..." << endl;
	
	for (int i = 0; i < movies.size(); i++) {
		cout <<(int) ((float)(i+1) / movies.size() * 100) << " %";
		movies.getnode(i)->n.File_Output();
		cout << "\r";
	}
	cout << endl;
	cout << "Data written to movie list" << endl;
	Sleep(2000);
	system("CLS");





    while (1) {
		system("cls");
		MenuGraphics();
        cin >> choice;
        cout << endl;
        if (choice == 1) {
			system("cls");
			gotoxy(0, 3);
            trainnewmodel();
            cout << "Training completed" << endl;
			system("pause");
        }
        else if (choice == 2) {
			system("cls");
			cout << endl<<"Loading word vectors into file. Please wait..."<<endl;
            loadwordvectorsintofile();
            cout <<"Word vector representations of Movies loaded into moviewordvectors.txt" << endl;
			

			one_dimensional_LL<one_dimensional_LL<float>> wordvectorsformovies;  //2d linked list

			loadwordvectorsintoLL(wordvectorsformovies,movies.size());
			//cout << endl<<"We are Processing your data. Please wait for a moment..." << endl;
			//SortMoviesData(&movies);
			findCosineSimilarityOfVectors(wordvectorsformovies,movies);
			system("pause");
        }
		else {
			system("cls");
			gotoxy(49, 3);
			cout << endl << endl << "Thank You For Your Time!!!" << endl;
			exit(0);
		}
        cout << endl;
    }

   




    





}
