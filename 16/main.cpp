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
		
};

class CRule{
	public:
		Range *r1 = nullptr;
		Range *r2 = nullptr;
		string name;
		
		vector<int> valid;
		int col = -1;
		
		bool check(int val){
			
			if((r1->start <= val && val <= r1->end) || (r2->start <= val && val <= r2->end))
				return true;
			return false;
			
		}
};


int main() {
	
	ifstream input("input");
	
	vector<string> rulesString;
	vector<string> yourTicket;
	vector<string> nearbyTickets;
	
	vector <int> nearby;
	vector <Range> ranges;
	vector <CRule> rules;
	
	
	int c = 0;
	
	if (input.is_open()) {
		string tmp;
		while(getline(input, tmp)){
			trim(tmp);
			if(tmp.size() == 0)
				c++;
			if(c == 0)
				rulesString.push_back(tmp);
			if(c == 1)
				yourTicket.push_back(tmp);
			if(c == 2)
				nearbyTickets.push_back(tmp);
			
		}
		input.close();
	}
	
	for(int i = 0; i < rulesString.size(); i++){
	
		vector<string> tmp;
		split(tmp, rulesString[i], is_any_of(":"));
		vector<string> tmp2;
		
		trim(tmp[1]);
		
		CRule *rule = new CRule();
		trim(tmp[0]);
		rule->name = tmp[0];
		
		split(tmp2, tmp[1], is_any_of(" or "));
		
		for(int t = 0; t < tmp2.size(); t++){
			string current = tmp2[t];
			trim(current);
			
			if(current.size() == 0)
				continue;
			
			vector<string> rg;
			split(rg, current, is_any_of("-"));
			
			Range *r = new Range();
			
			r->start = stoi(rg[0]);
			r->end = stoi(rg[1]);
			
			if(rule->r1 == nullptr){
				rule->r1 = r;
			}
			else
				rule->r2 = r;
			
			ranges.push_back(*r);
			
		}
		
		rules.push_back(*rule);
		
	}
	
	
	vector<int> invalid;
	vector<vector<int>> tickets;
	
	for(int i = 2; i < nearbyTickets.size(); i++){
		vector<string> tmp;
		split(tmp, nearbyTickets[i], is_any_of(","));
		vector<int> currentValues;
		bool thisRowIsValid = true;
		for(auto s: tmp) {
			nearby.push_back(stoi(s));
			currentValues.push_back(stoi(s));
			bool valid = false;
			for(auto r: ranges){
				int c = stoi(s);
				if(r.start <= c && c <= r.end){
					valid = true;
					break;
				}
			}
			if(!valid) {
				invalid.push_back(stoi(s));
				thisRowIsValid = false;
			}
		}
		if(thisRowIsValid)
			tickets.push_back(currentValues);
	}
	
	int total1 = 0;
	
	for(auto i: invalid) {
		total1 += i;
	}
	
	cout << "Total (p1): " << total1 << endl;
	
	for(int t = 0; t < rules.size(); t++) {
		
		for (int i = 0; i < tickets[0].size(); i++) {
			
			bool valid = true;
			
			for (int j = 0; j < tickets.size(); j++) {
				if (!rules[t].check(tickets[j][i])) {
					valid = false;
					break;
				}
			}
			
			if (valid) {
				rules[t].valid.push_back(i);
			}
		}
	}
	
	vector<int> found;
	
	for(int i = 0; i < rules.size(); i++){
		
		for(int j = 0; j < rules.size(); j++)
			if(rules[j].valid.size() == i + 1){
				rules[j].col = i;
				if(rules[j].valid.size() == 1){
					rules[j].col = rules[j].valid[0];
					found.push_back(rules[j].col);
				}
				else{
					
					for(auto a: rules[j].valid){
						if(find(found.begin(), found.end(), a) == found.end()){
							found.push_back(a);
							rules[j].col = a;
							break;
						}
					}
					
				}
			}
		
	}
	
	vector<string> yourTicketValues;
	split(yourTicketValues, yourTicket[2], is_any_of(","));
	long int total2 = 1;
	
	for(int i = 0; i < 6; i++){
		total2 *= stoi(yourTicketValues[rules[i].col]);
	}
	
	cout << fixed << "Total (p2): " << total2 << endl;
	
	return 0;
	
}