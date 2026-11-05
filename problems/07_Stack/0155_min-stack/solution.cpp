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
        if(st.empty()){
            min=INT_MAX;
        }
        else{
            min=st_min.top();
        }
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