//***********************************************************************
//			Dictionary Utilities (DU) 1.0
//
//	These utilities are used to manage the dictionary. Its main funcion
//	is to give a code to a string. 
//***********************************************************************


#ifndef __DICT_H__
#define __DICT_H__

#include <ul_def.h>

/*
#define IS_GBK(ps)	((((u_char)ps[0])>0x7f) && (((u_char)ps[0])<0xff))\
		      && (((u_char)ps[1])>0x39) && (((u_char)ps[1])<0xff)))
*/

#define Dlweight( index2 )	((int) (((unsigned int)(index2))>>25))
#define Dfreq( index2 )		(index2 & 0x1ffffff)
#define Dterm( w, uno )		((unsigned int) ((w<<25)|(uno&0x1ffffff)))

#define Dcpoff(i1, i2, i3)	((((i1*CHAR_LONUM)+i2)*CHAR_HINUM)+i3)

//********************************
// structs for building dictionary
//********************************

#define PHRASE_IND1_NUM	100001
#define	SUR_IND1_NUM	65536
#define	NODE_BLOCK_NUM	(256*1024)
#define MID_NODE_NUM	(4*1024)
#define BASE_SIGN	65547
#define MAX_SQRT_NUM	400000

#define	BASE_DICT_NUM	1000000
#define	BIG_DICT_HNUM	10000001

#define	IND2_NUM_PER_FILE	100000
#define WORDDELIMITER	'|'

/* this enum defined for dict operation db_op & ds_op */
typedef enum{
ADD,		//for dict building	: have been in dict(f++) not(add)
CLUSTER,	//for searcher cluster	: same sign -> keep the high weight
MOD,		//for dict building	: modify the struct of dict
SEEK,		//for dict building	: seek by sign
SEEKP,		//for parser identify	: found -> dict freq ++
DEL,		//for dict building	: del by sign
MODF,		//for dict searching	: frequence
MODW,		//for dict searching	: lowest weight
MODC		//for dict searching	: term code
} Eop_method;

/* for node in mem, using link */
struct ss_dict_build_node{
	u_int 	sign1;	//signature 1
	u_int 	sign2;	//signature 2
	int 	code;	//term code
	u_int 	other;	//lowest_weight(7) + frequence(25)
	struct 	ss_dict_build_node *next;	//next node
};
typedef struct ss_dict_build_node Sdict_bnode;

/* for hash in mem */
typedef struct{
	Sdict_bnode	*pnode;	//hash table
} Sdict_bhash;

/* for block of nodes in mem */
struct ss_dict_build_node_block{
	Sdict_bnode nodes[NODE_BLOCK_NUM];	//block of nodes, for build
	struct ss_dict_build_node_block	*next;	//next block
};
typedef struct ss_dict_build_node_block	Sdict_bnode_block;

/* for dict in mem */
typedef struct{
	int	hash_num;	// number of hash
	int	node_num;	// number of nodes
	int	cur_code;	// current minimum unused term code

	Sdict_bhash	*hash;	// hash

	Sdict_bnode_block	*nblock;	//first block
	Sdict_bnode_block	*cur_nblock;	//current block
	Sdict_bnode		*cur_node;	//current node
	int			node_avail;	//avail node_num in cur_b
} Sdict_build;

/* for creating key(sign-weight) list from dict -> for parser */
typedef struct{
	u_int sign1;
	u_int sign2;
	int weight;
} Skeyweight;

typedef struct{
	int 		num;
	Skeyweight 	*key;
} Skeyweightlist;

typedef struct{
	unsigned int	weight;
	unsigned int	urlno;
} Slongindex2;

typedef struct{
	int		num;
	void		*index2;
	int		*rept;
} Spagecluster;


//********************************
// structs for dictionary search
//********************************

/* node */
typedef struct{
	u_int 	sign1;		//signature 1
	u_int 	sign2;		//signature 2
	int 	code;		//term code
	u_int 	other;	//(7:lowest_w+25:freq)
} Sdict_snode;

