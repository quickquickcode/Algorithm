// 提交编号: 757773927
// 提交时间: 2026-10-30 15:38:26
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
private:
    int trans(string s){
        int result=0;
        int k=1;
        for(int i=s.size()-1;i>=0;i--){
            result += (int) (s[i]-'0')*k;
            k*=10;
        }
        return result;
    }
public:
    int evalRPN(vector<string>& tokens) {
        std::stack<int> st={};
        for(int i=0;i<tokens.size();i++){
            if (t.size() == 1 &&
                (t[0] == '+' || t[0] == '-' || t[0] == '*' || t[0] == '/')) {
                int b=st.top(); st.pop();
                int a=st.top(); st.pop();
                switch(tokens[i][-1]){
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
                st.push(trans(tokens[i]));
            }
        }

        
        return st.top();
    }
};