#include<iostream>
#include<string>
using namespace std;

int lengthOfLongestSubstring(string s) {
        int visited[256];
        string str = s;
        
        for(int i=0;i<256;i++)
            visited[i] = -1;
            
        int n = str.length();
        int max_len = 0;
        int cur_len = 0;
        int cur_pos = 0;
        
        for(int i=0;i<n;i++){
            int index = str[i];
            if(visited[index]==-1||visited[index]<cur_pos){
                cur_len++;
                
            }
            else{
                cur_pos = visited[index]+1;
				cur_len = i-cur_pos+1;
            }
            max_len = (cur_len>max_len)?cur_len:max_len;
            visited[index] = i;
        }
        
        return max_len;
        
    }

int main(){
	string str;
	cin>>str;
	cout<<lengthOfLongestSubstring(str);

}