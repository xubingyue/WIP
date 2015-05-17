#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <ctime>

using namespace std;

int s[] = {1,2,1,2,12,3,5,1,18,6,12,15,12,8,5,3,12,15,2,1,6,4,6,9,5,4,11,10,5,3,8,12,12,16,1,3,15,3,2,15,14,7,3,6,12,10,2,12,9,4,15};

struct node
{
	node* p;
	node* n;
	int data;
};

int main()
{
	int ta;
	cin>>ta;
	time_t ts,te,dt;
	
	vector<int> ss;
	ts = time(0);
	for(int y=0;y<ta;++y)
	{
		for(int i=0;i<50;++i)
		{
			ss.push_back(s[i]);
		}
		sort(ss.begin(), ss.end());
		ss.clear();
		/*
		for(int i=0;i<50;++i)
		{
			cout<<ss[i]<<",";
		}
		*/
	}
	cout<<endl;
	te = time(0);
	dt = te - ts;
	cout<<dt<<endl;

	//
	vector<vector<int>*> m;
	int n;
	for(int i=0;i<20;++i)
	{
		m.push_back(new vector<int> );
	}
	ts = time(0);
	for(int y=0;y<ta;++y)
	{
		for(int i=0;i<50;++i)
		{
			ss.push_back(s[i]);
		}
		for(int i=0;i<50;++i)
		{
			m[ss[i]]->push_back(ss[i]);
		}
		/*
		for(int i=0;i<20;++i)
		{
			n = m[i]->size();
			for(int j=0;j<n;++j)
			{
				cout<<(*m[i])[j]<<",";
			}
		}
		*/
	}
	cout<<endl;
	te = time(0);
	dt = te - ts;
	cout<<dt<<endl;
	getchar();
	getchar();
	return 0;
}