#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;


int find(int start, int end, int toFind, vector<int> list){
	
	/*cout << "\t\tStart:" << start << " End: " << end << endl;
	cout << "\t\t";
	
	
	for(auto t: list)
		cout << t << ",";
	
	cout << endl;*/
	

	for(int i = end; i >= start; i--) {
		//cout << "\t\t\tChecking " << i << " Value " << list[i] << " toFind:" << toFind << endl;
		if (list[i] == toFind)
			return i;
	}
	
	return -1;

}




int main() {
	
	ifstream input("input");
	
	vector<int> list;
	
	string tmp;
	if (input.is_open()) {
		getline(input, tmp);
		input.close();
	}
	
	vector<string> aux;
	split(aux, tmp, is_any_of(","));
	
	for(auto s: aux){
		trim(s);
		list.push_back(stoi(s));
	}
	
	int last = 0;
	
	for(int i = 0; i < 30000000; i++) {
		if(i >= list.size()){
			//cout << "Finding: " << list[i-1] << endl;
			/*for(auto t: list)
				cout << t << ",";
			
			cout << endl;*/
			
			int p1 = find(0, list.size() - 1, list[i-1], list);
			
			if(list[i-1] == list[i-2]){
				list.push_back(1);
			} else if(p1 == -1){
				list.push_back(0);
			}
			else{
				
				//cout << "-------" << endl;
				
				int p2 = find(0, p1-1, list[i-1], list);
				if(p2 == -1) {
					//cout << "\tLast" << endl;
					list.push_back(0);
				}else {
					//cout << "\tP1: " << p1 << " P2: " << p2 << endl;
					list.push_back(p1 - p2);
				}
			}
		}
		if(i % 10000 == 0 ) {
			cout << "Turn: " << (i + 1) << " Value: " << list[i] << endl;
			cout << "+++++++++++++++++++++++++++++++++++++" << endl;
		}
		
		last = list[i];
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