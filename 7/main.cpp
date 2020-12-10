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
		vector<int> quantity;
		
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
					string qs = s.substr(0, 1);
					contains.push_back(tmp);
					quantity.push_back(stoi(qs));
					
				}
			}
			
		}
		
		
		int getQuantity(map<string, BagRule> rules){
			
			BagRule currentRule= rules[type];
			
			if(currentRule.contains.size() == 0){
				return 1;
			}else{
				
				int i = 0;
				int total = 0;
				
				for(auto r: currentRule.contains){
					
					BagRule br = rules[r];
					
					int tmp = br.getQuantity(rules) * quantity[i];
					
					total += tmp;
					i++;
					
				}
				
				return total + 1;
				
			}
			
		}
		
		
};

class Bag{
	
	public:
		vector<Bag> parents;
		map<string, Bag> childs;
		map<string, int> quantity;
		string type;
		Bag(string type){
			
			this->type = type;
			
		}
		Bag(){
		
		}
		
		void addParent(Bag b){
		
			parents.push_back(b);
		
		}
		
		vector<string> getParents(map<string, Bag> currentBags){
			
			vector<string> parentsList;
			
			if(currentBags[type].parents.size() == 0){
				parentsList.push_back(type);
				return parentsList;
			}
			else{
				
				for(auto p: currentBags[type].parents){
					
					vector<string> tmp = p.getParents(currentBags);
					parentsList.reserve(parentsList.size() + tmp.size());
					parentsList.insert(parentsList.end(), tmp.begin(), tmp.end());
					
				}
				
				parentsList.push_back(type);
				
				return parentsList;
				
			}
			
		}
		
		
};

int main() {
	
	ifstream input("input");
	
	map <string, BagRule> rules;
	map<string, Bag> bags;
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
			
			BagRule *br = new BagRule(tmp);
			rules[br->type] = *br;
			Bag *b = new Bag(br->type);
			bags[br->type] = *b;
			
		}
		
		input.close();
	}
	
	for(auto [key, b]: rules){
		
		for(auto s: b.contains){
			
			bags[s].parents.push_back(bags[key]);
			
		}
	}
	
	vector<string> bagTypestmp = bags["shiny gold"].getParents(bags);
	vector<string> bagTypes;
	
	for(auto s: bagTypestmp){
		if(find(bagTypes.begin(), bagTypes.end(), s) == bagTypes.end()) {
			bagTypes.push_back(s);
		}
	}
	
	int count = bagTypes.size() -1;
	
	BagRule br = rules["shiny gold"];
	
	int total = br.getQuantity(rules) - 1;
	
	
	cout << "Ways to get Shiny Gold (P1): " << count << endl;
	cout << "Total bags into Shiny Gold (p2): " << total << endl;
	
	
	return 0;
	
}