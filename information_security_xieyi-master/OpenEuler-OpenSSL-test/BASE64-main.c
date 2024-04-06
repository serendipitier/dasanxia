#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/x509.h>

//Base64编码
void tEVP_Encode()
{
	EVP_ENCODE_CTX *ctx;
    ctx = EVP_ENCODE_CTX_new();				//EVP编码结构体
	unsigned char in[1024];			//输入数据缓冲区
	int inl;						//输入数据长度
	char out[2048]={0};				//输出数据缓冲区
	int outl;						//输出数据长度
	FILE *infp;						//输入文件句柄
	FILE *outfp;					//输出文件句柄

	infp = fopen("test.dat","rb");//打开待编码的文件
	if(infp == NULL)
	{
		printf("Open File \"Test.dat\"  for Read Err.\n");
		return;
	}
	
	outfp = fopen("test.txt","w");//打开编码后保存的文件
	if(outfp == NULL)
	{
		printf("Open File \"test.txt\" For Write Err.\n");
		return;
	}
	EVP_EncodeInit(ctx);//Base64编码初始化
	printf("文件\"Test.dat\" Base64编码后为：\n");
	//循环读取原文，并调用EVP_EncodeUpdate计算Base64编码
	while(1)
	{
		inl = fread(in,1,1024,infp);
		if(inl <= 0)
			break;
		EVP_EncodeUpdate(ctx,out,&outl,in,inl);//编码
		fwrite(out,1,outl,outfp);//输出编码结果到文件
		printf("%s",out);
	} 
	EVP_EncodeFinal(ctx,out,&outl);//完成编码，输出最后的数据。
	fwrite(out,1,outl,outfp);
	printf("%s",out);
	fclose(infp);
	fclose(outfp);	
	printf("对文件\"Test.dat\" Base64编码完成，保存到\"test.txt\"文件.\n\n\n");
}

//Base64解码
void tEVP_Decode()
{
	EVP_ENCODE_CTX *ctx;
    ctx = EVP_ENCODE_CTX_new();			//EVP编码结构体
	char in[1024];					//输入数据缓冲区
	int inl;						//输入数据长度
	unsigned char out[1024];		//输出数据缓冲区
	int outl;						//输出数据长度
	FILE *infp;						//输入文件句柄
	FILE *outfp;					//输出文件句柄
	
	infp = fopen("test.txt","r");//打开待解码的文件
	if(infp == NULL)
	{
		printf("Open File \"Test.txt\"  for Read Err.\n");
		return;
	}
	outfp = fopen("test-1.dat","wb");//打开解码后保存的文件
	if(outfp == NULL)
	{
		printf("Open File \"test-1.txt\" For Write Err.\n");
		return;
	}
	EVP_DecodeInit(ctx);//Base64解码初始化
	printf("开始对文件\"Test.txt\" Base64解码...\n\n");
	//循环读取原文，并调用EVP_DecodeUpdate进行Base64解码
	while(1)
	{
		inl = fread(in,1,1024,infp);
		if(inl <= 0)
			break;
		EVP_DecodeUpdate(ctx,out,&outl,in,inl);//Base64解码
		fwrite(out,1,outl,outfp);//输出到文件
	} 
	EVP_DecodeFinal(ctx,out,&outl);//完成解码，输出最后的数据。
	fwrite(out,1,outl,outfp);
	fclose(infp);
	fclose(outfp);	
	printf("对文件\"Test.txt\" Base64解码完成，保存为\"test-1.dat\"\n\n\n");
	
}
 
int main()
{
 
	tEVP_Encode();
	tEVP_Decode();
	
	return 0;
}
