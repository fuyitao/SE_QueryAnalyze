/**
 * @file 
 * @brief �ļ�������
 */
/* Description:
 *   These are functions used in file operation.
 *   Author: Cui Shanshan
 *   scui@baidu.com	
 */
#ifndef _UL_MODULE_FILE_
#define _UL_MODULE_FILE_

/**
 * �ж��ļ��Ƿ����
 *
 * @param path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @return 1���ڣ�0������
 */
int ul_fexist(const char *path,const char *fname);

/**
 * ����ļ��ĳ���
 *
 * @param path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @return -1�ļ������ڣ�����Ϊ�ļ�����
 */
int ul_fsize(const char *path, const char *fname);

/**
 * ����ļ���һЩ����ͳ����Ϣ
 *
 * @param path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param[out] nline �ļ�����
 * @param[out] nword ������
 * @param[out] nchar �ַ���
 * @return 1�ɹ���-1�ļ�������
 */
int ul_finfo(const char *path, const char *fname,int *nline,int *nword,int *nchar);

/**
 * ����һ�����ļ������������ضϵ�0������������򴴽�
 *
 * @param path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_nullfile(const char *path, const char *fname);

/**
 * ��ͬһ��Ŀ¼�¿����ļ�
 *
 * @param path �ļ�����Ŀ¼
 * @param fsrc Դ�ļ���
 * @param fdest Ŀ���ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_cpfile(char *path, char *fsrc, char *fdest);

/**
 * ��ͬһ��Ŀ¼�½�Դ�ļ�������ӵ�Ŀ���ļ���ĩβ
 *
 * @param path �ļ�����Ŀ¼
 * @param fsrc Դ�ļ���
 * @param fdest Ŀ���ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_appfile(char *path, char *fsrc, char *fdest);

/**
 * ��ͬһ��Ŀ¼��Ϊ�ļ�����
 *
 * @param path �ļ�����Ŀ¼
 * @param fsrc ���ļ���
 * @param fdest ���ļ���
 * @return 1�ɹ���-1ʧ��
 */
int ul_mvfile(char *path, char *fsrc, char *fdest);

/**
 * ��һ���ļ�����ȫ�������ڴ���
 *
 * @param path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param buf ���뻺����
 * @param size ��������С
 * @return 1�ɹ���-1ʧ��
 */
int ul_readfile(char *path, char *fname, void *buf, int size);

/**
 * ���ڴ��е�����д���ļ�
 *
 * @param path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param buf ���뻺����
 * @param size ��������С
 * @return -1ʧ�ܣ�����Ϊд���ֽ���
 */
int ul_writefile(char *path, char *fname, void *buf, int size);
 
/**
 * �����ļ���
 *
 * @param path �ļ�����Ŀ¼
 * @sname �ļ���s
 * @dname �ļ���d
 * @return 1�ɹ���-1ʧ��
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
