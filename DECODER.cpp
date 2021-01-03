#include<iostream>
#include<stack>
#include<string.h>
#include <sstream> 
#include<vector>
#include<queue>
#include<math.h>
#include <stdio.h>
#include <bitset>

using namespace std;

char strToChar(string data) {						//binary to character conversion
   	bitset<8> temp(data);
    return temp.to_ulong();
}

int binaryToDecimal(int n)                          //binary to decimal
{ 
    int num = n; 
    int dec_value = 0; 
    int base = 1; 
    int temp = num; 
    while (temp) { 
        int last_digit = temp % 10; 
        temp = temp / 10; 
        dec_value += last_digit * base; 
        base = base * 2; 
    } 
    return dec_value; 
} 

int stringtoint(string str)                         //convert string to integer
{
	stringstream geek(str);
    int x1 = 0; 
    geek >> x1;
    return x1;
}

string inttostring(int val)                         //convert integer to string
{
  	ostringstream str1; 
    str1 << val; 
    string geek = str1.str();
    return geek;
}

int hextodec(char *num)                                //hex to decimal
{
int i, r, len, hex = 0;
len = strlen(num);
    for (i = 0; num[i] != '\0'; i++)
    {
        len--;
        if(num[i] >= '0' && num[i] <= '9')
            r = num[i] - 48;
        else if(num[i] >= 'a' && num[i] <= 'f')
                r = num[i] - 87;
        else if(num[i] >= 'A' && num[i] <= 'F')
                    r = num[i] - 55;
        hex += r * pow(16,len);
    }
    return hex;
}

