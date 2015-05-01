#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <math.h>
#include "QuickUnion.h"

using namespace std;

enum shape { RECT, HEX };

//Fisher yates shuffle 
// Used to randomize the array positions for percolaiton
void FisherYatesShuffle(int * , int );

bool Percelated( bool ** , QuickUnion , int);

int main()
{
	srand(time(0));
	shape SH = HEX;

	fstream out;
	out.open("percolation probability RECT.csv", ios::out | ios::app );

	fstream out2;
	out2.open("percolation probability HEX.csv", ios::out | ios::app );

	for( int s=0; s<2; s++)
	{
		if( SH == HEX )
			SH=RECT;
		else
			SH=HEX;

		for( int SIZE = 5; SIZE < 81; SIZE++)
		{
				for( int iter = 0; iter < 150; iter++)
				{

					bool ** Vacant;

					int nvacant = 0;

					//cout << SIZE << endl;

					Vacant = new bool*[SIZE];
					for( int i = 0; i < SIZE; i++)
						Vacant[i] = new bool[SIZE];

					for( int i = 0; i < SIZE; i++)
						for( int j = 0; j < SIZE; j++)
							Vacant[i][j]=false; // spot is not vacant

					int * Yates;
					Yates = new int[SIZE*SIZE];

					for( int i = 0; i < SIZE*SIZE; i++)
						Yates[i]=i;

					FisherYatesShuffle(Yates, SIZE*SIZE);

					//inline function used to convert from 1d notation to 2d notation
					QuickUnion Detector(SIZE*SIZE);

					int traverser = 0;
					while( !Percelated(Vacant, Detector, SIZE) )
					{
						//converts 1d notation to 2d notation
						int i = Yates[traverser] / SIZE; //row
						int j = Yates[traverser] % SIZE; // column

						//percolates the spot, and then checks for surrounding 
						// spots for percolations
						Vacant[i][j] = true;
						nvacant++;

						if (SH==RECT)
						{
							//up
							if( i-1 >= 0 )
							{
								if( Vacant[i-1][j] )
								{
									//converts 2d notation to 1d notation.
									int tempid = ((i-1)*SIZE)+j;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//down
							if( i+1 < SIZE )
							{
								if( Vacant[i+1][j] )
								{
									//converts 2d notation to 1d notation.
									int tempid = ((i+1)*SIZE)+j;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//left
							if( j-1 >= 0 )
							{
								if( Vacant[i][j-1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = (i*SIZE)+j-1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//right
							if( j+1 < SIZE )
							{
								if( Vacant[i][j+1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = (i*SIZE)+j+1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}
						}
						else
						{
							//up and left
							if( i-1 >= 0 && j-1 >=0)
							{
								if( Vacant[i-1][j-1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = ((i-1)*SIZE)+j-1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//up and right
							if( i-1 >= 0 && j+1 >=0)
							{
								if( Vacant[i-1][j+1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = ((i-1)*SIZE)+j+1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//down and left
							if( i+1 < SIZE && j-1 >=0)
							{
								if( Vacant[i+1][j-1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = ((i+1)*SIZE)+j-1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//Down and right
							if( i+1 < SIZE && j+1 < SIZE)
							{
								if( Vacant[i+1][j+1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = ((i+1)*SIZE)+j+1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//Left
							if( j-1 >= 0 )
							{
								if( Vacant[i][j-1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = (i*SIZE)+j-1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

							//right
							if( j+1 < SIZE )
							{
								if( Vacant[i][j+1] )
								{
									//converts 2d notation to 1d notation.
									int tempid = (i*SIZE)+j+1;

									//if the adjacent spots do not have the same id
									if( !Detector.find(Yates[traverser], tempid) )
										//sets the to the same id
										Detector.unite(Yates[traverser], tempid);
								}
							}

						}


						traverser++;

					}

					for( int i = 0; i < SIZE; i++)
					{
						for( int j = 0; j < SIZE; j++)
						{
							if( !Vacant[i][j] )
								cout << (char)219;
							else
								cout << " ";
						}
						cout << endl;
					}

					for( int i = 0; i < SIZE; i++)
					{
						for( int j = 0; j < SIZE; j++)
						{
							cout << setprecision(3) << Detector.getRoot((i*SIZE)+j) << " ";
						}
						cout << endl;
					}

					if( SH == RECT )
						out << SIZE << ", " << nvacant << ", " << (nvacant/((double) SIZE*SIZE)) << endl;
					else
						out2 << SIZE << ", " << nvacant << ", " << (nvacant/((double) SIZE*SIZE)) << endl;

					cout << "Portion of vacant cells to size " << SIZE << " is " << nvacant << endl;
					cout << "p = nvacant/(n*n) = " << (nvacant)/((double)SIZE*SIZE) << endl;
					system("Pause");

					//deletes the dynamically allocated array Grid
					for( int i = 0; i < SIZE; i++)
						delete [] Vacant[i];
					delete [] Vacant;

				}

			}

	}

	return 0;
}

void FisherYatesShuffle(int * GridArray, int Size)
{
	for( int i = Size-1; i >=1;i--)
	{
		int j = rand() % i;
		int temp = GridArray[j];
		GridArray[j] = GridArray[i];
		GridArray[i]=temp;
	}
}

bool Percelated( bool ** grid, QuickUnion ID, int size)
{
	//finds a vacant top one
	for( int i = 0; i < size; i++)
		if( grid[0][i] )
			//finds a vacant bottom one
			for( int j = 0; j < size; j++)
				if( grid[size-1][j])
					if( ID.find((i), ((size-1)*size)+j) )
						return true;

	return false;
}