/* hash, implemented by unsinged int */
//typedef struct{
//	unsigned : 25 	//off
//	unsigned : 7	//num
//} Sdict_shash;

/* dict */
typedef struct{
	int	hash_num;
	int	node_num;
	int 	cur_code;	// current minimum code

	unsigned int	*hash;	// hash
	unsigned int 	*num;	// number of nodes in hash entries
	Sdict_snode	*node;	// nodes
} Sdict_search;

typedef struct{
	int hash_num;
	int node_num;
	int cur_code;

	int find1;
	int find2;
}Sdict_search_hd;


//*********************************
// structs for phrase dictionary
//*********************************

typedef struct {
	int off;
	int num;
} Shash_cphrase;

typedef struct {
	Shash_cphrase *hash;
	unsigned char *phrase;
	char	      *surname;
} Sdict_cphrase;

typedef struct{
	int off;
	int num;
} Shash_phrase;

typedef struct{
	Shash_phrase	*hash;
	char		*phrase;
} Sdict_phrase;


//*********************************
// structs for synonym dictionary
//*********************************

#define WORDBUFSIZE (512*1024)

struct ss_dict_build_syn_node{
	u_int 	sign1;	//signatures of word 1
	u_int 	sign2;
	u_int	sign3;	//signatures of word 2
	u_int	sign4;
	struct 	ss_dict_build_syn_node *next;	//next node
};
typedef struct ss_dict_build_syn_node Sdict_syn_bnode;

typedef struct{
	Sdict_syn_bnode	*pnode;	//hash table
} Sdict_syn_bhash;

struct ss_dict_syn_build_node_block{
	Sdict_syn_bnode nodes[NODE_BLOCK_NUM];	//block of nodes, for build
	struct ss_dict_syn_build_node_block	*next;	//next block
};
typedef struct ss_dict_syn_build_node_block	Sdict_syn_bnode_block;

struct ss_dict_syn_buffer_block{
	char	buf[WORDBUFSIZE];	//buffer block for words
	struct ss_dict_syn_buffer_block	*next;	//next block
};
typedef struct ss_dict_syn_buffer_block	Sdict_syn_buf_block;

typedef struct{
	int	hash_num;	// number of hash
	int	node_num;	// number of nodes

	Sdict_syn_bhash	*hash;	// hash

	Sdict_build		*pdword;	// word dictionary
	int			words;

	Sdict_syn_bnode_block	*nblock;	// first node block
	Sdict_syn_bnode_block	*cur_nblock;	// current node block
	Sdict_syn_bnode		*cur_node;	// current node
	int			node_avail;	// available node_num in cur_nblock

	Sdict_syn_buf_block	*bufblock;	// first buffer block
	Sdict_syn_buf_block	*cur_bufblock;	// current buffer block
	int			nrbufblock;	// number of buffer blocks
	int			cur_buf;	// available buffer
} Sdict_build_syn;

typedef struct{
	u_int 	sign1;	//signatures of word 1
	u_int 	sign2;
	u_int	sign3;	//signatures of word 2
	u_int	sign4;
} Sdict_syn_snode;

typedef struct{
	int	hash_num;
	int	node_num;
	Sdict_search	*pdword;// word dictionary

	unsigned int	*hash;	// hash
	unsigned int 	*num;	// number of nodes in hash entries
	Sdict_syn_snode	*node;	// nodes
	char		*wordbuffer;
} Sdict_search_syn;

//********************************
// functions : synonym dictionary
//********************************

Sdict_build_syn *db_syn_construct( char *fullpath, int hash_num, int dict_type );
Sdict_build_syn *db_syn_construct_unidirect( char *fullpath, int hash_num, int dict_type );
Sdict_build_syn *db_syn_creat( int hash_num );

