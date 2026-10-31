class Solution {
public:
    string convert(string s, int numRows) {
        string result="";
        // result+=s[0];
        if(numRows==1){
            return s;
        }
        for (int i=0;i<numRows;i++){
            int j=i;
            int times=0;
            int jiao=0;
            while(j<s.size()){
                result+=s[j];
                j = 2*(numRows-1)*(times+1)-j;
                if(j==2*(numRows-1)*(times+1)-j){
                    times++;
                    j=2*(numRows-1)*(times+1)-j;
                }
                times++;
            }
        }
        // int times=s.size()/
        return result;
    }
};

