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
		int t;
		
		Cell(int x, int y, int z, int t){
			this->x = x;
			this->z = z;
			this->y = y;
			this->t = t;
		}
		
		Cell(const Cell &p){
			this->x = p.x;
			this->z = p.z;
			this->y = p.y;
			this->t = p.t;
		}
		
		bool operator==(const Cell &other) const{
			
			if(
				x == other.x &&
				y == other.y &&
				t == other.t &&
				z == other.z
				)
				return true;
			return false;
			
		}
		
};

class Hash{
	public:
		size_t operator()(const Cell &c) const{
			string tmp = to_string(c.x) + "," + to_string(c.y) + "," + to_string(c.z) + "," + to_string(c.t);
			return tmp.length();
		}
};


int countNearbyActive(unordered_map<Cell, char, Hash> cube, vector<Cell> nearby, Cell current){
	
	int count = 0;
	
	for(auto c: nearby){
		Cell toCheck(current.x + c.x, current.y + c.y, current.z + c.z, current.t + c.t);
		
		if(cube.find(toCheck) == cube.end()) {
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
	int tMax = 1;
	
	vector<string> fields;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			trim(tmp);
			fields.push_back(tmp);
			
		}
		input.close();
	}
	
	int rng[] = {-1, 0, 1};
	vector<Cell> nearby;
	for(auto a1: rng){
		for(auto a2: rng){
			for(auto a3: rng){
				for(auto a4: rng) {
					if (a1 != 0 || a2 != 0 || a3 != 0 || a4 != 0) {
						Cell *c = new Cell(a1, a2, a3, a4);
						nearby.push_back(*c);
					}
				}
			}
		}
	}
	
	
	for(int i = -xMax; i <= yMax; i++){
		for(int j = -yMax; j <= yMax; j++){
			Cell t(i, j, 0, 0);
			cube[t] = fields[i+xMax][j+yMax];
		}
	}
	
	for(int round = 0; round < 6; round++) {
		
		unordered_map<Cell, char, Hash> nextCube = cube;
		int currentActive = 0;
		
		for (int t = -tMax; t <= tMax; t++){
			
			for (int z = -zMax; z <= zMax; z++) {
				
				//cout << "Z: " << z << endl << endl;
				
				for (int x = -xMax; x <= yMax; x++) {
					for (int y = -yMax; y <= yMax; y++) {
						
						Cell current(x, y, z, t);
						
						int currentCount = countNearbyActive(cube, nearby, current);
						
						if (cube.find(current) == cube.end() || cube.at(current) == '.') {
							if (currentCount == 3) {
								nextCube[current] = '#';
								//cout << "#";
								currentActive++;
							} else {
								nextCube[current] = '.';
								//cout << ".";
							}
						} else {
							if (currentCount == 2 || currentCount == 3) {
								nextCube[current] = '#';
								//cout << "#";
								currentActive++;
							} else {
								nextCube[current] = '.';
								//cout << ".";
							}
						}
						
					}
					//cout << endl;
				}
				
				//cout << endl << endl << endl;
				
			}
		}
		
		// Round ended
		
		xMax++;
		yMax++;
		zMax++;
		tMax++;
		
		cube = nextCube;
		
		cout << "Actives: " << currentActive << endl << endl;
		
	}
	
	/*int currentCount = countNearbyActive(cube, nearby, Cell(0, 0, 0));
	cout << currentCount << endl;*/
	
	
	
	
	
	return 0;
	
}