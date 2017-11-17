/*
 A partition of a positive integer n is a monotonically decreasing sequence of
positive integers that sum to n. For a given n, all such sequences are presented in
reverse lexicographic order. For example, if n = 7, the sequence of partitions is
 0: 7
 1: 6 1
 2: 5 2
 3: 5 1 1
 4: 4 3
 5: 4 2 1
 6: 4 1 1 1
 7: 3 3 1
 8: 3 2 2
 9: 3 2 1 1
 10: 3 1 1 1 1
 11: 2 2 2 1
 12: 2 2 1 1 1
 13: 2 1 1 1 1 1
 14: 1 1 1 1 1 1 1
 You are to write the three functions given below. For the above example,
 part_q(7) ==> 15
 part_k(7, 10) ==> {3, 1, 1, 1, 1}
 part_i({3, 1, 1, 1, 1}) ==> 10
 In fact, we should always have
 part_i(part_k(n, k)) == k.
 Your functions should be able to handle n < 417.
*/
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long long ULL;
typedef vector<int> VI;
// How many unrestricted partitions does n have?
<summary>Returns the number of partitions for a positive integer n</summary>
ULL part_q(int n){
    if(n==1) return 1;
    ULL k = 1;
    ULL partK = part_k(n,k).size();
    while(n!=partK){partK= part_k(n,k++);}
    return k;
}
// What is the kth partition of n?
int decFirstNum(const VI& part){ // if true decrement first number in vector by 1
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
        //1. Look at previous partition
        VI current(0);
        //2. Make an empty vector for current partition.
        if(!decFirstNum(prev)){//3. If the previous partition has one element in it or if the last element in that partition is 1.
            current.push_back(--prev[0]);//Then, the first element to push into current should be the previous partition's first element minus one.
            /* This makes sense because
            Consider partition for 4
            4
            31
            22
            21
            1111
            We are forced to decrement the first number one our previous partition reaches one or when we have 4.
            Thought: there does seem to be a case in the 7th partition where the previous partition is 421 and we want 4111 which
            might be fine because there we would want a recursion where our first element is the sub-vector 21 which expands into 111.
            So it makes sense.
            */
            int complement = n-current[0];//Here we store the value of the complement which is the difference between the first element and n.
            /*In the partition for 4.
            4
            31<- here 1 is the complement of 4.
            22
            21
            1111
            */
            if(complement<current[0]) current.push_back(complement);
            //Then if our complement is less than than our first element, then we can move on just push that complement.
            else{//But if we cannot because it most be monotonically decreasing then we must:
                int times = complement/current[0];//calculate the number of time to repeat the complement
                int remainder = complement%current[0];//Calculate the remainder so that we can append that at the end
                /*Thoughts: So I am worried that maybe the remainder is still larger than the first element.
                Let's try to prove that this will never happen:
                So y > x and y/x gives me a remainder that must be less than x.
                if its not less than x  than it is greater but then that means the remainder still contains an x so you need to subtract
                as many x's from the remainder till it is less than x. Conclusion: remainder will never be bigger than current[0]
                */
                VI appended(times,current[0]);//then we append the vector of current[0] y times where y is equal to the variable times
                if(remainder!=0) appended.push_back(remainder);//then we append the remainder at the end and if its equal to 0 we dont append it
                pushVector(current,appended,0,appended.size());//finally append this vector to the current one
            }
            return current;
        }
        else{//4. If the previous partition should not be decremented
            int toExpand = decFirstNum(prev); //Find index of first element from the right which is not 1. We will expand this number.
            //In order to expand, we need to first split the prev array into two parts each separated by the index.
            VI firstHalf(0);//This will keep the left part of the partition.
            VI secondHalf(0);//This will keep the right part.
            int midVal = prev[toExpand]; //this take the value of the element at the index where we will expand
            pushVector(firstHalf,prev,0,midVal);
            pushVector(secondHalf,prev,midVal+1,prev.size());
            //to expand this middle value just create a vector of that midval-- and 1
            VI midexp({--midVal,1});
            pushVector(firstHalf,midexp,0,midexp.size());//now reattach this expanded vector
            pushVector(firstHalf,secondHalf,0,secondHalf.size());//reattach the other half
            return firstHalf;
        }
        return current;
    }
}
// What is the index of the partition p (in reverse lexicographic order)
int sumVector(const VI& v){
    int sum = 0;
    for(int i : v){
        sum += i;
    }
    return sum;
}
bool operator==(VI& a, VI& b){
    if(a.size()!=b.size()) return false;
    int i = 0;
    while(a[i++]==b[i++]);
    return i == a.size();
}
<summary>Returns the index of the partition p in reverse lexicographical order</summary>
ULL part_i(const VI& p){
    int n = sumVector(p);
    int k = 0;
    while(p != part_k(n,k)){k++;}
    return k;
}

int main(){
    VI test = part_k(100,4);
    for(int i : test){
        cout<<i;
    }
    part_q(7);
    part
}
