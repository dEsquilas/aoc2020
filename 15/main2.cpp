#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;


int main() {
	
	ifstream input("input");
	
	vector<int> list;
	map<int, vector<int>> positions;
	
	string tmp;
	if (input.is_open()) {
		getline(input, tmp);
		input.close();
	}
	
	vector<string> aux;
	split(aux, tmp, is_any_of(","));
	
	for(int i = 0; i < aux.size(); i++){
		string s = aux[i];
		trim(s);
		list.push_back(stoi(s));
		positions[stoi(s)].push_back(i);
	}
	
	int last = list[aux.size() - 1];
	int llast = list[aux.size() - 2];
	
	int current;
	
	for(int i = list.size(); i < 10; i++) {
		
		int toFind = last;
		
		//cout << "To find " << toFind << endl;
		
		if(llast == last){
			
			positions[1].push_back(i);
			current = 1;
		}
		else if(positions[toFind].size() >= 2){
			
			int positionsLength = positions[toFind].size();
			current = positions[toFind][positionsLength - 1] - positions[toFind][positionsLength - 2];
			positions[current].push_back(i);
			
		}
		else{
			
			positions[0].push_back(i);
			current = 0;
			
		}
		
		llast = last;
		last = current;
		
		//cout << "Turn: " << (i + 1) << " Value: " << current << endl;
		//cout << "+++++++++++++++++++++++++++++++++++++++++" << endl;
		
		cout << current << endl;
		
	}
	
/*	vector<int>::iterator p1 = find(list.begin(), list.end(), 0);
	vector<int>::iterator p2 = find(list.begin(), list.end(), 6);
	vector<int>::iterator p3 = find(list.begin(), list.end(), 3);
	
	cout << (p1 - list.begin()) << endl;
	cout << (p2 - list.begin()) << endl;
	cout << (p3 - list.begin()) << endl;*/

	cout << "Total: " << last << endl;
	
	
	
	return 0;
	
}