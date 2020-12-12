#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>

using namespace std;


class Board{
	
	public:
		char **state;
		char **newState;
		int width;
		int height;
		int step;
		
		bool changed;
		
		Board(){
		
			width = 0;
			height = 0;
			step = 0;
			
		}
		
		void addRow(string t){
			
			height++;
			if(width == 0)
				width =  t.size() - 1;
			state = (char **) realloc(state, height * sizeof(char *));
			state[height - 1] = (char *) malloc(width * sizeof(char));
			
			for(int i = 0; i < width; i++)
				state[height - 1][i] = t[i];
			
		}
		
		void reallocate(){
			
			free(newState);
			newState = (char **) malloc(sizeof(char *) * height);
			for(int i = 0; i < height; i++) {
				newState[i] = (char *) malloc(sizeof(char) * width);
				memcpy(newState[i], state[i], sizeof(char) * width);
			}
			
			
		}
		
		void nextStep(){
			
			reallocate();
			
			changed = false;
			
			for(int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					set(i, j);
			
			free(state);
			state = (char **) malloc(sizeof(char *) * height);
			for(int i = 0; i < height; i++) {
				state[i] = (char *) malloc(sizeof(char) * width);
				memcpy(state[i], newState[i], sizeof(char) * width);
			}
			
		}
		
		int occupiedSeats(){
			
			int count = 0;
			for(int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					if(state[i][j] == '#')
						count++;
					
			return count;
		}
		
		void set(int i, int j) {
			
			if (state[i][j] == '.')
				return;
			
			int xStart = j - 1;
			int xEnd = j + 1;
			int yStart = i - 1;
			int yEnd = i + 1;
			
			if (xStart < 0)
				xStart = 0;
			if (xEnd >= width)
				xEnd = width;
			if (yStart < 0)
				yStart = 0;
			if (yEnd >= height)
				yEnd = height - 1;
			
			int ocuppied = 0;
			
			for (int y = yStart; y <= yEnd; y++) {
				for (int x = xStart; x <= xEnd; x++) {
					if (!(i == y && j == x)) {
						if (state[y][x] == '#') {
							ocuppied++;
						}
					}
				}
			}
			
			if (state[i][j] == 'L' && ocuppied == 0) {
				newState[i][j] = '#';
				changed = true;
			}
			
			if (state[i][j] == '#' && ocuppied >= 4) {
				newState[i][j] = 'L';
				changed = true;
			}
			
			
		}
		
		
		void nextStep2(){
			
			reallocate();
			changed = false;
			
			for(int i = 0; i < height; i++)
				for (int j = 0; j < width; j++)
					set2(i, j);
			
			free(state);
			state = (char **) malloc(sizeof(char *) * height);
			for(int i = 0; i < height; i++) {
				state[i] = (char *) malloc(sizeof(char) * width);
				memcpy(state[i], newState[i], sizeof(char) * width);
			}
		
		}
		
		void set2(int i, int j){
			
			int ocuppied = 0;
			
			int c = 0;
			
			if(checkRect(1, true, j, i))
				ocuppied++;
			if(checkRect(1, false, j, i))
				ocuppied++;
			if(checkRect(-1, true, j, i))
				ocuppied++;
			if(checkRect(-1, false, j, i))
				ocuppied++;
			if(checkXRect(true, j, i))
				ocuppied++;
			if(checkXRect(false, j, i))
				ocuppied++;
			if(checkYRect(true, j, i))
				ocuppied++;
			if(checkYRect(false, j, i))
				ocuppied++;
			
			if(state[i][j] == 'L' && ocuppied == 0) {
				newState[i][j] = '#';
				changed = true;
			}
			
			if(state[i][j] == '#' && ocuppied >= 5) {
				newState[i][j] = 'L';
				changed = true;
			}
			
			
		}
		
		bool checkXRect(bool direction, int x, int y){
			
			int xn = x;
			int yn = y;
			int incr = 1;
			
			bool occupied = false;
			
			if(!direction)
				incr = -1;
			
			do{
				
				xn += incr;
				if(xn > width || xn < 0 || yn > height -1 || yn < 0)
					break;
				
				if(state[yn][xn] == '#' || state[yn][xn] == 'L'){
					
					if(state[yn][xn] == '#')
						occupied = true;
					
					break;
				}
				
			}while(true);
			
			return occupied;
			
		}
		
		bool checkYRect(bool direction, int x, int y){
			
			int xn = x;
			int yn = y;
			int incr = 1;
			
			bool occupied = false;
			
			if(!direction)
				incr = -1;
			
			do{
				
				yn += incr;
				
				if(xn > width || xn < 0 || yn > height -1 || yn < 0)
					break;
				
				if(state[yn][xn] == '#' || state[yn][xn] == 'L'){
					
					if(state[yn][xn] == '#') {
						occupied = true;
					}
					
					break;
				}
				
				
			}while(true);
			
			return occupied;
			
		}
		
		bool checkRect(int m, bool direction, int x, int y){
			
			int n = y - m * x;
			int xn = x;
			int incr = 1;
			
			if(!direction)
				incr = -1;
			
			bool occupied = false;
			
			do{
				xn += incr;
				int yn = m * xn + n;
				
				if(xn > width || xn < 0 || yn > height -1 || yn < 0)
					break;
				
				if(state[yn][xn] == '#' || state[yn][xn] == 'L'){
					
					
					if(state[yn][xn] == '#') {
						occupied = true;
					}
					
					break;
				}
				
			}while(true);
			
			return occupied;
			
		}
		
		void debug(){
	
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++)
					cout << state[i][j];
				cout << endl;
			}
		}
		
		void debug2(){
			
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++)
					cout << newState[i][j];
				cout << endl;
			}
		}
	
};


int main() {
	
	ifstream input("input");
	
	Board *b1 = new Board();
	Board *b2 = new Board();
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
			b1->addRow(tmp);
			b2->addRow(tmp);
		}
		
		input.close();
	}
	
	int count = 0;
	
	do {
		count++;
		b1->nextStep();
		
	}while(b1->changed);
	
	int occupied1 = b1->occupiedSeats();
	
	count = 0;
	
	do{
		count++;
		b2->nextStep2();
		
	}while(b2->changed);
	
	int occupied2 = b2->occupiedSeats();
	
	cout << "Count (P1): " << occupied1 << endl;
	cout << "Count (P2): " << occupied2 << endl;
	
	
	return 0;
	
}