import java.util.*;
import java.lang.*;
import java.io.*;

class stack {
    public static Scaner scn = new Scanner(System.in);

    public static void main (String[] args) {
	int t = scn.nextInt();
	int i;
	while (t--)
	{
	    i = scn.nextInt();
	    int[] arr = new int[i];
	    for (int j = 0; j < i; j++)
	        arr[j] = scn.nextInt();
	    
	    Stack<Integer> st = new Stack<>();
	    st.push(-1);
	    for(int k = 0; k < i; k++)
	    {
	        while (st.top() != -1 && arr[k] > arr[st.top()])
	            st.pop();
	        st.push(k);
	    }
	    
        int[] ans = new int[st.size()];
	    for (int i = 0; i < st.size(); i++)
	    {
	        ans.add(arr[st.top()]);
	        st.pop();
	    }
	    
	    for (int i = 0; i < ans.size(); i++)
	        cout << ans[i] << " ";
	    
	    cout << endl;
	}
	return 0;
	}
}