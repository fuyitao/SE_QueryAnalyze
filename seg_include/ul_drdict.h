#ifndef UL_DRDICT_H
#define UL_DRDICT_H


typedef struct{
	int	hash_num;	// number of hash
	int	node_num;	// number of nodes
	int	cur_code;	// current minimum unused term code

	Sdict_bhash	*hash;	// hash
	
	Sdict_bnode_block	*nblock;	//first block
	Sdict_bnode_block	*cur_nblock;	//current block
	Sdict_bnode		*cur_node;	//current node
	Sdict_bnode *reclaim_node;
	int			node_avail;	//avail node_num in cur_b
} Sdict_reclaim;


/*
 *	create a dictionary for building in mem. it only allocate the
 *  space for the dictionary and do not add any new terms.
 *	return value
 *      pointer of dict
 *	arguments(in)
 *		int hash_num	: the initially hash number (good if it
 *			is equal to node number)
 *	int now_code	: current minimum term code
 */
Sdict_reclaim *dr_creat( int hash_num, int now_code );

/*
 *	delete this dictionary
 * 	return value :
 *       no
 *	arguments(in):
 *	     pdb : pointer of the dictionary
 */
int dr_del( Sdict_reclaim *pdb);


/*
 *	dictionary operations
 *	return value :
 *		1 : success
 *		0 : have not this term
 *		other : error
 *	arguments(in):
 *		pdb : pointer of dictionary
 *		pnode : the infomation for operation ( refer to op_method )
 *		op_method : operation method
 *	arguments(out):
 *		pnode : the result of the operation
 *	notice( about the op_method ) : 
 *		ADD  : 	if the term have been in dict, freq++ and get the
 *			info of this node, output by pnode; not in dict,
 *			add it to dict, code=cur_code, freq=1,
 *			low_weight=0;
 *		MOD  :	if term not in dict, MOD failed; in dict, change
 *			its info by input pnode;
 *		DEL  :	set code of this term -1 and keep its space.
 *			when dict is saved, this term will be ignored.
 *		SEEK :	found in dict, return info by pnode,
 *			else return 0
 */
int dr_op1( Sdict_reclaim *pdb, Sdict_snode *pnode, Eop_method op_method);

#endif
