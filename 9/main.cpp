#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>


using namespace std;

bool canI(vector<int> list, double current){

	for(int i = 0; i < list.size(); i++){
		
		for(int j = 0; j < list.size(); j++){
			
			if(i != j){
			
				if(list[i] + list[j] == current) {
					return true;
				}
			}
			
		}
		
	}
	
	return false;

}

int sumRange(vector<double> list, int start, double toFind){
	
	double total = 0;
	
	for(int i = start;  i < list.size(); i++){
		total += list[i];
		if(total == toFind){
			return i;
		}
		if(total > toFind)
			return -1;
	}
	
}


int main() {
	
	ifstream input("input");
	
	vector<double> auxList;
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
			auxList.push_back(stod(tmp));
		}
		
		input.close();
	}
	
	int preambleCount = 25;
	vector<double> list(auxList.begin() + preambleCount, auxList.end());
	double notFound = -1;
	
	for(int i = 0; i < list.size(); i++){
		
		
		vector<int> preamble(auxList.begin() + i, auxList.begin() + preambleCount + i);
		
		/*cout << "Checking: " << list[i] << endl;
		
		cout << "Preamble list: " << endl << endl;
		
		for(auto item: preamble){
			cout << item << " ";
		}
		
		cout << endl;
		 
		 */
		
		if(!canI(preamble, list[i])){
			//cout << "Not found " << list[i] << endl;
			notFound = list[i];
			break;
		}
		
		preamble.push_back(list[i]);
		
		//cout << endl << endl << endl;
		
	}
	
	int start;
	int end = 0;
	
	for(start = 0; start < auxList.size() -1; start++){
		
		end = sumRange(auxList, start, notFound);
		if(end != -1)
			break;
		
	}
	
	//cout << "Index Values: " << start << " " << "(" << auxList[start] << ") " << end << " " << "(" << auxList[end] << ")" << endl;
	
	
	double min = 9999999999999;
	double max = 0;
	
	for(int i = start; i <= end; i++){
		if(auxList[i] < min)
			min = auxList[i];
		if(max < auxList[i])
			max = auxList[i];
	}
	
	cout << fixed << "Not found (P1): " << notFound <<  endl;
	cout << fixed << "Sum MinMax (P2): " << (min + max) << endl;
	
	
	return 0;
	
}