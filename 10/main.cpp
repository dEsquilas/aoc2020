#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>


using namespace std;


class Node{

	public:
		int currentId;
		int currentValue;
		vector<int> childIds;
		vector<int> list;
		Node(int current, vector<int> list){
			this->currentId = current;
			this->list = list;
			
			currentValue = list[currentId];
			
			for(int i = currentId + 1; i < currentId + 4 && i < list.size(); i++){
				
				if(list[i] - currentValue <= 3){
					childIds.push_back(i);
				}
				
			}
			
		}
		
		Node(){
		
		}
		
		vector<vector<int>> getChilds(map<int, Node> nodemap){
			
			vector<vector<int>> list;
			
			if(childIds.size() == 0){
				
				vector<int> tmp;
				tmp.push_back(currentValue);
				list.push_back(tmp);
				return list;
				
			}else{
				
				for(auto id: childIds){
					
					Node tmpnode = nodemap[id];
					vector<vector<int>> tmplist = tmpnode.getChilds(nodemap);
					list.reserve(list.size() + tmplist.size());
					list.insert(list.end(), tmplist.begin(), tmplist.end());
					
				}
				
				for(int i = 0; i < list.size(); i++){
					list[i].push_back(currentValue);
				}
				
				return list;
				
			}
			
		}

};


int main() {
	
	ifstream input("input");
	vector<int> list;
	
	list.push_back(0);
	
	if (input.is_open()) {
		string tmp;
		
		while (getline(input, tmp)) {
		
			list.push_back(stoi(tmp));
			
		}
		
		input.close();
	}
	
	sort(list.begin(), list.end());
	
	for(auto item: list){
		
		cout << item << endl;
	}
	
	int joltDiff[] = {0, 0, 0, 1};
	
	for(int i = 0; i < list.size() - 1; i++){
		
		int diff = list[i+1] - list[i];
		joltDiff[diff]++;
		
	}
	
	for(int i = 0; i < 4; i++){
		cout << "Diff " << i << ": " << joltDiff[i] << endl;
	}
	
	///////////////////////////////////////
	
	map<int, Node> nodeList;
	
	for(int i = 0; i < list.size(); i++){
		
		Node *n = new Node(i, list);
		nodeList[i] = *n;
		
	}
	
	
	cout << endl << endl;
	
	
	/*int cid = 21;
	
	vector<int> childs = nodeList[cid].childIds;
	
	cout << "Current Id: " << cid << " Value: " << nodeList[cid].currentValue << endl;
	
	for(auto child: childs)
		cout << "Id: " << child << " Value: " << nodeList[child].currentValue << endl;
	
	cout << endl << endl;
	cout << endl << endl;
	 
	 */
	
	
	vector<vector<int>> plist = nodeList[0].getChilds(nodeList);
	
	
	
	cout << "Differencs Jolt 1 Per Jolt 3 (P1): " << joltDiff[1] * joltDiff[3] << endl;
	cout << "Total Options (P2): " << plist.size() << endl;
	
	return 0;
	
}