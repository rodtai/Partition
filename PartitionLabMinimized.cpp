#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long long ULL;
typedef vector<int> VI;
VI part_k(int n, ULL k);
ULL part_q(int n){
    if(n==1) return 1;
    ULL k = 1;
    ULL partK = part_k(n,k).size();
    while(n!=partK){partK= part_k(n,k++);}
    return k;
}
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
        VI part({n});
        return part;
    }
    else{
        VI prev = part_k(n,k-1);
        VI current;
        if(!decFirstNum(prev)){
            current.push_back(--prev[0]);
            int complement = n-current[0];
            if(complement<current[0]) current.push_back(complement);
            else{
                int times = complement/current[0];
                int remainder = complement%current[0];
                VI appended(times,current[0]);
                if(remainder!=0) appended.push_back(remainder);
                pushVector(current,appended,0,appended.size());
            }
            return current;
        }
        else{
            int toExpand = decFirstNum(prev);
            VI firstHalf;
            VI secondHalf;
            int midVal = prev[toExpand];
            pushVector(firstHalf,prev,0,toExpand);
            pushVector(secondHalf,prev,toExpand+1,prev.size());

            VI midexp = part_k(midVal,1);
            pushVector(firstHalf,midexp,0,midexp.size());
            pushVector(firstHalf,secondHalf,0,secondHalf.size());
            return firstHalf;
        }
    }
}
int main(){
    for(int i = 0; i < 200; i++){
        VI test = part_k(420,i);
        for(int i : test){
            cout<<i<<" ";
        }
        cout<<"\n";
    }
}

