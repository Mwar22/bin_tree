#ifndef BTREE_H
#define BTREE_H

/*Declaracao incompleta para a estrutura de lista*/
struct node;

/*estrutura que representa um nó da arvore*/
struct b_node
{
  void *data;
  struct b_node *left_son;
  struct b_node *right_son;
};

typedef enum {preorder, inorder, posorder} order;





struct b_node *new_b_node (void *data);

/*  Name: add_b_node.
 *  Description: Adiciona o nó.
 *  Parameters:
 *    btree: Endereço do ponteiro que aponta para root
 *    nd: Nó a ser adicionado.
 *    compare: Ponteiro para a função de "critério" para a inserção        
 * 
 */
void add_b_node (struct b_node **btree, struct b_node *nd, int (*compare) (struct b_node *, struct b_node *));


/*  Name:rm_b_node.
 *  Description: Remove um nó.
 *  Parameters:
 *    father: Pai do nó a ser removido.
 *    node: Nó a ser removidos
 *    deal_with: ponteiro para função que trata a remoção no caso em que o nó escolhido
 *    tem 2 filhos.Recebe 3 parametros: 1º indica o pai do nó. 2º armazena
 *    o endereço do ponteiro que aponta para o nó (dentro do pai).O 3º é o proprio nó.
 *    
 * 
 *  Return: Retorna um inteiro que indica se deu tudo certo.
 *          caso não, retorna -1.
 */
int rm_b_node (struct b_node *father, struct b_node *node, void (*deal_with)(struct b_node *, struct b_node **, struct b_node *));


/*  Name:sons_of.
 *  Description: Conta quantos filhos tem um nó.
 *  Parameters:
 *    father: Ponteiro para o nó que sera pai de nd.
 * 
 *  Return: Retorna 3 para ambos, 2 para filho direito, 1 para esquerdo, 0 para nenhum e -1 p/ erro
 */
int sons_of (struct b_node *father);


/*  Name:destroy_tree.
 *  Description: Desaloca a arvore.
 *  Parameters:
 *    tree: Ponteiro para o ponteiro que armazena o endereço da arvore
 */
void destroy_tree (struct b_node **tree);


/*  Name:get_level.
 *  Description: Obtem o nível(altura) da arvore.
 *  Parameters:
 *    tree: Ponteiro para o nó raiz.
 * 
 *  Return: Retorna um inteiro de 0 ao nível, e -1 caso a arvore esteja vazia
 */
int get_level (struct b_node *tree);


/*  Name:get_degree.
 *  Description: Obtem o grau do nó.
 *  Parameters:
 *    nd: Ponteiro para o nó.
 * 
 *  Return: Retorna um inteiro de 0 a 2
 */
int get_degree (struct b_node *nd);

/*  Name:get_tree_degree.
 *  Description: Obtem o grau da arvore.
 *  Parameters:
 *    tree: Ponteiro para o nó raiz.
 * 
 *  Return: Retorna um inteiro de 0 a 2
 */
int get_tree_degree (struct b_node *tree);

/*  Name:in_order.
 *  Description: exibe os nós da árvore in-order.
 *  Parameters:
 *    tree: Ponteiro para o nó raiz.
 *    print_node: ponteiro para uma função responsável por exibir um no
 * 
 *  Return: Retorna um inteiro de 0 a 2
 */
void in_order (struct b_node *tree, void (*print_node) (struct b_node *node));

#endif
