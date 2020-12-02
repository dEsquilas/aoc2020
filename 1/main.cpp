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
				
				cout << "Values: " << to_string(values[i]) << " - " << to_string(values[j]) << " Results(1): " << oper << endl;
				break;
				
			}
		
		}
		
	}
	
	bool stop = false;
	
	for(int i = 0; i < values.size(); i++){
		
		for(int j = i+1; j < values.size(); j++){
			
			for(int t = i+1; t < values.size(); t++)
				
				if(values[i] + values[j] + values[t] == 2020){
					
					int oper = values[i] * values[j] * values[t];
					
					cout << "Values: " << to_string(values[i]) << " - " << to_string(values[j]) << " - " << to_string(values[t]) << " Results(2):  " << oper << endl;
					stop = true;
					break;
					
				}
			
			if(stop)
				break;
			
		}
		
		if(stop)
			break;
		
	}
	
	return 0;
	
}