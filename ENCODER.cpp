#include<iostream>   
#include<stack>
#include<string>
#include <sstream> 
#include<vector>     
#include<queue>
#include<math.h>
#include <bits/stdc++.h>

using namespace std;

void space(int x)                                    //printing tabs
{
	for(int i=1;i<=x;i++)
	cout<<"\t";
}
string getString(char x) 
{ 
	string s(1, x); 
 	return s;    
}

string inttostring(int val)                         //convert integer to string
{
	ostringstream str1; 
    str1 << val; 
    string geek = str1.str();
    return geek;
}

int stringtoint(string str)                         //convert sring to integer
{
	stringstream geek(str);
    int x1 = 0; 
    geek >> x1;
    return x1;
}

void string2hexString(char* input, char* output)
{
    int loop;
    int i; 
    i=0;
    loop=0;
    while(input[loop] != '\0')
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    output[i++] = '\0';
}

void convertBinToHex(int binaryNumber)            //convert binary to hexa
{ 
int hex[1000];
  int i = 1, j = 0, rem, dec = 0;
  while (binaryNumber > 0) 
  {
   	rem = binaryNumber % 2;
   	dec = dec + rem * i;
   	i = i * 2;
   	binaryNumber = binaryNumber / 10;
  }
   	i = 0;
  while (dec != 0) 
  {
   	hex[i] = dec % 16;
   	dec = dec / 16;
   	i++;
  }
  for (j = i - 1; j >= 0; j--)
  {
   	if (hex[j] > 9) 
   	{
    cout<<(char)(hex[j] + 55);
   	} 
   	else
   	{
    cout<<hex[j];
   	}
  }
}

string decimaltobin(int n)	//decimal to binary
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
for(int i=0;i<5-ss;i++)
{
m+="0";
}
        return m+s;
}

void dtoh(int n)
{
	char hexaDeciNum[100]; 
    int i = 0; 
    while(n!=0) 
    {    
        int temp  = 0; 
        temp = n % 16; 
        if(temp < 10) 
        { 
            hexaDeciNum[i] = temp + 48; 
            i++; 
        } 
        else
        { 
            hexaDeciNum[i] = temp + 55; 
            i++; 
        } 
        n = n/16; 
    } 
    for(int j=i-1; j>=0; j--) 
        cout << hexaDeciNum[j]; 
}

void inttocbor(int value)                                //printing cbor of integer
{
	if(value==0)
		cout<<value<<" ";
	if(value>23 && value<256)
		cout<<18<<" ";
	else if(value>=256 && value<65536)
		cout<<19<<" ";
	else if(value>=65536 && value<pow(2,32))
		cout<<"1A"<<" ";	
	dtoh(value);
	cout<<"\t# unsigned("<<value<<")"<<endl;
}

void stringtocbor(string str, string opr, int x)
{
	string append;
	int len;
	if(str=="00")
		len=1;
	else	
		len=str.size();
	if(opr=="^" && len<23)
		append="011";
	else if(opr=="$" && len<23)
		append="010";
	string bindata=decimaltobin(len);
		append=append+bindata;
	int iappend= stringtoint(append);
	if(opr=="^")
	{
		if(len>23 && len<256)
			cout<<78<<" ";
		else if(len>=256 && len<65536)
			cout<<79<<" ";
		else if(len>=65536 && len<pow(2,32))
			cout<<"7A"<<" ";
	}
	else
	{
		if(len>23 && len<256)
			cout<<58<<" ";
		else if(len>=256 && len<65536)
			cout<<59<<" ";
		else if(len>=65536 && len<pow(2,32))
			cout<<"5A"<<" ";
	}	
	convertBinToHex(iappend);
	if(opr=="^")
		cout<<"\t# text("<<len<<")"<<endl;
	else
		cout<<"\t# bytes("<<len<<")"<<endl;
	space(x);
	cout<<"\t";
	if(str=="00" && opr=="$")
		cout<<"00"<<"\t# $"<<str<<"$"<<endl;
	else
	{	
		char hex_str[(len*2)+1];
    	char char_array[len + 1]; 
		strcpy(char_array, str.c_str()); 
		string2hexString(char_array, hex_str);
    	printf(hex_str);
    	if(opr=="^")
			cout<<"\t# ^"<<str<<"^"<<endl;
		else
			cout<<"\t# $"<<str<<"$"<<endl;
	}	
}
void identifyType(string str,int count)          //cbor of type array
{
	string append;
	if(str=="[" && count<23)
		append="100";
	else if(str=="{" && count<23)	
		append="101";
	string bindata=decimaltobin(count);
	append=append+bindata;
	int iappend= stringtoint(append);
	if(str=="[")
	{
		if(count>23 && count<256)
			cout<<98<<" ";
		else if(count>=256 && count<65536)
			cout<<99<<" ";
		else if(count>=65536 && count<pow(2,32))
			cout<<"9A"<<" ";
	}
	else
	{
		if(count>23 && count<256)
			cout<<"B8"<<" ";
		else if(count>=256 && count<65536)
			cout<<"B9"<<" ";
		else if(count>=65536 && count<pow(2,32))
			cout<<"BA"<<" ";
	}
	convertBinToHex(iappend);
	if(str=="[")
		cout<<"\t# array("<<count<<")"<<endl;
	else
		cout<<"\t# map("<<count<<")"<<endl;
} 

