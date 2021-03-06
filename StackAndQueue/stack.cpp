#include <iostream>
#include <stack>
using namespace std;

int main() {
	int t;
	cin >> t;
	int i;
	while (t--)
	{
	    cin >> i;
	    int arr[i];
	    for (int j = 0; j < i; j++)
	        cin >> arr[j];
	    
	    stack<int> st;
	    st.push(-1);
	    for(int k = 0; k < i; k++)
	    {
	        while (st.top() != -1 && arr[k] > arr[st.top()])
	            st.pop();
	        st.push(k);
	    }
	    
        int ans[st.size()];
	    for (int i = 0; i < st.size(); i++)
	    {
	        ans.push_back(arr[st.top()]);
	        st.pop();
	    }
	    
	    for (int i = 0; i < ans.size(); i++)
	        cout << ans[i] << " ";
	    
	    cout << endl;
	}
	return 0;
}