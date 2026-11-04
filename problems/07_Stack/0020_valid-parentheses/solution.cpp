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