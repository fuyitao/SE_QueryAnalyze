/**
 * @file
 * @brief pack����д
 */

#ifndef __PACK_UL_H__
#define __PACK_UL_H__

#include <errno.h>
#include <unistd.h>
#include "ul_log.h"
#include "ul_net.h"
#include "ul_func.h"

#define MAX_PACK_ITEM_NUM 50
#define MAX_ITEM_SIZE 256
#define SIZE_NUM 20
#define MAX_HEAD_SIZE 26000

typedef struct
{
    char name[MAX_PACK_ITEM_NUM][MAX_ITEM_SIZE];
    char value[MAX_PACK_ITEM_NUM][MAX_ITEM_SIZE];
    int pairnum;
    int bufsize;
    char *buf;
}ul_package;

/**
 *  ����pack�ռ�
 *  
 *  @param[in]  ��
 *  @param[out] ��
 *  @return ָ��pack�ռ��ָ��
 *  - NULL   ��ʾʧ��
 *  - ��NULL ��ʾ�ɹ�
 */
ul_package * ul_pack_init();

/**
 *  �ͷ�pack�ռ�(please free the buffer before by yourself)
 *  
 *  @param[in]  ppack ָ��pack�ռ�
 *  @param[out] ��
 *  @return ָ��pack�ռ��ָ��
 *  - 0   ��ʾ�ɹ�
 */
int ul_pack_free(ul_package *ppack);

/**
 *  ��pack������ӻ�����
 *  
 *  @param[in]  ppack  ָ��pack�ռ�
 *  @param[in]  buffer ����ӵĻ�����
 *  @param[in]  size   �������Ĵ�С
 *  @param[out] ��
 *  @return �����������
 *  - 0   ��ʾ�ɹ�
 *  - <0  ��ʾʧ��
 */
int ul_pack_putbuf(ul_package *ppack,char *buffer,int size);

/**
 *  ��pack���л�ȡ��������ַ
 *  
 *  @param[in]  ppack  ָ��pack�ռ�
 *  @param[out] ��
 *  @return ָ�򻺳�����ָ��
 *  - ��NULL   ��ʾ�ɹ�
 *  - NULL     ��ʾʧ��
 */ 
char *ul_pack_getbuf(ul_package *ppack);

/**
 *  ��pack����������ֺ�ֵ
 *  
 *  @param[in]  ppack  ָ��pack�ռ�
 *  @param[in]  pname  ��ӵ�����
 *  @param[in]  pvalue ���ֶ�Ӧ��ֵ
 *  @param[out] ��
 *  @return �����������
 *  - 1  �����Ѵ��ڣ���ӳɹ�
 *  - 0  �ɹ�
 *  - -1 ���ֻ�ֵ���������ȣ�ʧ��
 *  - -2 packû�пռ䣬ʧ��
 */  
int ul_pack_putvalue(ul_package *ppack,char *pname,char *pvalue);

/**
 *  ��pack��ȡָ�����ֵ�ֵ
 *  
 *  @param[in]  ppack  ָ��pack�ռ�
 *  @param[in]  pname  ��ӵ�����
 *  @param[out]  pvalue ���ֶ�Ӧ��ֵ
 *  @return �����������
 *  - 1  �ɹ�
 *  - 0  ʧ��
 */ 
int ul_pack_getvalue(ul_package *ppack,char *pname,char *pvalue);

/**
 *  ��ָ���ľ����ȡpack��
 *  
 *  @param[in]  sockfd  ���Ӿ��
 *  @param[in]  ppack   ָ��pack�ռ�
 *  @param[out] ppack   ��ȡ�İ�����
 *  @return �����������
 *  - >=0  pack����Ĵ�С
 *  - <0   ʧ��
 */
int ul_pack_read(int sockfd,ul_package *ppack);

 
/**
 *  ��ָ���ľ�� ��ȡ����
 *  
 *  @param[in]  fd      ���Ӿ��
 *  @param[in]  ptr1    ���ջ�����
 *  @param[in]  nbytes  Ҫ��ȡ���ݵ��ֽ���
 *  @param[out] ptr1    ��ȡ������
 *  @return �����������
 *  - >0  ʵ�ʶ�ȡ���ֽ���
 *  - <=0   ʧ��
 */ 
int ul_pack_readall(int fd, void *ptr1, size_t nbytes);

/**
 *  ��ȡ���Ľ�����־
 *  
 *  @param[in]  fd      ���Ӿ��
 *  @return �����������
 *  - 0  �ɹ�
 *  - -1 ʧ��
 */ 
int ul_pack_readend(int sockfd);

 
/**
 *  ��ָ���ľ����ȡ����
 *  
 *  @param[in]  sockfd      ���Ӿ��
 *  @param[in]  ppack       ָ��pack�ռ�
 *  @param[in]  over_time   ��ʱʱ��
 *  @param[out] ppack       ��ȡ�İ�����
 *  @return �����������
 *  - >=0  pack����Ĵ�С
 *  - <0   ʧ��
 */
int ul_pack_reado(int sockfd,ul_package *ppack,int over_time);

 
/**
 *  ��ָ���ľ����ȡpack����֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd      ���Ӿ��
 *  @param[in]  ppack       ָ��pack�ռ�
 *  @param[in]  msec        ��ʱʱ��
 *  @param[out] ppack       ��ȡ�İ�����
 *  @return �����������
 *  - >=0  pack����Ĵ�С
 *  - <0   ʧ��
 */