string decimaltobin(long int n)							//decimal to binary
{	
	int binaryNum[32]; 
    int i = 0;
    string s="";
    while (n > 0) { 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
    for (int j = i - 1; j >= 0; j--) 
    {
   		string geek = inttostring(binaryNum[j]);
        s+=geek;
	}
		int ss=s.size();
		string m="";
	for(int i=0;i<8-ss;i++)
	m+="0";
    return m+s;
}

string htob(string str)
{
string j="";
int value;
int len=str.size();
for(int i=0;str[i]!='\0';i=i+2)
{
	string part=str.substr(i,2);
	istringstream ost(part);
	ost >> hex >> value;
	bitset<8> bits(value);
	string binaryString (bits.to_string());
	j=j+binaryString;
}
return j;
}

int main()
{
int flag,size,m=-1,a=-1;
vector<int> vmap,varr;
stack<char> st;
string str="84 01 83 41 00 0B 01 82 83 01 01 19 0800 83 02 01 A1 00 F5 A0";
for(int i=0;str[i]!='\0';i++) {
    string s="";
    while(str[i]!=' '&& str[i]!='\0')
	{
		s+=str[i];
		i++;
	}
	if(str[i]=='\0')
		i--;
	int len=s.size();
	char char_array[len + 1]; 
	strcpy(char_array, s.c_str()); 
	string bin=decimaltobin(hextodec(char_array));
	if(bin[0]=='1' && bin[1]=='0' && bin[2]=='1')
	{
		if(m>=0 && st.top()=='{' && vmap[m]%2!=0)
		cout<<":";
		
		cout<<"{";
		if(!varr.empty() && st.top()=='[')
		varr[a]--;
		st.push('{');
		m++;
		bin[0]='0';
		bin[2]='0';
		size=binaryToDecimal(stringtoint(bin));
		if(size>23)
    	{
    		i++;
			string s="";
    		while(str[i]!=' '&& str[i]!='\0')
			{
				s+=str[i];
				i++;
			}
			if(str[i]=='\0')
			i--;
			int len=s.size();
			char char_array[len + 1]; 
			strcpy(char_array, s.c_str()); 
			size=hextodec(char_array);
		}
		flag=size*2;
		vmap.push_back(flag);
		if(m>=0 && vmap[m]%2==0 && vmap[m]>0 && vmap[m]!=flag)
		cout<<",";
	}
	else if(bin[0]=='1' && bin[1]=='0' && bin[2]=='0')
	{
		if(m>=0 && st.top()=='{' && vmap[m]%2!=0)
		{
			cout<<":";
		}
		bin[0]='0';
    	a++;
    	cout<<"[";
    	if(!vmap.empty() && st.top()=='{')
		vmap[m]--;
		st.push('[');
    	int size=binaryToDecimal(stringtoint(bin));
    	if(size>23)
    	{
    		i++;
			string s="";
    		while(str[i]!=' '&& str[i]!='\0')
			{
				s+=str[i];
				i++;
			}
			if(str[i]=='\0')
			i--;
			int len=s.size();
			char char_array[len + 1]; 
			strcpy(char_array, s.c_str()); 
		    size=hextodec(char_array);	
		}
    	varr.push_back(size);
	}
	else if(bin[0]=='0' && bin[1]=='0' && bin[2]=='0')
	{
	  	if(st.top()=='{')
		{
			if(vmap[m]%2!=0)
				cout<<":";
   			vmap[m]--;	
   			if(binaryToDecimal(stringtoint(bin))>23)
   			{
   				i++;
				string s="";
    			while(str[i]!=' '&& str[i]!='\0')
				{
					s+=str[i];
					i++;
				}
				if(str[i]=='\0')
					i--;
				int len=s.size();
				char char_array[len + 1]; 
				strcpy(char_array, s.c_str()); 
				cout<<hextodec(char_array);
				
			}
			else
				cout<<binaryToDecimal(stringtoint(bin));
   			if(m>=0 && vmap[m]%2==0 && vmap[m]>0)
				cout<<",";
		}
		else
		{
			if(binaryToDecimal(stringtoint(bin))>23)
   			{
   				i++;
				string s="";
    			while(str[i]!=' '&& str[i]!='\0')
				{
					s+=str[i];
					i++;
				}	
			if(str[i]=='\0')
				i--;
			int len=s.size();
			char char_array[len + 1]; 
			strcpy(char_array, s.c_str()); 
			cout<<(hextodec(char_array));
			
			}
			else
				cout<<binaryToDecimal(stringtoint(bin));
       		varr[a]--;
			if(a>=0 && varr[a]>0)	
       			cout<<",";
		}
	}
	else if(bin[0]=='0' && bin[1]=='1' && bin[2]=='1')
	{
		if(st.top()=='{')
		{
			if(vmap[m]%2!=0)
				cout<<":";
   			vmap[m]--;
   		}
   		else
   			varr[a]--;

		bin[1]='0';
		bin[2]='0';
		if(binaryToDecimal(stringtoint(bin))>23)
		{
			i++;
			string s="";
    		while(str[i]!=' '&& str[i]!='\0')
			{
				s+=str[i];
				i++;
			}
			if(str[i]=='\0')
				i--;
		}
		i++;
		string s="";
    	while(str[i]!=' '&& str[i]!='\0')
		{
			s+=str[i];
			i++;
		}
		if(str[i]=='\0')
			i--;
		string bin=htob(s);
		int ss=bin.size();
		string j="";
		if(ss<8)
			ss=(8-ss);
		else
			ss=8-(ss%8);
		for(int i=0;i<ss;i++)
			j+="0";
		bin=j+bin;
		j="";
		for(int x=0;x<bin.length();x+=8)
		{
			string part = bin.substr(x,8);
			j=j+strToChar(part);
		}
		cout<<'"'<<j<<'"';
		if(m>=0 && vmap[m]%2==0 && vmap[m]>0)
			cout<<",";
		if(a>=0 && varr[a]>0)	
       		cout<<",";	
	}
	else if(bin[0]=='0' && bin[1]=='1' && bin[2]=='0')
	{
		if(st.top()=='{')
		{
			if(vmap[m]%2!=0)
				cout<<":";
   			vmap[m]--;
   		}
   		else
   		   	varr[a]--;
		
		bin[1]='0';
		if(binaryToDecimal(stringtoint(bin))>23)
			i++;
		i++;
		string s="";
    	while(str[i]!=' '&& str[i]!='\0')
		{
			s+=str[i];
			i++;
		}
		if(str[i]=='\0')
			i--;
		int len=s.size();
		if(s=="00")
			cout<<"h"<<"'"<<"00"<<"'";	
		else
		{
			char char_array[len + 1]; 
			strcpy(char_array, s.c_str()); 
			string bin=decimaltobin(hextodec(char_array));
			int ss=bin.size();
			string j="";
			if(ss<8)
				ss=(8-ss);
			else
				ss=8-(ss%8);
			for(int i=0;i<ss;i++)
				j+="0";
			bin=j+bin;
			j="";
			for(int x=0;x<bin.length();x+=8)
			{		
				string part = bin.substr(x,x+8);
				j=j+strToChar(part);
			}
			cout<<"h"<<"'"<<j<<"'";
		}
		if(m>=0 && vmap[m]%2==0 && vmap[m]>0)
			cout<<",";
		if(a>=0 && varr[a]>0)	
       		cout<<",";	
	}
	else if(bin[0]=='1' && bin[1]=='1' && bin[2]=='1')
	{
		if(st.top()=='{')
		{
			if(vmap[m]%2!=0)
			cout<<":";
   			vmap[m]--;	
		}		
		else
			varr[a]--;
		if(bin=="11110101")
			cout<<"true";
		else if(bin=="11110100")
			cout<<"false";
		else if(bin=="11110110")
			cout<<"null";
		if(m>=0 && vmap[m]%2==0 && vmap[m]>0)
			cout<<",";
		if(a>=0 && varr[a]>0)	
       		cout<<",";	
	}	
	l1:while(a>=0  && varr[a]==0 && st.top()=='[')
	{		
		cout<<"]";
		st.pop();
		varr.pop_back();
		a--;
		if(a>=0 && varr[a]!=0)
			varr[a]--;
		if(m>=0 && vmap[m]%2==0 && vmap[m]>0 && st.top()=='{')
			cout<<",";
		if(a>=0 && varr[a]>0 && st.top()!='{')	
       		cout<<",";
	}
	while(m>=0  && vmap[m]==0 && st.top()=='{')
	{
		cout<<"}";
		st.pop();
		vmap.pop_back();
		m--;
		if(m>=0)
			vmap[m]--;
		if(m>=0 && vmap[m]%2==0 && st.top()!='{')
			cout<<",";
		goto l1;
	}	
}
	for(int i=0;i<=a;i++)
    	cout<<"]";
	return 0;
}

