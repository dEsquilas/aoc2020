#include <iostream>
#include <bitset>
#include <fstream>
#include <map>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

class Bi{
	
	public:
		long double n;
		string mask;
		Bi(long double n, string mask){
			
			this->n = n;
			this->mask = mask;
			
			trim(this->mask);
			
		}
		
		Bi(const Bi &b){
			
			this->n = b.n;
			this->mask = b.mask;
			
			trim(this->mask);
			
		}
		
		Bi(){}
		
		void debug(){
			
			string t = bitset<36>(n).to_string();
			
			//cout << "Mask: " << mask << endl;
			cout << "Number: " << n << endl;
			cout << "N:" << t << endl;
			//cout << "N2: " << stoi(t, 0, 2) << endl;
			
		}
		
		void applyMask(){
			
			string out = bitset<36>(n).to_string();
			
			for(int i = 0; i < 36; i++){
				if(mask[i] != 'X'){
					out[i] = mask[i];
				}
			}
			
			n = stol(out, 0, 2);
			
		}
	
};

class Bi2{

	public:
		string mask;
		long double pos;
		long double value;
		
		Bi2(string mask, long double pos, long double value){
			
			this->pos = pos;
			this->mask = mask;
			this->value = value;
			
			trim(this->mask);
			
		}
		
		vector<long double> getMemPositions(){
			
			string out = bitset<36>(pos).to_string();
			
			int count = 0;
			
			for(int i = 0; i < 36; i++){
				if(mask[i] != '0'){
					out[i] = mask[i];
					if(mask[i] == 'X')
						count++;
				}
			}
			
			vector<long double> outList;
			
			vector<string> outPositions;
			
			for(int i = 0; i < count; i++){
			
				if(outPositions.size() == 0){
					int posX = out.find_first_of("X");
					out[posX] = '1';
					string o1 = out;
					out[posX] = '0';
					string o2 = out;
					
					outPositions.push_back(o1);
					outPositions.push_back(o2);
				}
				else{
					int posX = outPositions[0].find_first_of("X");
					vector<string> tmp;
					for(auto s: outPositions){
						s[posX] = '1';
						string o1 = s;
						s[posX] = '0';
						string o2 = s;
						tmp.push_back(o1);
						tmp.push_back(o2);
					}
					
					outPositions = tmp;
				}
			
			}
			
			for(auto s: outPositions){
				outList.push_back(stol(s, 0, 2));
			}
			
			return outList;
			
			
		}

};

int main() {
	
	ifstream input("input");
	
	map<int, Bi> numbers;
	
	vector<Bi2> list;
	
	if (input.is_open()) {
		string tmp;
		string currentMask = "a";
		while (getline(input, tmp)){
			
			vector<string> aux;
			split(aux, tmp, boost::is_any_of("="));
			
			string t = aux[0];
			trim(t);
			
			if(t.compare("mask") == 0){
				currentMask = aux[1];
			}
			else{
				
				string pos = aux[0];
				replace_all(pos, "mem[", "");
				replace_all(pos, "]", "");
				trim(pos);
				
				Bi *b = new Bi(stoi(aux[1]), currentMask);
				numbers[stoi(pos)] = *b;
				
				Bi2 *b2 = new Bi2(currentMask, stol(pos), stol(aux[1]));
				list.push_back(*b2);
				
			}
			
		}
		
		input.close();
	}
	
	long double sum = 0;
	
	for(auto [key, b]: numbers) {
		b.applyMask();
		sum += b.n;
	}
	
	map <long double, long double> memory;
	
	for(auto i: list){
		
		vector<long double> m = i.getMemPositions();
		
		for(auto t: m){
			memory[t] = i.value;
		}
		
	}
	
	long double t = 0;
	
	for(auto [key, value]: memory){
		
		t += value;
		
	}
	
	cout << fixed << "Sum (P1): " << sum << endl;
	cout << fixed << "Sum (P2): " << t << endl;
	
	return 0;
	
}