int ul_pack_reado_ms(int sockfd,ul_package *ppack,int msec);

/**
 *  ��ָ���ľ����ȡ���ݣ�֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  fd      ���Ӿ��
 *  @param[in]  ptr1    ���ջ�����
 *  @param[in]  nbytes  Ҫ��ȡ���ݵ��ֽ���
 *  @param[in]  msec    ��ʱʱ��
 *  @param[out] ptr1    ��ȡ������
 *  @return �����������
 *  - >0  ʵ�ʶ�ȡ���ֽ���
 *  - <=0   ʧ��
 */
int ul_pack_readallo_ms(int fd, void *ptr1, size_t nbytes,int msec);

/**
 *  ��ȡ���Ľ�����־��֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd      ���Ӿ��
 *  @param[in]  msec        ��ʱʱ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 */ 
int ul_pack_readendo_ms(int sockfd,int msec);

/**
 *  д��socketдpack
 *  
 *  @param[in]  sockfd      ���Ӿ��
 *  @param[in]  ppack       ��д��pack��
 *  @param[out] ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 */ 
int ul_pack_write(int sockfd,ul_package *ppack);

 
/**
 *  ��ָ���ľ��д����(Inner function)
 *  
 *  @param[in]  sockfd    ���Ӿ��
 *  @param[in]  buf       ��д����
 *  @param[in]  n         ���ݵ��ֽ���
 *  @return �����������
 *  - >0    ʵ��д�����ֽ���
 *  - <��0  ʧ��
 */
int ul_pack_writeall(int sockfd, char *buf, int n);

/**
 *  ���pack����ͷ����pack�������ֺ�ֵ
 *  
 *  @param[in]  ppack    ָ��pack�ռ�
 *  @param[out] ��
 *  @return �����������
 *  - 1    �ɹ�
 *  - -1   ʧ��
 */
int ul_pack_cleanhead(ul_package* ppack);

 
/**
 *  ���pack���е���������(not reset the content in the buffer)
 *  
 *  @param[in]  ppack    ָ��pack�ռ�
 *  @param[out] ��
 *  @return �����������
 *  - 1    �ɹ�
 *  - -1   ʧ��
 */ 
int ul_pack_cleanall(ul_package* ppack);

/**
 *  дpack�����Ƚ�pack���������ʱ���������ٽ�������������ͨ�����Ӿ��д��
 *  
 *  @param[in]  sockfd    ���Ӿ��
 *  @param[in]  ppack     ��д��pack��
 *  @param[out] ��
 *  @return �����������
 *  - 0    �ɹ�
 *  - -1   ʧ��
 */ 
int ul_pack_write_m(int sockfd,ul_package *ppack);






/**
 *  д��socketдpack,֧���뼶��ʱ
 *  
 *  @param[in]  sockfd      ���Ӿ��
 *  @param[in]  ppack       ��д��pack��
 *  @param[in]  sec         ��ʱʱ��
 *  @param[out] ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 */
int ul_pack_writeo(int sockfd,ul_package *ppack ,int sec);


/**
 *  д��socketдpack,֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd      ���Ӿ��
 *  @param[in]  ppack       ��д��pack��
 *  @param[in]  msec        ��ʱʱ��
 *  @param[out] ��
 *  @return �����������
 *  - 0   �ɹ�
 *  - -1  ʧ��
 */
int ul_pack_writeo_ms(int sockfd,ul_package *ppack, int msec);




/**
 *  ��ָ���ľ��д����,֧���뼶��ʱ
 *  
 *  @param[in]  sockfd    ���Ӿ��
 *  @param[in]  buf       ��д����
 *  @param[in]  n         ���ݵ��ֽ���
 *  @param[in]  sec       ��ʱʱ��
 *  @return �����������
 *  - >0    ʵ��д�����ֽ���
 *  - <��0  ʧ��
 */
int ul_pack_writeallo(int sockfd, char *buf, int n,int sec);


/**
 *  ��ָ���ľ��д����,֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd    ���Ӿ��
 *  @param[in]  buf       ��д����
 *  @param[in]  n         ���ݵ��ֽ���
 *  @param[in]  msec      ��ʱʱ��
 *  @return �����������
 *  - >0    ʵ��д�����ֽ���
 *  - <��0  ʧ��
 */
int ul_pack_writeallo_ms(int sockfd, char *buf, int n,int msec);



/**
 *  дpack�����Ƚ�pack���������ʱ���������ٽ�������������ͨ�����Ӿ��д��,֧���뼶��ʱ
 *  
 *  @param[in]  sockfd    ���Ӿ��
 *  @param[in]  ppack     ��д��pack��
 *  @param[in]  sec       ��ʱʱ��
 *  @param[out] ��
 *  @return �����������
 *  - 0    �ɹ�
 *  - -1   ʧ��
 */ 
int ul_pack_write_mo(int sockfd,ul_package *ppack, int sec);



/**
 *  дpack�����Ƚ�pack���������ʱ���������ٽ�������������ͨ�����Ӿ��д��,֧�ֺ��뼶��ʱ
 *  
 *  @param[in]  sockfd    ���Ӿ��
 *  @param[in]  ppack     ��д��pack��
 *  @param[in]  msec      ��ʱʱ��
 *  @param[out] ��
 *  @return �����������
 *  - 0    �ɹ�
 *  - -1   ʧ��
 */ 
int ul_pack_write_mo_ms(int sockfd,ul_package *ppack, int msec);





#endif
