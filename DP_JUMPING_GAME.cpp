
/*
	Question: DP Jumping Game
	https://codeforces.com/blog/entry/93892
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int memo(vector <int> &A, int i, vector <int> &dp, vector <int> &PGE, vector <int> &NGE){
    if(i<0 || i>=A.size())
        return A.size()+1;
    if(dp[i]!=-1)
        return dp[i];
    dp[i]=1+min(memo(A, PGE[i], dp, PGE, NGE), memo(A, NGE[i], dp, PGE, NGE));
    return dp[i];
}

vector <int> findMinSteps(vector <int> &A){
    int i, max_index;
    vector <int> PGE(A.size(), -1), NGE(A.size(), -1), dp(A.size(), -1);
    stack <int> st;
    for(i=0; i<A.size(); i++){
        while(!st.empty() && A[st.top()]<A[i])
            st.pop();
        if(!st.empty())
            PGE[i]=st.top();
        st.push(i);
    }
    while(!st.empty())
        st.pop();
    for(i=0; i<A.size(); i++){
        while(!st.empty() && A[st.top()]<A[i]){
            NGE[st.top()]=i;
            st.pop();
        }
        st.push(i);
    }
    for(i=1, max_index=0; i<A.size(); i++){
        if(A[max_index]<A[i])
            max_index=i;
    }
    dp[max_index]=0;
    for(i=0; i<dp.size(); i++){
        if(dp[i]==-1)
            dp[i]=memo(A, i, dp, PGE, NGE);
    }
    return dp;
}

int main(){
    vector <int> A={5, 1, 3, 2, 7};
    vector <int> ans=findMinSteps(A);
    for(int i=0; i<ans.size(); i++)
        cout<<ans[i]<<" ";
}