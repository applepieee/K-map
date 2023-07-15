#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define eight_block_size 8
#define four_block_size 24
#define two_block_size 32

char table[16];//rec table is 1 or ' ' or X
bool one_blocks[16];//rec one blocks have been visied or not;true : visited
int count[16];//rec the number of the times which blocks(contain 1) have been visited
int binary[16][4];
char* prime_implicant[20];
int prime_implicant_size;//rec prime_implicant's size
char* essential_prime_implicant[20];
int essential_implicant_size;//rec essential_prime_implicant's size
int index_two,index_four,index_eight;
void handle_binary(int num)
{
    if(num==0)
        binary[0][0]=binary[0][1]=binary[0][2]=binary[0][3]=0;
    else
    {
        int index=3;
        int tmp=num;
        while(num > 0)
        {
            binary[tmp][index--]=num%2;
            num/=2;
        }
    }    
}
int is_num(int number)
{
    return (number>=0 && number <=9)?1:-1;
}
void handle_str(char* str,int *index,int *arr)
{
    char *ptr;
    for(ptr=str;*ptr != '\0'; ptr++)
    {   
        if(*ptr !=' ' && *ptr !=',')
        {
            int number=*ptr-'0';
            if(is_num(number)==1)
            {
                int past_number=*(ptr-1)-'0';
                if(is_num(past_number)==1)
                    arr[--*index]*=10;
                arr[*index]+=number;
                *index+=1;  
            }
        }
    }
}
int handle_blocks(int arr[][8],int rec_index[],int arr_size,int size)
{
    int index=0;
    bool at_least_one_block_count_zero;
    for(int i=0;i< arr_size;i++)
    {
        int circle=1; 
        at_least_one_block_count_zero=false;
        for(int j=0;j<size;j++)
        {
            if(table[arr[i][j]]!='1' && table[arr[i][j]]!='X')//every block has to be 1 or don't care
            {
                circle=0;
                break;
            }
            if(table[arr[i][j]]=='1' && count[arr[i][j]]==0)//at least one block hasn't been visited
                at_least_one_block_count_zero=true;  
        }
        if(circle==1 &&  at_least_one_block_count_zero==true)
            rec_index[index++]=i;    
    }
    for(int i=0;i< index;i++)
        for(int j=0;j<size;j++)
            count[arr[rec_index[i]][j]]+=1;
    for(int i=0;i<index;i++)//del invalid index
    {
        bool at_least_one_block_count_one=false;
        for(int j=0;j<size;j++)
            if(table[arr[rec_index[i]][j]]=='1' && count[arr[rec_index[i]][j]]==1)//at least one block hasn't been visited
            {
                at_least_one_block_count_one=true;
                break;
            }
    } 
    return index;
}

void transalte_to_str(int result,int number,char** arr)
{
    char str1[5]="",str2[5]="",str3[5]="",str4[5]="";
    char *dest=(char*)malloc(sizeof(char)*10);
    memset(dest,'\0',sizeof(dest));
    for(int i=0;i<4;i++)
    {
        if(binary[result][i]==1)
        {
            if(i==0)
            {
                if(binary[number][i]==1)
                    str1[0]='A';
                else
                {
                    str1[0]='A';str1[1]=39 ;
                }   
                str1[2]='\0';
            }
            else if(i==1)
            {
                
                if(binary[number][i]==1)
                    str2[0]='B';
                else
                {
                    str2[0]='B';str2[1]=39 ;
                }    
                str2[2]='\0';
            }
            else if(i==2)
            {
                
                if(binary[number][i]==1)
                    str3[0]='C';
                else
                {
                    str3[0]='C';str3[1]=39 ;
                }   
                str3[2]='\0';
            }
            else if(i==3)
            {
                
                if(binary[number][i]==1)
                    str4[0]='D';
                else
                {
                    str4[0]='D';str4[1]=39 ;
                }   
                str4[2]='\0'; 
            }         
        }
    }
    strcat(dest,str1);
    strcat(dest,str2);
    strcat(dest,str3);
    strcat(dest,str4);
    (arr==prime_implicant)?(arr[prime_implicant_size++]=dest):(arr[essential_implicant_size++]=dest);
    
}
void handle_single_blocks(int *num_one,int index_one)
{
   for(int i=0;i<index_one;i++)
   {
        if(count[num_one[i]]==0)
        {
            transalte_to_str(15,num_one[i],prime_implicant);//15="1111"
            transalte_to_str(15,num_one[i],essential_prime_implicant);
        }

   }

}  
void handle_translate(int* rec_2blocks_index,int two_blocks[][8],int *rec_4blocks_index,int four_blocks[][8],int *rec_8blocks_index,char eight_blocls_prime_implicant[][10],
char **arr,int *arr_size) 
{
    int result;
    for(int i=0;i< index_two;i++)
    {
        if(rec_2blocks_index[i] !=-1)//consider del blocks
        {
            result=two_blocks[rec_2blocks_index[i]][0]^ two_blocks[rec_2blocks_index[i]][1];
            transalte_to_str(15-result,two_blocks[rec_2blocks_index[i]][1],arr);

        }
    }

    for(int i=0;i< index_four;i++)
    {
        if(rec_4blocks_index[i] !=-1)//consider del blocks
        {

            int r1=four_blocks[rec_4blocks_index[i]][0]^ four_blocks[rec_4blocks_index[i]][1];
            int r2=four_blocks[rec_4blocks_index[i]][0]^ four_blocks[rec_4blocks_index[i]][2];
            int r3=four_blocks[rec_4blocks_index[i]][0]^ four_blocks[rec_4blocks_index[i]][3];
            int result=(15-r1)&(15-r2) & (15-r3);
            transalte_to_str(result,four_blocks[rec_4blocks_index[i]][1],arr);
        }
    }
    for(int i=0;i< index_eight;i++)
    {
        if(rec_8blocks_index[i] !=-1)//consider del blocks
           arr[(*arr_size)++]=eight_blocls_prime_implicant[rec_8blocks_index[i]];
    }

}

