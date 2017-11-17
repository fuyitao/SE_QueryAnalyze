/**
 * @file
 * @brief 日志库
 */
#ifndef __UL_LOG_H__
#define __UL_LOG_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <sys/param.h>
#include <unistd.h>
#include <sys/types.h> 
#include <signal.h>
#include <sys/wait.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <limits.h>    
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <assert.h>
#include "ul_def.h"
#define ERR_NOSPACE		-1
#define ERR_OPENFILE	-2
#define ERR_EVENT		-3
#define ERR_FILEFULL	-4

#define LOG_FILE_NUM	2048
#define LOG_BUFF_SIZE	640
#define LOG_BUFF_SIZE_EX 2048

#define MAX_FILE_SIZE		2047
#define MAX_FILENAME_LEN	1024

#define MAX_ATTACH_NUM  1000
#define NAMENUM_INDATA  100
#define NAMELEN_INDATA  32
#define BUFSIZE_INDATA  640
#define SLEEP_INVAL     300

#define SVSEM_MODE      0666
#define SVSHM_MODE      (SHM_R | SHM_W | SHM_R>>3 | SHM_R>>6)
#define PRO_NAME_LEN    256
#define TIME_LEN        20

/* 事件类型  */
#define UL_LOG_WFSTART	-2
#define UL_LOG_START	-1
#define UL_LOG_END		UL_LOG_START
#define UL_LOG_WFEND	UL_LOG_WFSTART

#define UL_LOG_NONE		0
#define UL_LOG_FATAL	0x01    /**<   fatal errors */
#define UL_LOG_WARNING	0x02    /**<   exceptional events */
#define UL_LOG_NOTICE   0x04    /**<   informational notices */
#define UL_LOG_TRACE	0x08    /**<   program tracing */
#define UL_LOG_DEBUG	0x10    /**<   full debugging */
#define UL_LOG_ALL		0xff    /**<   everything     */

/* ul_log_t  log_sepc */
#define UL_LOGTTY		0x02    /**<   also log to stderr */
#define UL_LOGNEWFILE	0x08    /**<   create new file to log*/

/* ul_file_t  flag */
#define UL_FILE_TRUNCATE	0x01
#define UL_FILE_FULL		0x02

#define UL_LOG_RECORD	15	

/** @brief 日志相关参数 */
typedef struct {
        int events;		/**< interesting events, 0-15 */
        int to_syslog;	/**< interesting events to send to syslog, 0-15 */
        int spec;		/**< assorted switches, 0 or @ref UL_LOGTTY or @ref UL_LOGNEWFILE */
}ul_logstat_t;

typedef struct
{
	FILE *fp;						//文件句柄
	int  flag;						//标志  UL_FILE_TRUNCATE | UL_FILE_FULL
	int  ref_cnt;					//引用计数
	int  max_size;			//文件可以记录的最大长度
	pthread_mutex_t file_lock;		//写文件锁
	char file_name[MAX_FILENAME_LEN+1];	//文件名字
}ul_file_t;

struct ul_log_t
{
	char used;						//0-未使用  1-已使用
	ul_file_t *pf;					//*log
	ul_file_t *pf_wf;				//*log.wf
	pthread_t tid;                  //线程id
	int  mask;						//可以记录的事件的掩码
	int  log_syslog;				//输出到系统日志的事件掩码
	int  log_spec;					//UL_LOGTTY | UL_LOGNEWFILE
};

typedef struct ul_log_t ul_log_t;

struct ul_log_ctrl
{
    char  processname[PRO_NAME_LEN]; /* 包含进程名和参数 , 并用"_" 连接。
                       如 ： start_-d_/usr/mydir_c_myconf */
    int  processid;
    char start_time[TIME_LEN];
    ul_log_ctrl *next;
};

typedef struct ul_log_ctrl  Ul_log_ctrl;

typedef struct
{
    char  name[NAMELEN_INDATA];
    int  value;
}Ul_log_item;

typedef struct
{
    Ul_log_item  item_str[NAMENUM_INDATA]; // the process information
    char    buff[BUFSIZE_INDATA] ; // record the WARNING and FATAL log
} Ul_log_data;

/*
 * Log using manual
 * multi-thread process
 *  main process  child thread 1   child thread 2 ...
 *  ul_openlog
 *      |
 *  ul_threadlog_sup
 *      |
 *      ------------------------------------
 *      |               |               |
 *  ul_writelog  ul_openlog_r       ul_openlog_r
 *     ...              |               |
 *     ...       ul_writelog        ul_writelog
 *     ...           ...              ...
 *               ul_closelog_r      ul_closelog_r
 *                      |               |
 *      --------------------------------------
 *      |
 *  ul_closelog
 * single thread process
 *  ul_openlog
 *      |
 *  ul_writelog
 *     ...
 *      |
 *  ul_closelog
 * if using ul_writelog before ul_openlog, the log will
 *    be writen to stderr
 * this log library does not support multi-process program.
 *     You should fork process  before open log. and using
 *     diffrent log files in diffrent process.
 *
 */

