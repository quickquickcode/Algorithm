// 提交编号: 757772077
// 提交时间: 2026-10-30 15:30:15
// 判题结果: Runtime Error
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
            int a=0,b=0;
            switch(tokens[i][-1]){
                case '+':
                    b=st.top(); st.pop();
                    a=st.top(); st.pop();
                    st.push(a+b);
                    break;
                case '-':
                    b=st.top(); st.pop();
                    a=st.top(); st.pop();
                    st.push(a-b);
                    break;
                
                case '*':                    
                    b=st.top(); st.pop();
                    a=st.top(); st.pop();
                    st.push(a*b);
                    break;
                
                case '/':                    
                    b=st.top(); st.pop();
                    a=st.top(); st.pop();
                    st.push(a/b);
                    break;
                default:
                    st.push(trans(tokens[i]));
                    break;

            }
        }
        return st.top();
    }
};