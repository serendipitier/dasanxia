#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/ec.h>

void tSign_sm2()
{
    unsigned char sign_value[1024];     //保存签名值的数组
    unsigned int sign_len;         //签名值长度
    EVP_MD_CTX* mdctx;        //摘要算法上下文变量
    mdctx = EVP_MD_CTX_new();
    char mess1[] = "Test Message";     //待签名的消息

    EC_KEY* sm2_pkey = EC_KEY_new_by_curve_name(NID_sm2p256v1);
    EVP_PKEY* evpKey = NULL;       //EVP KEY结构体变量
    int i;

    printf("正在产生sm2密钥...");

    if (!sm2_pkey) {
        printf("sm2_pkey结构体为空");
        return;
    }

    if (!EC_KEY_generate_key(sm2_pkey))
    {
        printf("gen sm2 err\n");
        return;
    }
    printf(" 成功.\n");
    if (!EC_KEY_can_sign(sm2_pkey)) {
        printf("生成的私钥无法签名\n");
        return;
    }
    if (!EC_KEY_check_key(sm2_pkey)) {
        printf("生成的私钥无效\n");
        return;
    }
    evpKey = EVP_PKEY_new();      //新建一个EVP_PKEY变量
    if (evpKey == NULL)
    {
        printf("EVP_PKEY_new err\n");
        EC_KEY_free(sm2_pkey);
        return;
    }

    if (EVP_PKEY_set1_EC_KEY(evpKey, sm2_pkey) != 1)   //保存RSA结构体到EVP_PKEY结构体
    {
        printf("EVP_PKEY_set1_EC_KEY err\n");
        EC_KEY_free(sm2_pkey);
        EVP_PKEY_free(evpKey);
        return;
    }

    //以下是计算签名代码
    EVP_MD_CTX_init(mdctx);      //初始化摘要上下文
    if (!EVP_SignInit_ex(mdctx, EVP_sm3(), NULL)) //签名初始化，设置摘要算法，本例为sm3
    {
        printf("设置sm3 err\n");
        EVP_PKEY_free(evpKey);
        EC_KEY_free(sm2_pkey);
        return;
    }
    if (!EVP_SignUpdate(mdctx, mess1, strlen(mess1))) //计算签名（摘要）Update
    {
        printf("签名err\n");
        EVP_PKEY_free(evpKey);
        EC_KEY_free(sm2_pkey);
        return;
    }

    if (!EVP_SignFinal(mdctx, sign_value, &sign_len, evpKey)) //签名输出
    {
        printf("签名结束err\n");
        EVP_PKEY_free(evpKey);
        printf("%d\n", sizeof(mdctx));
        printf("%d\n", sizeof(evpKey));
        printf("签名值：%s\n", sign_value);
        printf("长度：%d\n", sign_len);
        EC_KEY_free(sm2_pkey);
        return;
    }
    printf("消息\"%s\"的签名值是: \n", mess1);
    for (i = 0; i < (int)sign_len; i++)
    {
        if (i % 16 == 0)
            printf("\n%08xH: ", i);
        printf("%02x ", sign_value[i]);
    }
    printf("\n");
    EVP_MD_CTX_reset(mdctx);

    printf("\n正在验证签名...\n");
    //以下是验证签名代码
    EVP_MD_CTX_init(mdctx);       //初始化摘要上下文
    if (!EVP_VerifyInit_ex(mdctx, EVP_sm3(), NULL))  //验证初始化，设置摘要算法，一定要和签名一致。
    {
        printf("EVP_VerifyInit_ex err\n");
        EVP_PKEY_free(evpKey);
        EC_KEY_free(sm2_pkey);
        return;
    }
    if (!EVP_VerifyUpdate(mdctx, mess1, strlen(mess1))) //验证签名（摘要）Update
    {
        printf("验签err\n");
        EVP_PKEY_free(evpKey);
        EC_KEY_free(sm2_pkey);
        return;
    }
    if (!EVP_VerifyFinal(mdctx, sign_value, sign_len, evpKey))//验证签名
    {
        printf("验签结束verify err\n");
        EVP_PKEY_free(evpKey);
        EC_KEY_free(sm2_pkey);
        return;
    }
    else
    {
        printf("验证签名正确.\n");
    }
    //释放内存
    EVP_PKEY_free(evpKey);
    EC_KEY_free(sm2_pkey);
    EVP_MD_CTX_reset(mdctx);
    return;
}

int main()
{
	OpenSSL_add_all_algorithms();
    tSign_sm2();
	return 0;
}
