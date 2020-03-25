#include <bits/stdc++.h> 
using namespace std;

int main()
{
    ofstream myfile;
    myfile.open ("keys.txt");
    myfile << "All possible keys are : \n";
    cout<<"All possible keys are : "<<endl;
    string key = "a@cde";
    for(int i=33; i<127; i++)
    {
        key[0] = char(i);
        for(int x=48; x<127; x++)
        {
            key[2] = char(x);
            for(int y=33; y<127; y++)
            {
                int t = 300 -x - y;
                bool check1 = t >= 33;
                bool check2 = t <= 126;
                key[3] = char(y);
                //cout<<"Hi2 : " << char(y) << endl;
                int brek;
                if(check1&&check2)
                {
                    key[4] = char(t);
                    //cout<<"HI";
                    cout<<key<<endl;
                    myfile << key + "\n";
                    
                    //cin>>brek;
                }
            }
        }
    }
    myfile.close();
}