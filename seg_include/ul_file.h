/**
 * @file 
 * @brief 文件操作库
 */
/* Description:
 *   These are functions used in file operation.
 *   Author: Cui Shanshan
 *   scui@baidu.com	
 */
#ifndef _UL_MODULE_FILE_
#define _UL_MODULE_FILE_

/**
 * 判断文件是否存在
 *
 * @param path 文件所在目录
 * @param fname 文件名
 * @return 1存在，0不存在
 */
int ul_fexist(const char *path,const char *fname);

/**
 * 获得文件的长度
 *
 * @param path 文件所在目录
 * @param fname 文件名
 * @return -1文件不存在，否则为文件长度
 */
int ul_fsize(const char *path, const char *fname);

/**
 * 获得文件的一些内容统计信息
 *
 * @param path 文件所在目录
 * @param fname 文件名
 * @param[out] nline 文件行数
 * @param[out] nword 单词数
 * @param[out] nchar 字符数
 * @return 1成功，-1文件不存在
 */
int ul_finfo(const char *path, const char *fname,int *nline,int *nword,int *nchar);

/**
 * 生成一个空文件，如果存在则截断到0，如果不存在则创建
 *
 * @param path 文件所在目录
 * @param fname 文件名
 * @return 1成功，-1失败
 */
int ul_nullfile(const char *path, const char *fname);

/**
 * 在同一个目录下拷贝文件
 *
 * @param path 文件所在目录
 * @param fsrc 源文件名
 * @param fdest 目标文件名
 * @return 1成功，-1失败
 */
int ul_cpfile(char *path, char *fsrc, char *fdest);

/**
 * 在同一个目录下将源文件内容添加到目标文件的末尾
 *
 * @param path 文件所在目录
 * @param fsrc 源文件名
 * @param fdest 目标文件名
 * @return 1成功，-1失败
 */
int ul_appfile(char *path, char *fsrc, char *fdest);

/**
 * 在同一个目录下为文件更名
 *
 * @param path 文件所在目录
 * @param fsrc 旧文件名
 * @param fdest 新文件名
 * @return 1成功，-1失败
 */
int ul_mvfile(char *path, char *fsrc, char *fdest);

/**
 * 将一个文件内容全部读入内存中
 *
 * @param path 文件所在目录
 * @param fname 文件名
 * @param buf 读入缓冲区
 * @param size 缓冲区大小
 * @return 1成功，-1失败
 */
int ul_readfile(char *path, char *fname, void *buf, int size);

/**
 * 将内存中的数据写入文件
 *
 * @param path 文件所在目录
 * @param fname 文件名
 * @param buf 读入缓冲区
 * @param size 缓冲区大小
 * @return -1失败，否则为写入字节数
 */
int ul_writefile(char *path, char *fname, void *buf, int size);
 
/**
 * 交换文件名
 *
 * @param path 文件所在目录
 * @sname 文件名s
 * @dname 文件名d
 * @return 1成功，-1失败
 */
int ul_exchangedir(char *path, char *sname, char *dname);

/**
 *  Function description: The following three functions are used in display the  running process.
 *  Arguments in: char *remark, int base, int goint.
 */
int ul_showgo(char *remark, int goint); 
int ul_showgocmp(char *remark, int base, int goint); 
int ul_showgoend(char *remark, int base, int goint) ;

#endif
