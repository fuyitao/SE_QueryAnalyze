/**
 * @file
 * @brief pack包读写
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
 *  分配pack空间
 *  
 *  @param[in]  无
 *  @param[out] 无
 *  @return 指向pack空间的指针
 *  - NULL   表示失败
 *  - 非NULL 表示成功
 */
ul_package * ul_pack_init();

/**
 *  释放pack空间(please free the buffer before by yourself)
 *  
 *  @param[in]  ppack 指向pack空间
 *  @param[out] 无
 *  @return 指向pack空间的指针
 *  - 0   表示成功
 */
int ul_pack_free(ul_package *ppack);

/**
 *  向pack包中添加缓冲区
 *  
 *  @param[in]  ppack  指向pack空间
 *  @param[in]  buffer 待添加的缓冲区
 *  @param[in]  size   缓冲区的大小
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0   表示成功
 *  - <0  表示失败
 */
int ul_pack_putbuf(ul_package *ppack,char *buffer,int size);

/**
 *  从pack包中获取缓冲区地址
 *  
 *  @param[in]  ppack  指向pack空间
 *  @param[out] 无
 *  @return 指向缓冲区的指针
 *  - 非NULL   表示成功
 *  - NULL     表示失败
 */ 
char *ul_pack_getbuf(ul_package *ppack);

/**
 *  向pack包中添加名字和值
 *  
 *  @param[in]  ppack  指向pack空间
 *  @param[in]  pname  添加的名字
 *  @param[in]  pvalue 名字对应的值
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 1  名字已存在，添加成功
 *  - 0  成功
 *  - -1 名字或值超过允许长度，失败
 *  - -2 pack没有空间，失败
 */  
int ul_pack_putvalue(ul_package *ppack,char *pname,char *pvalue);

/**
 *  从pack中取指定名字的值
 *  
 *  @param[in]  ppack  指向pack空间
 *  @param[in]  pname  添加的名字
 *  @param[out]  pvalue 名字对应的值
 *  @return 函数操作结果
 *  - 1  成功
 *  - 0  失败
 */ 
int ul_pack_getvalue(ul_package *ppack,char *pname,char *pvalue);

/**
 *  从指定的句柄读取pack包
 *  
 *  @param[in]  sockfd  连接句柄
 *  @param[in]  ppack   指向pack空间
 *  @param[out] ppack   读取的包数据
 *  @return 函数操作结果
 *  - >=0  pack包体的大小
 *  - <0   失败
 */
int ul_pack_read(int sockfd,ul_package *ppack);

 
/**
 *  从指定的句柄 读取数据
 *  
 *  @param[in]  fd      连接句柄
 *  @param[in]  ptr1    接收缓冲区
 *  @param[in]  nbytes  要读取数据的字节数
 *  @param[out] ptr1    读取的数据
 *  @return 函数操作结果
 *  - >0  实际读取的字节数
 *  - <=0   失败
 */ 
int ul_pack_readall(int fd, void *ptr1, size_t nbytes);

/**
 *  读取包的结束标志
 *  
 *  @param[in]  fd      连接句柄
 *  @return 函数操作结果
 *  - 0  成功
 *  - -1 失败
 */ 
int ul_pack_readend(int sockfd);

 
/**
 *  从指定的句柄读取数据
 *  
 *  @param[in]  sockfd      连接句柄
 *  @param[in]  ppack       指向pack空间
 *  @param[in]  over_time   超时时间
 *  @param[out] ppack       读取的包数据
 *  @return 函数操作结果
 *  - >=0  pack包体的大小
 *  - <0   失败
 */
int ul_pack_reado(int sockfd,ul_package *ppack,int over_time);

 
/**
 *  从指定的句柄读取pack包，支持毫秒级超时
 *  
 *  @param[in]  sockfd      连接句柄
 *  @param[in]  ppack       指向pack空间
 *  @param[in]  msec        超时时间
 *  @param[out] ppack       读取的包数据
 *  @return 函数操作结果
 *  - >=0  pack包体的大小
 *  - <0   失败
 */
int ul_pack_reado_ms(int sockfd,ul_package *ppack,int msec);

/**
 *  从指定的句柄读取数据，支持毫秒级超时
 *  
 *  @param[in]  fd      连接句柄
 *  @param[in]  ptr1    接收缓冲区
 *  @param[in]  nbytes  要读取数据的字节数
 *  @param[in]  msec    超时时间
 *  @param[out] ptr1    读取的数据
 *  @return 函数操作结果
 *  - >0  实际读取的字节数
 *  - <=0   失败
 */
