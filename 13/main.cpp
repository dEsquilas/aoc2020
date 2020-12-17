#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <math.h>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;


vector<int> toBinary(int t){

	vector<int> list;
	
	//for(int i = 0; )

}

class Bi{
	
	public:
		int n;
		string mask;
		Bi(int n, string mask){
		
			this->n = n;
			this->mask = mask;
		
		}
		
};

int main() {
	
	ifstream input("input");
	
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)){
			
			vector<string> aux = split(aux, tmp, boost::any_of_this())
			
		}
		
		
		input.close();
	}
	
	return 0;
	
}