int db_syn_del( Sdict_build_syn *pdb );
int db_syn_adjust( Sdict_build_syn *pdb );
//int db_syn_op1( Sdict_build_syn *pdb, Sdict_syn_snode *pnode, Eop_method op_method);
int db_syn_add( Sdict_build_syn *pdb, char *word1, char *word2 );
int db_syn_seek( Sdict_build_syn *pdb, char *word, char *outbuf, int len );
int db_syn_save( Sdict_build_syn *pdb, char *path, char *fname );
Sdict_build_syn *db_syn_load( char *path, char *fname, int hash_n);

Sdict_search_syn  *ds_syn_load( char *path, char *fname );
int ds_syn_del( Sdict_search_syn *pds );
int ds_syn_seek( Sdict_search_syn *pds, char *word, char *outbuf, int len );
//int ds_syn_op1( Sdict_search_syn *pds, Sdict_syn_snode *pnode, Eop_method op_method);

//**********************
// functions : signature
//**********************

u_int creat_term_sign(char *str_src);
u_int creat_sign32(char *str_src);
int creat_sign64(char *str_src, u_int *psign1, u_int *psign2);
int creat_sign_t64(void *t_src, int t_size, char *pstr, 
		u_int *psign1, u_int *psign2);
int creat_sign_nt64(void *t_src, int t_size, char *pstr, 
		u_int *psign1, u_int *psign2);

int creat_sign_t256(char *psrc, int slen, u_int* psign1, u_int* psign2);


//******************************
// functions : create dictionary
//******************************

Sdict_build *db_creat( int hash_num, int now_code );
int db_renew( Sdict_build *pdb);
int db_renew_fast(Sdict_build *pdb);
int db_del( Sdict_build *pdb);
int db_op1( Sdict_build *pdb, Sdict_snode *pnode, Eop_method op_method);
int db_opn( Sdict_build *pdb, Sdict_snode *plnode, int lnum, 
		Eop_method op_method);
int db_keylist (Sdict_build *pdb, Skeyweight *pkey, int pkey_num);
int db_cluster(Sdict_build *pdb, Spagecluster *pcluster);
int db_adjust (Sdict_build *pdb);
int db_save( Sdict_build *pdb, char *path, char *fname );
int db_save_freq( Sdict_build *pdb, char *path, char *fname );

Sdict_build *db_load( char *path, char *fname, int h_num );
Sdict_build *db_load_0( char *path, char *fname, int h_num );
int page_cluster(Sdict_snode *pnode, int node_num, Spagecluster *pcluster);

// for compatibility only
int db_add_link( Sdict_build *pdb, Sdict_snode *pnode);
int db_stand_link( Sdict_build *pdb );
int db_save_link( Sdict_build *pdb, char *path, char *fname );
int db_save_link_search( Sdict_build *pdb, char *path, char *fname );



//******************************
// functions : search dictionary
//******************************

Sdict_search *ds_load( char *path,  char *fname );
Sdict_search *ds_load_parse( char *path,  char *fname );
Sdict_search *ds_load_name( char *path,  char *fname );
int ds_reload_test(Sdict_search *pds, char *path, char *fname);
Sdict_search *ds_reload(Sdict_search *pds, char *path, char *fname, 
		char *cpath);
int ds_del(Sdict_search *pds);
int ds_save(Sdict_search *pds, char *path, char *fname);
int ds_save_freq(Sdict_search *pds, char *path, char *fname);
int ds_save_parser(Sdict_search *pds, char *path, char *cpath);
int ds_op1( Sdict_search *pds, Sdict_snode *pnode, Eop_method op_method);
int ds_opn( Sdict_search *pds, Sdict_snode *plnode, int lnum, 
		Eop_method op_method);
int pre_creat_search_dict(char *path, char *fnold_dict, char *fnnew_dict,
		char *fn_dbfreq, char *fn_dsfreq);
int creat_search_dict(char *path, char *fnold_dict, char *fnnew_dict,
		char *fn_dbfreq);
int creat_vice_dict(char *path, char *fnbase_dict, char *fnold_dict, 
		char *fnnew_dict, char *fn_dbfreq);
int creat_parser_dict(char *path, char *fnold_dict, char *fnnew_dict,
		char *fn_lw);
