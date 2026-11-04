// 提交编号: 758606658
// 提交时间: 2026-11-04 18:15:45
// 判题结果: Runtime Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
public:
    bool isValid(string s) {
        stack<char> st={};
        for(int i=0;i<s.length();i++){
            switch(s[i]){
                case '(':
                    st.push(s[i]);
                    break;
                case ')':
                    if(st.top()!='('){
                        return false;
                    }
                    st.pop();
                    break;
                case '[':
                    st.push(s[i]);
                    break;
                case ']':    
                    if(st.top()!='['){
                        return false;
                    }
                    st.pop();
                    break;
                case '{':
                    st.push(s[i]);
                    break;
                case '}':
                    if(st.top()!='{'){
                        return false;
                    }
                    st.pop();
                    break;
            }
        }
        if(st.empty()){
            return true;
        }
        else {
            return false;
        }
    }
};