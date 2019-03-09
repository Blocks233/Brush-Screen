#include <cstdio>
#include <Windows.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
int num,Time,ForNum;
int FileMod;
string Data;
bool CopyToClipboard(const char*);
int main(){
	system("color fc") ;
	while(1){
	printf("请选择模式:\n1.文字模式(刷屏特定文字)\n2.文件/图片模式(需要先将待刷屏的文件/图片写入剪切板)\n3.TXT模式(从Input.txt读取刷屏数据，每个数据以#结束)\n");
	scanf("%d",&num);
	if(num==1)FileMod=0;
	if(num==2)FileMod=1;
	if(num==3)FileMod=2;
	if(FileMod==1) printf("模式=文件/图片模式\n");
	if(FileMod==0) printf("模式=文字模式\n");
	if(FileMod==2) printf("模式=TXT模式\n");
	printf("请输入\n刷屏次数 间隔毫秒数 每个数据循环次数 刷屏数据(以#结束,如使用文件/图片模式则直接输入#)\n"); 
	scanf("%d %d %d ",&num,&Time,&ForNum);//输入前三个数据 
	getline(cin,Data,'#');//输入刷屏数据 
	if(FileMod!=2)printf("刷屏数据 = %s\n",Data.c_str()); 
	const char* data = Data.data();//将输入的string型转换为char*型 
	if(FileMod==0) CopyToClipboard(data);//将data写入到剪切板中 
	ifstream fp("Input.txt");
	int numm;
	if(FileMod==2){
		printf("请选择文件格式:\n1.支持多行，每个数据以#结尾\n2.每个数据一行\n");
		scanf("%d",&numm);
	}
	printf("3秒后开始刷屏...\n");
	Sleep(3000);//延迟3秒 
	for(int i=1;i<=num;i++){
		if(FileMod==2){
			Data="\0";
			if(numm==1) getline(fp,Data,'#');
			if(numm==2) getline(fp,Data);
			
			if(Data.length()==0) {
				printf("正在重新读取...\n");
				fp.clear();
				Data="\0";
				fp.seekg(0,ios::beg);
				if(numm==1) getline(fp,Data,'#');
				if(numm==2) getline(fp,Data);
			}
			const char* data = Data.data();
			CopyToClipboard(data);
			if(numm==1) getline(fp,Data,'\n');
			
		}
		for(int j=0;j<ForNum;j++){//重复ForNum次 

			keybd_event(VK_CONTROL, (BYTE) 0, 0, 0);//按下ctrl键 具体操作为  keybd_event(虚拟按键码, (BYTE) 0, 0, 0); 虚拟按键码可到 https://docs.microsoft.com/zh-cn/windows/desktop/inputdev/virtual-key-codes 查询 
			keybd_event('V', (BYTE)0, 0, 0);//按下V键 
		
			keybd_event('V', (BYTE)0, KEYEVENTF_KEYUP, 0);//放开V键 
   			keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);//放开ctrl键 
   		
		}
   		keybd_event(VK_CONTROL, (BYTE) 0, 0, 0);//按下ctrl键 
		keybd_event(VK_RETURN, (BYTE)0, 0, 0);//按下回车键(默认QQ/TIM发送消息快捷键为 ctrl+Enter 可按需修改) 
		
		keybd_event(VK_RETURN, (BYTE)0, KEYEVENTF_KEYUP, 0);//放开回车键 
   		keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);//放开ctrl键 
   		printf("第%d次刷屏\n",i);  
   		Sleep(Time);//延迟 
	}
	fp.close();
	fp.clear();
	printf("刷屏完毕,");
	system("pause");
	printf("\n");
	}
	return 0;
}

bool CopyToClipboard(const char* pszData)//官方的代码，复制的，pszData为数据 
{
	int nDataLen=Data.length();//nDataLen为数据长度，按需修改 
    if(::OpenClipboard(NULL))
    {
        ::EmptyClipboard();
        HGLOBAL clipbuffer;
        char *buffer;
        clipbuffer = ::GlobalAlloc(GMEM_DDESHARE, nDataLen+1);
        buffer = (char *)::GlobalLock(clipbuffer);
        strcpy(buffer, pszData);
        ::GlobalUnlock(clipbuffer);
        ::SetClipboardData(CF_TEXT, clipbuffer);
        ::CloseClipboard();
        return TRUE;
    }
    return FALSE;
}
