#include <stdio.h>
#include <stdlib.h>
#include "bin_tree.h"



/*função criterio*/
int compare (struct b_node *a, struct b_node *b)
{
  if (*((int *) a->data) > *((int *) b->data))
    return 1;
  else
    return -1;
}

/*função de tratamento (para a função de remoção)*/

void deal_with (struct b_node *father, struct b_node **choosed_son, struct b_node *node)
{
  void *tmp = NULL;
  struct b_node *current_father = node;
  struct b_node *current = node->right_son;
  
  /*pega  o menor da subarvore direita*/
  while (current->left_son != NULL)
    {
      current_father = current;
      current = current->left_son;
    }
  
  /*copia os dados (na verdade, faz uma troca de ponteiros)*/
  tmp = node->data;
  node->data = current->data;
  current->data = tmp;
  
  rm_b_node (current_father, current, &deal_with);  /*exclui o nó*/
}


/*função que exibe um nó*/
void print_node (struct b_node *nd)
{
  printf ("\t %d ", *((int *) nd->data));
}


/*exibe os nós e os respectivos graus*/
void print_levels (struct b_node *tree)
{
  if (tree != NULL)
    {
      print_levels (tree->left_son);
      printf ("  [%d. g = %d] ",  *((int *) tree->data), get_degree(tree));
      print_levels (tree->right_son);
    }
}

int main (int argc, char *argv[])
{
  int m = 5;
  int n[] = {3,2,4,6,8,7,10,9,20,18,15,19};
  struct b_node *tree = NULL;

  
 
  /*adiciona os nós*/
  printf ("Testando criação e inserção... Adicionando nós\n");
  int i = 0;
  for (i = 0; i < 12; i++)
    add_b_node (&tree, new_b_node (&n[i]), compare);
  printf (">>Ok. Feito.\n\n");
  
  printf ("Exibindo a arvore 'in-order'\n");
  in_order (tree, print_node);
  printf ("\n");
  printf (">>Ok. Feito.\n\n");
  
  printf ("Calculando altura da arvore\n");
  int sz = get_level (tree);
  printf ("Altura: %d\n", sz);
  printf (">>Ok. Feito.\n\n");
  
  printf ("Obtendo os graus dos nós\n");
  print_levels (tree);
  printf ("\n>>Ok. Feito.\n\n");
  
  printf ("Obtendo o grau da arvore\n");
  int degree = get_tree_degree(tree);
  printf ("Grau: %d\n", degree);
  printf (">>Ok. Feito.\n\n");
  
  printf ("Obtendo o nível da arvore\n");
  int lvl = get_level(tree);
  printf ("Nível: %d\n", lvl);
  printf (">>Ok. Feito.\n\n");
  
  printf ("Excluindo o filho direito no nó raiz da arvore\n");
  struct b_node *ls = tree->right_son;
  in_order (tree, print_node);
  rm_b_node (tree, ls, &deal_with);
  printf("\nDepois de excluído\n");
  in_order (tree, print_node);
  printf ("\n>>Ok. Feito.\n\n");
  
  
  
  
  destroy_tree (&tree);
  return (0);
}
