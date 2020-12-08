#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
using namespace boost;
using namespace boost::algorithm;


class BagRule{
	
	public:
		
		string type;
		vector<string> contains;
		BagRule(string data){
			
			parse(data);
		
		}
		
		BagRule(){
		
		}
		
		void parse(string data){
			erase_all(data, " bags");
			erase_all(data, " bag");
			erase_all(data, ".");
	
			
			int p1 = data.find(" contain ");
			
			type = data.substr(0, p1);
			string childsString = data.substr(p1 + 9);
			
			vector<string> splited;
			
			split(splited, childsString, is_any_of(","));
			
			for(auto s: splited){
				
				trim(s);
				
				if(s.compare("no other") != 0) {
					
					string tmp = s.substr(2);
					contains.push_back(tmp);
					
				}
			}
			
		}
		
};

class Bag{
	
	public:
		map<string, BagRule> rules;
		vector<Bag> childs;
		string type;
		Bag(string type, map<string, BagRule> rules){
			
			this->type = type;
			this->rules = rules;
			
			generateChilds();
			
		}
		Bag(){
		
		}
		
		void generateChilds(){
		
			vector<string> childRules = rules[type].contains;
			
			for(auto s: childRules){
				
				Bag *b = new Bag(s, rules);
				childs.push_back(*b);
				
			}
		
		}
		
		vector<vector<string>> getMyWay(){
			
			vector<vector<string>> outList;
			vector<vector<string>> list;
			
			for(auto b: childs){
				vector<vector<string>> tmp = b.getMyWay();
				list.reserve(list.size() + tmp.size());
				list.insert(list.end(), tmp.begin(), tmp.end());
			}
			
			if(childs.size() == 0){
				
				vector<string> tmp;
				tmp.push_back(type);
				outList.push_back(tmp);
				return outList;
			}
			else{
			
				for(auto l: list){
					l.push_back(type);
					outList.push_back(l);
				}
				
				return outList;
				
			}
			
		}
		
};

int main() {
	
	ifstream input("input");
	
	map <string, BagRule> rules;
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
			
			BagRule *b = new BagRule(tmp);
			rules[b->type] = *b;
			
		}
		
		input.close();
	}
	
	for(auto [key, b]: rules){
		
		cout << "Bag Type: ||" << b.type << "||" << endl;
		cout << "Childs: " << endl;
		
		for(auto s: b.contains){
			
			cout << "\t||" << s << "||" << endl;
			
		}
		
		cout << endl << endl;
		
	}
	
	cout << endl << endl << "Creating Bag" << endl << endl;
	
	Bag *b = new Bag("bright white", rules);
	
	vector<vector<string>> ways = b->getMyWay();
	
	
	cout << endl << endl << "Routes Bag: " << b->type << endl << endl;
	
	for(auto l: ways){
		for(auto s: l){
			cout << s << " - ";
		}
		cout << endl;
	}
	
	
	return 0;
	
}