int creat_stand_dict(char *path, char *fnsrc, char *fndes, int num );

Sdict_build *ds_filter(Sdict_search *pds, int number);

//*****************************
// functions : HD version dict
//*****************************

Sdict_search_hd *ds_load_hd( char *path,  char *fname );
int ds_del_hd(Sdict_search_hd *pds);
int ds_seek_hd(Sdict_search_hd *pds, Sdict_snode *pnode);

//******************************
// functions : phrase dictionary
//******************************

Sdict_cphrase *dcp_load(char *path, char *fname, char *fsurname);
int dcp_seek(Sdict_cphrase *dcp, char *src_ph, char *des_ph);
int dcp_search(Sdict_cphrase *dcp, char *src_ph, char *des_ph);
int dcp_del(Sdict_cphrase *dcp);

int dp_build(char *path, char *fnsrc, char *fndes);
Sdict_phrase *dp_load(char *path, char *fname);
int dp_seek(Sdict_phrase *dp, char *ssrc, char *sdes);
int dp_search(Sdict_phrase *dp, char *ssrc, char *sdes);
int dp_del(Sdict_phrase *pd);


//******************************
// functions : surname dictionary
//******************************

char *dsur_load( char *path, char *fname );
int dsur_seek( char *dsur, char *spstr, char *dpstr);
int dsur_search( char *dsur, char *spstr, char *dpstr);
int dsur_del( char *dsur );

