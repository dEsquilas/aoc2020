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
		
};

int main() {
	
	ifstream input("input");
	
	map<Cell, char> cube;
	
	int xMax;
	int yMax;
	int zMax = 0;
	
	vector<string> fields;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			trim(tmp);
			fields.push_back(tmp);
			
		}
		input.close();
	}
	
	for(auto s: fields){
		cout << s << endl;
	}
	
	
	
	
	return 0;
	
}