class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        std::stack<int> st={};
        for(int i=0;i<tokens.size();i++){
            string t=tokens[i];
            if (t.size() == 1 &&
                (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
                int b=st.top(); st.pop();
                int a=st.top(); st.pop();
                switch(tokens[i][0]){
                    case '+':
                        st.push(a+b);
                        break;
                    case '-':
                        st.push(a-b);
                        break;
                    case '*':                    
                        st.push(a*b);
                        break;
                    case '/':                    
                        st.push(a/b);
                        break;
                }
            }
            else {
                st.push(std::stoi(tokens[i]));  
            }
            
        }

        
        return st.top();
    }
};