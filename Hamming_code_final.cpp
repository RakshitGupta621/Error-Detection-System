#include <bits/stdc++.h>
using namespace std;

int random(int min, int max) 
{
   static bool first = true;
   if (first) 
   {  
      srand( time(NULL) ); 
      first = false;
   }
   return min + rand() % (( max + 1 ) - min);
}

void tokenise(vector<int> recdata){
   
   int c, c1, c2, c3, i;
   vector<int> data(7,0);

   data[0]=recdata[0];
   data[1]=recdata[1];
   data[2]=recdata[2];
   data[4]=recdata[3];
    
                            
    data[6] = data[0] ^ data[2] ^ data[4];
    data[5] = data[0] ^ data[1] ^ data[4];
    data[3] = data[0] ^ data[1] ^ data[2];

    cout <<"\nEncoded data is: ";
    for (i = 0; i < 7; i++)
        cout << data[i];
    cout<<endl;
    float p;
    cout<<"Enter the Proability: ";
    cin >> p;
    vector<int> vt;
    for(int i=0;i<7;i++){
        int rno = random(0,100);
        if (rno >= p){
            data[i]=data[i]^1;
            vt.push_back(i);
        }
    }
    
    c1 = data[6] ^ data[4] ^ data[2] ^ data[0];
    c2 = data[5] ^ data[4] ^ data[1] ^ data[0];
    c3 = data[3] ^ data[2] ^ data[1] ^ data[0];

    c = c3 * 4 + c2 * 2 + c1;

    if (c == 0)
    {
        cout << "No error while transmission of data"<<endl;
        cout<<data[0]<<" "<<data[1]<<" "<<data[2]<<" "<<data[4];
    }
    else{
        cout <<"Data received: ";
        for (i = 0; i < 7; i++)
            cout << data[i];
        cout<<endl;    
        if(vt.size()==1){
            cout<<"Error on position: "<<c<<endl;
        }
        else{
           cout<<"Multiple errors! "<<endl; 
           for(int i=0;i<vt.size();i++){
              cout<<"Error at location: "<<vt[i]<<"\n";
           }   
        }
        
        for(int i=0;i<vt.size();i++){
            data[vt[i]]=data[vt[i]]^1;
        } 
        cout << "Actual Data: ";
        cout<<data[0]<<" "<<data[1]<<" "<<data[2]<<" "<<data[4];
    }
    cout<<"\n";
}

int main()
{
    cout<<"\nEnter the size of data: ";
    int size;
    cin>>size;
    vector<int> data(size,0);
    
    if(size>=16){
        if(size % 4 != 0){
                int rem = size %4;
                for(int i=0; i<4-rem; i++){
                    data.push_back(0);
                }
        }
    }
    else{
        cout<<"Size should be atleast 16!\n";
        return 0;
    }

    for(int i=0;i<size;i++){
        int x;
        cin>>x;
        data[i]=x;
    }

    for(int i=0;i<size;i+=4){
        vector<int> slicedData;
        for(int j=i;j<i+4;j++){
            slicedData.push_back(data[j]);
            
        }
        tokenise(slicedData);
        
    }
    return 0;
}