/*
============
signature

	this group of functions is used to create one or two integer
	to represent a string

======
int creat_term_sign(char *str_src);

*	creat term signature. the 31th bit and the 23th bit is the token
	31th	23th
	1	1	: chinese 2-gram
	1	0	: chinese phrase
	0	?	: english words

*	return value :
		the signature of the term
*	arguments(in) :
		char* str_src : input string

======
int creat_sign32(char *str_src);

*	creat string signature (32 bits) (url, site, content)
*	return value :
		the signature of the input string
*	arguments(in) :
		char* str_src : input string


======
int creat_sign64(char *str_src, int *psign1, int *psign2);

*	creat string signature (64 bits) (url, site, content)
*	return value :
		no
*	arguments(in) :
		char* str_src : input string
	arguments(out):
		int *psign1 : first 32 bits signature
		int *psign2 : other 32 bits signature


============
Create Dictionary

	This group of functions are used to creat codes for a term.
	The dictionary is located in memory. We can add, modify, delete,
	seek a signature in this dictionary. This dictionary's
	performance is worse than the dictionary for searching, but
	the dictionary for searching can not add any new term after
	it is initiated in memory.

======
Sdict_build *db_creat( int hash_num, int now_code );

*	create a dictionary for building in mem. it only allocate the
	space for the dictionary and do not add any new terms.

*	return value
		pointer of dict

*	arguments(in)
		int hash_num	: the initially hash number (good if it
			is equal to node number)
		int now_code	: current minimum term code

======
int db_del( Sdict_build *pdb);

*	delete this dictionary

* 	return value :
		no

*	arguments(in):
		pdb : pointer of the dictionary

======
int db_op1( Sdict_build *pdb, Sdict_snode *pnode, Eop_method op_method);

*	dictionary operations

*	return value :
		1 : success
		0 : have not this term
		other : error

*	arguments(in):
		pdb : pointer of dictionary
		pnode : the infomation for operation ( refer to op_method )
		op_method : operation method
*	arguments(out):
		pnode : the result of the operation

*	notice( about the op_method ) : 
		ADD  : 	if the term have been in dict, freq++ and get the
			info of this node, output by pnode; not in dict,
			add it to dict, code=cur_code, freq=1,
			low_weight=0;
		CLUSTER : for searcher. sign1&sign2 is the data should
			be clustered. code is the url_no. other is the
			weight.
		MOD  :	if term not in dict, MOD failed; in dict, change
			its info by input pnode;
		DEL  :	set code of this term -1 and keep its space.
			when dict is saved, this term will be ignored.
		SEEK :	found in dict, return info by pnode,
			else return 0

======
int db_opn( Sdict_build *pdb, Sdict_snode *plnode, int lnum,
                Eop_method op_method);

*	like op1, but deal with many nodes in one time.

*	arguments(in) :
		lnum	: number of plnode


======
int db_keylist (Sdict_build *pdb, Skeyweightlist *plkey);

*	create the keyword list for parser. This func trans the dict format
	to key-weight format. the key-weight was create by db_op

*	return value :
		the number of the list

*	arguments(in) :
		pdb	: dict
		plkey	: list of key-weight, space was given by caller

*	arguments(out) :
		plkey	: list of key-weight

* 	notice 	:
		this func malloc space for plkey
		plkey->key
		must be freed by caller

======
int db_cluster(Sdict_build *pdb, Spagecluster *pcluster);

*	save the clustered result. / refer to db_op (CLUSTER)

*	return value :
		the number of node after cluster

*	arguments(in) :
		pdb	: dict
		pcluster: clustered result

*	arguments(out) :
		pcluster: clustered result

*	notice :
		pcluster have malloced two block of space
		pcluster->rept & pcluster->index2
		must be freed by the caller.

======
int db_save( Sdict_build *pdb, char *path, char *fname );

*	save the created dictionary to file

*	return value :
		no

*	arguments(in) :
		pdb : dict
		path : working path
		fname : the file name where dict will be saved

======
int db_save_freq(Sdict_search *pds, char *path, char *fname);

*	save the freqence of every term to a file (by indexer)

*	return value :
		no

*	arguments(in) :
		pds	: dict
		path	: path
		fname	: the file name for saving

*	arguments(out) :
		path	: path
		fname	: the file name for saving

======
Sdict_build *db_load( char *path, char *fname, int h_num );

*	load dict from file

*	return value:
		a pointer of the initiated dict

*	arguments(in):
		path : working path
		fname : file name of the dict
		h_num : the hash number, 
			<=0: will according to the number saved in file
			>0 : ingored the number saved in file

============
Search Dictionary

	this dictionary is builled for searching. it save the memory space
	and enchance the performance of seeking. it can deal with the
	concurrency. the shortcoming of it is that it can not add new
	term.

======
Sdict_search *ds_load( char *path,  char *fname );

*	load dict from file

*	return value :
		pointer of dict

*	arguments(in):
		path : working path
		fname : file name of dictionary

======
int ds_del(Sdict_search *pds);

*	free the memory space taken by dict

*	return value:
		no

*	arguments(in):
		pds : pointer of the dict.

======
int ds_save(Sdict_search *pds, char *path, char *fname);

*	save the dict to file

*	return value :
		no

*	arguments(in):
		pds : pointer of dict
		path : working path
		fname : file name of dict

======
int ds_save_freq(Sdict_search *pds, char *path, char *fname);

*	save the freqence of every term to a file (by parser)

*	return value :
		no

*	arguments(in) :
		pds	: dict
		path	: path
		fname	: the file name for saving

*	arguments(out) :
		path	: path
		fname	: the file name for saving

======
int ds_op1( Sdict_search *pds, Sdict_snode *pnode, Eop_method op_method);

* 	operations of dictionary for searching

* 	return value :
		1 : success
		0 : not found
		other : failed

* 	arguments(in):
		pds : pointer of dict
		pnode : term info for operation
		op_method : operation method

*	arguments(out):
		pnode : the result of operation


*	notice (about op_method) :
		SEEK :	seek the term in the dict
		SEEKP:	seek the term in the dict & add the freq of it
		MODF :	freq++
		MODW :	change the lowest_weight to new value
		MODC :	give this term a new code (=cur_code)

======
int ds_opn( Sdict_search *pds, Sdict_snode *plnode, int lnum, 
		Eop_method op_method);

*	like op1, but deal with many nodes in one time.

*	arguments(in) :
		lnum	: number of plnode


============
*/

#endif
