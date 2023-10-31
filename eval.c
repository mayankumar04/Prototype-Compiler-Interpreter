/**************************************************************************
 * C S 429 EEL interpreter
 * 
 * eval.c - This file contains the skeleton of functions to be implemented by
 * you. When completed, it will contain the code used to evaluate an expression
 * based on its AST.
 * 
 * Copyright (c) 2021. S. Chatterjee, X. Shen, T. Byrd. All rights reserved.
 * May not be used, modified, or copied without permission.
 **************************************************************************/ 

#include "ci.h"

/* Function interfaces */

/* Returns true if the given token is a binary operator and false otherwise */
extern bool is_binop(token_t);
/* Returns true if the given token is a unary operator and false otherwise */
extern bool is_unop(token_t);
/* It might be helpful to note that TOK_QUESTION is the only ternary operator. */

char *strrev(char *str);


/* infer_type() - set the type of a non-root node based on the types of children
 * Parameter: A node pointer, possibly NULL.
 * Return value: None.
 * Side effect: The type field of the node is updated.
 * (STUDENT TODO)
 */

static void infer_type(node_t *nptr) {
    // check running status - you can ignore this
    if (terminate || ignore_input) return;

    if(nptr == NULL)
        return;

    switch (nptr->node_type) {
        // Week 2 TODO: Extend type inference to handle operators on string types.
        // Week 3 TODO: Implement tpye evaluation for variables.
        
        case NT_INTERNAL:
            switch (nptr->tok) {
                case TOK_PLUS:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE){
                        nptr->type = INT_TYPE;
                    }
                    else if(nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == STRING_TYPE){
                        nptr->type = STRING_TYPE;
                    }
                    else{
                        handle_error(ERR_TYPE);
                    }
                    break;

                case TOK_BMINUS:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type != INT_TYPE || nptr->children[1]->type != INT_TYPE){
                        handle_error(ERR_TYPE);
                    }
                    else{
                        nptr->type = INT_TYPE;
                    }
                    break;

                case TOK_TIMES:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE){
                        nptr->type = INT_TYPE;
                    }
                    else if(nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == INT_TYPE){
                        nptr->type = STRING_TYPE;
                    }
                    else{
                        handle_error(ERR_TYPE);
                    }
                    break;

                case TOK_DIV:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type != INT_TYPE || nptr->children[1]->type != INT_TYPE){
                        handle_error(ERR_TYPE);
                    }
                    else{
                        nptr->type = INT_TYPE;
                    }
                    break;

                case TOK_MOD:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type != INT_TYPE || nptr->children[1]->type != INT_TYPE){
                        handle_error(ERR_TYPE);
                    }
                    else{
                        nptr->type = INT_TYPE;
                    }
                    break;

                case TOK_AND:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type != BOOL_TYPE || nptr->children[1]->type != BOOL_TYPE){
                        handle_error(ERR_TYPE);
                    }
                    else{
                        nptr->type = BOOL_TYPE;
                    }
                    break;

                case TOK_OR:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type != BOOL_TYPE || nptr->children[1]->type != BOOL_TYPE){
                        handle_error(ERR_TYPE);
                    }
                    else{
                        nptr->type = BOOL_TYPE;
                    }
                    break;

                case TOK_LT:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE){
                        nptr->type = BOOL_TYPE;
                    }
                    else if(nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == STRING_TYPE){
                        nptr->type = BOOL_TYPE;
                    }
                    else{
                        handle_error(ERR_TYPE);
                    }
                    break;

                case TOK_GT:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE){
                        nptr->type = BOOL_TYPE;
                    }
                    else if(nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == STRING_TYPE){
                        nptr->type = BOOL_TYPE;
                    }
                    else{
                        handle_error(ERR_TYPE);
                    }
                    break;

                case TOK_EQ:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    if(nptr->children[0]->type == INT_TYPE && nptr->children[1]->type == INT_TYPE){
                        nptr->type = BOOL_TYPE;
                    }
                    else if(nptr->children[0]->type == STRING_TYPE && nptr->children[1]->type == STRING_TYPE){
                        nptr->type = BOOL_TYPE;
                    }
                    else{
                        handle_error(ERR_TYPE);
                    }
                    break;

                case TOK_UMINUS:
                    infer_type(nptr->children[0]);
                    if(nptr->children[0]->type == INT_TYPE){
                        nptr->type = INT_TYPE;
                    }
                    else if(nptr->children[0]->type == STRING_TYPE){
                        nptr->type = STRING_TYPE;
                    }
                    else{
                        handle_error(ERR_TYPE);
                    }
                    break;

                case TOK_NOT:
                    infer_type(nptr->children[0]);
                    if(nptr->children[0]->type != BOOL_TYPE){
                        handle_error(ERR_TYPE);
                    }else{
                        nptr->type = BOOL_TYPE;
                    }
                    break;

                case TOK_QUESTION:
                    infer_type(nptr->children[0]);
                    infer_type(nptr->children[1]);
                    infer_type(nptr->children[2]);
                    if(nptr->children[0]->type != BOOL_TYPE){
                        handle_error(ERR_TYPE);
                    }else{
                        if(nptr->children[1]->type != nptr->children[2]->type){
                            handle_error(ERR_TYPE);
                        }
                        else{
                            nptr->type = nptr->children[1]->type;
                        }
                    }
                    break;

                case TOK_IDENTITY:
                    infer_type(nptr->children[0]);
                    nptr->type = nptr->children[0]->type; 
                    break;

                default:
                    break;

            }
            break;

        case NT_LEAF:
            switch(nptr->tok){
                case TOK_ID:;
                    entry_t *var = get(nptr->val.sval);
                    free(nptr->val.sval);
                    if(var == NULL){
                        handle_error(ERR_UNDEFINED);
                        return;
                    }
                    nptr->type = var->type;
                    if(nptr->type == INT_TYPE)
                        nptr->val.ival = var->val.ival;
                    else if(nptr->type == BOOL_TYPE)
                        nptr->val.bval = var->val.bval;
                    else{
                        nptr->val.sval = malloc(strlen(var->val.sval) + 1);
                        strcpy(nptr->val.sval, var->val.sval);
                        nptr->val.sval[strlen(var->val.sval)] = '\0';
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
    return;
}

/* infer_root() - set the type of the root node based on the types of children
 * Parameter: A pointer to a root node, possibly NULL.
 * Return value: None.
 * Side effect: The type field of the node is updated. 
 */

static void infer_root(node_t *nptr) {
    if (nptr == NULL) return;
    // check running status
    if (terminate || ignore_input) return;

    // check for assignment
    if (nptr->type == ID_TYPE) {
        //cleanup(nptr->children[0]);
        infer_type(nptr->children[1]);
    } else {
        for (int i = 0; i < 3; ++i) {
            infer_type(nptr->children[i]);
        }
        if (nptr->children[0] == NULL) {
            logging(LOG_ERROR, "failed to find child node");
            return;
        }
        nptr->type = nptr->children[0]->type;
    }
    return;
}

/* eval_node() - set the value of a non-root node based on the values of children
 * Parameter: A node pointer, possibly NULL.
 * Return value: None.
 * Side effect: The val field of the node is updated.
 * (STUDENT TODO) 
 */

static void eval_node(node_t *nptr) {
    // check running status - you can ignore this.
    if (terminate || ignore_input) return;

    if(nptr == NULL)
        return;
    
    switch (nptr->node_type) {
        case NT_INTERNAL:
            // Week 2 TODO: Extend evaluation to handle operators on string types.
            if (is_unop(nptr->tok)) {
                eval_node(nptr->children[0]);
                switch (nptr->tok) {
                    case TOK_UMINUS:
                        if(nptr->type == INT_TYPE){
                            nptr->val.ival = -(nptr->children[0]->val.ival);
                        }
                        else{
                            nptr->val.sval = strrev(nptr->children[0]->val.sval);
                        }
                        break;

                    case TOK_NOT:
                        nptr->val.bval = !(nptr->children[0]->val.bval);
                        break;

                    default:
                        break;
                }
            }
            if (is_binop(nptr->tok)) {

                eval_node(nptr->children[0]);
                eval_node(nptr->children[1]);

                switch (nptr->tok) {
                    case TOK_PLUS:
                        if(nptr->children[0]->type == INT_TYPE){
                            nptr->val.ival = (nptr->children[0]->val.ival) + (nptr->children[1]->val.ival);
                        }
                        else{
                            int len0 = strlen(nptr->children[0]->val.sval);
                            int len1 = strlen(nptr->children[1]->val.sval);
                            nptr->val.sval = malloc(len0 + len1 + 1);
                            for(int i = 0; i != len0; ++i){
                                nptr->val.sval[i] = nptr->children[0]->val.sval[i];
                            }
                            for(int i = 0; i != len1; ++i){
                                nptr->val.sval[i + len0] = nptr->children[1]->val.sval[i];
                            }
                            nptr->val.sval[len0 + len1] = '\0';
                        }
                        break;

                    case TOK_BMINUS:
                        nptr->val.ival = (nptr->children[0]->val.ival) - (nptr->children[1]->val.ival);
                        break;

                    case TOK_TIMES:
                        if(nptr->children[0]->type == INT_TYPE){
                            nptr->val.ival = (nptr->children[0]->val.ival) * (nptr->children[1]->val.ival);
                        }
                        else{
                            if(nptr->children[1]->val.ival < 0){
                                handle_error(ERR_EVAL);
                            }
                            else if(nptr->children[1]->val.ival == 0){
                                nptr->val.sval = malloc(1);
                                nptr->val.sval[0] = '\0';
                            }
                            else{
                                int slen = strlen(nptr->children[0]->val.sval);
                                int llen = slen * nptr->children[1]->val.ival;
                                nptr->val.sval = malloc(llen + 1);
                                for(int i = 0; i != llen; ++i){
                                    nptr->val.sval[i] = nptr->children[0]->val.sval[i % slen];
                                }
                                nptr->val.sval[llen] = '\0';
                            }
                        }
                        break;

                    case TOK_DIV:
                        if(nptr->children[1]->val.ival == 0){
                            handle_error(ERR_EVAL);
                        }
                        else{
                            nptr->val.ival = (nptr->children[0]->val.ival) / (nptr->children[1]->val.ival);
                        }
                        break;

                    case TOK_MOD:
                        if(nptr->children[1]->val.ival == 0){
                            handle_error(ERR_EVAL);
                        }else{
                            nptr->val.ival = (nptr->children[0]->val.ival) % (nptr->children[1]->val.ival);
                        }
                        break;

                    case TOK_AND:
                        nptr->val.bval = (nptr->children[0]->val.bval) && (nptr->children[1]->val.bval);
                        break;

                    case TOK_OR:
                        nptr->val.bval = (nptr->children[0]->val.bval) || (nptr->children[1]->val.bval);
                        break;

                    case TOK_LT:
                        if(nptr->children[0]->type == INT_TYPE){
                            nptr->val.bval = (nptr->children[0]->val.ival) < (nptr->children[1]->val.ival);
                        }
                        else{
                            int len0 = strlen(nptr->children[0]->val.sval);
                            int len1 = strlen(nptr->children[1]->val.sval);
                            for(int i = 0; i <len0 && i < len1; ++i){
                                if(nptr->children[0]->val.sval[i] != nptr->children[1]->val.sval[i]){
                                    nptr->val.bval = ((int)(nptr->children[0]->val.sval[i]) - (int)(nptr->children[1]->val.sval[i])) < 0;
                                    return;
                                }
                            }
                            if(len0 < len1){
                                nptr->val.bval = true;
                                return;
                            }else{
                                nptr->val.bval = false;
                                return;
                            }
                        }
                        break;

                    case TOK_GT:
                        if(nptr->children[0]->type == INT_TYPE){
                            nptr->val.bval = (nptr->children[0]->val.ival) > (nptr->children[1]->val.ival);
                        }
                        else{
                            int len0 = strlen(nptr->children[0]->val.sval);
                            int len1 = strlen(nptr->children[1]->val.sval);
                            for(int i = 0; i <len0 && i < len1; ++i){
                                if(nptr->children[0]->val.sval[i] != nptr->children[1]->val.sval[i]){
                                    nptr->val.bval = ((int)(nptr->children[0]->val.sval[i]) - (int)(nptr->children[1]->val.sval[i])) > 0;
                                    return;
                                }
                            }
                            if(len0 > len1){
                                nptr->val.bval = true;
                                return;
                            }else{
                                nptr->val.bval = false;
                                return;
                            }
                        }
                        break;

                    case TOK_EQ:
                        if(nptr->children[0]->type == INT_TYPE){
                            nptr->val.bval = (nptr->children[0]->val.ival) == (nptr->children[1]->val.ival);
                        }
                        else{
                            nptr->val.bval = true;
                            int len0 = strlen(nptr->children[0]->val.sval);
                            int len1 = strlen(nptr->children[1]->val.sval);
                            if(len0 != len1){
                                nptr->val.bval = false;
                            }
                            else{
                                for(int i = 0; i != len0; ++i){
                                    if(nptr->children[0]->val.sval[i] != nptr->children[1]->val.sval[i]){
                                        nptr->val.bval = false;
                                        break;
                                    }
                                }
                            }
                        }
                        break;

                    default:
                        break;
                }
            }
            if (nptr->tok == TOK_QUESTION) {
                eval_node(nptr->children[0]);
                if(nptr->children[0]->val.bval){
                    eval_node(nptr->children[1]);
                    if(nptr->children[1]->type == BOOL_TYPE){
                        nptr->val.bval = nptr->children[1]->val.bval;
                    }
                    else if(nptr->children[1]->type == INT_TYPE){
                        nptr->val.ival = nptr->children[1]->val.ival;
                    }else{
                        int len = strlen(nptr->children[1]->val.sval);
                        nptr->val.sval = malloc(len + 1);
                        for(int i = 0; i != len; ++i){
                            nptr->val.sval[i] = nptr->children[1]->val.sval[i];
                        }
                        nptr->val.sval[len] = '\0';
                    }
                }else{
                    eval_node(nptr->children[2]);
                    if(nptr->children[2]->type == BOOL_TYPE){
                        nptr->val.bval = nptr->children[2]->val.bval;
                    }
                    else if(nptr->children[2]->type == INT_TYPE){
                        nptr->val.ival = nptr->children[2]->val.ival;
                    }else{
                        int len = strlen(nptr->children[2]->val.sval);
                        nptr->val.sval = malloc(len + 1);
                        for(int i = 0; i != len; ++i){
                            nptr->val.sval[i] = nptr->children[2]->val.sval[i];
                        }
                        nptr->val.sval[len] = '\0';
                    }
                }
            }
            // For reference, the identity (do-nothing) operator has been implemented for you.
            if (nptr->tok == TOK_IDENTITY) {
                eval_node(nptr->children[0]);
                if(nptr->type == STRING_TYPE) {
                    int len = strlen(nptr->children[0]->val.sval);
                    nptr->val.sval = malloc(len + 1);
                    for(int i = 0; i != len; ++i){
                        nptr->val.sval[i] = nptr->children[0]->val.sval[i];
                    }
                    nptr->val.sval[len] = '\0';
                }else if(nptr->type == INT_TYPE){
                    nptr->val.ival = nptr->children[0]->val.ival;
                }else{
                    nptr->val.bval = nptr->children[0]->val.bval;
                }
            }
            break;

        case NT_LEAF:
            break;

        default:
            break;
    }
    return;
}

/* eval_root() - set the value of the root node based on the values of children 
 * Parameter: A pointer to a root node, possibly NULL.
 * Return value: None.
 * Side effect: The val dield of the node is updated. 
 */

void eval_root(node_t *nptr) {
    if (nptr == NULL) return;
    // check running status
    if (terminate || ignore_input) return;

    // check for assignment
    if (nptr->type == ID_TYPE) {
        eval_node(nptr->children[1]);
        if (terminate || ignore_input) return;
        
        if (nptr->children[0] == NULL) {
            logging(LOG_ERROR, "failed to find child node");
            return;
        }
        put(nptr->children[0]->val.sval, nptr->children[1]);
        return;
    }

    for (int i = 0; i < 2; ++i) {
        eval_node(nptr->children[i]);
    }
    if (terminate || ignore_input) return;
    
    if (nptr->type == STRING_TYPE) {
        (nptr->val).sval = malloc(strlen(nptr->children[0]->val.sval) + 1);
        if (! nptr->val.sval) {
            logging(LOG_FATAL, "failed to allocate string");
            return;
        }
        strcpy(nptr->val.sval, nptr->children[0]->val.sval);
    } else {
        nptr->val.ival = nptr->children[0]->val.ival;
    }
    return;
}

/* infer_and_eval() - wrapper for calling infer() and eval() 
 * Parameter: A pointer to a root node.
 * Return value: none.
 * Side effect: The type and val fields of the node are updated. 
 */

void infer_and_eval(node_t *nptr) {
    infer_root(nptr);
    eval_root(nptr);
    return;
}

/* strrev() - helper function to reverse a given string 
 * Parameter: The string to reverse.
 * Return value: The reversed string. The input string is not modified.
 * (STUDENT TODO)
 */

char *strrev(char *str) {
    int len = strlen(str);
    char *rev = malloc(len + 1);
    for(int i = 0; i != len; ++i){
        rev[len - i - 1] = str[i];
    }
    rev[len] = '\0';
    return rev;
}

/* cleanup() - frees the space allocated to the AST
 * Parameter: The node to free.
 */
void cleanup(node_t *nptr) {
    // Week 2 TODO: Recursively free each node in the AST
    if(nptr == NULL)
        return;
    for(int i = 0; i != 3; ++i)
        cleanup(nptr->children[i]);
    if(nptr->type == STRING_TYPE || nptr->type == ID_TYPE)
        free(nptr->val.sval);    
    free(nptr);
}