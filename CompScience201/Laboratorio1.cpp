//Ashley Ogamba
//Laboratorio 1
//

#include<iostream>
#include<cstdlib>
#include <ctime>
#include<cmath>

using namespace std;
double calculateDistance(int x1, int y1, int x2, int y2);
double originDistance(int x, int y);//I think I could just call the function many times
void printPointandDistance(int x1, int y1, int x2, int y2);//prints out the points and distances from origin and each other and then also prints out which is closest to origin

int main()
{

	int x1, x2, y1, y2;

	cout << " Please select 1 if you would like to choose 4 numbers and please select 2 if you would like the computer to randomly generate the numbers.";
	
	int response;
	cin >> response;

	if (response == 1)
	{
		cout << "Enter two coordinate points in this manner (x1 y1 x2 y2).";
		cin >> x1;
		if (x1 < -10 || x1>10)
		{
			cout << "Please enter a number greater than -10 and less than 10.";
		}
		
		cin >> y1;
		if (y1 < -10 || y1>10)
		{
			cout << "Please enter a number greater than -10 and less than 10.";
		}


		cin >> x2;
		if (x2 < -10 || x2>10)
		{
			cout << "Please enter a number greater than -10 and less than 10.";
		}

		cin >> y2;
		if (y2 < -10 || y2>10)
		{
			cout << "Please enter a number greater than -10 and less than 10.";
		}


		printPointandDistance(x1, y1, x2, y2);

	}
	else if (response == 2)

	{
		srand(time(0));
		x1= rand() % 21+(- 10 );
		y1=rand() % 21 + (-10);
		x2= rand() % 21 + (-10);
		y2= rand() % 21 + (-10);

		cout << "Random coordinates generated: (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")\n";


		printPointandDistance(x1, y1, x2, y2);

			
	}

	
		

	return 0;
}
//Calculates distance to origin
double originDistance(int x, int y)
{
	//now we are doing what we are supposed to do
	1
	double distance = sqrt(pow(x, 2) + pow(y, 2));

	return distance;

}



//This calculates distance between two points
double calculateDistance(int x1, int y1, int x2, int y2)
{

	//okay so here we already have values passed in through the function
	//we know that we are returning distance
	//we will first calculate the distance between the first two integers from the origin

	double distanceY = pow((y2 - y1), 2);

	double distanceX = pow((x2 - x1), 2);
	
	double overallDistance = sqrt(distanceY + distanceX);

	return overallDistance;

}

void printPointandDistance(int x1, int y1, int x2, int y2)
{
	double originDistanceVar1 = originDistance( x1, y1);
	double originDistanceVar2 = originDistance(x2, y2);

	cout << "The distance from the origin from (" << x1 << ", " << y1
		<< "is " << originDistanceVar1 << ".\n";

	cout << "The distance from the origin from (" << x2 << ", " << y2
		<< "is " << originDistanceVar2 << ".\n";

	if (originDistanceVar1 < originDistanceVar2)
	{
		cout << " The closets distance to the origin is " << originDistanceVar1<< ".";

	}
	else if (originDistanceVar2 < originDistanceVar1)
	{
		cout<< " The closets distance to the origin is " << originDistanceVar2 << ".";
	}
	else {
		cout << "Both distances of " << originDistanceVar1 << " are equivalent.";
	}

	

}






