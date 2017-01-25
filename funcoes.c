/*
 * Função que compara duas estruturas do tipo HORAS e devolve um valor de
  * verdade se o primeiro argumento for maior ou igual ao segundo 
 */
int cmphoras(HORAS var1, HORAS var2)
{
  if(var1.horas == var2.horas){
    return (var1.mins >= var2.mins);}
  else
    if(var1.horas >= var2.horas){
      return (var1.horas >= var2.horas);}
    else{
      return (var1.horas >= var2.horas);}
}

/* 
 * converte: Coloca dois inteiros numa estrutura do tipo HORAS e devolve a mesma  
 */
HORAS converte(int h, int m)
{
  HORAS aux;
  aux.horas = h;
  aux.mins = m;
  return aux;
}

/*
 * Função que soma duas estruturas do tipo HORAS e devolve o resultado
 */

HORAS SomaHoras(HORAS var1, HORAS var2) {
  int soma;

  if(((var1.mins)+(var2.mins)) >= 60) 
    {
      (var1.mins) = (((var1.mins)+(var2.mins)) - 60);
      soma = 1; 
    }
  else
    {
      (var1.mins) = ((var1.mins)+(var2.mins));
      soma = 0;
    }

  if(((var1.horas)+(var2.horas)+soma) >= 24)
     (var1.horas) = (((var1.horas)+(var2.horas)+soma) - 24);
  else
     (var1.horas) = ((var1.horas)+(var2.horas)+soma);

 return var1;
}



/* 
 * reverse:  inverte a string s  
 */
