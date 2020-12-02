#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(){
	
	ifstream input("input");
	
	vector<int> values;
	
	if (input.is_open()){
		string tmp;
		while ( getline (input,tmp) ){
			//cout << tmp << '\n';
			values.push_back(stoi(tmp));
		}
		input.close();
	}
	
	for(int i = 0; i < values.size(); i++){
		
		for(int j = i+1; j < values.size(); j++){
		
			if(values[i] + values[j] == 2020){
				
				int oper = values[i] * values[j];
				
				cout << to_string(values[i]) << " - " << to_string(values[j]) << " : " << oper << endl;
				
			}
		
		}
		
	}
	
	return 0;
	
}