int calculatesize(int j,string str)                 //calculate size
{
	int count=0;
	int open=0;
	if(str[j]==']' || str[j]=='}')
		return count;
	for(int i=j;str[i]!='\0';i++)
	{
		if(open==0 && (str[i]==','||str[i]==']'||str[i]=='}'))
			count++;
		if(str[i]=='['||str[i]=='{')
			open++;
		if(str[i]==']'||str[i]=='}')
			open--;
		if(open<0)
			break;
   }
    return count;
}

int main()                                               //main program
{
	queue<string> q;
	int c=0,k=0;
	vector<int> v1;
	string str="[1,[h$00$,11,1],[[1,1,2048],[2,1,{0:true}]],{}]";
	for(int i=0;str[i]!='\0';i++)                      //size vector
	{
		if(str[i]=='['||str[i]=='{')
		{
			int size=calculatesize(i+1,str);
			v1.push_back(size);
		}
	}
	for(int i=0;str[i]!='\0';i++)                      //creating queue
	{
		if(str[i]=='['||str[i]=='{')
		{
			string st= getString(str[i]); 
			q.push(st);
     		}
		else if(str[i]=='^')
		{
  			q.push("^");	
  			i++;
  			string x2="";
   			while(str[i]!='^')
   			{
       			x2+=str[i];
       			i++;
   			}
   			if(x2!="")
    			q.push(x2);	
			string st= getString(str[i]); 
			q.push(st);

		}
		else if(str[i]=='$' || (str[i]=='h' && str[i+1]=='$'))
		{
			q.push("$");	
  			i++;
  			if(str[i]=='$')
  				i++;
   			string x2="";
   			while(str[i]!='$')
   			{
       			x2+=str[i];
       			i++;
   			}
   			if(x2!="")
    			q.push(x2);	
			q.push("$");
		}
		else if(str[i]==':')
		{}
		else
		{	
			string x2="";
   			while(str[i]!=','&& str[i]!=']'&&str[i]!=':'&&str[i]!='}')
   			{
       			x2+=str[i];
       			i++;
   			}
   			if(x2!="")
    			q.push(x2);
    		if(str[i]==']'||str[i]=='}')
			{
				string st= getString(str[i]); 
				q.push(st);
     		}
		}
	}
	int k1=0;
	int x=0;
	
	while(!q.empty())                                       //final traversing
	{
		if(q.front()=="["||q.front()=="{")
   		{
   			space(x);
			x++;
   			identifyType(q.front(),v1[k1++]);
		}
		else if(q.front()=="]"||q.front()=="}")
			x--;
		else if(q.front()=="^"||q.front()=="$")
		{
			space(x);
			string s2=q.front();
			q.pop();
			stringtocbor(q.front(),s2,x);
			q.pop();
		}
		else 
		{
			space(x);
			if(q.front()=="true" || q.front()=="false" || q.front()=="null")
			{
				if(q.front()=="false")
					cout<<"F4"<<"\t"<<"# primitive(20)"<<endl;
				else if(q.front()=="true")
					cout<<"F5"<<"\t"<<"# primitive(21)"<<endl;
				else
					cout<<"F6"<<"\t"<<"# primitive(22)"<<endl;
			}
			else
			{
				int x1= stringtoint(q.front());
				inttocbor(x1);
			}
		}
		q.pop();
	}
	return 0;
}


