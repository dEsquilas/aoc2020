#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

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

int str2int(string str)
{
	return stoi(str, nullptr,16);
}

class Passport{
	
	public:
		string data;
		int byr;
		int iyr;
		int eyr;
		string hgt;
		string hcl;
		string ecl;
		string pid;
		int cid;
		
		Passport(){
			
			data = hcl = ecl = hgt = pid = "";
			byr = iyr = eyr = cid = -1;
			
		}
		
		void add(string toAdd){
			
			data.append(" " + toAdd);
		
		}
		
		void process(){
			
			vector<string> props = explode(data, ' ');
			
			for(auto s: props){
				if(s.size() > 0){
					vector<string> tmp = explode(s, ':');
					
					if(tmp[0].compare("byr") == 0)
						byr = stoi(tmp[1]);
					else if(tmp[0].compare("iyr") == 0)
						iyr = stoi(tmp[1]);
					else if(tmp[0].compare("eyr") == 0)
						eyr = stoi(tmp[1]);
					else if(tmp[0].compare("hgt") == 0)
						hgt = tmp[1];
					else if(tmp[0].compare("hcl") == 0)
						hcl = tmp[1];
					else if(tmp[0].compare("ecl") == 0)
						ecl = tmp[1];
					else if(tmp[0].compare("pid") == 0)
						pid = tmp[1];
					else if(tmp[0].compare("cid") == 0)
						cid = stoi(tmp[1]);
					else{
						cerr << "Field not found: " << tmp[0] << endl;
						exit(-1);
					}
					
				}
			}
			
		}
		
		bool validateFields(){
			
			if(
					byr != -1 &&
					iyr != -1 &&
					eyr != -1 &&
					hgt.size() > 0 &&
					pid.size() > 0 &&
					hcl.size() > 0 &&
					ecl.size() > 0
					)
				return true;
			else
				return false;
			
		}
		
		bool validateCompleteFields(){
		
			if(
					validateBYR() &&
					validateIYR() &&
					validateEYR() &&
					validateHGT() &&
					validateHCL() &&
					validateECL() &&
					validatePID()
					)
				return true;
			else
				return false;
		
		}
		
		bool validateBYR(){
			
			if(1920 <= byr && byr <= 2002)
				return true;
			return false;
			
		}
		
		bool validateIYR(){
			
			if(2010 <= iyr && iyr <= 2020)
				return true;
			return false;
			
		}
		
		bool validateEYR(){
			
			if(2020 <= eyr && eyr <= 2030)
				return true;
			return false;
		
		}
		
		bool validateHGT(){
		
			if(hgt.find("cm") != string::npos){
				int n = stoi(hgt.substr(0, hgt.find("cm")));
				if(150 <= n && n <= 193)
					return true;
				else
					return false;
			}else if(hgt.find("in") != string::npos){
				int n = stoi(hgt.substr(0, hgt.find("in")));
				if(59 <= n && n <= 76)
					return true;
				else
					return false;
			
			}else
				return false;
		
		}
		
		bool validateHCL(){
			
			if(hcl.size() != 7)
				return false;
			
			if(hcl[0] != '#')
				return false;
			
			for(int i = 1; i < 7; i++) {
				if (!validateHexValue(hcl[i]))
					return false;
			}
			
			return true;
			
		}
		
		bool validateHexValue(char c){
			
			char values[] = {'a', 'b', 'c', 'd', 'e', 'f', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
			
			for(char a: values)
				if(c == a)
					return true;
			return false;
			
		}
		
		bool validateECL(){
			
			string values[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
			
			for(string c: values)
				if(c.compare(ecl) == 0)
					return true;
				
			return false;
			
		}
		
		bool validatePID(){
			
			
			if(pid.size() != 9)
				return false;
			
			for(int i = 0; i < pid.size(); i++)
				if(!isdigit(pid[i]))
					return false;
					
			return true;
		
		}
		
		void debug(){
			
			cout <<
				"byr " << to_string(byr) << endl <<
				"iyr " << to_string(iyr) << endl <<
				"eyr " << to_string(eyr) << endl <<
				"hgt " << hgt << endl <<
				"hcl " << hcl << endl <<
				"ecl " << ecl << endl <<
				"pid " << pid << endl <<
				"cid " << to_string(cid) << endl <<
			endl;
			
		}
};


int main(){
	
	ifstream input("input");
	vector<Passport> passports;
	int count1 = 0;
	int count2 = 0;
	
	if (input.is_open()){
		string tmp;
		Passport *p = new Passport();
		while ( getline (input,tmp) ){
			
			if(tmp.size() == 0){
				passports.push_back(*p);
				p = new Passport();
			}
			else{
				p->add(tmp);
			}
			
		}
		
		passports.push_back(*p);
		
		input.close();
	}
	
	for(auto p: passports){
		p.process();
		
		if(p.validateFields())
			count1++;
		if(p.validateCompleteFields())
			count2++;
		
	}
	
	cout << "Valid Passports (p1): " << to_string(count1) << endl;
	cout << "Valid Passports (p2): " << to_string(count2) << endl;
	
	return 0;
	
}