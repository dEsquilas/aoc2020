#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

class Range{
	
	public:
		int start;
		int end;
		
		Range(int start, int end){
			this->start = start;
			this->end = end;
		}
		
};

Range *getPharenthesisPosition(int offset, string data){
	
	int deep = 0;
	int startPosition = -1;
	int endPosition = -1;
	
	for(int i = offset; i < data.size(); i++){
		
		if(data[i] == '('){
			if(startPosition == -1)
				startPosition = i;
			else{
				deep++;
			}
		}
		if(data[i] ==')'){
			if(deep > 0){
				deep--;
			}
			else {
				endPosition = i;
				break;
			}
		}
		
	}
	
	if(endPosition != -1 && startPosition != -1)
		return new Range(startPosition, endPosition);
	else
		return new Range(-1, -1);

}

long unsigned int operate(string data, int offset){
	
	cout << "Cheking Parenthedis for " << data << endl;
	
	do{
		Range *r = getPharenthesisPosition(offset, data);
		if(r->start == -1)
			break;
		
		int parenthesisOperation = operate(data.substr(r->start + 1, r->end - r->start -1), 0);
		
		string dataPrev = data.substr(0, r->start);
		string dataPos = data.substr(r->end+1);
		
		data = dataPrev + to_string(parenthesisOperation) + dataPos;
		
		cout << "Updated Data is " << data << endl;
		
	}while(true);
	
	cout << "Data to calculate: " << data << endl;
	
	vector<string> elements;
	split(elements, data, is_any_of(" "));
	
	long int ret = stoi(elements[0]);
	
	cout << "Splitted: ";
	for(auto e: elements)
		cout << e << " ";
	cout << endl;
	
	for(int i = 1; i < elements.size(); i+=2){
		
		if(elements[i][0] == '+'){
			ret = ret + stoi(elements[i+1]);
		}
		else if(elements[i][0] == '*'){
			ret = ret * stoi(elements[i+1]);
		}
		else{
			cout << "FATAL ERROR" << endl;
		}
		
	}
	
	cout << "Returning " << ret << " for " << data << endl;
	
	return ret;
	
	
}


int main() {
	
	ifstream input("input");
	vector<string> operations;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			trim(tmp);
			operations.push_back(tmp);
			
		}
		input.close();
	}
	
	long unsigned int i = 0;
	
	for(auto o: operations) {
		long unsigned int tmp = operate(o, 0);
		cout << tmp << endl;
		i += tmp;
	}
	
	cout << "Val: " << i << endl;
	
	return 0;
	
}