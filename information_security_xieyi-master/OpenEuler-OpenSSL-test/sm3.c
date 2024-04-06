#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
void tDigest()
{
	unsigned char sm3_value[EVP_MAX_MD_SIZE];	//���������ժҪֵ������
	int sm3_len, i;
	EVP_MD_CTX *sm3ctx;							//EVP��ϢժҪ�ṹ��
	sm3ctx = EVP_MD_CTX_new();
	char msg1[] = "Test Message1";				//������ժҪ����Ϣ1	
	char msg2[] = "Test Message2";				//������ժҪ����Ϣ2
	
	EVP_MD_CTX_init(sm3ctx);					//��ʼ��ժҪ�ṹ�� 
	EVP_DigestInit_ex(sm3ctx, EVP_sm3(), NULL);	//����ժҪ�㷨�������㷨���棬���������㷨ʹ��MD5���㷨����ʹ��OpenSSLĬ�����漴���㷨
	EVP_DigestUpdate(sm3ctx, msg1, strlen(msg1));//����ժҪUpDate����msg1��ժҪ
	EVP_DigestUpdate(sm3ctx, msg2, strlen(msg2));//����ժҪUpDate����msg2��ժҪ	
	EVP_DigestFinal_ex(sm3ctx, sm3_value, &sm3_len);//ժҪ���������ժҪֵ	
	EVP_MD_CTX_reset(sm3ctx);						//�ͷ��ڴ�
	
	printf("ԭʼ����%s��%s��ժҪֵΪ:\n",msg1,msg2);
	for(i = 0; i < sm3_len; i++) 
	{
		printf("0x%02x ", sm3_value[i]);
	}
	printf("\n");
}
int main()
{ 
	OpenSSL_add_all_algorithms();
	tDigest();
	return 0;
}
