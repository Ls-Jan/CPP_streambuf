#include<iostream>
#include<string>
using namespace std;

//继承streambuf：https://www.cnblogs.com/wangshaowei/p/11905831.html
class XJ_Streambuf :public streambuf {
private:
	enum { __size = 10 };//缓冲区大小，一般建议设置1024，毕竟1024字节也就1MB大小，内存不痛不痒
	char __buffer[__size + 1] = { 0 };//缓冲区
public:
	XJ_Streambuf() {
		setbuf(__buffer, __size);
	}

protected://以下全是streambuf类的virtual函数的重写
	int_type overflow(int_type c)override {//缓冲区溢出时要调用sync清空缓冲区
		printf("/");
		sync();//清空缓冲区
		sputn((char*)&c, 1);//把溢出的字符c塞回到缓冲区
		return c;
	}
	int __CLR_OR_THIS_CALL sync()override {//这个是关键，在刷新缓冲区时将被被动调用，表现为输出缓冲区内容+清空缓冲区
		printf(__buffer);
		setbuf(__buffer, __size);
		printf(".");
		return 0;
	}
	streambuf* setbuf(char* s, streamsize n)override {//重置缓冲区
		memset(s, 0, __size);
		setp(s, s, s + n);
		setg(s, s, s + n);
		return this;
	}
};

int main() {
	char str_P[32] = { 0 };//搞份字符串
	char str_Q[32] = { 0 };
	memset(str_P, 'P', 15);
	memset(str_Q, 'Q', 20);

	XJ_Streambuf buf;//字符缓冲区
	cout.rdbuf(&buf);//cout重定向
	cout << str_P << str_Q << endl;
	return 0;
}