int main()
{
    memset(table,'0',sizeof(table));//init table
    int num_one[16],num_d[16];//rec one's index ;rec dc's index 
    int v;
    int table_index[4][4]={{0,4,12,8},{1,5,13,9},{3,7,15,11},{2,6,14,10}}; //table index
    memset(num_one,0,sizeof(num_one));
    memset(num_d,0,sizeof(num_d));
    char str1[50],str2[50],str3[50];
    
    gets(str1);
    gets(str2);
    gets(str3);

    int index_one=0,index_d=0;
    char *str[3]={str1,str2,str3};
    for(int i=0;i<3;i++)
    {
        if(*(str[i]+1)=='m')//one number
        {
            handle_str(str[i],&index_one,num_one);   
        }
        else if(*(str[i]+1)=='d')//dont care
        {
           handle_str(str[i],&index_d,num_d);
        }
        else if(*(str[i]+1)=='v')
            v=*(str[i]+3);
    }
    for(int i=0;i<index_one;i++)
    {
        table[num_one[i]]='1';
        one_blocks[num_one[i]]=true;// true: haven't visited
    }
    for(int i=0;i<index_d;i++)
        table[num_d[i]]='X';  
    for(int i=0;i<16;i++)//initial arr binary
        handle_binary(i);
    //handle 16 blocks 
    if(index_d+index_one == 16)
    {
        printf("==========Kmap==========\n");
        printf("   \\AB|                |\n");
        printf("  CD\\ | 00  01  11  10 |\n");
        for(int i=0;i<4;i++)
        {
            if(i==0) printf("   00 |  ");
            else if(i==1) printf("   01 |  ");
            else if(i==2) printf("   11 |  ");
            else printf("   10 |  ");
            for(int j=0;j<4;j++)
                printf("%c | ",table[table_index[i][j]]);
            printf("\n");    
        }
        printf("prime implicant: ");
        printf("1");
        printf("\nessential prime implicant: ");
        printf("1");
        printf("\nF(A,B,C,D)=");
        printf("1");
    }
    else
    {
        //handle 8 blocks         
        int rec_8blocks_index[eight_block_size];
        memset(rec_8blocks_index,-1,sizeof(rec_8blocks_index));
        int eight_blocks[eight_block_size][8]
        ={{0,1,2,3,4,5,6,7},{4,12,5,13,7,15,6,14},{12,13,15,14,8,9,11,10},
        {0,1,2,3,8,9,10,11},{0,4,12,8,2,6,14,10},{0,4,12,8,1,5,13,9},
        {1,5,13,9,3,7,15,11},{3,7,15,11,2,6,14,10}};
        index_eight=handle_blocks(eight_blocks,rec_8blocks_index,eight_block_size,8);//handle 8 blocks
        char eight_blocls_prime_implicant[8][10]={"A'","B","A","B'","D'","C'","D","C"};

        //handle 4 blocks
        int rec_4blocks_index[four_block_size];
        memset(rec_4blocks_index,-1,sizeof(rec_4blocks_index));
        int four_blocks[four_block_size][8]={{0,1,4,5},{4,12,5,13},{12,13,8,9}
        ,{1,5,3,7},{5,13,7,15},{13,9,15,11},{3,7,2,6},{7,15,6,14},{15,11,14,10}
        ,{0,8,2,10},{0,4,2,6},{4,12,6,14},{12,8,14,10}
        ,{0,1,8,9},{1,3,9,11},{3,2,11,10},{0,4,12,8},{1,5,13,9},{3,7,15,11},{2,6,14,10}
        ,{0,1,3,2},{4,5,7,6},{12,13,15,14},{8,9,11,10}};
        index_four=handle_blocks(four_blocks,rec_4blocks_index,four_block_size,4);//handle 4 blocks

        //handle 2 blocks
        int rec_2blocks_index[two_block_size];
        memset(rec_2blocks_index,-1,sizeof(rec_2blocks_index));
        int two_blocks[two_block_size][8]=
        {{0,4},{4,12},{12,8},{1,5},{5,13}
        ,{13,9},{3,7},{7,15},{15,11},{2,6}
        ,{6,14},{14,10},{0,1},{1,3},{3,2}
        ,{4,5},{5,7},{7,6},{12,13},{13,15}
        ,{15,14},{8,9},{9,11},{11,10},{0,2}
        ,{4,6},{12,14},{8,10},{0,8},{1,9}
        ,{3,11},{2,10}};
        index_two=handle_blocks(two_blocks,rec_2blocks_index,two_block_size,2);//handle 2 blocks

        handle_single_blocks(num_one,index_one);//handle 1 block
    
        

        //translate to string
        handle_translate( rec_2blocks_index,two_blocks,rec_4blocks_index,four_blocks,rec_8blocks_index, eight_blocls_prime_implicant,prime_implicant,&prime_implicant_size) ;
        for(int i=0;i< index_eight;i++)//del invaild eight blocks circle
        {
            bool at_least_one_block_count_one=false;
            if(rec_8blocks_index[i] !=-1)//consider del blocks
            {
                for(int j=0;j<8;j++)
                {
                    if(table[eight_blocks[rec_8blocks_index[i]][j]]=='1' && count[eight_blocks[rec_8blocks_index[i]][j]]==1)
                    {
                        //printf("11111");//t
                        at_least_one_block_count_one=true;break;
                    }
                }
                if(at_least_one_block_count_one==false)
                {
                    for(int j=0;j<8;j++)
                        count[eight_blocks[rec_8blocks_index[i]][j]]--;
                    rec_8blocks_index[i]=-1; 

                }
            }
        }
        for(int i=0;i< index_four;i++)//del invaild four blocks circle
        {
            bool at_least_one_block_count_one=false;
            if(rec_4blocks_index[i] !=-1)//consider del blocks
            {
                for(int j=0;j<4;j++)
                {
                    if(table[four_blocks[rec_4blocks_index[i]][j]]=='1' && count[four_blocks[rec_4blocks_index[i]][j]]==1)
                    {
                        at_least_one_block_count_one=true;break;
                    }
                }
                if(at_least_one_block_count_one==false)
                {
                    for(int j=0;j<4;j++)
                         count[four_blocks[rec_4blocks_index[i]][j]]--;
                    rec_4blocks_index[i]=-1; 
                }
            }
        }
        for(int i=0;i< index_two;i++)//del invaild 2 blocks circle
        {
            bool at_least_one_block_count_one=false;
            if(rec_2blocks_index[i] !=-1)//consider del blocks
            {
                for(int j=0;j<2;j++)
                {
                    if(table[two_blocks[rec_2blocks_index[i]][j]]=='1' && count[two_blocks[rec_2blocks_index[i]][j]]==1)
                    {
                        at_least_one_block_count_one=true;break;
                    }
                }
                if(at_least_one_block_count_one==false)
                {
                    for(int j=0;j<2;j++)
                        count[two_blocks[rec_2blocks_index[i]][j]]--;
                    rec_2blocks_index[i]=-1; 
                }
            }
        }
        handle_translate( rec_2blocks_index,two_blocks,rec_4blocks_index,four_blocks,rec_8blocks_index, eight_blocls_prime_implicant,essential_prime_implicant,&essential_implicant_size) ;
        //print screen
        printf("==========Kmap==========\n");
        printf("   \\AB|                |\n");
        printf("  CD\\ | 00  01  11  10 |\n");
        for(int i=0;i<4;i++)
        {
                if(i==0) printf("   00 |  ");
                else if(i==1) printf("   01 |  ");
                else if(i==2) printf("   11 |  ");
                else printf("   10 |  ");
                for(int j=0;j<4;j++)
                    printf("%c | ",table[table_index[i][j]]);
                printf("\n");    
        }
        printf("prime implicant: ");
        for(int i=0;i<prime_implicant_size;i++)
        {
            printf("%s",prime_implicant[i]);
            if(i!=prime_implicant_size-1)
                printf(" + ");
        }
        printf("\nessential prime implicant: ");
        for(int i=0;i<essential_implicant_size;i++)
        {
            printf("%s",essential_prime_implicant[i]);
            if(i!=essential_implicant_size-1)
                printf(" + ");
        }
        printf("\nF(A,B,C,D)=");
        for(int i=0;i<essential_implicant_size;i++)
        {
            printf("%s",essential_prime_implicant[i]);
            if(i!=essential_implicant_size-1)
                printf(" + ");
        }
    }
    
}