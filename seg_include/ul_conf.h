/**
 * @file
 * @brief �����ļ���
 */
/* Description:
 *   This program give some tools to manage the config file.
 *
 * Author: Cui Shanshan
 *         scui@baidu.com
 */
#ifndef _UL_MODULE_CONF_
#define _UL_MODULE_CONF_

#include "ul_def.h"
#define MAX_CONF_ITEM_NUM   1024*4

typedef struct 
{
	char name[WORD_SIZE];
	char value[WORD_SIZE];

}Ul_confitem;

typedef struct {
    int num;
    int size;
    Ul_confitem *item;
} Ul_confdata;

/**
 * ��ʼ�������ļ��ṹ
 *
 * @param conf_num ������Ŀ�������С��1024�����Զ�ʹ��1024
 * @return NULLʧ�ܣ�����Ϊ�����ļ��ṹָ��
 */ 
Ul_confdata *ul_initconf(int conf_num);

/**
 * �ͷ������ļ��ṹ
 *
 * @param pd_conf �ṹָ��
 * @return 1���ǳɹ�
 */ 
int ul_freeconf(Ul_confdata *pd_conf);

/**
 * �������ļ����ݶ���ṹ
 *
 * @param work_path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param pd_conf �ṹָ��
 * @return 1�ɹ���-1���� 
 */ 
int ul_readconf(const char *work_path, const char *fname, Ul_confdata *pd_conf);

/**
 * �������ļ����ݶ���ṹ
 *
 * @param fullpath �ļ�ȫ·��
 * @param pd_conf �ṹָ��
 * @return 1�ɹ���-1���� 
 */ 
int ul_readconf_no_dir(const char *fullpath, Ul_confdata *pd_conf);

/**
 * �����ýṹ��Ϣд���ļ�
 *
 * @param work_path �ļ�����Ŀ¼
 * @param fname �ļ���
 * @param pd_conf �ṹָ��
 * @return 1�ɹ���-1���� 
 */ 
int ul_writeconf(const char *work_path,const  char *fname, Ul_confdata *pd_conf);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪchar*����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */ 
int ul_getconfstr(Ul_confdata *pd_conf, char *conf_name, char *conf_value);
int ul_modifyconfstr(Ul_confdata *pd_conf, char *conf_name, char *conf_value);
int ul_addconfstr(Ul_confdata *pd_conf, char *conf_name, char *conf_value);

/**
 * ��������Ϣ�ṹ�ж�ȡ�������ֵ��ֵΪint����
 *
 * @param pd_conf �ṹָ��
 * @param conf_name ��������
 * @param[out] conf_value �������ֵ
 * @return 1�ɹ���0û���ҵ�
 */ 
int ul_getconfint(Ul_confdata *pd_conf, char *conf_name, int *conf_value); 
int ul_modifyconfint(Ul_confdata *pd_conf, char *conf_name, int conf_value); 
int ul_addconfint(Ul_confdata *pd_conf, char *conf_name, int conf_value); 

/* Function description: Get the value of a name from the conf file.
 * Arguments in: const char *work_path,const char *fname,char *vname.
 * Arguments out: int *pvalue.
 * Return value: 1-> find it
 *               0-> not find
 */
int ul_readnum_oneint(const char *work_path,const char *fname,char *vname, int *pvalue);

/* Function description: Get the value of a name from the conf file.
 *                       this function write log when can't find the name.
 * Arguments in: const char *work_path,const char *fname,char *vname.
 * Arguments out: int *pvalue.
 * Return value: 1-> find it
 *               -1-> not find
 */
int ul_kreadnum_oneint (const char *work_path,const char *fname,char *vname, int *pvalue);

/* Function description: Init the conf file we want to write.
 *                       if the file has exit, truncate it to 0.
 * Arguments in: const char *work_path, const char *fname.
 * Return value: >=0 sucess
 *               <0  failed
 */
