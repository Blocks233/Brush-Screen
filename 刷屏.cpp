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
	printf("��ѡ��ģʽ:\n1.����ģʽ(ˢ���ض�����)\n2.�ļ�/ͼƬģʽ(��Ҫ�Ƚ���ˢ�����ļ�/ͼƬд����а�)\n3.TXTģʽ(��Input.txt��ȡˢ�����ݣ�ÿ��������#����)\n");
	scanf("%d",&num);
	if(num==1)FileMod=0;
	if(num==2)FileMod=1;
	if(num==3)FileMod=2;
	if(FileMod==1) printf("ģʽ=�ļ�/ͼƬģʽ\n");
	if(FileMod==0) printf("ģʽ=����ģʽ\n");
	if(FileMod==2) printf("ģʽ=TXTģʽ\n");
	printf("������\nˢ������ ��������� ÿ������ѭ������ ˢ������(��#����,��ʹ���ļ�/ͼƬģʽ��ֱ������#)\n"); 
	scanf("%d %d %d ",&num,&Time,&ForNum);//����ǰ�������� 
	getline(cin,Data,'#');//����ˢ������ 
	if(FileMod!=2)printf("ˢ������ = %s\n",Data.c_str()); 
	const char* data = Data.data();//�������string��ת��Ϊchar*�� 
	if(FileMod==0) CopyToClipboard(data);//��dataд�뵽���а��� 
	ifstream fp("Input.txt");
	int numm;
	if(FileMod==2){
		printf("��ѡ���ļ���ʽ:\n1.֧�ֶ��У�ÿ��������#��β\n2.ÿ������һ��\n");
		scanf("%d",&numm);
	}
	printf("3���ʼˢ��...\n");
	Sleep(3000);//�ӳ�3�� 
	for(int i=1;i<=num;i++){
		if(FileMod==2){
			Data="\0";
			if(numm==1) getline(fp,Data,'#');
			if(numm==2) getline(fp,Data);
			
			if(Data.length()==0) {
				printf("�������¶�ȡ...\n");
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
		for(int j=0;j<ForNum;j++){//�ظ�ForNum�� 

			keybd_event(VK_CONTROL, (BYTE) 0, 0, 0);//����ctrl�� �������Ϊ  keybd_event(���ⰴ����, (BYTE) 0, 0, 0); ���ⰴ����ɵ� https://docs.microsoft.com/zh-cn/windows/desktop/inputdev/virtual-key-codes ��ѯ 
			keybd_event('V', (BYTE)0, 0, 0);//����V�� 
		
			keybd_event('V', (BYTE)0, KEYEVENTF_KEYUP, 0);//�ſ�V�� 
   			keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);//�ſ�ctrl�� 
   		
		}
   		keybd_event(VK_CONTROL, (BYTE) 0, 0, 0);//����ctrl�� 
		keybd_event(VK_RETURN, (BYTE)0, 0, 0);//���»س���(Ĭ��QQ/TIM������Ϣ��ݼ�Ϊ ctrl+Enter �ɰ����޸�) 
		
		keybd_event(VK_RETURN, (BYTE)0, KEYEVENTF_KEYUP, 0);//�ſ��س��� 
   		keybd_event(VK_CONTROL, (BYTE)0, KEYEVENTF_KEYUP, 0);//�ſ�ctrl�� 
   		printf("��%d��ˢ��\n",i);  
   		Sleep(Time);//�ӳ� 
	}
	fp.close();
	fp.clear();
	printf("ˢ�����,");
	system("pause");
	printf("\n");
	}
	return 0;
}

bool CopyToClipboard(const char* pszData)//�ٷ��Ĵ��룬���Ƶģ�pszDataΪ���� 
{
	int nDataLen=Data.length();//nDataLenΪ���ݳ��ȣ������޸� 
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
