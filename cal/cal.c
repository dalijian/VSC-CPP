
double add(double,double);
double sub(double,double);
double mul(double,double);
double div(double,double);

double(*oper_func[])(double,double);
// 转换表 就是 一个 函数 指针 数组 
double(*oper_func[])(double,double){
    add,sub,mul,div
}
//open_func[0] 指向 add
//open_func[0](op1,op2) 相当于 调用 add(op1,op2);
result=oper_func[0](op1,op2);
