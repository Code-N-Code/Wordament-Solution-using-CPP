#include<iostream>
#include<fstream>
#include<set>

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
	
	REP(index , 4)
	{
		int x = i + dx[index];
		int y = j + dy[index];
		
		if(x >= 1 && x <= 4 && y >= 1 && y <= 4 && visit[x][y] == false)
		dfs(x , y , word + inputArray[x][y]);
	}
	visit[i][j] = false;
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
		
		for(string word : foundWords)
		cout<<word<<endl;
		
		cout<<"enter 0 for exit"<<endl;
		cin>>code;
	}
	
}


