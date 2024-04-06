#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
//#include "crypto/sm4.h" 

void tEVP_Encrypt()
{
	unsigned char key[EVP_MAX_KEY_LENGTH];	//��Կ
	unsigned char iv[EVP_MAX_KEY_LENGTH];//��ʼ������
	EVP_CIPHER_CTX *ctx;//EVP�㷨������
	ctx = EVP_CIPHER_CTX_new();
	unsigned char out[1024];//������Ļ�����
	int outl;//���ĳ���
	int outltmp;
	char *msg="Hello OpenSSL";//�����ܵ�����
	int rv;
	int i;
	
	//����key��iv�����Բ���������Ϳ������û����룩
	for(i=0;i<24;i++)
	{
		key[i]=i;
	}
	for(i=0;i<8;i++)
	{
		iv[i]=i;
	}
	//��ʼ�������㷨�ṹ��
	EVP_CIPHER_CTX_init(ctx);
	//�����㷨����Կ��
	rv = EVP_EncryptInit_ex(ctx,EVP_sm4_cbc(),NULL,key,iv);
	if(rv!=1)
	{
		printf("Err\n");
		return;
	}
	//���ݼ���
	rv = EVP_EncryptUpdate(ctx,out,&outl,msg,strlen(msg));
	if(rv!=1)
	{
		printf("Err\n");
		return;
	}
	//�������ݼ��ܣ���ʣ�����������
	rv = EVP_EncryptFinal_ex(ctx,out+outl,&outltmp);
	if(rv!=1)
	{
		printf("Err\n");
		return;
	}
	outl = outl +outltmp;	
	printf("ԭ��Ϊ:%s\n",msg);
	//��ӡ�������
	printf("���ĳ��ȣ�%d\n�������ݣ�\n",outl);
	for(i=0;i<outl;i++)
	{
		printf("0x%02x ",out[i]);
	}
	printf("\n");
	
}

int main()
{ 
	
	OpenSSL_add_all_algorithms();
	tEVP_Encrypt();
	return 0;
}
