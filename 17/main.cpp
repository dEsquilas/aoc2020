#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

class Cell{
	
	public:
		int x;
		int y;
		int z;
		
		Cell(int x, int y, int z){
			this->x = x;
			this->z = z;
			this->y = y;
		}
		
		Cell(const Cell &p){
			this->x = p.x;
			this->z = p.z;
			this->y = p.y;
		}
		
		bool operator==(const Cell &other) const{
			
			if(
				x == other.x &&
				y == other.y &&
				z == other.z
				)
				return true;
			return false;
			
		}
		
};

class Hash{
	public:
		size_t operator()(const Cell &c) const{
			string tmp = to_string(c.x) + "," + to_string(c.y) + "," + to_string(c.z);
			return tmp.length();
		}
};


int countNearbyActive(unordered_map<Cell, char, Hash> cube, vector<Cell> nearby, Cell current){
	
	int count = 0;
	
	for(auto c: nearby){
		Cell toCheck(current.x + c.x, current.y + c.y, current.z + c.z);
		
		/*if(c.z == 0){
			
			cout << "Cheking " << c.x << ", " << c.y << "< " << c.z << " ON " << current.x << ", " << current.y << " " << current.z << " VALUE " << cube.at(toCheck) << endl;
			
		}*/
		
		if(cube.find(toCheck) == cube.end()) {
			//cout << "\tNOT EXISTS" << endl;
			continue;
		}
		
		if(cube.at(toCheck) == '#')
			count++;
	}
	
	return count;
	
}


int main() {
	
	ifstream input("input");
	
	unordered_map<Cell, char, Hash> cube;
	
	int xMax = 4;
	int yMax = 4;
	int zMax = 1;
	
	int rng[] = {-1, 0, 1};
	vector<Cell> nearby;
	vector<string> fields;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			trim(tmp);
			fields.push_back(tmp);
			
		}
		input.close();
	}
	
	for(auto a1: rng){
		for(auto a2: rng){
			for(auto a3: rng){
				if(a1 != 0 || a2 != 0 || a3 != 0){
					Cell *c = new Cell(a1, a2, a3);
					nearby.push_back(*c);
				}
			}
		}
	}
	
	
	for(int i = -xMax; i <= yMax; i++){
		for(int j = -yMax; j <= yMax; j++){
			Cell t(i, j, 0);
			cube[t] = fields[i+xMax][j+yMax];
		}
	}
	
	
	for(int i = -xMax; i <= yMax; i++){
		for(int j = -yMax; j <= yMax; j++){
			Cell t(i, j, 0);
			cout << cube[t];
		}
		cout << endl;
	}
	
	cout << endl;cout << endl;
	
	for(int round = 0; round < 6; round++){
		
		unordered_map<Cell, char, Hash> nextCube = cube;
		int currentActive = 0;
		
		for(int z = -zMax; z <= zMax; z++){
			
			//cout << "Z: " << z << endl << endl;
			
			for(int x = -xMax; x <= yMax; x++){
				for(int y = -yMax; y <= yMax; y++){
					
					Cell current(x,y,z);
					
					int currentCount = countNearbyActive(cube, nearby, current);
					
					if(cube.find(current) == cube.end() || cube.at(current) == '.'){
						if(currentCount == 3) {
							nextCube[current] = '#';
							//cout << "#";
							currentActive++;
						}else {
							nextCube[current] = '.';
							//cout << ".";
						}
					}
					else{
						if(currentCount == 2 || currentCount == 3) {
							nextCube[current] = '#';
							//cout << "#";
							currentActive++;
						}else {
							nextCube[current] = '.';
							//cout << ".";
						}
					}
				
				}
				//cout << endl;
			}
			
			//cout << endl << endl << endl;
			
		}
		
		// Round ended
		
		xMax++;
		yMax++;
		zMax++;
		
		cube = nextCube;
		
		cout << "Actives: " << currentActive << endl << endl;
		
	}
	
	/*int currentCount = countNearbyActive(cube, nearby, Cell(0, 0, 0));
	cout << currentCount << endl;*/
	
	
	
	
	
	return 0;
	
}