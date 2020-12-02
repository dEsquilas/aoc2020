#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

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


class Password{
	
	public:
		
		string password;
		char letter;
		int min;
		int max;
		
		Password(string input){
			
			vector<string> tmp = explode(input, ':');
			
			password = tmp[1].substr(1, tmp[1].size());
			
			vector<string> rules = explode(tmp[0], ' ');
			
			letter = rules[1][0];
			
			vector<string> mm = explode(rules[0], '-');
			
			min = stoi(mm[0]);
			max = stoi(mm[1]);
		
		}
		
		void debug(){
		
			cout << password << " - " << letter << " - " << to_string(min) << " - " << to_string(max) << endl;
		
		}
		
		bool isValid(){
			
			int count = 0;
			
			for(int i = 0; i < password.size(); i++)
				if(password[i] == letter)
					count++;
			
			if(min <= count && count <= max)
				return true;
			return false;
			
		}
		
		bool isValid2(){
			
			if((password[min-1] == letter && password[max-1] != letter) || (password[min-1] != letter && password[max-1] == letter))
				return true;
			
			return false;
			
		}
	
};

int main(){
	
	ifstream input("input");
	
	int valid1 = 0;
	int valid2 = 0;
	
	if (input.is_open()){
		string tmp;
		while ( getline (input,tmp) ){
			
			Password *n = new Password(tmp);
			
			if(n->isValid())
				valid1++;
			
			if(n->isValid2())
				valid2++;
			
		}
		input.close();
	}
	
	cerr << "Correct Passwords (p1): " << to_string(valid1) << endl;
	cerr << "Correct Passwords (p2): " << to_string(valid2) << endl;
	
	return 0;
	
}