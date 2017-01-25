/*
 * Definição de uma estrutura auxiliar para guardar os valores das horas de partida dos voos constítuido por um
 * inteiro que aramazena a componente das horas e outro que aramazena os minutos
 */
typedef struct
{
  int horas;
  int mins;
} HORAS;


/*
 * 
 *
 *Esta estrutura tem a seguinte forma:
 *										-----------------------------------------------------
 *										|									|Aeroporto 	de	|Aeroporto de			|
 *										|Código de voo		|Origem					|chegada					|
 *										|									|								|									|
 *										-----------------------------------------------------
 *										|Horas da partida |Horas da 			|Apontador para		|
 *										|									|chegada				|o próximo 				|
 *										|									|								|Voo							|
 *										-----------------------------------------------------
 *										|Preço do voo			|
 *										|									|
 *										|									|
 *										-------------------
 *
 *
 */

struct voo
{
  char codigo[6+1], origem[3+1], destino[3+1];
  HORAS	partida, chegada;
  float preco;
  struct voo *proximo;
  int estado;
};

struct percurso {
  char codigo[6+1];
  struct percurso *proximo;
};

struct lista_voos {
  struct percurso *inicio;
  struct percurso *fim;
};

/*
 *Definição do 
 */
typedef struct voo * LISTA;