int ul_pack_readallo_ms(int fd, void *ptr1, size_t nbytes,int msec);

/**
 *  读取包的结束标志，支持毫秒级超时
 *  
 *  @param[in]  sockfd      连接句柄
 *  @param[in]  msec        超时时间
 *  @return 函数操作结果
 *  - 0   成功
 *  - -1  失败
 */ 
int ul_pack_readendo_ms(int sockfd,int msec);

/**
 *  写向socket写pack
 *  
 *  @param[in]  sockfd      连接句柄
 *  @param[in]  ppack       待写的pack包
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0   成功
 *  - -1  失败
 */ 
int ul_pack_write(int sockfd,ul_package *ppack);

 
/**
 *  向指定的句柄写数据(Inner function)
 *  
 *  @param[in]  sockfd    连接句柄
 *  @param[in]  buf       待写数据
 *  @param[in]  n         数据的字节数
 *  @return 函数操作结果
 *  - >0    实际写出的字节数
 *  - <＝0  失败
 */
int ul_pack_writeall(int sockfd, char *buf, int n);

/**
 *  清空pack包的头，即pack包中名字和值
 *  
 *  @param[in]  ppack    指向pack空间
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 1    成功
 *  - -1   失败
 */
int ul_pack_cleanhead(ul_package* ppack);

 
/**
 *  清空pack包中的所有数据(not reset the content in the buffer)
 *  
 *  @param[in]  ppack    指向pack空间
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 1    成功
 *  - -1   失败
 */ 
int ul_pack_cleanall(ul_package* ppack);

/**
 *  写pack包，先将pack包输出到临时缓冲区，再将缓冲区的内容通过连接句柄写出
 *  
 *  @param[in]  sockfd    连接句柄
 *  @param[in]  ppack     待写的pack包
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0    成功
 *  - -1   失败
 */ 
int ul_pack_write_m(int sockfd,ul_package *ppack);






/**
 *  写向socket写pack,支持秒级超时
 *  
 *  @param[in]  sockfd      连接句柄
 *  @param[in]  ppack       待写的pack包
 *  @param[in]  sec         超时时间
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0   成功
 *  - -1  失败
 */
int ul_pack_writeo(int sockfd,ul_package *ppack ,int sec);


/**
 *  写向socket写pack,支持毫秒级超时
 *  
 *  @param[in]  sockfd      连接句柄
 *  @param[in]  ppack       待写的pack包
 *  @param[in]  msec        超时时间
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0   成功
 *  - -1  失败
 */
int ul_pack_writeo_ms(int sockfd,ul_package *ppack, int msec);




/**
 *  向指定的句柄写数据,支持秒级超时
 *  
 *  @param[in]  sockfd    连接句柄
 *  @param[in]  buf       待写数据
 *  @param[in]  n         数据的字节数
 *  @param[in]  sec       超时时间
 *  @return 函数操作结果
 *  - >0    实际写出的字节数
 *  - <＝0  失败
 */
int ul_pack_writeallo(int sockfd, char *buf, int n,int sec);


/**
 *  向指定的句柄写数据,支持毫秒级超时
 *  
 *  @param[in]  sockfd    连接句柄
 *  @param[in]  buf       待写数据
 *  @param[in]  n         数据的字节数
 *  @param[in]  msec      超时时间
 *  @return 函数操作结果
 *  - >0    实际写出的字节数
 *  - <＝0  失败
 */
int ul_pack_writeallo_ms(int sockfd, char *buf, int n,int msec);



/**
 *  写pack包，先将pack包输出到临时缓冲区，再将缓冲区的内容通过连接句柄写出,支持秒级超时
 *  
 *  @param[in]  sockfd    连接句柄
 *  @param[in]  ppack     待写的pack包
 *  @param[in]  sec       超时时间
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0    成功
 *  - -1   失败
 */ 
int ul_pack_write_mo(int sockfd,ul_package *ppack, int sec);



/**
 *  写pack包，先将pack包输出到临时缓冲区，再将缓冲区的内容通过连接句柄写出,支持毫秒级超时
 *  
 *  @param[in]  sockfd    连接句柄
 *  @param[in]  ppack     待写的pack包
 *  @param[in]  msec      超时时间
 *  @param[out] 无
 *  @return 函数操作结果
 *  - 0    成功
 *  - -1   失败
 */ 
int ul_pack_write_mo_ms(int sockfd,ul_package *ppack, int msec);





#endif
