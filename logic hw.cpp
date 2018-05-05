#include<vector>
#include <cstring>
#include<ctype.h>
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std; 
#define a 0
#define b 1
#define c 2
#define d 3

string sol[50];
typedef struct   
{
	int row;
	int col;
}Point;
Point re8[9][8],re4[50][4],re2[85][2],re1[95][1];

class Kmap{
	public:
	Kmap();	
	void exminterm();	
	void check(int);
	void setStr(string);
	void setGraph();
	char getGraph(int,int);
	int logic();
	void find(int,int,int[][4]);
	string getS();
	private:
	vector<string> str;
	int nWeight[5];//¼Æ¦rÅv­« 
	int cnt_graph[16][2];
	int cnt_1;
	bool map[16];
	bool dont_care[16],exist[4];	
	char graph[4][4];
	string s[100];
};
Kmap::Kmap(){
	for(int i=0;i<16;i++){
		map[i]=false;
		dont_care[i]=false;
		exist[i]=false;
	}
	for(int i=0;i<16;i++)
		for(int j=0;j<2;j++)
			cnt_graph[i][j]=0;
	for(int i=0;i<100;i++)
		s[i]=" ";		
	cnt_1=0;		
	nWeight[0]=8;
	nWeight[1]=4;
	nWeight[2]=2;
	nWeight[3]=1;
}
void Kmap::setStr(string s){
	str.push_back(s);
}
void Kmap::exminterm(){
	for(int i=0; i<str.size();i++) 
	{
		int index=0,tmp,length,real_len=0,punct=0;
		char test_char[10];
		length=strlen(str.at(i).c_str());
		strcpy(test_char,str.at(i).c_str());
		for(int i=0 ;i<length; i++)
		{
			switch(test_char[i])
			{
				case 'a':
					index+=8;
					tmp=8;
					exist[a]=true;
					break;
				case 'b':
					index+=4;
					tmp=4;
					exist[b]=true;
					break;
				case 'c':
					index+=2;
					tmp=2;
					exist[c]=true;
					break;
				case 'd':
					index+=1;
					tmp=1;
					exist[d]=true;
					break;
				default:
					if(ispunct(test_char[i]))
						punct++;
						if(test_char[i] != '('&& test_char[i] != ')' )
							index-=tmp;	 
					break;	
			}						
		}
		map[index]=true;
		real_len=length-punct;
		if(real_len < 4) check(index);
		for(int i=0;i<4;i++) exist[i]=false;
		if(test_char[0]=='(' && test_char[length-1]==')')
			dont_care[index]=true;
	}	
}
void Kmap::check(int index)
{
	int cnt=0;
	for(int i=0; i<4 ; i++)
		if(!exist[i]) cnt++;
	if(cnt>=1) 
		for(int i=0; i<4 ; i++)
			if(!exist[i])
				map[index+nWeight[i]]=true;	
	if(cnt>=2)	
		for(int i=0; i<4 ; i++)
			for(int j=i+1;j<4;j++)
				if(!exist[i]&&!exist[j])	
					map[index+nWeight[i]+nWeight[j]]=true;	
	if(cnt==3){
		for(int i=0; i<4 ; i++)
			if(!exist[i])	
				index+=nWeight[i];
		map[index]=true;
	}
}
void Kmap::setGraph()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(dont_care[j*4+i]==true) graph[i][j]='X';
			else if(map[j*4+i]) graph[i][j]='1';
			else if(!map[j*4+i]) graph[i][j]='0';	
	for(int i=0;i<4;i++)			
		swap(graph[i][2],graph[i][3]);
	for(int j=0;j<4;j++)
		swap(graph[2][j],graph[3][j]);		
}
char Kmap::getGraph(int i,int j)
{
	return graph[i][j];
}
int Kmap::logic()
{
	int cnt=0;
	int icnt[4][4]={0};	
	bool t=true;
	
	for(int i=0;i<9;i++)
		for(int j=0;j<8;j++)
		{
			re8[i][j].row=-1;
			re8[i][j].col=-1;
		}
	for(int i=0;i<50;i++)
		for(int j=0;j<4;j++)
		{
			re4[i][j].row=-1;
			re4[i][j].col=-1;
		}
	for(int i=0;i<85;i++)
		for(int j=0;j<2;j++)
		{
			re2[i][j].row=-1;
			re2[i][j].col=-1;
		}
	for(int i=0;i<95;i++)
		for(int j=0;j<1;j++)
		{
			re1[i][j].row=-1;
			re1[i][j].col=-1;
		}
					
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(graph[i][j]!='X'&& graph[i][j]!='1')
				t=false;			
	if(t) {
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++) icnt[i][j]+=1;
		s[cnt]="0";
		return 0;
	}
		
	int k=0;
	while(k <= 3){//¾î¦C8 
		t=true;
		if(k==3)
		{
			int count=0;
			for(int j=0;j<4;j++) 
				if(graph[3][j]!='X'&& graph[3][j]!='1')	t=false;
			for(int j=0;j<4;j++) 
				if(graph[0][j]!='X'&& graph[0][j]!='1')	t=false;
			if(k==3 && t==true)	{
				for(int j=0;j<4;j++){
					icnt[3][j]+=1;
					re8[cnt][count].row=3;
					re8[cnt][count].col=j;
					count++;
				}		
				for(int j=0;j<4;j++){
					icnt[0][j]+=1;
					re8[cnt][count].row=0;
					re8[cnt][count].col=j;
					count++;	
				}
				s[cnt]="d'";
				cnt++;
			}		
		}
		else
		{
			for(int i=k;i<(k+2);i++){
				for(int j=0;j<4;j++){
					if(graph[i][j]!='X'&& graph[i][j]!='1')	
						t=false;
				}				
			}	
			if(t)
			{
				int count=0;
				for(int i=k;i<(k+2);i++){
					for(int j=0;j<4;j++){
						icnt[i][j]+=1;
						re8[cnt][count].row=i;
						re8[cnt][count].col=j;
						count++;
					}
				}
				if(k==0) s[cnt]="c'";
				if(k==1) s[cnt]="d";
				if(k==2) s[cnt]="c";
				cnt++;		
			}	
		}k++;
	}
	
	k=0;
	while(k <= 3){//ª½¦C8 
		t=true;
		if(k==3)
		{
			int count=0;
			for(int i=0;i<4;i++) 
				if(graph[i][3]!='X'&& graph[i][3]!='1')	t=false;
			for(int i=0;i<4;i++) 
				if(graph[i][0]!='X'&& graph[i][0]!='1')	t=false;
			if(k==3 && t==true)	{
				for(int i=0;i<4;i++){
					icnt[i][3]+=1;
					re8[cnt][count].row=i;
					re8[cnt][count].col=3;
					count++;
				}
				for(int i=0;i<4;i++){
					icnt[i][0]+=1;
					re8[cnt][count].row=i;
					re8[cnt][count].col=0;
					count++;
				} 	
				s[cnt]="b'";
				cnt++;
			}	
		}
		else
		{
			for(int j=k;j<(k+2);j++){
				for(int i=0;i<4;i++){
					if(graph[i][j]!='X'&& graph[i][j]!='1')	
						t=false;
				}				
			}
			if(t)
			{
				int count=0;
				for(int j=k;j<(k+2);j++){
					for(int i=0;i<4;i++){
						icnt[i][j]+=1;
						re8[cnt][count].row=i;
						re8[cnt][count].col=j;
						count++;
					}
				}
				if(k==0) s[cnt]="a'";
				if(k==1) s[cnt]="b";
				if(k==2) s[cnt]="a";
				cnt++;
			}	
		}	
		k++;
	}
	
	k=0;	
	while(k<=3)//®ø4­Ó 
	{
		t=true;
		if(k==3)
		{
			for(int j=0;j<2;j++) 
				if(graph[3][j]!='X'&& graph[3][j]!='1' || graph[0][j]!='X'&& graph[0][j]!='1')	t=false;
			if(t==true)	{
				if(icnt[3][0]==0 || icnt[3][1]==0 || icnt[0][0]==0 || icnt[0][1]==0 )
				{
					for(int j=0;j<2;j++){
						icnt[3][j]+=1;
						icnt[0][j]+=1;
					}
					re4[cnt][0].row=3;
					re4[cnt][0].col=0;
					re4[cnt][1].row=3;
					re4[cnt][1].col=1;
					re4[cnt][2].row=0;
					re4[cnt][2].col=0;
					re4[cnt][3].row=0;
					re4[cnt][3].col=1;
					s[cnt]="a'd'";
					cnt++;
				}
			}
			t=true;
			for(int j=1;j<3;j++) 
				if(graph[3][j]!='X'&& graph[3][j]!='1' || graph[0][j]!='X'&& graph[0][j]!='1')	t=false;
			if(t==true)	{
				if(icnt[3][1]==0 || icnt[3][2]==0 || icnt[0][1]==0 || icnt[0][2]==0 )
				{
					for(int j=1;j<3;j++){
						icnt[3][j]+=1;
						icnt[0][j]+=1;
					}
					re4[cnt][0].row=3;
					re4[cnt][0].col=1;
					re4[cnt][1].row=3;
					re4[cnt][1].col=2;
					re4[cnt][2].row=0;
					re4[cnt][2].col=1;
					re4[cnt][3].row=0;
					re4[cnt][3].col=2;
					s[cnt]="bd'";
					cnt++;
				}
			}
			t=true;	
			for(int j=2;j<4;j++) 
				if(graph[3][j]!='X'&& graph[3][j]!='1' || graph[0][j]!='X'&& graph[0][j]!='1')	t=false;
			if(t==true)	{
				if(icnt[3][2]==0 || icnt[3][3]==0 || icnt[0][2]==0 || icnt[0][3]==0 ){
					for(int j=2;j<4;j++){
						icnt[3][j]+=1;
						icnt[0][j]+=1;
					}
					re4[cnt][0].row=3;
					re4[cnt][0].col=2;
					re4[cnt][1].row=3;
					re4[cnt][1].col=3;
					re4[cnt][2].row=0;
					re4[cnt][2].col=2;
					re4[cnt][3].row=0;
					re4[cnt][3].col=3;
					s[cnt]="ad'";
					cnt++;
				}
			}
			t=true;	
			
			if(graph[0][0]!='X'&& graph[0][0]!='1' || graph[0][3]!='X'&& graph[0][3]!='1'
			|| graph[3][0]!='X'&& graph[3][0]!='1' || graph[3][3]!='X'&& graph[3][3]!='1')	t=false;
			if(t==true)	{
				if(icnt[0][0]==0 || icnt[0][3]==0 || icnt[3][0]==0 || icnt[3][3]==0 ){
					icnt[0][0]+=1; icnt[0][3]+=1; icnt[3][0]+=1; icnt[3][3]+=1;
					re4[cnt][0].row=0; re4[cnt][0].col=0;
					re4[cnt][1].row=0; re4[cnt][1].col=3;
					re4[cnt][2].row=3; re4[cnt][2].col=0;
					re4[cnt][3].row=3; re4[cnt][3].col=3;
					s[cnt]="b'd'";
					cnt++;
				}
			}
			t=true;	
			if(graph[0][0]!='X'&& graph[0][0]!='1' || graph[1][0]!='X'&& graph[1][0]!='1'
			|| graph[0][3]!='X'&& graph[0][3]!='1' || graph[1][3]!='X'&& graph[1][3]!='1')	t=false;
			if(t==true)	{
				if(icnt[0][0]==0 || icnt[1][0]==0 || icnt[0][3]==0 || icnt[1][3]==0 ){
					icnt[0][0]+=1; icnt[1][0]+=1; icnt[0][3]+=1; icnt[1][3]+=1;
					re4[cnt][0].row=0; re4[cnt][0].col=0;
					re4[cnt][1].row=1; re4[cnt][1].col=0;
					re4[cnt][2].row=0; re4[cnt][2].col=3;
					re4[cnt][3].row=1; re4[cnt][3].col=3;
					s[cnt]="b'c'";
					cnt++;
				}
			}
			t=true;	
			if(graph[1][0]!='X'&& graph[1][0]!='1' || graph[1][3]!='X'&& graph[1][3]!='1'
			|| graph[2][0]!='X'&& graph[2][0]!='1' || graph[2][3]!='X'&& graph[2][3]!='1')	t=false;
			if(t==true)	{
				if(icnt[1][0]==0 || icnt[1][3]==0 || icnt[2][0]==0 || icnt[2][3]==0 ){
					icnt[1][0]+=1; icnt[1][3]+=1; icnt[2][0]+=1; icnt[2][3]+=1;
					re4[cnt][0].row=1; re4[cnt][0].col=0;
					re4[cnt][1].row=1; re4[cnt][1].col=3;
					re4[cnt][2].row=2; re4[cnt][2].col=0;
					re4[cnt][3].row=2; re4[cnt][3].col=3;
					s[cnt]="b'd";
					cnt++;
				}
			}
			t=true;	
			if(graph[2][0]!='X'&& graph[2][0]!='1' || graph[2][3]!='X'&& graph[2][3]!='1'
			|| graph[3][0]!='X'&& graph[3][0]!='1' || graph[3][3]!='X'&& graph[3][3]!='1')	t=false;
			if(t==true)	{
				if(icnt[2][0]==0 || icnt[2][3]==0 || icnt[3][0]==0 || icnt[3][3]==0 ){
					icnt[2][0]+=1; icnt[2][3]+=1; icnt[3][0]+=1; icnt[3][3]+=1;
					re4[cnt][0].row=2; re4[cnt][0].col=0;
					re4[cnt][1].row=2; re4[cnt][1].col=3;
					re4[cnt][2].row=3; re4[cnt][2].col=0;
					re4[cnt][3].row=3; re4[cnt][3].col=3;
					s[cnt]="b'c";
					cnt++;
				}
			}					
		}
		else
		{
			for(int i=k;i<(k+2);i++)
				for(int j=0;j<2;j++) 
					if(graph[i][j]!='X'&& graph[i][j]!='1')	
						t=false;
			if(t)
			{
				bool zero=false;
				for(int i=k;i<(k+2);i++)
					for(int j=0;j<2;j++)
						if(icnt[i][j]==0) zero=true;
				if(zero){		
					int count=0;
					for(int i=k;i<(k+2);i++){
						for(int j=0;j<2;j++){
							re4[cnt][count].row=i;
							re4[cnt][count].col=j;
							icnt[i][j]+=1;
							count++;
						}
					}
				if(k==0) s[cnt]="a'c'";
				if(k==1) s[cnt]="a'd";
				if(k==2) s[cnt]="a'c";
				cnt++;
				}
			}
			t=true;					
			for(int i=k;i<(k+2);i++)
				for(int j=1;j<3;j++) 
					if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
			if(t)
			{
				bool zero=false;
				for(int i=k;i<(k+2);i++)
					for(int j=1;j<3;j++)
						if(icnt[i][j]==0) zero =true;
				if(zero){		
					int count=0;
					for(int i=k;i<(k+2);i++){
						for(int j=1;j<3;j++) {
							re4[cnt][count].row=i;
							re4[cnt][count].col=j;
							icnt[i][j]+=1;
							count++;
						}
					}
					if(k==0) s[cnt]="bc'";
					if(k==1) s[cnt]="bd";
					if(k==2) {
						s[cnt]="bc";
					}
					cnt++;
				}
			}
			
			t=true;		
			for(int i=k;i<(k+2);i++)
				for(int j=2;j<4;j++) 
					if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
			if(t)
			{
				bool zero=false;
				for(int i=k;i<(k+2);i++)
					for(int j=2;j<4;j++)
						if(icnt[i][j]==0) zero=true;
				if(zero){
					int count=0;
					for(int i=k;i<(k+2);i++)
						for(int j=2;j<4;j++){ 
							re4[cnt][count].row=i;
							re4[cnt][count].col=j;
							icnt[i][j]+=1;
							count++;
						}
					if(k==0) s[cnt]="ac'";
					if(k==1) s[cnt]="ad";
					if(k==2) s[cnt]="ac"; 	
					cnt++;
				}
			}		
		}
		
		t=true;		
		for(int i=0;i<4;i++)
			for(int j=k;j<(k+1);j++) 
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
		if(t)
		{
			bool zero=false;
			for(int i=0;i<4;i++)
				for(int j=k;j<(k+1);j++)
					if(icnt[i][j]==0) zero=true;
			if(zero){
				int count=0;
				for(int i=0;i<4;i++)
					for(int j=k;j<(k+1);j++){ 
						re4[cnt][count].row=i;
						re4[cnt][count].col=j;
						icnt[i][j]+=1;
						count++;
					}
				if(k==0) s[cnt]="a'b'";
				if(k==1) s[cnt]="a'b";
				if(k==2) s[cnt]="ab"; 
				if(k==3) s[cnt]="ab'";	
				cnt++;
			}
		}
		
		t=true;		
		for(int i=k;i<(k+1);i++)
			for(int j=0;j<4;j++) 
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
		if(t)
		{
			bool zero=false;
			for(int i=k;i<(k+1);i++)
				for(int j=0;j<4;j++)
					if(icnt[i][j]==0) zero=true;
			if(zero){
				int count=0;
				for(int i=k;i<(k+1);i++)
					for(int j=0;j<4;j++){ 
						re4[cnt][count].row=i;
						re4[cnt][count].col=j;
						icnt[i][j]+=1;
						count++;
					}
				if(k==0) s[cnt]="c'd'";
				if(k==1) s[cnt]="c'd";
				if(k==2) s[cnt]="cd"; 
				if(k==3) s[cnt]="cd'";	
				cnt++;
			}
		}	
		k++;
	}	
	
	k=0;
	while(k<=3)//2ª½ 
	{
		t=true;
		for(int i=0;i<2;i++)
			for(int j=k;j<(k+1);j++)
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
		if(t)
		{
			bool zero=false;
			for(int i=0;i<2;i++)
				for(int j=k;j<(k+1);j++)
					if(icnt[i][j]==0) zero=true;
			if(zero){
				int count=0;
				for(int i=0;i<2;i++)
					for(int j=k;j<(k+1);j++){
						icnt[i][j]+=1;
						re2[cnt][count].row=i;
						re2[cnt][count].col=j;
						count++;
					} 	
				if(k==0) s[cnt]="a'b'c'";
				if(k==1) s[cnt]="a'bc'";
				if(k==2) s[cnt]="abc'";
				if(k==3) s[cnt]="ab'c'";	
				cnt++;	
			}
		}
			
		t=true;	
		for(int i=1;i<3;i++)
			for(int j=k;j<(k+1);j++)
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;	
		if(t)
		{
			bool zero=false;
			for(int i=1;i<3;i++)
				for(int j=k;j<(k+1);j++)
					if(icnt[i][j]==0) zero=true;
			if(zero){	
				int count=0;
				for(int i=1;i<3;i++)
					for(int j=k;j<(k+1);j++){
						icnt[i][j]+=1;
						re2[cnt][count].row=i;
						re2[cnt][count].col=j;
						count++;
					}
				if(k==0) s[cnt]="a'b'd";
				if(k==1) s[cnt]="a'bd";
				if(k==2) s[cnt]="abd";
				if(k==3) s[cnt]="ab'd";
				cnt++;	
			}
		}
		
		t=true;	
		for(int i=2;i<4;i++)
			for(int j=k;j<(k+1);j++)
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;	
		if(t)
		{
			bool zero=false;
			for(int i=2;i<4;i++)
				for(int j=k;j<(k+1);j++)
					if(icnt[i][j]==0) zero=true;	
			if(zero){
				int count=0;
				for(int i=2;i<4;i++)
					for(int j=k;j<(k+1);j++){
						icnt[i][j]+=1;
						re2[cnt][count].row=i;
						re2[cnt][count].col=j;
						count++;
					} 
				if(k==0) s[cnt]="a'b'c";	
				if(k==1) s[cnt]="a'bc";
				if(k==2) s[cnt]="abc";
				if(k==3) s[cnt]="ab'c";
				cnt++;
			}
		}	
		
		t=true;
		if(graph[3][0]!='X'&& graph[3][0]!='1' || graph[0][0]!='X'&& graph[0][0]!='1' ) t=false;
		if(t)
		{
			if(icnt[3][0] == 0 || icnt[0][0]==0)
			{
				icnt[3][0]+=1; icnt[0][0]+=1;
				re2[cnt][0].row=3; re2[cnt][0].col=0;
				re2[cnt][1].row=0; re2[cnt][1].col=0;
				s[cnt]="a'b'd'";
				cnt++;	
			}
		}
		t=true; 
		if(graph[3][1]!='X'&& graph[3][1]!='1' || graph[0][1]!='X'&& graph[0][1]!='1' ) t=false;
		if(t)
		{
			if(icnt[3][1] == 0 || icnt[0][1]==0){
				icnt[3][1]+=1; icnt[0][1]+=1;
				re2[cnt][0].row=3; re2[cnt][0].col=1;
				re2[cnt][1].row=0; re2[cnt][1].col=1;
				s[cnt]="a'bd'";
				cnt++;	
			}
		}
		t=true; 
		if(graph[3][2]!='X'&& graph[3][2]!='1' || graph[0][2]!='X'&& graph[0][2]!='1' ) t=false;
		if(t)
		{
			if(icnt[3][2] == 0 || icnt[0][2]==0){
				icnt[3][2]+=1; icnt[0][2]+=1;
				re2[cnt][0].row=3; re2[cnt][0].col=2;
				re2[cnt][1].row=0; re2[cnt][1].col=2;
				s[cnt]="abd'";
				cnt++;
			}
		}
		t=true;
		if(graph[3][3]!='X'&& graph[3][3]!='1' || graph[0][3]!='X'&& graph[0][3]!='1' ) t=false;
		if(t)
		{
			if(icnt[3][3] == 0 || icnt[0][3]==0){
				icnt[3][3]+=1; icnt[0][3]+=1;
				re2[cnt][0].row=3; re2[cnt][0].col=3;
				re2[cnt][1].row=0; re2[cnt][1].col=3;
				s[cnt]="ab'd'";
				cnt++;	
			}
		}
		k++;			
	}
	
	k=0;
	while(k<=3)//¾î2 
	{
		t=true;
		for(int i=k;i<(k+1);i++)
			for(int j=0;j<2;j++)
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;	
		if(t)
		{
			bool zero=false;
			for(int i=k;i<(k+1);i++)
				for(int j=0;j<2;j++)
					if(icnt[i][j] == 0) zero=true;
			if(zero){ 
				int count=0;
				for(int i=k;i<(k+1);i++)
					for(int j=0;j<2;j++){
						icnt[i][j]+=1;
						re2[cnt][count].row=i;
						re2[cnt][count].col=j;
						count++;
					}
				if(k==0) s[cnt]="a'c'd'";
				if(k==1) s[cnt]="a'c'd";
				if(k==2) s[cnt]="a'cd";
				if(k==3) s[cnt]="a'cd'";	
				cnt++;
			}
		}
		
		t=true;			
		for(int i=k;i<(k+1);i++)
			for(int j=1;j<3;j++)
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
		if(t)
		{
			bool zero=false;
			for(int i=k;i<(k+1);i++)
				for(int j=1;j<3;j++) 
					if(icnt[i][j]==0 )zero=true;
			if(zero){		
				int count=0;
				for(int i=k;i<(k+1);i++)
					for(int j=1;j<3;j++) {
						icnt[i][j]+=1;	
						re2[cnt][count].row=i;
						re2[cnt][count].col=j;
						count++;
					}
				if(k==0) s[cnt]="bc'd'";
				if(k==1) s[cnt]="bc'd";
				if(k==2) s[cnt]="bcd";
				if(k==3) s[cnt]="bcd'"; 	
				cnt++;	
			}
		}
		
		t=true;			
		for(int i=k;i<(k+1);i++)
			for(int j=2;j<4;j++)
				if(graph[i][j]!='X'&& graph[i][j]!='1')	t=false;
		if(t)
		{
			bool zero=false;
			for(int i=k;i<(k+1);i++)
				for(int j=2;j<4;j++)
					if(icnt[i][j]==0) zero=true;
			if(zero){
				int count=0;
				for(int i=k;i<(k+1);i++)
					for(int j=2;j<4;j++) {
						icnt[i][j]+=1;
						re2[cnt][count].row=i;
						re2[cnt][count].col=j;
						count++;		
					}
				if(k==0) s[cnt]="ac'd'";
				if(k==1) s[cnt]="ac'd";
				if(k==2) s[cnt]="acd";
				if(k==3) s[cnt]="acd'";	
				cnt++;	
			}
		}
		
		t=true;
		if(graph[0][0]!='X'&& graph[0][0]!='1' || graph[0][3]!='X'&& graph[0][3]!='1' ) t=false;
		if(t)
		{
			if(icnt[0][0] ==0 || icnt[0][3] == 0){
				icnt[0][0]+=1;icnt[0][3]+=1;
				re2[cnt][0].row=0; re2[cnt][0].col=0;
				re2[cnt][1].row=0; re2[cnt][1].col=3;
				s[cnt]="b'c'd'";
				cnt++;
			}
		}
		t=true; 
		if(graph[1][0]!='X'&& graph[1][0]!='1' || graph[1][3]!='X'&& graph[1][3]!='1' ) t=false;
		if(t)
		{
			if(icnt[1][0] ==0 || icnt[1][3] == 0)
			{
				icnt[1][0]+=1;icnt[1][3]+=1;
				re2[cnt][0].row=1; re2[cnt][0].col=0;
				re2[cnt][1].row=1; re2[cnt][1].col=3;
				s[cnt]="b'c'd";
				cnt++;			
			}
		}
		
		t=true;
		if(graph[2][0]!='X'&& graph[2][0]!='1' || graph[2][3]!='X'&& graph[2][3]!='1' ) t=false;
		if(t)
		{
			if(icnt[2][0] ==0 || icnt[2][3] == 0){
				icnt[2][0]+=1;icnt[2][3]+=1;
				re2[cnt][0].row=2; re2[cnt][0].col=0;
				re2[cnt][1].row=2; re2[cnt][1].col=3;
				s[cnt]="b'cd";
				cnt++;	
			}
		}
		t=true;
		if(graph[3][0]!='X'&& graph[3][0]!='1' || graph[3][3]!='X'&& graph[3][3]!='1' ) t=false;
		if(t)
		{
			if(icnt[3][0] ==0 || icnt[3][3] ==0 ){
				icnt[3][0]+=1;icnt[3][3]+=1;
				re2[cnt][0].row=3; re2[cnt][0].col=0;
				re2[cnt][1].row=3; re2[cnt][1].col=3;
				s[cnt]="b'cd'";
				cnt++;	
			}
		}							
		k++;				
	}	
	
	for(int i=0;i<4;i++){//³æ1­Ó 
		for(int j=0;j<4;j++){
			if(graph[i][j]=='1'){
				if(icnt[i][j]==0)
				{	
					if(i==0 && j==0) s[cnt]="a'b'c'd'";	
					if(i==0 && j==1) s[cnt]="a'bc'd'";
					if(i==0 && j==2) s[cnt]="abc'd'";
					if(i==0 && j==3) s[cnt]="ab'c'd'";
					if(i==1 && j==0) s[cnt]="a'b'c'd";
					if(i==1 && j==1) s[cnt]="a'bc'd";
					if(i==1 && j==2) s[cnt]="abc'd";	
					if(i==1 && j==3) s[cnt]="ab'c'd";
					if(i==2 && j==0) s[cnt]="a'b'cd";
					if(i==2 && j==1) s[cnt]="a'bcd";
					if(i==2 && j==2) s[cnt]="abcd";	
					if(i==2 && j==3) s[cnt]="ab'cd";
					if(i==3 && j==0) s[cnt]="a'b'cd'";
					if(i==3 && j==1) s[cnt]="a'bcd'";
					if(i==3 && j==2) s[cnt]="abcd'";
					if(i==3 && j==3) s[cnt]="ab'cd'";
					icnt[i][j]+=1;
					re1[cnt][0].row=i; re1[cnt][0].col=j;
					cnt++;	 	
				}
			}
		}
	}

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(icnt[i][j]==1 && graph[i][j]=='1'){
				find(i,j,icnt);	
			}
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(icnt[i][j]>=1 && graph[i][j]=='1'){
				find(i,j,icnt);	
			}																						
}
void Kmap::find(int i_row,int j_col,int icnt[][4])
{
	bool ifind=false,same=false;
	for(int i=0;i<9;i++){
		for(int j=0;j<8;j++){
			if(re8[i][j].row==i_row && re8[i][j].col==j_col){
				for(int k=0;k<50;k++)
					if(s[i] == sol[k]) same=true;		
				if(!same)	sol[cnt_1++]=s[i]; 
				ifind=true;	
			}
			if(ifind) break;
			if(re8[i][j].row==-1) break;
		}
	}
	same=false;
	if(!ifind){
		for(int i=0;i<50;i++){
			for(int j=0;j<4;j++){
				if(re4[i][j].row==i_row && re4[i][j].col==j_col){
					for(int k=0;k<50;k++)
						if(s[i] == sol[k]) same=true;	
					if(!same)	sol[cnt_1++]=s[i]; 
					ifind=true;
				}	
				if(ifind) break;	
				if(re4[i][j].row==-1) break;
			}
		}
	}
	same=false;
	if(!ifind){
		for(int i=0;i<85;i++){
			for(int j=0;j<2;j++){
				if(re2[i][j].row==i_row && re2[i][j].col==j_col)
				{
					for(int k=0;k<50;k++){
						if(s[i] == sol[k]) same=true;
					}	
					if(!same) sol[cnt_1++]=s[i];	
					ifind=true;
				}
				if(ifind) break;		
				if(re2[i][j].row==-1) break;
			}
		}
	}
	same=false;
	if(!ifind){
		for(int i=0;i<95;i++){
			for(int j=0;j<2;j++){
				if(re1[i][j].row==i_row && re1[i][j].col==j_col)
				{
					for(int k=0;k<50;k++)
						if(s[i] == sol[k]) same=true;
					if(!same)	sol[cnt_1++]=s[i];
					ifind=true;
				}
				if(ifind) break;
				if(re1[i][j].row==-1) break;
			}
		}
	}
}

