// 提交编号: 757775059
// 提交时间: 2026-10-30 15:43:24
// 判题结果: Accepted
// 运行时间: 4 ms (击败 25.44%) | 内存: 16.8 MB (击败 56.48%)

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