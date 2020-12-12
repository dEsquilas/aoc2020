#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3


using namespace std;

typedef void (*ptrtd)(int, int*, int*, int*);
typedef void (*ptrtd2)(int, int*, int*, int*, int*);

class Instruction{
	
	public:
		char order;
		int count;
		
};

class Ship{
	
	public:
		vector<Instruction> instructions;
		
		int x = 0;
		int y = 0;
		int wx = 1;
		int wy = 10;
		int direction = EAST;
		map<char, ptrtd> functions;
		map<char, ptrtd2> f2;
		
		Ship(){
			
			init();
			init2();
			
		}
		
		void init(){
			
			functions['N'] = &north;
			functions['E'] = &east;
			functions['S'] = &south;
			functions['W'] = &west;
			functions['L'] = &left;
			functions['R'] = &right;
			functions['F'] = &forward;
			
		}
		
		
		void init2(){
			
			f2['N'] = &northw;
			f2['E'] = &eastw;
			f2['S'] = &southw;
			f2['W'] = &westw;
			f2['L'] = &leftw;
			f2['R'] = &rightw;
			f2['F'] = &forwardw;
			
		}
		
		void add(string t){
			
			Instruction *i = new Instruction();
			
			i->order = t[0];
			i->count = stoi(t.substr(1));
			
			instructions.push_back(*i);
			
		}
		
		void followInstructions(){
			
			x = 0;
			y = 0;
			wx = 0;
			wy = 0;
		
			for(auto i: instructions){
				functions[i.order](i.count, &x, &y, &direction);
			}
		
		}
		
		void followInstructions2(){
			
			x = 0;
			y = 0;
			wx = 1;
			wy = 10;
			
			for(auto i: instructions){
				f2[i.order](i.count, &x, &y, &wx, &wy);
			}
			
		}
		
		static void north(int arg, int *x, int *y, int *dir){
			
			*x += arg;
			
		}
		
		static void south(int arg, int *x, int *y, int *dir){
			
			*x -= arg;
			
		}
		
		static void east(int arg, int *x, int *y, int *dir){
			
			*y += arg;
			
		}
		
		static void west(int arg, int *x, int *y, int *dir){
			
			*y -= arg;
			
		}
		
		
		static void left(int arg, int *x, int *y, int *dir){
			
			int realDirection = *dir - (arg / 90);
			
			while(realDirection < 0)
				realDirection += 4;
			
			*dir = realDirection;
			
		}
		
		static void right(int arg, int *x, int *y, int *dir){
			
			int realDirection = *dir + (arg / 90);
			
			while(realDirection > 3)
				realDirection -= 4;
			
			*dir = realDirection;
			
		}
		
		static void forward(int arg, int *x, int *y, int *dir){
			
			char directionOptions[] = {'N', 'E', 'S', 'W'};
			
			map<char, ptrtd> f2;
			
			f2['N'] = &north;
			f2['E'] = &east;
			f2['S'] = &south;
			f2['W'] = &west;
			
			f2[directionOptions[*dir]](arg, x, y, dir);
		
		}
		
		
		static void northw(int arg, int *x, int *y, int *xw, int *yw){
			
			*xw += arg;
			
		}
		
		static void southw(int arg, int *x, int *y, int *xw, int *yw){
			
			*xw -= arg;
			
		}
		
		static void eastw(int arg, int *x, int *y, int *xw, int *yw){
			
			*yw += arg;
			
		}
		
		static void westw(int arg, int *x, int *y, int *xw, int *yw){
			
			*yw -= arg;
			
		}
		
		
		static void leftw(int arg, int *x, int *y, int *xw, int *yw){
			
			int tmp = arg / 90;
			
			while(tmp > 3){
				tmp -= 4;
			}
			
			int tmpx = *xw;
			int tmpy = *yw;
			
			switch(tmp){
				
				case 0:
					// nothing to do
					break;
				case 1:
					*xw = tmpy;
					*yw = -tmpx;
					break;
				case 2:
					*xw = -tmpx;
					*yw = -tmpy;
					break;
				case 3:
					*xw = -tmpy;
					*yw = tmpx;
					break;
			}
			
		}
		
		static void rightw(int arg, int *x, int *y, int *xw, int *yw){
			
			int tmp = arg / 90;
			
			while(tmp > 3){
				tmp -= 4;
			}
			
			int tmpx = *xw;
			int tmpy = *yw;
			
			switch(tmp){
				
				case 0:
					// nothing to do
					break;
				case 1:
					*xw = -tmpy;
					*yw = tmpx;
					break;
				case 2:
					*xw = -tmpx;
					*yw = -tmpy;
					break;
				case 3:
					*xw = tmpy;
					*yw = -tmpx;
					break;
			}
			
		}
		
		static void forwardw(int arg, int *x, int *y, int *xw, int *yw){
		
			*x += arg * (*xw);
			*y += arg * (*yw);
			
		}
		
		
		
		void debug(){
			
			for(auto i: instructions)
				cout << i.order << " " << i.count << endl;
			
		}
		
		
};


int main() {
	
	ifstream input("input");
	
	Ship *s = new Ship();

	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
			s->add(tmp);
		}
		
		input.close();
	}
	
	s->followInstructions();
	
	int tmp1 = abs(s->x) + abs(s->y);
	
	s->followInstructions2();
	
	
	cout << "Sum (p1): " << tmp1 << endl;
	cout << "Sum (p2): " << abs(s->x) + abs(s->y) << endl;
	
	return 0;
	
}