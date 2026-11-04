// 提交编号: 758655087
// 提交时间: 2026-11-04 22:46:17
// 判题结果: Runtime Error
// 运行时间: N/A (击败 0.00%) | 内存: N/A (击败 0.00%)

class MinStack {
private:
    int min=INT_MAX;
    stack<int> st={};
    // 偷看答案了
    stack<int> st_min={};

public:
    MinStack() {
        // 查了Deepseek C++ 怎么表达int的最大值
        min=INT_MAX;

    }
    
    void push(int value) {
        min = std::min(min, value);
        st.push(value);
        st_min.push(min);
    }
    
    void pop() {
        st.pop();
        st_min.pop();
        min=st_min.top();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */