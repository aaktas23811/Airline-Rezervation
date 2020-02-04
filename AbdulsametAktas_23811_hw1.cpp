// Abdulsamet AKTAS cs307 hw1. Enjoy :)
#include <iostream>
#include <cstdlib>
#include <pthread.h>

using namespace std;
// Global varibles that every thread can reach
const int column = 50;
const int row = 2;
int Plane[row][column];
int Turn = 0;

void initialize()
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
			Plane[j][i] = 0;
	}
}
bool CheckIfEmpty()
{
	bool Flag = false;
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
			if (Plane[j][i]== 0)
			{  
				Flag = true;
				return Flag;
			}
	}
	return Flag;
}
int SeatCalculator(int row1, int col){
	int num= 0;
	if (row1 == 0)
		num = col*2 + 1;
	else
		num = col*2 +2;
	return num;
}

void* ReverveSeat (void* id1){
	int* id = (int*) id1;
	while (CheckIfEmpty())
	{
		if (*id == 1)
		{
			while (Turn != 0);
			// Critical reigon
			int x = rand()%2; int y = rand()%50;
			bool loop = true;
			do
			{
				if (Plane[x][y] == 0 )
				{
					cout << "TravelAgency" << *id << " is entering the critical region" << endl;
					cout << "Seat Number " << SeatCalculator(x, y) << " is reserved by TravelAgency1 " << endl;
					cout << "TravelAgency" << *id << " is exiting the critical region" << endl << endl;
					Plane[x][y] = 1;
					loop = false;
				}
				else
				{
					x = rand()%2;
					y = rand()%50;

				}
			} while (CheckIfEmpty()  && loop  );
			
			Turn = 1;
		}

	   if (*id == 2)
		{
			while (Turn != 1);
			// Critical reigon
			int x = rand()%2; int y = rand()%50;
			bool loop = true;
			do
			{
				if (Plane[x][y] == 0 )
				{
					cout << "TravelAgency" << *id << " is entering the critical region" << endl;
					cout << "Seat Number " << SeatCalculator(x, y) << " is reserved by TravelAgency2 " << endl;
					cout << "TravelAgency" << *id << " is exiting the critical region" << endl << endl;
					Plane[x][y] = 2;
					loop = false;

				}
				else
				{
					x = rand()%2;
					y = rand()%50;

				}
			} while (CheckIfEmpty() && loop );
			
			Turn = 2;
			
		}

		if (*id == 3)
		{
			while (Turn != 2);
			// Critical reigon
			int x = rand()%2; int y = rand()%50;
			bool loop = true;
			do
			{
				if (Plane[x][y] == 0 )
				{
					cout << "TravelAgency" << *id << " is entering the critical region" << endl;
					cout << "Seat Number " << SeatCalculator(x, y) << " is reserved by TravelAgency3 " << endl;
					cout << "TravelAgency" << *id << " is exiting the critical region" << endl << endl;
					Plane[x][y] = 3;
					loop = false;
				}
				else
				{
					x = rand()%2;
					y = rand()%50;

				}
			} while (CheckIfEmpty() &&  loop );
			Turn = 0;
		}

	}
}
int main()
{
	int id1 = 1; int id2 = 2; int id3 = 3;
	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	pthread_create(&thread1,NULL, ReverveSeat,(void*) &id1);
	pthread_create(&thread2,NULL, ReverveSeat,(void*) &id2);
	pthread_create(&thread3,NULL, ReverveSeat,(void*) &id3);

	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread3,NULL);
	
	cout << "The fligth is full. All the seats are taken by: \n" ;
	if (CheckIfEmpty()== false)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
				cout << Plane[i][j] << " " ;
			cout << endl;
		}
	}
	
	return 0;
}
