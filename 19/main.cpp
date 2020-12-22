#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

class Rule{
	
	public:
		string data;
		int id;
		bool isCharacter = false;
		char c;
		vector<vector<int>> ids;
		
		Rule(string data, int id){
			
			trim(data);
			this->data = data;
			this->id = id;
			
			process();
			
		}
		
		Rule(const Rule &r){
			this->data = r.data;
			this->id = r.id;
		}
		
		Rule(){}
		
		
		void process(){
		
			if(data.find('"') != string::npos){
				
				isCharacter = true;
				c = data[1];
				
			}
			else{
				
				vector<string> aux;
				split(aux, data, is_any_of("|"));
				
				for(auto s: aux){
					
					vector<int> tmp;
					vector<string> idsv;
					trim(s);
					split(idsv, s, is_any_of(" "));
					
					for(auto id: idsv)
						tmp.push_back(stoi(id));
						
					ids.push_back(tmp);
					
				}
			
			}
		
		}
		void debug(){
		
			cout << "Rule: " << id << " Data: " << data << endl << endl;
			if(isCharacter)
				cout << "Character: " << c << endl;
			else{
				for(auto group: ids){
					cout << "AND ";
					for(auto id: group){
						cout << id << " ";
					}
					cout << endl;
					cout << "OR" << endl;
				}
			}
			cout << endl;
			cout << "---------------------------" << endl;
		
		}
		
};

void drawTab(int deep){
	
	for(int i = 0; i < deep; i++)
		cout << "\t";
	
}

int recursiveFind(map<int, Rule*> rules, int currentId, int deep, int position, string data){
	
	Rule *current = rules[currentId];
	//drawTab(deep+1); cout << "Finding on " << position << endl;
	
	if(currentId == 8 || currentId == 11){
		drawTab(deep); cout << "Found: " << currentId << endl;
	}
	
	if(current->isCharacter){
		drawTab(deep+2);
		if(data[position] == current->c){
			cout << position << " " << current->c;
			cout << " MATCH" << endl;
			return position;
		}
		else{
			cout << position << " " << current->c << endl;
			return -1;
		}
	}
	else{
		
		bool validGroup = true;
		int offset = position;
		
		int count = 0;
		
		for(auto group: current->ids){
			
			drawTab(deep+1); cout << "OR GROUP " << position << endl;
			
			offset = position;
			
			int offsetCount = offset;
			
			for(auto id: group){
				drawTab(deep+1); cout << "\tAND GROUP " << count << " " << offset << " " << position << endl;
				offset = recursiveFind(rules, id, deep+2, offsetCount, data);
				offsetCount = offset +1;
				
				if(offset != -1) {
					//drawTab(deep+1); cout << "\tReturned Offset: " << offset << endl;
				}
				
				if(offset == -1) {
					//cout << "NOT FOUND" << endl;
					validGroup = false;
					break;
				}
				cout << endl;
				
				count++;
			}
			
			if(offset != -1)
				break;
			
		}
		
		if(offset == -1)
			return -1;
		else{
			//drawTab(deep); cout << "\tReturning Offset: " << offset << endl;
			return offset;
		}
		
	}
	
}


int main() {
	
	ifstream input("input");
	map <int, Rule*> rules;
	vector<string> messages;
	
	bool isRules = true;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			
			trim(tmp);
			if(tmp.size() == 0)
				isRules = false;
			else{
				if(isRules){
					vector <string> aux;
					split(aux, tmp, is_any_of(":"));
					Rule *r = new Rule(aux[1], stoi(aux[0]));
					rules[stoi(aux[0])] = r;
				}
				else{
					messages.push_back(tmp);
				}
			}
		}
		input.close();
	}
	
	int adv = 0;
	
	int count = 0;
	
	//for(auto m: messages) {
		int ret = recursiveFind(rules, 0, 0, 0, "babbbbaabbbbbabbbbbbaabaaabaaa");
		/*if(ret == m.size() - 1)
			count++;*/
		adv++;
		cout << adv << "/" << messages.size() << endl;
		
	//}
	
	
	cout << "Count (p1): " << count << endl;
	
	return 0;
	
}