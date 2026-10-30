// 提交编号: 757770658
// 提交时间: 2026-10-30 15:24:06
// 判题结果: Compile Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class Solution {
private:
    int trans(string s){
        int result=0;
        int k=1;
        for(int i=0;i<s.size();i++){
            result += (int) (s[i]-"0")*k;
            k*=10;
        }
        return result;
    }
public:
    int evalRPN(vector<string>& tokens) {
        std::stack<int> st={};
        for(int i=0;i<tokens.size();i++){
            int a=0,b=0;
            switch(tokens[i]){
                case "+":
                    b=st.pop();
                    a=st.pop();
                    st.push(a+b);
                    break;
                case "-":
                    b=st.pop();
                    a=st.pop();
                    st.push(a-b);
                    break;
                
                case "*":                    
                    b=st.pop();
                    a=st.pop();
                    st.push(a*b);
                    break;
                
                case "/":                    
                    b=st.pop();
                    a=st.pop();
                    st.push(a/b);
                    break;
                default:
                    st.push(trans(tokens[i]));
            }
        }
        return st.pop();
    }
};