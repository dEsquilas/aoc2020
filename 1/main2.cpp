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
			
			for(int t = i+1; t < values.size(); t++)
		
			if(values[i] + values[j] + values[t] == 2020){
				
				int oper = values[i] * values[j] * values[t];
				
				cout << to_string(values[i]) << " - " << to_string(values[j]) << " - " << to_string(values[t]) << " : " << oper << endl;
				
			}
		
		}
		
	}
	
	return 0;
	
}