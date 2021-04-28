#include<iostream>
#include<fstream>
#include<set>
#include<vector>
#include<algorithm>

#define REP(i,n) for (int i = 1; i <= n; i++)
using namespace std;

set<string> wordList[26];
set<string> foundWords;
string inputArray[5][5];

bool visit[5][5];
int dx[] = {-1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};
int dy[] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};

int getIndex(char ch)
{
	return ch - 'a';
}

void preProcess()
{
	cout<<"preprocessing..."<<endl;
	string word;
	ifstream word_file("corncob_lowercase.txt");
	
	while(word_file>>word)
	{
		int index = getIndex(word[0]);

		wordList[index].insert(word);
	}
	
	word_file.close();
	
	cout<<"preprocessing done"<<endl;
}

void reset()
{
	REP(i , 26) REP(j , 26) visit[i][j] = false;
}

void dfs(int i , int j , string word)
{
	visit[i][j] = true;
	int index = getIndex(word[0]);
	if(wordList[index].find(word) != wordList[index].end())
	{
		foundWords.insert(word);
	}
	
	if(foundWords.size() > 50) return;
	
	REP(index , 8)
	{
		int x = i + dx[index-1];
		int y = j + dy[index-1];
		
		if(x >= 1 && x <= 4 && y >= 1 && y <= 4 && visit[x][y] == false)
		dfs(x , y , word + inputArray[x][y]);
	}
	visit[i][j] = false;
}

bool comp(string a , string b)
{
	return a.size() > b.size();
}

int main()
{
	preProcess();
	
	int code = 1;
	
	while(code)
	{
		foundWords.clear();
		
		REP(i , 4) REP(j , 4) cin>>inputArray[i][j];
		
		REP(i , 4) REP(j , 4) {
			reset();
			dfs(i , j , inputArray[i][j]);
		}
		
		cout<<foundWords.size()<<endl;
		cout<<endl<<endl<<"printing words"<<endl;
		
		vector<string> res;
		for(string word : foundWords)
		res.push_back(word);
		
		sort(res.begin() , res.end() , comp);
		
		for(string word : res)
		cout<<word<<endl , res.pop_back();
		
		cout<<"enter 0 for exit"<<endl;
		cin>>code;
	}
	
}

