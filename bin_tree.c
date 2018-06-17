#include "bin_tree.h"
#include <stdio.h>
#include <stdlib.h>


/*cria novo no*/
struct b_node *new_b_node (void *data)
{
  struct b_node *new  =  (struct b_node *)malloc (sizeof(struct b_node));
  
  if (new == NULL)
    {
      printf ("\t>>Sem memoria para alocar no!\n");
      return NULL;
    }
  
  new->data = data;
  new->right_son =  NULL;
  new->left_son = NULL;
  
  return new;
}


/*acidiona o nó "nd", à arvore apontada por bthree*/
void add_b_node (struct b_node **btree, struct b_node *nd, int (*compare) (struct b_node *, struct b_node *))
{
  if (*btree == NULL)
  {
    *btree = nd;
    return;
  }
  else
  {
    struct b_node *i = *btree;
    
    while (1)
    {
      if ((*compare)(nd,i) > 0)
      {
          if (i->right_son  == NULL)
          {
            i->right_son = nd;
            break;
          }
          else
          {
            i = i->right_son;
          }
      }
      else
        {
          if (i->left_son  == NULL)
          {
            i->left_son = nd;
            break;
          }
          else
          {
            i = i->left_son;
          }
        }
    }
  }
}

/*Retorna 3 para ambos, 2 para filho direito, 1 para esquerdo, 0 para nenhum e -1 p/ erro*/
int sons_of (struct b_node *father)
{
  int sons = 3;
  if (father != NULL)
    {
      if (father->left_son == NULL)
        sons -= 1;
      
      if (father->right_son == NULL)
        sons -= 2;
    }
    else
        sons = -1;  /*erro*/
    
  return sons;
}

int get_degree (struct b_node *father)
{
  int s = sons_of (father);
  return (s != 3)? s: 2;
}

int get_tree_degree (struct b_node *tree)
{
  int a, b, c;
  if (tree != NULL)
    {
      a = get_tree_degree (tree->left_son);
      b = get_degree (tree);
      c = get_tree_degree (tree->right_son);
      
      if (a > b) /*  c > a ou b > c */
        {
          if (c > a)
              return c; 
          return a;
        } /* implica que  b > a */
        else if (c > b) /*c é o maior*/
            return c;
        else
          return b; /*b é o maior*/
    }
    return 0;
}



/*apaga a arvore*/
void destroy_tree (struct b_node **btree)
{
  struct b_node *tree = *btree;
  if (tree != NULL)
    {
      destroy_tree (&(tree->left_son));
      destroy_tree (&(tree->right_son));
      free (tree);
    }
    
  *btree = NULL;
  
}


/*retorna a profundidade do nível da arvore. retorna 0 se a arvore esta vazia*/
static int get_level2 (struct b_node *tree)
{
  int left_tree_level = 0;
  int right_tree_level = 0;
  
  if (tree != NULL)
    {
      left_tree_level = get_level2 (tree->left_son) +1;
      right_tree_level = get_level2 (tree->right_son) +1;
    }
  
  /*retorna o maior caminho*/
  if (left_tree_level > right_tree_level)
    return left_tree_level;
  else
    return right_tree_level;
}

int get_level (struct b_node *tree)
{
  return (get_level2(tree) - 1);
}

void in_order (struct b_node *tree, void (*print_node) (struct b_node *node))
{
    if (tree != NULL)
      {
        in_order(tree->left_son, print_node);       /*adiciona a arvore filha esquerda */
        (*print_node) (tree);                       /*exibe o no*/
        in_order(tree->right_son, print_node);      /*adiciona a arvore filha direita*/
      }
}

static struct b_node **help_choose_son (struct b_node *father, struct b_node *node)
{
  if (father->left_son == node)
    {
      return &(father->left_son);
    }
    else if (father->right_son == node)
      {
        return &(father->right_son);
      }
      else 
        return NULL;
}

int rm_b_node (struct b_node *father, struct b_node *node, void (*deal_with)(struct b_node *, struct b_node **, struct b_node *))
{
  struct b_node **choosed_son = help_choose_son (father, node);
  
  /*node não é filho*/
  if (choosed_son == NULL)
    return -1;

  if (node->left_son == NULL || node->right_son == NULL)
    {
      /*nó terminal*/
      if (node->left_son == NULL && node->right_son == NULL)
        {
          free (node);
          *choosed_son = NULL;
        }
        else if (node->left_son != NULL)  /*tem somente filho esquerdo*/
          {
            *choosed_son = node->left_son;
            free(node);
          }
          else  /*tem somente filho direito*/
            {
              *choosed_son = node->right_son;
              free(node);
            }
            
    }
    else  /*tem 2 filhos*/
      {
        (*deal_with)(father, choosed_son, node);
      }
}