int main(){
	char s[100];
	char *pch;
	Kmap test;
	for(int i=0;i<50;i++) sol[i]=" ";
	
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	if(!fout){
		cerr << "Fail opening" << endl;
		exit(1);
	}
	
	while(!fin.eof()){
		fin.getline(s,sizeof(s));
	}
	pch=strtok(s," +");
	while(pch !=NULL){
		test.setStr(pch);
		pch=strtok(NULL," +");
	}
	test.exminterm();
	fout<<"------K Map------" << endl;
	fout << "  \\AB|" << endl;
	fout << " CD\\ |";
	fout << " 00  01  11  10" << endl;
	test.setGraph();
	for(int i=0;i<4;i++)
	{
		if(i==0) fout << " 00  | ";
		if(i==1) fout << " 01  | ";
		if(i==2) fout << " 11  | ";
		if(i==3) fout << " 10  | ";
		for(int j=0;j<4;j++)
			fout << test.getGraph(i,j) << "   ";
		fout<<endl;
	}	
	test.logic();
	fout << "F(A,B,C,D)= ";
	for(int i=0;i<50;i++){
		if(sol[i]!= " "){
			fout << sol[i];
		}
		if(sol[i+1] !=" ")
			fout << "+";
		else break;	
	}
	return 0;
}	
	


