#include<bits/stdc++.h>
using namespace std;

int hops;
int p;

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

string xorOperation(string a, string b)
{
    string xor_string = "";
    int n = b.length();
  
    for(int i = 1; i < n; i++)
    {
        if (a[i] == b[i])
            xor_string += "0";
        else
            xor_string += "1";
    }
    return xor_string;
}
 
string divOperation(string dividend, string divisor)
{
    int div_len = divisor.length();
    string temp = dividend.substr(0, div_len);
    int n = dividend.length();
     
    while (div_len < n)
    {
        if (temp[0] == '1')
            temp = xorOperation(divisor, temp) + dividend[div_len];
        else
            temp = xorOperation(std::string(div_len, '0'), temp) +
                  dividend[div_len];
        div_len += 1;
    }
  
    if (temp[0] == '1')
        temp = xorOperation(divisor, temp);
    else
        temp = xorOperation(std::string(div_len, '0'), temp);  
    return temp;
}
 
bool checkEncodedData(string appended_data, string key)
{
    // int key_length = key.length();
    // string appended_data = (data + std::string(key_length - 1, '0'));
    // cout<<"Appended data before: "<<appended_data<<"\n";

    for(int i=0;i<hops;i++){
        int randomNumber=random(0, appended_data.length()); // random bit position
        int randomprob=random(0,100); 
        // cout<<"Random prob is:   "<<randomprob<<"\n";
        // cout<<"Random location is: "<<randomNumber<<"\n";

        if(randomprob>=p){
            if(appended_data[randomNumber]=='1'){
              appended_data[randomNumber]='0'; 
            }else{
              appended_data[randomNumber]='1';
            }
        }
    } 

    // cout<<"Appended data after:  "<<appended_data<<"\n";
    string remainder = divOperation(appended_data, key);
    
    for(int i=0;i<remainder.length();i++){
        if(remainder[i]=='1'){
           return false;
        }
    }
    return true;
}


string encodedData(string data, string key)
{
    int key_length = key.length();
    string appended_data = (data + std::string(key_length - 1, '0'));
    string remainder = divOperation(appended_data, key);
    string codeword = data + remainder;
    //cout << "\nRemainder : "<< remainder << "\n";
    // cout << "Encoded Data (Data + Remainder) :"<< codeword << "\n";
    return codeword;
}
  

int main()
{
    string data;
    cout<<"Enter data 32 bits or more: ";
    cin>>data;

    int rno = random(0,100);
    int len = data.length(), rem;
    
    if(len >= 32 ) {
       if(len % 16 != 0){
            rem = len % 16;
            for(int i=0; i<16-rem; i++){
                data += "0";
            }
       }
    }
    else{
        cout<<"Data word length must be 32 or more!"<<"\n";
         return 0;
    }


    cout<<"Enter the number of hops 1 or 2: ";
    cin>> hops;

    cout<<"Enter the Proability: ";
    cin >> p;
    cout<<"\n";


    cout<<"Original Data Length: "<<len<<"\tAppended Data length: "<< data.length()<<"\n";
    string key = "100000111";

    for(int i=0; i<data.length(); i+=16) {
        string dword = data.substr(i,16);
        string encodedDword = encodedData(dword,key);
        
        // cout<<"Dataword length"<< dword.length()<<"\n"<<"Encoded Data Word: "<<encodedDword.length()<<"\n";

        bool answer=checkEncodedData(encodedDword,key);
        if(answer){
            cout<<"\ni is: "<<i<<"\nDiscard"<<endl;
        }
        else{
            cout<<"\ni is: "<<i<<"\nData is: "<<dword<<endl;
        }
        cout<<"\n";
    }
    return 0;
}

// 10101010101111010110101011100001010101010101001101010101111