/**
 * 打开日志文件（log和log.wf）并初始化日志对象(包括attach共享内存)
 *
 * @param log_path 日志文件所在目录 
 * @param log_procname 日志文件名前缀。如果文件名中包含'_'，则截断为'_'之前的字符串
 * @param l_stat 日志相关参数(用来设置log的特性)
 * @param maxlen 单个日志文件的最大长度（unit: MB）
 * @return 0成功，-1失败
 * @note 退出时需要调用ul_closelog释放资源
 */
extern int ul_openlog(const char *log_path,const char *log_procname, ul_logstat_t  *l_stat , int maxlen );


/**
 * 打印指定级别的字符串到对应的日志文件
 *
 * @param event 日志级别 (include UL_LOG_DEBUG,UL_LOG_TRACE,UL_LOG_NOTICE,UL_LOG_WARNING,UL_LOG_FATAL)
 * @param fmt 格式串
 * @param ... 打印参数列表
 * @return 0成功，<0失败
 * @note 日志长度经过扩展，线程级日志可支持最大为2048字节，共享内存中的log信息在超过640字节依然会截断。
 */
#ifdef  _UN_WRITELOG_FORMAT_CHECK
extern int ul_writelog(const int event, const char* fmt, ... );
#else
extern int ul_writelog(const int event, const char* fmt, ... ) __attribute__ ((format (printf,2,3)));
#endif

/**
 * 关闭日志文件并释放相关资源
 *
 * @param iserr 在日志中记录结束状态。0为正常，非0为不正常
 * @return 0成功，-1失败
 */
extern int ul_closelog(int iserr);

/**
 * 为本线程打开日志
 *
 * @param threadname 用于打印的线程名字(如果设置了UL_LOGNEWFILE,会根据threadname创建新的log文件)
 * @param l_stat 日志相关参数
 * @return 0成功，-1失败
 * @note 当线程退出以后，要使用ul_closelog_r来释放资源
 */
extern int ul_openlog_r(const char *threadname, ul_logstat_t  *l_stat);

/**
 * 关闭本线程的日志
 *
 * @param iserr 在日志中记录结束状态。0为正常，非0为不正常
 * @return 0成功，-1失败
 */
extern int ul_closelog_r(int iserr);

/**
 * 关闭本线程的日志
 *
 * @return 0成功，-1失败
 * @note 必须在任何ul_openlog_r之前调用
 */
extern int ul_threadlog_sup();


/*
 * In order to monitor the state of the process when it is running.
 * we need to export some status information.share memory is a good
 * choise.
 * when we open the log, we will attach a piece of share memory(
 * about 100 name-value pairs and a 640 byte buffer for this process
 * to export the information.
 * when exporting information,
 * use ul_log_assign to assign a name-value pair,
 * use ul_log_getid to get the id of the name-value pair,
 * use ul_log_setval by the id and value to set the value,
 * use ul_log_getval by the id and value to increment the value.
 * when monitor the information,
 * use ul_log_monproc to choise the process data
 * use ul_log_getval to get the value
 * use ul_log_getbuf to get the buffer content
 *
 */




/*
 * function : assign a share memory variable for the name
 * argu-in  : name, the variable name
 *          : ini_val, the initial value
 * return   : 0 if successfully, -1 if failed
 */
extern int ul_log_assign(char *name, int ini_val);

/*
 * function : get the share memory variable id by the name
 * argu-in  : name, the variable name
 * return   : -1 if failed
 *          : id(>=0) if successfully
 */
extern int ul_log_getid(char *name);

/*
 * function : the set the share memory variable
 * argu-in  : rel_loc, the shm variable id
 *          : val, the setting value
 * return   : 0 if successfully, -1 if failed
 */
extern int ul_log_setval( int rel_loc ,int val);
/*
 * function : increment the shm variable by a given value
 * argu-in  : rel_loc, the shm variable id
 *          : val, the incremental step
 * return   : 0 if successfully, -1 if failed
 */
extern int ul_log_addval( int rel_loc, int val);

/*
 * function : choice the monitor process in share memory
 * argu-in  : processname, the processname(as the argu
 *          :     2 of ul_openlog)
 * return   : 0 if successfully
 *          : -1 if failed
 */
extern int ul_log_monproc(char * processname);

/*
 * function : get the shm variable by the given name
 * argu-in  : name, the variable name
 * argu-out : pval, the buffer for output value
 * return   : 0 if successfully, the *pval will be set
 *          : -1 if failed
 */
extern int ul_log_getval(char * name,int *pval);

/*
 * function : get the a special buffer in share memory
 * argu-in  : buflen, the output buffer size.
 * argu-out : buff, the outbuf buffer
 * return   : 0 if successfully, the *pval will be set
 *          : -1 if failed
 */
extern int ul_log_getbuf(char * buff,int buflen);

/*
 * function : set item_str's number of Ul_log_data
 * argu-in  : namenum, item_str's number
 * 	      namenum will be set to NAMENUM_INDATA if namenum less than NAMENUM_INDATA
 * return   : the item_str's number
 */
extern int ul_set_namenum(int namenum);

extern int ul_log_createshm(void);
extern int ul_log_attachshm(void);
extern int ul_log_deattachshm(void);
extern int ul_log_cleanshm(char *proc_name, char *item_name, bool clean_buff);
extern int ul_log_listproc(char *proc_name, Ul_log_ctrl *proc_ctrl);
extern int ul_log_listitem(char *proc_name, Ul_log_item *item_str, char *buff, int buff_len);

#endif
