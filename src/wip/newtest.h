#include<iostream>
void* operator new[](size_t size)  
{  
    std::cout<<"call global new[] size: "<<size<<std::endl;  
    return malloc(size);  
}  
class Time
{
private:
 int hrs,mins,secs;//时,分,秒
public:
 Time(int hrs=19,int mins=35,int secs=20);//默认参数的带参构造函数
 ~Time();//析构函数
 void showTime()const;
 Time operator ++();//重载前缀递增运算符,++x
 Time operator ++(int);//重载后缀递增运算法,x++
 bool operator ==(const Time &)const;//重载相等性运算符
 Time & operator =(const Time &);//重载赋值运算符
 void * operator new(size_t size);//重载new()运算符,如:int * pInt=new int(0);
 void operator delete(void * ptr);//重载delete()运算符,如:delete pInt;
 void * operator new[](size_t size);//重载new[]()运算符,以分配数组
 void operator delete[](void * ptr);//重载delete[]()运算符,以去配数组,释放数组所占内存
};
Time::Time(int hrs,int mins,int secs)
{
 this->hrs=hrs;
 this->mins=mins;
 this->secs=secs;
 std::cout<<"Time类默认参数的带参构造函数 "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl;
}

Time::~Time()
{
 std::cout<<"Time类析构函数 "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl; 
}

void Time::showTime()const
{
 std::cout<<"Time类showTime()const函数 "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl;
}
Time Time::operator ++()//重载前缀递增运算符,++x
{
 secs++;
 if(secs>=60)
 {
  secs=0;
  mins++;
  if(mins>=60)
  {
   mins=0;
   hrs++;
   if(hrs>=24)
   {
    hrs=0;
   }
  }
 }
 return Time(hrs,mins,secs);//返回无名临时对象
}
Time Time::operator ++(int)//重载后缀递增运算法,x++
{
 Time temp(hrs,mins,secs);//生成临时对象,并进行初始化
 ++secs;
 if(secs>=60)
 {
  secs=0;
  mins++;
  if(mins>=60)
  {
   mins=0;
   hrs++;
   if(hrs>=24)
   {
    hrs=0;
   }
  }
 }
 return temp;
}
bool Time::operator ==(const Time & aTime)const//重载相等性运算符
{
 return ((hrs==aTime.hrs)&&(mins==aTime.mins)&&(secs==aTime.secs));
}
Time & Time::operator =(const Time & aTime)//重载赋值运算符
{
 hrs=aTime.hrs;
 mins=aTime.mins;
 secs=aTime.secs;
    std::cout<<"Time类赋值运算符函数 "<<(this->hrs)<<':'<<(this->mins)<<':'<<(this->secs)<<std::endl;
 return (*this);//返回当前对象的引用
}
void * Time::operator new(size_t size)//重载new()运算符,如:int * pInt=new int();
{
 std::cout<<"operator new() is called.Object size is "<<size<<std::endl;
 return malloc(size);//?//在自由存储中分配内存
}
void Time::operator delete(void * ptr)//重载delete()运算符,如:delete pInt;
{
 std::cout<<"operator delete() is called"<<std::endl;
 free(ptr);//在自由存储中释放内存
}
void * Time::operator new[](size_t size)//重载new[]()运算符,以分配数组
{ 
 std::cout<<"operator new[]() is called.Object size is "<<size<<std::endl;
 return malloc(size);//?//在自由存储中分配内存
}
void Time::operator delete[](void * ptr)//重载delete[]()运算符,以去配数组,释放数组所占内存
{ 
 std::cout<<"operator delete[]() is called"<<std::endl;
 free(ptr);//在自由存储中释放内存
}

int main()
{
 Time * pTime;
 pTime=new Time;//重载new()运算符,调用默认构造函数
 pTime->showTime();
 delete pTime;//重载delete()运算符
 pTime=new Time[3];//重载new[]()运算符,以分配数组,调用默认构造函数
 delete [] pTime;//重载delete[]()运算符,以去配数组,释放数组所占内存
 getchar();
 return 0;
}