#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <stack>
#include <queue>
#include <utility>
#include <set> 
#include <cstring>

using namespace std;

// An Array which stores the degree of the respective Node number of the random tree
vector<long long> degree;

long long int myrandom (long long int i) 
{ 
    srand(time(NULL));
    return rand()%(i);
}

long long int calculate(long long int n,long long int start)
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
   /*
      (1) Destination array contains random array of 'n' integers; where n --> number of nodes
      (2) Pop one element from Destination array and push into Source array --> root of the tree
      (3) while(!destination.empty())
          {
             variable1 = random element from Source array.
             variable2 = Destination.top()
	       
             Add the edge between (variable1, variable2)
             Source.push( variable2)
          }
   */
   long long int n; //n -> 'n' denotes the number of nodes
   cin >> n;
   
   vector<long long> src; //Source array
   vector<long long> dst; //Destination array
   
   for(long long int i=0;i<n;i++)
   {
       dst.push_back(i);
   }
   random_shuffle(dst.begin(),dst.end(),myrandom); // to generate a random permutation of elements in destination array
 
   vector<long long> tree[n]; 
   
   src.push_back(dst[0]); // root of the tree
   long long int index = 1; 
   
   while(index!=n)
   {
      srand(time(NULL));
      long long int random_index = rand()%index;
      tree[src[random_index]].push_back(dst[index]);
      tree[dst[index]].push_back(src[random_index]);
      long long int next = dst[index];
      src.push_back(dst[index]);
      index++;
   }
  
   //DISPLAYING THE RANDOM TREE GENERATED OF 'N' NODES
   for(long long int i=0;i<n;i++)
   {
      cout << i << ": ";
      for(long long int j=0;j<tree[i].size();j++)
      {
         cout << tree[i][j] << " ";
      }
      cout << "\n";      
   }
   
   for(long long int i=0;i<n;i++)
   {
      degree.push_back((tree[i].size()));
   }

   vector<long long>::iterator it;
   vector<long long> seq; //A vector to store the burning sequence of the Random Generated Tree

   long long int l_index = -2; //Initialized a variable to store the index of the largest degree Node in the Tree
   set <int> se;
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
                for(long long int i=0;i<tree[a].size();i++)
                {
                    long long int b = tree[a][i];
                     if(se.count(b)==0)
                     {
                        se.insert(b);
                        degree[b]=-1;
                        for(long long int j=0;j<tree[b].size();j++)
                        {
                            if(degree[tree[b][j]]>0)
                            {
                               degree[tree[b][j]]--;
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

   cout << "\n" <<"The Burning Number of the Following Graph: "<< b_num << "\n";
   cout << "The Burning Sequence of the Following Graph is: ";
   for(it=seq.begin();it!=seq.end();it++)
   {
      cout << *it << " ";
   }
   cout << "\n\n";
}