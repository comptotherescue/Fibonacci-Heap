//////////////////////////////////////////////////////////////////////////////////
/*
* Author : Aditya Kulkarni
* UFID : 8961-9482
* Description: This Program is for DuckduckGo Search engine,
* where ?? most popular keywords are at any given time is calculated.
*/
#include <iostream>
#include<sstream>
#include <string.h>
#include <fstream>
#include <map>
#include <limits.h>
#include<vector>
#include<map>
#include<stdlib.h>
using namespace std;
//Class for node structure
class Fib
{
public:
	int m_iDegree, m_iData;
	Fib * m_pChild;
	Fib * m_pLeftsib;
	Fib* m_pRightsib;
	Fib * m_pParent;
	bool m_bChildcut;

	Fib(int a_idata)
	{
		m_iDegree = 0;
		m_iData = a_idata;
		m_pChild = NULL;
		m_pLeftsib = this;
		m_pRightsib = this;
		m_pParent = NULL;
		m_bChildcut = false;
	}
};
//Class for Fibonacci operations
class Fibops
{
	Fib *m_pMax;
public:
	Fibops()
	{
		m_pMax = NULL;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: IncreaseKey
	Desciption: Function to Increase frequence of words
	returns: void
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	void IncreaseKey(Fib *key, int a_iVal)
	{
		Fib* k;
		key->m_iData += a_iVal;
		//Check if the value is greater than it's parent
		if (NULL == key->m_pParent)
		{
			if (m_pMax->m_iData < key->m_iData)
			{
				m_pMax = key;
			}
			return;
		}
		if (key->m_pParent->m_iData < key->m_iData)
		{
			do
			{
				if (key->m_pRightsib == key)
				{ 
					key->m_pParent->m_pChild = NULL;
				}
				else
				{
					key->m_pParent->m_pChild = key->m_pRightsib;
					key->m_pLeftsib->m_pRightsib = key->m_pRightsib;
					key->m_pRightsib->m_pLeftsib = key->m_pLeftsib;
				}
				//Make childcut boolean true
				key->m_pParent->m_bChildcut = true;
				key->m_pParent->m_iDegree -= 1;
				m_pMax->m_pRightsib->m_pLeftsib = key;
				key->m_pRightsib = m_pMax->m_pRightsib;
				m_pMax->m_pRightsib = key;
				key->m_pLeftsib = m_pMax;
				if (m_pMax->m_iData < key->m_iData)
				{
					m_pMax = key;
				}
				k = key->m_pParent;
				key->m_pParent = NULL;
				key = k;
			} while (NULL != key->m_pParent && key->m_pParent->m_bChildcut == true); // check if parent's childcut is true
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: Insert
	Desciption: Used to insert new nodes to heap
	returns: pointer to the inserted node
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Fib* Insert(int a_ival)
	{
		Fib *node = new Fib(a_ival);
		
		if (m_pMax != NULL)
		{
			if (m_pMax->m_pLeftsib == m_pMax) {
				m_pMax->m_pLeftsib = node;
				node->m_pRightsib = m_pMax;
				node->m_pLeftsib = m_pMax;
				m_pMax->m_pRightsib = node;
			}
			else {
				m_pMax->m_pRightsib->m_pLeftsib = node;
				node->m_pRightsib = m_pMax->m_pRightsib;
				node->m_pLeftsib = m_pMax;
				m_pMax->m_pRightsib = node;
			}
			if (m_pMax->m_iData < a_ival) {
				m_pMax = node;
			}
		}
		else
		{
			m_pMax = node;
		}
		return node;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: GetMax
	Desciption: Get function for Max node
	returns: Pointer to max node
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Fib* getMax()
	{
		return m_pMax;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: RemoveMax
	Desciption: Removes the max node from heap and does pairwise combine nodes
	returns: pointer to removed node
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Fib* RemoveMax()
	{
		map<int, Fib*> l_pTreet;
		map<int, Fib*>::iterator it;
		int max = INT_MIN;
		Fib *q, *p, *l_pMax = NULL;
		q = m_pMax->m_pChild;
		//make parent pointer of all children of removed node NULL
		if (q != NULL)
		{
			do
			{
				q->m_pParent = NULL;
				q = q->m_pRightsib;
			} while (q != m_pMax->m_pChild && q != q->m_pRightsib);
			m_pMax->m_pChild->m_pLeftsib->m_pRightsib = m_pMax->m_pRightsib;
			m_pMax->m_pRightsib->m_pLeftsib = m_pMax->m_pChild->m_pLeftsib;
			m_pMax->m_pChild->m_pLeftsib = m_pMax;
			m_pMax->m_pRightsib = m_pMax->m_pChild;
			m_pMax->m_pChild = NULL;
			m_pMax->m_iDegree = 0;
		}
		q = m_pMax->m_pRightsib;
		vector<Fib*> Vec;
		map<int, Fib*>::iterator itr;
		Vec.clear();
		while (q != m_pMax)
		{
			Vec.push_back(q);
			q = q->m_pRightsib;
		}
		//Remove links for each node
		for (int i = 0; i < Vec.size(); i++)
		{
			Vec[i]->m_pLeftsib = Vec[i];
			Vec[i]->m_pRightsib = Vec[i];
		}
		Fib*y, *x;
		for (int i = 0; i<Vec.size(); i++)
		{
			it = l_pTreet.find(Vec[i]->m_iDegree);
			while (it != l_pTreet.end()) {
				if (Vec[i]->m_iData > it->second->m_iData)
				{
					y = Vec[i];
					x = it->second;
					x->m_pLeftsib->m_pRightsib = x->m_pRightsib;
					x->m_pRightsib->m_pLeftsib = x->m_pLeftsib;
					if (y->m_pChild == NULL)
					{
						x->m_pRightsib = x;
						x->m_pLeftsib = x;
						y->m_pChild = x;
						x->m_pParent = y;
						y->m_iDegree = y->m_iDegree + 1;
					}
					else
					{
						x->m_pLeftsib = y->m_pChild;
						y->m_pChild->m_pRightsib->m_pLeftsib = x;
						x->m_pRightsib = y->m_pChild->m_pRightsib;
						y->m_pChild->m_pRightsib = x;
						x->m_pParent = y;
						y->m_iDegree = y->m_iDegree + 1;
					}
				}
				else {
					x = Vec[i];
					y = it->second;
					if (y->m_pChild == NULL)
					{
						x->m_pRightsib = x;
						x->m_pLeftsib = x;
						y->m_pChild = x;
						x->m_pParent = y;
						y->m_iDegree += 1;
					}
					else
					{
						x->m_pLeftsib = y->m_pChild;
						y->m_pChild->m_pRightsib->m_pLeftsib = x;
						x->m_pRightsib = y->m_pChild->m_pRightsib;
						y->m_pChild->m_pRightsib = x;
						x->m_pParent = y;
						y->m_iDegree += 1;
					}
					Vec[i] = y;
				}
				l_pTreet.erase(it);
				it = l_pTreet.find(Vec[i]->m_iDegree);
			}
			if (it == l_pTreet.end())
			{
				l_pTreet.insert({ Vec[i]->m_iDegree,Vec[i] });
			}

		}
		itr = l_pTreet.begin();
		itr->second->m_pRightsib = itr->second;
		itr->second->m_pLeftsib = itr->second;
		l_pMax = itr->second;
		while (itr != l_pTreet.end())
		{
			l_pMax = Consolidate(l_pMax, itr->second);
			itr++;
		}
		Fib* t = m_pMax;
		m_pMax = l_pMax;
		return t;
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: Consolidate
	Desciption: Used to meld two nodes
	returns: pointer to the Max node
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////
	Fib* Consolidate(Fib* m, Fib* n)
	{
		if (m->m_pRightsib == n)
		{
			m->m_pLeftsib = n;
			n->m_pLeftsib = m;
			m->m_pRightsib = n;
			m->m_pRightsib = m;
		}
		else
		{
			m->m_pRightsib->m_pLeftsib = n;
			n->m_pRightsib = m->m_pRightsib;
			m->m_pRightsib = n;
			n->m_pLeftsib = m;
		}
		if (n->m_iData > m->m_iData)
		{
			return n;
		}
		return m;
	}

};
int main(int argc,char* argv[])
{
	//check if input file is present
	if (argc == 2)
	{
		map<string, Fib*> words;
		map<string, Fib*>::iterator itr;
		vector<pair<string, Fib*>> pairs;
		map<Fib*, string> heapmap;
		map<Fib*, string>::iterator itr2;
		bool l_bIsword = false;
		Fibops *Fibop = new Fibops();
		ofstream myfile;
		string strline, line, name;
		//output file
		myfile.open("output_file.txt");
		ifstream file(argv[1]);
		while (file)
		{
			l_bIsword = false;
			if (!getline(file, strline))
			{
				break;
			}
			istringstream line2(strline);
			while (line2)
			{

				if ((!getline(line2, line, ' ')))
				{
					break;
				}

				if (line[0] == '$')
				{
					name = line.substr(1, line.size() - 1);
					l_bIsword = true;
				}
				else if (l_bIsword)
				{
					int data = atoi(line.c_str());
					itr = words.find(name);
					if (itr == words.end())
					{
						Fib* q;

						q = Fibop->Insert(data);
						words.insert({ name,q });
						heapmap.insert({ q,name });
					}
					else
					{

						Fibop->IncreaseKey(itr->second, data);
					}
				}
				else if (line == "stop")
				{
					myfile.close();
					exit(1);
				}
				else
				{
					int h = atoi(line.c_str());


					for (int i = 0; i < h; i++)
					{   
						//Removes max from heap
						Fib* q = Fibop->RemoveMax();
						itr2 = heapmap.find(q);
						myfile << itr2->second;
						if (i != h - 1)
						{
							myfile << ",";
						}
						pairs.push_back(make_pair(itr2->second, itr2->first));
					}
					for (int j = 0; j < pairs.size(); j++)
					{
						words.erase(pairs[j].first);
						heapmap.erase(pairs[j].second);
						Fib* temp = Fibop->Insert(pairs[j].second->m_iData);
						words.insert({ pairs[j].first,temp });
						heapmap.insert({ temp,pairs[j].first });
					}
					pairs.clear();
					myfile << "\n";
				}
			}

		}
	}
	else
	{
		cout << "Invalid parameters";
	}
	return 0;
}

