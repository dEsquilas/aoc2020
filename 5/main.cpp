#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;


class Seat{

	public:
		string data;
		int col;
		int row;
		int id;

		Seat(string input){
			data = input;

			int rangeMin = 0;
			int rangeMax = 127;

			for(int i = 0; i < 6; i++){

				int intervalRange = (rangeMax - rangeMin + 1) / 2;

				if(data[i] == 'F'){

					rangeMax = rangeMin + intervalRange - 1;

				}
				if(data[i] == 'B'){

					rangeMin = rangeMin + intervalRange;

				}

			}

			if(data[6] == 'F')
				row = rangeMin;
			if(data[6] == 'B')
				row = rangeMax;

			rangeMin = 0;
			rangeMax = 7;

			for(int i = 7; i < 9; i++){

				int intervalRange = (rangeMax - rangeMin + 1) / 2;

				if(data[i] == 'L'){

					rangeMax = rangeMin + intervalRange - 1;

				}
				if(data[i] == 'R'){

					rangeMin = rangeMin + intervalRange;

				}

			}

			if(data[9] == 'L')
				col = rangeMin;
			if(data[9] == 'R')
				col = rangeMax;

			id = col + row * 8;

			cout << "Row: " << row << " Col: " << col  << " Id: " << id << endl;

		}

};

class Plane{

	public:
		vector<Seat> seats;
		Plane(){

		}

		void addSeat(Seat s){

			seats.push_back(s);

		}

		bool idExists(int id){

			for(auto c: seats){
				if(c.id == id)
					return true;
			}

			return false;

		}

		int searchEmptyId(int min, int max){

			for(int i = min + 1; i < max; i++){
				if(!idExists(i)){
					cout << "Not found" << i << endl;
				}
			}

			return 0;

		}

};

int main(){

	ifstream input("input");
	int maxID = 0;
	int minID = 999;

	Plane *p = new Plane();

	if (input.is_open()){
		string tmp;
		while ( getline (input,tmp) ){

			Seat *s = new Seat(tmp);
			if(s->id > maxID)
				maxID = s->id;

			if(s->id < minID)
				minID = s->id;

			p->addSeat(*s);

		}

		input.close();
	}

	p->searchEmptyId(minID, maxID);

	cout << "Max ID (P1): " << maxID << endl;
	cout << "Min ID (P2): " << minID << endl;

	return 0;

}