#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using namespace boost;
using namespace boost::algorithm;

vector<string> explode(const string& s, char c) {

	string::size_type i = 0;
	string::size_type j = s.find(c);

	vector<string> v;

	while (j != string::npos) {
		v.push_back(s.substr(i, j-i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
			v.push_back(s.substr(i, s.length()));
	}

	return v;
}

class BagRule{

	public:
		string type;
		vector<string> rules;

		BagRule(string data){

			parse(data);

		}

		BagRule(){

		}

		void parse(string data){

			erase_all(data, ".");
			erase_all(data, "bags");
			erase_all(data, "bag");

			int p1 = data.find(" contain ");

			type = data.substr(0, p1-1);

			string containString = data.substr(p1 + 9);
			replace_all(containString, ", ", ",");
			vector<string> exploded = explode(containString, ',');

			if(exploded.size() > 0)
				for(auto s: exploded){

					string bagType = s.substr(2);
					rules.push_back(bagType);

				}
			else{

				if(containString.compare("no other ") != 0){

					string bagType = containString.substr(2);
					rules.push_back(bagType);

				}

			}

		}

		vector<vector<string>> getChildsRoute(){

			vector<vector<string>> list;

			if(contains.size() == 0)
				return list;

			else{


				foreach(auto c: contains){



				}

				return list;

			}

		}

};


class Bag{

	public:
		vector<Bag> contains;
		map<string, BagRule> rules;
		string id;

		Bag(string id, map<string, BagRule> rules){
			this->id = id;
			this->rules = rules;

			generateChilds();
		}

		void generateChilds(){

			vector<string> childs = rules[id].rules;

			for(auto c: childs){
				Bag *tmp = new Bag(c, rules);
				contains.push_back(*tmp);
			}

		}

};

int main(){

	ifstream input("input");

	map<string, BagRule> rules;
	vector<Bag> bags;

	if (input.is_open()){
		string tmp;

		while ( getline (input,tmp) ){

			BagRule *b = new BagRule(tmp);
			rules[b->type] = *b;

		}

		input.close();
	}

	for(auto [key, rule]: rules){

		Bag *tmp = new Bag(rule.type, rules);
		bags.push_back(*tmp);

	}

	vector<vector<string>> list;

	for(auto b: bags){
		cout << "BagType: " << b.id << " childs: " << b.contains.size() << endl;
	}


	return 0;

}