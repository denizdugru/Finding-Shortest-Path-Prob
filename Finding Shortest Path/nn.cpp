#include <iostream>
#include <fstream>
#include <list>
#include <math.h> 
#include <ctime>

using namespace std;


typedef struct cities{
	int index;
	double x;
	double y;
	bool isVisited = false;
}city;

list<city> cities;
int lengthOfCities;

std::list<city> tour;
double tourLength =0;


void createCities(string filename){
	
	bool coordSectionPassed = false;
	string line;

	city temp;
	ifstream file(filename);

	if (file.is_open()){
		while (getline(file, line)){
			
			if(line == "NODE_COORD_SECTION"){
				coordSectionPassed = true;
			}
			else if(line == "EOF" || line == " ")
				continue;
			else if(coordSectionPassed){
				sscanf(line.c_str(), "%d %lf %lf", &temp.index, &temp.x, &temp.y);
				lengthOfCities = temp.index;
				cities.push_back(temp);
				
			}
		}
		file.close();
	}
}

double getDistance(city location, city target){
	double distance;
	distance = pow(sqrt(abs(location.x-target.x))+sqrt(abs(location.y-target.y)),2);
	return distance;
}

double FindNearestNeighbor(int index, int counter){
	double minDistance = 99999999999;
	double tmpDistance;
	int minDistanceIndex;
	
	std::list<city>::iterator it1 = cities.begin();
	std::advance(it1, index);
	std::list<city>::iterator it2 = cities.begin();
	
	(*it1).isVisited = true;
	int unvisitedCount = 0;
	for(int i=0;i<lengthOfCities;i++){
		if(!(*it2).isVisited){
			unvisitedCount++;
			tmpDistance = getDistance(*it1,*it2);
			if(tmpDistance<minDistance){
				minDistance = tmpDistance;
				minDistanceIndex = i;
			}
		}
		std::advance(it2, 1);
	}
	std::list<city>::iterator it3 = cities.begin();
	std::advance(it3, minDistanceIndex);
	tourLength += minDistance;
	(*it3).isVisited = true;
	unvisitedCount--;
	tour.push_back(*it3);
	counter++;
	if(unvisitedCount >0){
		FindNearestNeighbor(minDistanceIndex, counter);
	}
	return tourLength;
}

int main(){
	int counter = 1;
	createCities("ca4663.tsp");
	double tourLength;
	
	ofstream tmpFile;
	

	tour.push_back(*(cities.begin()));
	const clock_t start = clock();
	tourLength =  FindNearestNeighbor(0, counter);
	const clock_t end = clock();
	const double duration = double(end - start) / CLOCKS_PER_SEC;
	printf("Time: %f\n", duration);
	printf("%lf", tourLength);

	tmpFile.open ("output");
	std::list<city>::iterator tourIt = tour.begin();
	for(int i=0;i<lengthOfCities;i++){
		tmpFile << (*tourIt).x << "\t"<< (*tourIt).y<< "\n";
		std::advance(tourIt,1);
	}
	tmpFile << "EOF\n";
	tmpFile.close();
	

	return 0;
}