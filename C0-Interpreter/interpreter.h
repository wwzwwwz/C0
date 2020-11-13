#include<string> 
#include<fstream>
#include<iostream>
#include<vector>
#include<map>
#include<stack>
using namespace std;

const string fct[14]= {
    "LIT","LOD","STO",
    "CAL", "INT","JMP",
    "JPC", "ADD", "SUB",
    "MUL", "DIV", "RED",
    "WRT", "RET",
    };

/* 虚拟机代码结构 */
class Instruction
{
    map<string,int>mappoint; //指令与序号键值映射	
	int stack[500];//栈式数据区,大小500
    int top=0;//栈顶寄存器
	int basic=0;//基址地址
	int p=0;//指向下一条执行的目标程序的地址


public:
    Instruction(string);
    ~Instruction();
    void printline(vector<string>&);
    void excuteInstruction(vector<string>&);
    void lit(int l, int a);
    void lod(int l, int a);
    void sto(int l, int a);
    void cal(int l, int a);
    void Int(int l, int a);
    void jmp(int l, int a);
    void jpc(int l, int a);
    void add(int l, int a);
    void sub(int l, int a);
    void mul(int l, int a);
    void div(int l, int a);
    void red(int l, int a);
    void wrt(int l, int a);
    void ret(int l, int a);
    


};


class Destfile
{
    
    public:
        ifstream path;
        vector <string> file;
        Destfile(string fname);
};

