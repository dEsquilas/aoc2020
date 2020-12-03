#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

#define MAP_WIDTH  31
#define MAP_HEIGHT 323

//#define MAP_WIDTH  11
//#define MAP_HEIGHT 11

#define MRIGHT 3
#define MBOT 1

using namespace std;

class Map{
	
	public:
		
		char innerMap[MAP_HEIGHT][MAP_WIDTH];
		int currentLine;
		
		Map(){
		
			currentLine = 0;
			
		}
		
		void addLine(string toAdd){
			
			for(int i = 0; i < MAP_WIDTH; i++)
				innerMap[currentLine][i] = toAdd[i];
			currentLine++;
			
		}
		
		void debug(){
			
			for(int i = 0; i < MAP_HEIGHT; i++){
				for(int j = 0; j < MAP_WIDTH; j++){
					cout << innerMap[i][j];
				}
				cout << endl;
			}
			
		}
		
		int countTrees(int mright, int mbot){
		
			int treeCount = 0;
			
			int pointerX = 0;
			int pointerY = 0;
			
			do{
				
				if(innerMap[pointerY][pointerX] == '#') {
					treeCount++;
				}
				
				pointerX += mright;
				if(pointerX >= MAP_WIDTH)
					pointerX = pointerX - MAP_WIDTH;
				pointerY += mbot;
			
			}while(pointerY < MAP_HEIGHT);
			
			return treeCount;
		
		}
		
};

int main(){
	
	ifstream input("input");
	
	Map *m = new Map();

	if (input.is_open()){
		string tmp;
		while ( getline (input,tmp) ){
			
			m->addLine(tmp);
			
		}
		input.close();
	}
	
	
	
	int trees11 = m->countTrees(1,1);
	int trees31 = m->countTrees(3,1);
	int trees51 = m->countTrees(5,1);
	int trees71 = m->countTrees(7,1);
	int trees12 = m->countTrees(1,2);
	
	//m->debug();
	
	unsigned int total = trees11 * trees31 * trees51 * trees71 * trees12;
	
	cout << "Trees (P1): " << to_string(trees31) << endl;
	cout << "Multiplied (P2):" << to_string(total) << endl;
	
	return 0;
	
}