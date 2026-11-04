// 提交编号: 758606801
// 提交时间: 2026-11-04 18:16:57
// 判题结果: Accepted
// 运行时间: 0 ms (击败 100.00%) | 内存: 8.9 MB (击败 36.46%)

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
                    if(st.empty()){
                        return false;
                    }
                    if(st.top()!='('){
                        return false;
                    }
                    st.pop();
                    break;
                case '[':
                    st.push(s[i]);
                    break;
                case ']':    
                    if(st.empty()){
                        return false;
                    }
                    if(st.top()!='['){
                        return false;
                    }
                    st.pop();
                    break;
                case '{':
                    st.push(s[i]);
                    break;
                case '}':
                    if(st.empty()){
                        return false;
                    }
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