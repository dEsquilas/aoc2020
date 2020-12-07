#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

class Question{

	public:
		string data;
		Question(){

			data = "";

		}

		void addData(string add){

			data.append(add);

		}

		int countDifferent(){

			vector<char> found;

			for(int i = 0; i < data.size(); i++)

				if(find(found.begin(), found.end(), (char)(data[i])) == found.end())
					found.push_back(data[i]);

			return found.size();

		}

		void debug(){

			cout << data << endl;

		}

};

class QuestionGroup{

	public:
		vector<string> personAnswer;
		vector<char> totalQuestions;
		QuestionGroup(){

		}

		void addPersonAnswer(string s){
			personAnswer.push_back(s);
		}

		int peopleSayYes(){

			int questionYes = 0;

			generateDifferentQuestions();

			for(auto q: totalQuestions){
				int count = 0;
				for(auto p: personAnswer) {
					if (didPersonSayYes(q, p))
						count++;
				}
				if(count == personAnswer.size())
					questionYes++;
			}

			return questionYes;

		}

		bool didPersonSayYes(char question, string answer){

			return answer.find(question) != string::npos;

		}


		void generateDifferentQuestions(){

			for(auto p: personAnswer){
				for(int i = 0; i < p.size(); i++)
					if(find(totalQuestions.begin(), totalQuestions.end(), (char)(p[i])) == totalQuestions.end())
						totalQuestions.push_back(p[i]);
			}

		}


};

int main(){

	ifstream input("input");

	vector<Question> questions;
	vector<QuestionGroup> qgs;

	if (input.is_open()){
		string tmp;
		Question *q = new Question();
		QuestionGroup *qg = new QuestionGroup();
		while ( getline (input,tmp) ){

			if(tmp.size() > 0) {
				q->addData(tmp);
				qg->addPersonAnswer(tmp);
			}else{
				questions.push_back(*q);
				qgs.push_back(*qg);
				q = new Question();
				qg = new QuestionGroup();
			}

		}

		questions.push_back(*q);
		qgs.push_back(*qg);

		input.close();
	}

	int sum1 = 0;

	for(auto q: questions) {
		sum1 += q.countDifferent();
	}

	int sum2 = 0;

	for(auto q: qgs){
		sum2 += q.peopleSayYes();
	}

	cout << "Count (p1): " << sum1 << endl;
	cout << "Count (p2): " << sum2 << endl;


	return 0;

}