void reverse(char s[])
{
  int i, j;
  char c;
 
  for (i = 0, j = strlen(s)-1; i<j; i++, j--)
    {
      c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
}

/* 
 * itoa: converte uma string para um numero inteiro 
 */
void itoa(int n, char s[])
{
  int i, sign;
  if ((sign = n) < 0)   
    n = -n;          
  i = 0;
  do 
    {  
      s[i++] = n % 10 + '0';  
    } 
  while ((n /= 10) > 0);    
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}


/*
 * Esta função irá percorrer a lista dos voos guardados e irá fazer uma "estatística" de todos os voos 
 * Presentes na lista até ao momento (só os contabiliza se o estado do voo que indica se o aeroporto
 * estiver aberto). Devolve um vector com o output correspondente.
 */
char* pedidoInfoI(char* aero, char* info, int contaOrig, int contaDesti, float maisbarato, HORAS maistarde, char* baratoDesti, char * tardioDesti, LISTA* lista)
{

  if( (*lista) != NULL)
    {
      if( (*lista)->estado == 1)
        {
          if(strcmp(aero, (*lista)->origem) == 0) 
            { 
              if( ((*lista)->preco <= maisbarato) && (cmphoras((*lista)->partida, maistarde)))
                pedidoInfoI(aero, info, ++contaOrig, contaDesti, (*lista)->preco, (*lista)->partida, (*lista)->destino, (*lista)->destino, &(*lista)->proximo);    
              else
                if((*lista)->preco <= maisbarato)
                  pedidoInfoI(aero, info, ++contaOrig, contaDesti, (*lista)->preco, maistarde, (*lista)->destino, tardioDesti, &(*lista)->proximo);
                else
                  if(cmphoras((*lista)->partida, maistarde))
                    pedidoInfoI(aero, info, ++contaOrig, contaDesti, maisbarato, (*lista)->partida, baratoDesti, (*lista)->destino, &(*lista)->proximo);
                  else
                    pedidoInfoI(aero, info, ++contaOrig, contaDesti, maisbarato, maistarde, baratoDesti, tardioDesti, &(*lista)->proximo);
            }
          else
            if(strcmp(aero, (*lista)->destino) == 0)
              pedidoInfoI(aero, info, contaOrig, ++contaDesti, maisbarato, maistarde, baratoDesti, tardioDesti, &(*lista)->proximo);
            else
              pedidoInfoI(aero, info, contaOrig, contaDesti, maisbarato, maistarde, baratoDesti, tardioDesti, &(*lista)->proximo);
        }
      else
        pedidoInfoI(aero, info, contaOrig, contaDesti, maisbarato, maistarde, baratoDesti, tardioDesti, &(*lista)->proximo);
    }
  else
    { 
      char aux1[4+1], aux2[4+1];
      itoa(contaOrig , aux1);
      itoa(contaDesti , aux2);
      strcpy(info, aero);
      strcat(info, " ");
      strcat(info, aux1);
      strcat(info, " ");
      strcat(info, aux2);
      strcat(info, " ");
      strcat(info, baratoDesti);
      strcat(info, " ");
      strcat(info, tardioDesti);
    }
  return info;
}

/*
 * Esta função insere um voo na lista dos dados na primeira posição da lista fazendo alocação da memória
 * necessária para tal.
 */
void insereVoo(char *codigo, char *origem, char *destino, HORAS partida, HORAS chegada, float preco, LISTA *lista)
{
  LISTA aux = *lista;

  *lista = (LISTA) malloc(sizeof(struct voo));
  strcpy((*lista)->codigo, codigo);
  strcpy((*lista)->origem, origem);
  strcpy((*lista)->destino, destino);
  (*lista)->partida.horas = partida.horas;
  (*lista)->partida.mins = partida.mins;
  (*lista)->chegada.horas = chegada.horas;
  (*lista)->chegada.mins = chegada.mins;
  (*lista)->preco = preco;
  (*lista)->estado = 1;
  (*lista)->proximo = aux;
}

/*
 * Esta função procura na lista dos dados os voos que têm partida e destino
 * em determinado aeroporto. Ao encontrá-los altera o estado dos voos 
 * para zero
 */
void fechaAero(char* aero, LISTA *lista)
{
  if((*lista) == NULL)
    return;
  else
    if(strcmp(aero, (*lista)->origem) == 0 || strcmp(aero, (*lista)->destino) == 0)
      {
        (*lista)->estado = 0;
        fechaAero(aero, &(*lista)->proximo);
      }
    else
      fechaAero(aero, &(*lista)->proximo);
}

/*
 * Esta função procura na lista dos dados os voos que têm partida e destino
 * em determinado aeroporto. Ao encontrá-los altera o estado dos voos 
 * para um
 */
void abreAero(char* aero, LISTA *lista)
{
  if((*lista) == NULL)
    return;
  else {
    if(strcmp(aero, (*lista)->origem) == 0 || strcmp(aero, (*lista)->destino) == 0)
      {
        (*lista)->estado = 1;
        abreAero(aero, &(*lista)->proximo);
      }
    else
      abreAero(aero, &(*lista)->proximo);
  }
}

/*
 * Esta função procura um voo na lista dos dados e ao encontrá-lo apaga-o
 * da lista libertando a memória alocada para tal e altera os ponteiros de
 * modo a o elemento anterior da lista apontar para o seguinte
 */
void cancelaVoo(char* voo, LISTA *lista)
{
  if( (*lista) == NULL)
    return;
  else
    if( strcmp( voo, (*lista)->codigo) == 0)
      {
        LISTA aux = (*lista);
        free(*lista);
        (*lista) = aux->proximo;
        return;
      }
    else
      cancelaVoo(voo, &(*lista)->proximo);
}

/*
 * Esta função procura na lista dos dados um voo e adia as horas de partida
 * e de chegada do mesmo
 */
void adiaVoo(char* voo, HORAS horas, LISTA *lista)
{
  if ( (*lista) == NULL)
    return;
  else{
    if ( (*lista)->estado == 1)
      {
        if (strcmp(voo, (*lista)->codigo) == 0)
          {
            HORAS aux = SomaHoras((*lista)->partida, horas);
            (*lista)->partida.horas = aux.horas;
            (*lista)->partida.mins = aux.mins;
            aux = SomaHoras((*lista)->chegada, horas);
            (*lista)->chegada.horas = aux.horas; 
            (*lista)->chegada.mins = aux.mins;
          }
        else
          adiaVoo(voo, horas, &(*lista)->proximo);
      }
    else
      adiaVoo(voo, horas, &(*lista)->proximo);
  }
}
/*
 * Recebe um vector que contem a informacao de uma linha "p" e copia para
 * outro vector todo o conteudo a partir da posicao 12 (que e onde se
 * encontra os codigos de voo). 
 */
 
char* dadosPercurso(char* dados, char* aux)
{
  int i=12, j=0;

  while(dados[i] != '\n')
    { aux[j]=dados[i];
     ++i;
     ++j;
    }
  return aux;
}

/*
 * Recebe um vector com um codigo de voo e insere-o na estrutura.
 */

void separaDados(char* codigo, struct lista_voos *voos)
{
  struct percurso *novo_fim = (struct percurso*) malloc(sizeof(struct percurso));
  strcpy(novo_fim->codigo, codigo);
  
  if (voos->fim) 
    {
      voos->fim->proximo = novo_fim;
      voos->fim = novo_fim;
    } 
  else 
    {
      voos->inicio = novo_fim;
      voos->fim = novo_fim;
    }
}

/*
 * Recebe um vector com codigos de voo e separa-os em vários vectores.
 */
 
void insereDados(char* codigos, char* codigo, struct lista_voos *lista)
{
  int i=0, j=0;
  strcat(codigos, "@");
  
  while(codigos[j] != '\0')
    {
      if(codigos[j] == ' ' || codigos[j] == '@')
        {
          separaDados(codigo, lista);
          i=0;
        }
      else
        {
          codigo[i]=codigos[j];
          ++i;
        }
      ++j;
    }
}

/*
 * Converte o tipo HORAS em string.
 */

char* itoahoras(HORAS hora, char* vhora)
  {
    char aux[2+1];
    char aux2[5+1]="0";
    
    if (hora.horas < 10) {
      itoa((hora.horas), aux);
      strcat(aux2, aux);
    }
    else {
      itoa((hora.horas), aux);
      strcpy(aux2, aux);
    }
    strcat(aux2, ":");

    if (hora.mins < 10) {
      strcat(aux2, "0");
      itoa((hora.mins), aux);
      strcat(aux2, aux);
    }
    else {
    itoa((hora.mins), aux);
    strcat(aux2, aux);
    }
    strcpy(vhora, aux2);
    return vhora;
}   
/*
 * Vai percorrer a lista de voos e verifica se os codigos de voos fornecidos 
 * existem nesta. Caso existam devolve uma string com a informação do percurso: 
 * o preco total, horas de partida em cada aeroporto e o aeroporto em questão.
 */

char* pedidoInfoP(char* orig, char* dest, int contador, char* output, struct lista_voos *voo, LISTA* lista)
{
  char origem[3+1]="";
  char estado[2+1]="";
  char aux[(3+1+5+1)*1000]="";
  char prec[10]="";
  char horas[2+1+2+1];
  float preco=0;
  
  strcpy(origem, orig);
  
  while(contador >= 0) {
    --contador;
    
    if(contador == 0) {  /* Contador a 0?*/
      LISTA codigos = (*lista);
      while( codigos != NULL) { /* Enquanto não chegar ao fim da lista */
        if( strcmp(codigos->codigo, voo->inicio->codigo) == 0) {  /* VOOS == VOOS ?*/
          if((codigos->estado == 1) && (strcmp( codigos->origem , origem) == 0) && (strcmp(codigos->destino, dest) ==0) ) {
            strcpy(estado, "OK");
            preco = codigos->preco + preco;
            strcat(aux, " ");
            strcat(aux, codigos->origem);
            strcat(aux, " ");
            itoahoras(codigos->partida, horas);
            strcat(aux, horas);
            strcpy(output, estado);
            strcat(output, " ");
            sprintf(prec, "%.2f", preco);
            strcat(output, prec);
            strcat(output, aux);
            return output;
          } else {
              strcpy(estado, "KO");
              strcpy(output, estado);
              return output;
              }
        }
        else codigos = codigos->proximo;
      }
    }
    else {/* Contador maior que 0 */
      LISTA codigos = (*lista);
      while(codigos != NULL) { /*Enquanto não chegar ao fim da lista*/
        if(strcmp(codigos->codigo, voo->inicio->codigo) == 0) {
          if((codigos->estado == 1) && (strcmp(codigos->origem, origem) == 0)) {
            strcpy(origem, codigos->destino);
            strcpy(estado, "OK");
            preco = codigos->preco + preco;
            strcat(aux, " ");
            strcat(aux, codigos->origem);
            strcat(aux, " ");
            itoahoras(codigos->partida, horas);
            strcat(aux, horas);
            voo->inicio = voo->inicio->proximo;
            break;
          }else {
              strcpy(estado, "KO");
              strcpy(output, estado);
              return output;
              }        
        }
        else { codigos=codigos->proximo; }
      }
    }
  }
  strcpy(estado, "KO");
  strcpy(output, estado);
  return output;
}
