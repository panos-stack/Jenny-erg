#include <iostream>
#include <array>
#include <vector>
#include <list>
using namespace std;

// -------------- version 1 of find Min --------------
// int findMin(vector<int> v){
//     int i = 0;
//     int min = INT_MAX;
//     for(City c : allCities){
//         if(v[i] != 0 && v[i] < min && !c.x){
//             min = v[i];
//             c.x = true;
//             route.push_back(c);
//         }
//         i++;
//     }
//     return min;
// }

// -------------- used for debug --------------
// void printCities() {
//     for (int i = 0; i < allCities.size(); i++) {
//         cout << "City " << i + 1 << " distances: "; 
//         for (int dist : allCities[i].distance) {
//             cout << dist << " ";
//         }
//         cout << endl;
//     }
// }

const int L = 10;
int allDistances[L][L];
void createDistanceMatrix(){
    srand(time(0));
    // Fill array
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            if(i == j){
                allDistances[i][j] = 0;
            }
            else {
                int r = rand() % 100 + 1;
                allDistances[i][j] = r;
                allDistances[j][i] = r;
            }
        }
    }
}

class City {
    public:
        vector<int> distance;
        bool x;
        City(int i){
            x = false;
        }

        string printCity(){
            for(int i = 0; i < L; i++){
                if(distance[i] == 0){
                    cout << "city" << to_string(i + 1);
                }
            }
            return "";
        }
};

vector<City> allCities; // Contains all cities 
vector<City> route; // Contains the route followed
vector<bool> visited(L, false); // Contains visited cities
int minDistance;

void createCities(){
    for(int i = 0; i < L; i++){
        City c(i);
        for(int j = 0; j < L; j++){
            // Adds in every city the list with every other city's distance (each row of the matrix corresponds to one city)
            c.distance.push_back(allDistances[i][j]);
        }
        // Adds in every index i of the list allCities the city i
        allCities.push_back(c);
    }
}


void printDistanceMatrix(int d[L][L]){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < L; j++){
            cout << d[i][j] << "\t";
        }
        cout << endl;
    }
}

void printBestRoute(){
    for (int i = 0; i < route.size(); i++){
        cout << route[i].printCity();
        if (i == route.size()-1){ 
            cout << "\n";      
            break;
        }
        cout << " -> ";
    }
}

int findMin(vector<int> v){
    int min = INT_MAX;
    for(int i = 0; i < v.size(); i++){
        if(v[i] != 0 && v[i] < min && !allCities[i].x){
            min = v[i];
            allCities[i].x = true;
            route.push_back(allCities[i]);
        }
    }
    return (min == INT_MAX) ? v[0] : min;
}

void findBestRoute(){
    minDistance = 0;
    route.push_back(allCities[0]); // Add city #1
    allCities[0].x = true;
    int i = 0;
    for(City c : allCities){
        minDistance += findMin(c.distance);
        i++;
    }
    // Add distance from last city back to city #1
    route.push_back(allCities[0]);
    minDistance += allCities[allCities.size() - 1].distance[0];
}

int main(){
    createDistanceMatrix();
    printDistanceMatrix(allDistances);
    createCities();
    findBestRoute();
    printBestRoute();
    cout << "The minimum distance reqiered to travel is: " << minDistance << endl;
    return 0;
}