#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <time.h>
#include <set>

using namespace std;

vector<long long> degree;

bool check(vector<long long>graph[],long long int a, long long int b)
{
     bool mark = false;
     for(long long int i=0;i<graph[a].size();i++)
     {
        if(graph[a][i]==b)
        {
          mark = true;
          break;
        }
     }
     return mark;
}

long long int calculate(long long int n,long long int start) // Function to Calculate the Index of the Node of Largest Index.
{
  long long int index = -1;
  long long int num = -2;
  
  for(long long int i=start;i<n;i++)
  {
     if(degree[i]>num)
     {
        num = degree[i];
        index = i;
     } 
  }
  return index;
}

int main()
{
  srand(time(NULL));
  long long int n,m; // n -> Number of Nodes in the Graph 
  cin >> n >> m;     // m -> Number of Edges in the Graph

  vector<long long>graph[n];

  // Generating Random Graph of 'n' nodes and 'm' edges
  for(long long int i=0;i<m;i++)
  {
     long long int a,b;
     do
     {
        a = rand()%n;
        b = rand()%n;
     } while(a==b || check(graph,a,b));
     graph[a].push_back(b);
     graph[b].push_back(a);
  }

  // PRINTING THE RANDOM GENERATED GRAPH
  for(long long int i=0;i<n;i++)
  {
    cout << i << ": ";
    for(long long int j=0;j<graph[i].size();j++)
    {
        cout << graph[i][j] << " ";
    }
    cout << "\n";      
   }
   
   for(long long int i=0;i<n;i++)
   {
      degree.push_back((graph[i].size()));
   }
   vector<long long>::iterator it;
   vector<long long> seq; 

   long long int l_index = -2; // l_index -> stores the index of the Node which has the largest degree
   set <int> se; // To check if all nodes are burnt or not
   set <int>::iterator it2;
   int arr[n];
   //memset(arr,arr+n,1);
   for(long long int i=0;i<n;i++)
   {
       arr[i]=1;
   }
   long long int b_num=0;
   while(se.size()<n)
   {
      if(se.size()!=0)
      {
         for(it2=se.begin();it2!=se.end();it2++)
         {
             long long int temp1 = *it2;
             if(arr[temp1]==1)
             {
                long long int a = temp1;
                for(long long int i=0;i<graph[a].size();i++)
                {
                    long long int b = graph[a][i];
                     if(se.count(b)==0)
                     {
                        se.insert(b);
                        degree[b]=-1;
                        for(long long int j=0;j<graph[b].size();j++)
                        {
                            if(degree[graph[b][j]]>0)
                            {
                               degree[graph[b][j]]--;
                            }
                        }
                     }
                }
                arr[temp1]=2;
             }
         }
      }
      bool mark = false;
      long long int start = 0;
       
      while(!mark&&start<n)
      { 
         l_index = calculate(n,start);
         if(se.count(l_index)==0)
         {
            se.insert(l_index);
            degree[l_index]=-1;
            seq.push_back(l_index);
            b_num++;
            mark=true;
         }
         else
         {
            start = l_index+1;
         }
      }
   }
   cout << "\n\n";
   cout <<"The Burning Number of the Following Graph with "<< n << " nodes and "<< m <<" edges is : "<< b_num << "\n";
   cout << "The Burning Sequence of the Following Graph is: ";
   for(it=seq.begin();it!=seq.end();it++)
   {
      cout << *it << " ";
   }
   cout << "\n\n";
}
