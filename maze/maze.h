#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

class maze
{
private:
	int rows;
	int cols;
	int begin;
	int end;
	vector<char> map;
public:
	maze()
	{
		rows=0;
		cols=0;
		begin = -1;
		end = -1;
	}
	void parse_board(istream& r)
	{
		r>>rows;
		r>>cols;
		char temp;
		for(int x=0;x<rows*cols;++x)
		{
			r>>temp;
			if(temp == 'B')
				begin = x;
			if(temp == 'E')
				end = x;
			map.push_back(temp);
		}
	}
	void print_board(ostream& w)
	{
		int count=0;
		for(int x=0;x<rows*cols;++x)
		{
			char temp = map[x];
			// if(temp=='-' || temp=='=' || temp=='+')
			// 	w<<' ';
			// else if(temp=='*')
			// 	w<<'-';
			// else
				w<<temp;
			if(count==(cols-1))
			{
				w<<endl;
				count=0;
			}
			else
				count++;
		}
	}
	void run()
	{
		if(begin == -1)
			cout<<"No begin."<<endl;
		else if(end == -1)
			cout<<"No end."<<endl;
		else
			follow_path(begin);
	}
	void follow_path(int spot)
	{

		if(map[spot] == '@')
			return;
		else if(map[spot]!='B'/* && map[spot]!='+'*/)
			map[spot] = '=';

		int n = spot-cols;
		int e = spot+1;
		int w = spot-1;
		int s = spot+cols;
		int numPaths = 0;

		if(map[n] == 'E' || map[e] == 'E' || map[s] == 'E' || map[w] == 'E')
		{
			// tracefinal(spot);
			return;
		}

		if(n>0 && map[n] == '.')
			numPaths++;
		if(e>0 && map[e] == '.')
			numPaths++;
		if(s>0 && map[s] == '.')
			numPaths++;
		if(w>0 && map[w] == '.')
			numPaths++;

		if(numPaths > 1 && map[spot]!='B')
			map[spot] = '+';

		if(numPaths == 0)
		{
			rollback(spot);
		}

		if(n>0 && map[n] == '.')
			follow_path(n);
		if(e>0 && map[e] == '.')
			follow_path(e);
		if(s>0 && map[s] == '.')
			follow_path(s);
		if(w>0 && map[w] == '.')
			follow_path(w);
	}
	void rollback(int spot)
	{
		if(map[spot] != '=')
			return;
		else
		{
			map[spot] = '-';
			int n = spot-cols;
			int e = spot+1;
			int w = spot-1;
			int s = spot+cols;
			if(map[n] == '=')
				rollback(n);
			if(map[e] == '=')
				rollback(e);
			if(map[s] == '=')
				rollback(s);
			if(map[w] == '=')
				rollback(w);
		}
	}
	void tracefinal(int spot)
	{
		int n = spot-cols;
		int e = spot+1;
		int w = spot-1;
		int s = spot+cols;
		if(map[n] == 'B' || map[e] == 'B' || map[s] == 'B' || map[w] == 'B')
		{
			map[spot] = '*';
			return;
		}
		else
		{
			if(map[spot]!='E')
				map[spot] = '*';
			if(n>0 && (map[n] == '=' || map[n] == '+'))
				tracefinal(n);
			if(e>0 && (map[e] == '=' || map[e] == '+'))
				tracefinal(e);
			if(s>0 && (map[s] == '=' || map[s] == '+'))
				tracefinal(s);
			if(w>0 && (map[w] == '=' || map[w] == '+'))
				tracefinal(w);
		}
	}
};