#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

#include <thread>
#include <future>
#include <chrono>


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
		
		
		double getChildOptions(map<int, Node> nodemap){
			
			double total = 0;
			
			if(childIds.size() == 0){
				
				return 1;
				
			}else{
				
				for(auto id: childIds){
					
					Node tmpnode = nodemap[id];
					int tmp = tmpnode.getChildOptions(nodemap);
					
					total += tmp;
					
				}
				
				
				return total;
				
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
	
	
	//double plist = nodeList[0].getChildOptions(nodeList);
	
	map<int, double> paths;
	
	paths[0] = 1;
	
	for(int i = 1; i < nodeList.size(); i++){
		
		paths[i] = 0;
		
	}
	
	for(int i = 0; i < nodeList.size(); i++){
		
		for(auto id: nodeList[i].childIds){
		
			paths[id] += paths[i];
		
		}
		
	}
	
	cout << "Differencs Jolt 1 Per Jolt 3 (P1): " << joltDiff[1] * joltDiff[3] << endl;
	cout << fixed << "Total Options (P2): " << paths[nodeList.size() - 1] << endl;
	
	return 0;
	
}