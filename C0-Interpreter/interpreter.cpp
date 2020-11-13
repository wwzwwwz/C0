#include "interpreter.h"
#include <regex>
#include<sstream>
Instruction::~Instruction(){cout << "解释器执行完毕" << endl;}
Instruction::Instruction(string fname)
{
    stack[0]=0;stack[1]=stack[2]=0;//三个静态连、动态连，返回地址设置为零
    for (int i = 0; i < 14;i++)
        mappoint[fct[i]] = i;

    Destfile destfile = Destfile(fname);

    if(destfile.path)
      excuteInstruction(destfile.file);
}

void Instruction::printline(vector<string>& pointline)
{
    regex reg1("(\\s+\\d+\\s+)");
    regex reg2("(\\s+\\d+\\//)");
    smatch match1;
    smatch match2;

    int l, a;//层数及地址
    for (int i = 0; i < pointline.size();i++){
        stringstream t1,t2;
            regex_search(pointline[i], match1, reg1);
            regex_search(pointline[i], match2, reg2);
            t1 << match1[1];
            t1 >> l;
            t2 << match2[1];          
            t2 >> a;

            cout << pointline[i].substr(0, 3) << " " << l <<" "<< a << endl;

    }
}
void Instruction::excuteInstruction(vector<string>& pointline)
{

    printline(pointline);
    regex reg1("(\\s+\\d+\\s+)");
    regex reg2("(\\s+\\d+\\//)");
    smatch match1;
    smatch match2;

    int l, a;//层数及地址
    int choice;

    do
    {
        stringstream t1, t2;
        choice = mappoint[pointline[p].substr(0, 3)];

        regex_search(pointline[p], match1, reg1);
        regex_search(pointline[p], match2, reg2);
        t1 << match1[1];
        t1 >> l;
        t2 << match2[1];
        t2 >> a;
        switch (choice)
        {

        case 0:
            lit(l, a);
            break;
        case 1:
            lod(l, a);
            break;
        case 2:
            sto(l, a);
            break;
        case 3:
            cal(l, a);
            break;
        case 4:
            Int(l, a);
            break;
        case 5:
            jmp(l, a);
            break;
        case 6:
            jpc(l, a);
            break;
        case 7:
            add(l, a);
            break;
        case 8:
            sub(l, a);
            break;
        case 9:
            mul(l, a);
            break;
        case 10:
            div(l, a);
            break;
        case 11:
            red(l, a);
            break;
        case 12:
            wrt(l, a);
            break;
        case 13:
            ret(l, a);
            break;
        }
        p++; //指令寄存器

    } while (p != 0&&p<pointline.size());


}

Destfile::Destfile(string fname)
        {
            string s;
            ifstream destfile = ifstream(fname, ios::in);
            if (!destfile)
                cout << "文件不能打开" <<endl;
                
            else
                while(getline(destfile,s))
                    file.push_back(s);
            
        };











int main(){
    //Instruction a = Instruction();
    string ad;
    cout << ">>>Input target filepath:";
    cin>>ad;
    Instruction i = Instruction(ad);

    system("pause");

}


//LIT 0 a	将常数值取到栈顶，a为常数值
void Instruction::lit(int l, int a)   
{
    top++;
    stack[top] = a;
    
    //cout << "lit:" << endl;
}
//LOD t a	将变量值取到栈顶，a为相对地址，t为层差
/*
 指令 “LOD  L  A”
  将层差为L、偏移量为A的存储单元的值取到栈顶
    T 加 1

 注：层差为L、偏移量为A的存储单元，即沿当前层静
     态链SL开始向前第L层的SL作为基址，加上A，即为该
     单元的地址
*/

void Instruction::lod(int l, int a) 
{
    top++;
        //同层变量位置为基地址+相对地址
        if (!l)
            stack[top] = stack[basic + a];
        //外层变量，位置为0+相对地址
        else
            stack[top] = stack[a];
    
    //cout << "lod:" << endl;
}  

//STO t a	将栈顶内容送入某变量单元中，a为相对地址，t为层数
void Instruction::sto(int l, int a)
{
   
    if(!l)
        stack[basic + a] = stack[top];
    else
        stack[a] = stack[top];

    top--;
    //cout << "sto:" << endl;

} 
//层差为L、偏移量为A的存储单元，即沿当前层
//静态链SL开始向前第L层的SL作为基址，加上A，即为该单元的地址

//CAL0 a	调用函数，a为函数地址
void Instruction::cal(int l, int a)
{

    
    stack[top+1] = basic; //更新DL，存储调用之前的基址
    stack[top+2] = p+1; //更新RA，存储函数调用完毕的返回地址
    basic = top;
    p = a-1;//置指令地址寄存器为a
    //top = top + 2;

    //cout << "cal:" << endl;
} 
//INT 0 a	在运行栈中为被调用的过程开辟a个单元的数据区
void Instruction::Int(int l, int a)
{
    top += a;
    //cout << "Int:" << endl;
}
//JMP 0 a	无条件跳转至a地址      
void Instruction::jmp(int l, int a)
{
    p = a-1;
    //cout << "jmp:" << endl;
} 
//JPC 0 a	条件跳转，当栈顶值为0，则跳转至a地址，否则顺序执行
void Instruction::jpc(int l, int a)
{
    
    if(!stack[top])p=a-1;

    //cout << "jpc:" << endl;

} 
//ADD 0 0	次栈顶与栈顶相加，退两个栈元素，结果值进栈
void Instruction::add(int l, int a)
{
    
    stack[top-1 ] = stack[top - 1] + stack[top];
    top--;
    //cout << "add:" << endl;
}  
//SUB 0 0	次栈顶减去栈顶，退两个栈元素，结果值进栈      
void Instruction::sub(int l, int a)
{
    
    stack[top-1] = stack[top - 1] - stack[top];
    top--;
    //cout << "sub:" << endl;
} 
//MUL 0 0	次栈顶乘以栈顶，退两个栈元素，结果值进栈
void Instruction::mul(int l, int a)
{
    
    stack[top-1] = stack[top - 1] * stack[top];
    top--;
    //cout << "mul:" << endl;
}
//DIV 0 0	次栈顶除以栈顶，退两个栈元素，结果值进栈
void Instruction::div(int l, int a)
{
    
    if(stack[top])
        stack[top-1] = stack[top-1] / stack[top];
    else
        cout << "输入有误！" << endl;
    top--;
    //cout << "div:" << endl;
} 

//RED 0 0	从命令行读入一个输入置于栈顶
void Instruction::red(int l, int a)
{
    top++;
    cout << "Input<<<";
    cin >> stack[top];
    
   // cout << "red:" << endl;
} 
//WRT 0 0	栈顶值输出至屏幕并换行
void Instruction::wrt(int l, int a)
{
    
    cout << "Output>>>" << stack[top] << endl;
    top--;
    //写文件待2添加
    //cout << "wrt:" << endl;
}  

//RET 0 0	函数调用结束后,返回调用点并退栈(PL0:opr 0 0)
      
void Instruction::ret(int l, int a)
{
   
    top = basic; //退栈
    p = stack[basic + 2]-1;//找到调用函数前的p值 要返回的地址为0时程序结束
    basic = stack[basic+1]; //回到引用层基址
  

}