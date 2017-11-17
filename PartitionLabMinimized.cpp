#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long long ULL;
typedef vector<int> VI;
void printVector(VI& input){
    for(int i:input){
        cout<<i<<" ";
    }
}
int decFirstNum(const VI& part){
    if(part.size()==1) return 0;
    for(int i = part.size()-1; i > 0; i--){
        if(part[i]!=1) return i;
    }
    return 0;
}
void pushVector(VI& input,const VI& appended, int start, int end){
    for(int i = start; i < end; ++i){
        input.push_back(appended[i]);
    }
}

VI part_k(int n, ULL k){
    if(!k){
        VI current({n});
    }
    else{
        VI current;
        VI prev = part_k(n,k-1);
        if(decFirstNum(prev)){
            int first = --prev[0];
            current.push_back(first);
            int complement = n - first;
            if(complement>first){
                int k = 1;
                VI appendage = part_k(complement,k);
                while(appendage[0]!=complement){
                    appendage = part_k(complement,++k);
                }
                pushVector(current,appendage,0,appendage.size());
                return current;
            }
            else{
            current.push_back(complement);
            return current;
            }
        }
        else{
            if(prev[prev.size()-2]!=1 && prev.back()==1){
                int sum = prev[prev.size()-2] + prev.back();
                VI appendage({sum-2,2});
                VI part;
                pushVector(part, prev, 0, prev.size()-2);
                pushVector(part,appendage,0,appendage.size());
                return part;
            }
            else{
                int index = decFirstNum(prev);
                VI appendage({prev[index]-1,1});
                VI firstPart, lastPart;
                pushVector(firstPart,prev,0,index);
                pushVector(lastPart,prev,index+1,prev.size()-1);
                pushVector(firstPart,appendage,0,appendage.size());
                pushVector(firstPart,lastPart,0,lastPart.size());
                return firstPart;
            }
        }
    }
}
int main(){
    for(int i = 0; i < 1; i++){
        VI test = part_k(7,i);
        for(int i : test){
            cout<<i<<" ";
        }
        cout<<"\n";
    }
}

