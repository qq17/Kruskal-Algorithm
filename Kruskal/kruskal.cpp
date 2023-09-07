#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct edge
{
	int a;
	int b;
	int weight;
};

struct disjointset
{
	int parent[50];
	int rank[50];
	vector<string> vertex;
};

int checkvertex(disjointset& s, string name)
{
	for (int i = 0; i < s.vertex.size(); i++)
	{
		if (s.vertex[i] == name)
		{
			return i;
		}
	}
	s.vertex.push_back(name);
	return s.vertex.size()-1;
}

void initializeset(disjointset& s)
{
	for (int i = 0; i < 50; i++)
	{
		s.parent[i] = i;
		s.rank[i] = 0;
	}
}

char findset(disjointset& s, int v)
{
	if (v == s.parent[v])
		return v;
	return s.parent[v] = findset(s, s.parent[v]);
}

void unionsets(disjointset& s, int v1, int v2)
{
	v1 = findset(s, v1);
	v2 = findset(s, v2);
	if (v1 != v2)
	{
		if (s.rank[v1] < s.rank[v2])
		{
			s.parent[v1] = v2;
		}
		else
		{
			s.parent[v2] = v1;
			if (s.rank[v1] == s.rank[v2])
			{
				s.rank[v1]++;
			}
		}
	}
}

void sort(vector<edge> &a)
{
	bool flag = true;
	while (flag)
	{
		flag = false;
		for (int i = 0; i < a.size() - 1; i++)
		{
			if (a[i].weight > a[i + 1].weight)
			{
				flag = true;
				edge tmp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = tmp;
			}
		}
	}
}

int main()
{
	vector<edge> graph;
	vector<edge> mst;
	disjointset djs;

	ifstream input;
	string s, tmp;
	edge e;
	int minweight = 0;

	input.open("C:\\Users\\Master\\Documents\\input.txt");
	if (!input.is_open())
	{
		cout << "error" << endl;
		return 1;
	}
	initializeset(djs);
	while (!input.eof())
	{
		input >> s;
		e.a = checkvertex(djs, s);
		input >> s;
		e.b = checkvertex(djs, s);
		input >> e.weight;
		graph.push_back(e);
	}
	for (auto var : graph)
	{
		cout << djs.vertex[var.a] << " " << djs.vertex[var.b] << " " << var.weight << endl;
	}
	sort(graph);
	for (auto var : graph)
	{
		if (findset(djs, var.a) != findset(djs, var.b))
		{
			unionsets(djs, var.a, var.b);
			mst.push_back(var);
		}
	}

	cout << endl << "minimal tree:" << endl;
	for (auto var : mst)
	{
		cout << djs.vertex[var.a] << " " << djs.vertex[var.b] << " " << var.weight << endl;
		minweight += var.weight;
	}
	cout << endl << "minimal weight: " << minweight << endl;
	input.close();
	return 0;
}