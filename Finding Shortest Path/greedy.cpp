#include <iostream>
#include <fstream>
#include <list>
#include <math.h> 

using namespace std;


typedef struct cities{
	int index;
	double x;
	double y;
	bool previousOne;
	bool isVisited;
	struct cities* next;
}city;

list<city> cities;
int lengthOfCities;

list<city> tour;
double tourLength =0.0;

city* oneCity;


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
				temp.isVisited = false;
				temp.previousOne = false;
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

double GreedyAlg(){
	
	double tempLength = 9999999999;
	double minLength =  99999999;
	int tempI,tempJ;
	double a=0;
	std::list<city>::iterator it1;
	std::list<city>::iterator it2;
	
	for(int i=0;i<lengthOfCities;i++){
		it1 = cities.begin();
		std::advance(it1, i);
		
		for(int j=0;j<lengthOfCities;j++){
			it2 = cities.begin();
			std::advance(it2,j);
			if((!(*it1).isVisited || !(*it2).previousOne) || (*it1).x!=(*it2).x){

				tempLength = getDistance(*it1, *it2);
			}
			if(tempLength<minLength){

				minLength = tempLength;
				tempI = i;
				tempJ = j;
			}
		}
	}
	printf("%lf\n", minLength);
	if(minLength == 99999999){
		printf("hello");
		oneCity = &(*it1);
		it1 = cities.begin();
		std::advance(it1, tempI);
		it2 = cities.begin();
		std::advance(it2,tempJ);
		
		(*it1).next = &(*it2);
		(*it1).isVisited = true;
		(*it2).previousOne = true;
	}

	a = minLength;
	return a = minLength==99999999? a:GreedyAlg();

}

int main(){
	
	createCities("ca4663.tsp");
	tourLength = GreedyAlg();
	printf("hello");
	printf("%d",(*oneCity).x);
	printf("%lf",tourLength);
	return 0;
}