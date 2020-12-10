#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>


using namespace std;
using namespace boost;

class Order{
	
	
	public:
		string order;
		int arg;
		bool used;
		Order(string t){
		
			vector<string> tmp;
			split(tmp, t, is_any_of(" "));
			order = tmp[0];
			arg = stoi(tmp[1]);
			
			used = false;
		
		}
		
		bool acc(){
			
			return order.compare("acc") == 0;
			
		}
		
		bool jmp(){
			
			return order.compare("jmp") == 0;
			
		}
		
		bool nop(){
			
			return order.compare("nop") == 0;
			
		}
		
};


class Machine{
	
	public:
		vector<Order> commands;
		int pointer;
		bool executed = false;
		Machine(){
			pointer = 0;
		}
		
		Machine(const Machine &old){
			
			commands = old.commands;
			pointer = 0;
			executed = false;
			
		}
		
		void add(string s){
			
			Order *o = new Order(s);
			commands.push_back(*o);
			
		}
		
		int findFirstChangeOrder(int start){
			
			for(int i = start; i < commands.size(); i++)
				if(commands[i].jmp() || commands[i].nop()) {
					if(commands[i].jmp()) {
						commands[i].order = "nop";
					}
					else if(commands[i].nop()) {
						commands[i].order = "jmp";
					}
					
					cout << "Changed: " << commands[i].order << endl;
					
					return i;
				}
				
			return -1;
			
		}
		
		int execute(int acc, int pointer){
			
			this->pointer = pointer;
			
			if(pointer >= commands.size()){
				
				cout << "Ended!" << endl;
				
				executed = true;
				return acc;
			}
			
			cout << commands[pointer].order << ": " << commands[pointer].arg << " | " << acc << endl;
			
			if(commands[pointer].used)
				return acc;
			else
				commands[pointer].used = true;
			
			Order current = commands[pointer];
			
			if(current.nop()){
				return execute(acc, pointer + 1);
			}
			if(current.jmp()){
				return execute(acc, pointer + current.arg);
			}
			if(current.acc()){
				return execute(acc + current.arg, pointer + 1);
			}
			
			cout << "Fatal error" << endl;
			
			exit(-1);
			
		}
		
};

int main() {
	
	ifstream input("input");
	Machine *m = new Machine();
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
		
			m->add(tmp);
			
		}
		
		input.close();
	}
	
	Machine m1 = *m;
	
	int acc1 = m1.execute(0, 0);
	
	int nextptr = -1;
	bool executed = false;
	
	int acc2 = 0;
	int replacedPos = 0;
	
	cout << "+++++++++++++++++++++++++++++++++" << endl;
	
	do{
		
		Machine current = *m;
		nextptr++;
		
		nextptr = current.findFirstChangeOrder(nextptr);
		
		acc2 = current.execute(0, 0);
		
		cout << "Replacing " << nextptr << " v: " << acc2 << endl;
		
		executed = current.executed;
		
		cout << "-----------------------------------" << endl;
		
	}while(!executed && nextptr != -1);
	
	cout << "Accomulator (P1): " << acc1 << endl;
	cout << "Accomulator (P2): " << acc2 << endl;
	
	return 0;
	
}