int ul_writenum_init(const char *work_path, const char *fname);

/* Function description: Write a name-value pair to the conf file, the value is int.
 * Arguments in: const char *work_path, const char *fname,const char *vname, int value.
 * Return value: >=0 sucess
 *               <0  failed
 */
int ul_writenum_oneint(const char *work_path,const char *fname,const char *vname,int value); 


/* 
** command argument 
*/
#define MAX_OPT_CONTENT 256
#define MAX_OPTION_NUM  20
#define MAX_MUTI_OPT    20
#define MAX_MOPT_NUM    10
#define MAX_BASE_OPTLEN 128
#define MAX_BASE_OPTNUM 10

struct arg_option {
    char t_out;
    char option;
    char opt_cont[MAX_OPT_CONTENT];
};

struct base_arg {
    // 1 -- out ;
    char t_out;
    char b_argument[MAX_BASE_OPTLEN];
};

struct muti_option {
    char t_out ;
    char option[MAX_MUTI_OPT];
    char opt_cont[MAX_OPT_CONTENT];
};

typedef struct {
//
    int opt_num;
    int cur_opt;
    struct arg_option option[MAX_OPTION_NUM];
//
    int mopt_num;
    int cur_mopt;
    struct muti_option m_option[MAX_MOPT_NUM];
//
    int arg_num;
    int cur_arg;
    struct base_arg b_arg[MAX_BASE_OPTNUM];
} Ul_argu_stru ;

//=====================================================================/
//        function prototype
//=====================================================================
/*
 * function : create a Ul_argu_stru struct
 * argu     : void
 * return   : the pointer is successfully
 *          : NULL if failed
 */
Ul_argu_stru *argument_init();

/*
 * function : destroy the struct and free thr resource
 * argu-io  : argument_struct, the pointer to the struct
 * return   : void
 */
void argument_destroy(Ul_argu_stru  *argument_struct);

/*
 * function : convert the argv into Ul_argu_stru struct
 * argu-in  : argc,argv,the main function arguments
 * argu-out : argument_struct, the struct
 * return   : 0 if successfully
 *          : -1 if failed.
 */
int read_argument(Ul_argu_stru  *argument_struct, int argc, char **argv);

/*
 * function : check a option in argus
 * argu-in  : option, the option char
 * argu-io  : argument_struct, some member will be changed in this function
 *          : opt_size, when input, it is the buffer size of the opt_value
 *          :     if successfully, opt_size will be set with the length
 *          :     of the opt_value. if failed, it will be undefined
 * argu-out : opt_value, the option string buffer
 * return   : 0 if not find the option or buffer is not enough
 *          : >0 if successfully
 */
int get_one_option(Ul_argu_stru  *argument_struct,char option,char *opt_value,int *opt_size);

/*
 * function : check a complex option in argus
 * argu-in  : option, the option string
 * argu-io  : argument_struct, some member will be changed in this function
 *          : opt_size, when input, it is the buffer size of the opt_value
 *          :     if successfully, opt_size will be set with the length
 *          :     of the opt_value. if failed, it will be undefined
 * argu-out : opt_value, the option string buffer
 * return   : 0 if not find the option or buffer is not enough
 *          : >0 if successfully
 * notice   : refer get_one_option
 */
int get_one_complex_option(Ul_argu_stru  *argument_struct,char *option,char *opt_value,int *opt_size);

/*
 * function : take out the base parameter
 * argu-in  : serial : serial of the base option
 *          :          0 means the first parameter
 * argu-out : b_argument, the output buffer for base argument
 * argu-io  : size, when in, it is the max  size of the b_argument
 *          :       when out, the length of the b_argument is successfully
 *          :       undefined if failed.
 * return   : 0 if not found or the buffer was little
 *          : >0 if found
 */
int get_base_argument(Ul_argu_stru  *argument_struct,int serial ,char *b_argument, int *size );

#endif
