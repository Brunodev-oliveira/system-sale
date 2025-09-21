#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<regex.h>
#include<locale.h>

struct Cliente{
  char name[30];
  char gender;
  int age;

};
typedef struct Cliente cliente;

struct Venda{
  cliente customer;
  int qtItens;
  char store;
  float price;


};
typedef struct Venda venda;

typedef enum venda_fields{
qt_Sales,
  name,
  gender,
  age,
  qtItens,
  store,
  price,
  priceQuery
}fields;
//====================================Assinatura de funções==============================
void capitalized_case(char *str);
int strlen_utf8(char *str);
void regex_compiler(regex_t *exp);
void clearBuffer();
int inputDecisions_sanitized(char *option);
int input_sanitized(venda *p,float *floatQuery, fields field,int minRange, int maxRange);
void register_sale(venda **sale,int *qtRow);
void sale_forName(venda *sale, int qtRow);
void sales_lessThan(venda *sale, int qtRow);
void sales_withThree_items(venda *sale, int qtRow);
void sales_in_B(venda *sale, int qtRow);
void Get_men(venda *sale, int qtRow);
void sale_genderN(venda *sale, int qtRow);
void Get_itensTotal(venda *sale, int qtRow);
void Get_totalValue(venda *sale, int qtRow);
void sale_averageValue(venda *sale, int qtRow);
void sale_lowPrice_Women(venda *sale, int qtRow);
void Get_youngest(venda *sale, int qtRow);
void Get_biggestName(venda *sale, int qtRow);



//======================================inicio main ===============================
int main(){
  int input = -1;
  char decision;
  int end = 1;
  int option = 0;
  int qtRow = 0;
  char row[60];
  int i = 0;
  venda *sale = NULL;
  FILE *file;

  setlocale(LC_ALL, "pt_BR.UTF-8");
  
  file = fopen("loja.txt","r");
  if(file == NULL){
    printf("Erro ao carregar banco de dados!\n");
    return 1;
  }
  while(fgets(row,sizeof(row),file) != NULL){
    qtRow++;
  }
  rewind(file);
   sale = realloc(sale,qtRow * sizeof(venda));

  if(sale == NULL){
    printf("Erro não foi possível alocar memória");
    return 1;
  }

  while(fscanf(file,"%[^/]/%c/%d/%d/%c/%f/\n",sale[i].customer.name,&sale[i].customer.gender,&sale[i].customer.age,&sale[i].qtItens,&sale[i].store,&sale[i].price) == 6){    
    i++;
  }
  
  fclose(file);



  while(end != 0){ 
    system("clear");   
    printf("============================LOJA DE SALGADINHOS============================\n");  
    printf("===========================================================================\n\n");
    printf("\n               |DIGITE 1 - PARA CADASTRAR UMA VENDA\n");
    printf("\n               |DIGITE 2 - PARA INFORMAÇÕES DE UMA VENDA\n");
    printf("\n               |DIGITE 3 - PARA INFORMAÇÕES DE TODAS AS VENDAS\n");
    printf("\n               |DIGITE 4 - PARA SAIR DO PROGRAMA\n");    
    printf("\n");
    printf("===========================================================================\n");
    printf("===========================================================================\n\n");
    scanf("%d",&option);
    clearBuffer();
    switch(option){
      case 1:
          register_sale(&sale, &qtRow);
        break;
      case 2:
          sale_forName(sale, qtRow);
        break;
      break;
      case 3:
        system("clear");
        
        printf("----------------------------------------------------------------------------------");
        printf("\n");
        sales_lessThan(sale, qtRow);       
        
        printf("\n");
        sales_withThree_items(sale, qtRow);
        sales_in_B(sale, qtRow);
        Get_men(sale, qtRow);
        printf("----------------------------------------------------------------------------------");
        printf("\n");
        printf("----------------------------------------------------------------------------------");
        printf("\n");
        sale_lowPrice_Women(sale, qtRow);
        sale_genderN(sale, qtRow);
        Get_itensTotal(sale, qtRow);
        Get_totalValue(sale, qtRow);
        sale_averageValue(sale, qtRow);
        printf("----------------------------------------------------------------------------------");
        printf("\n");
        printf("----------------------------------------------------------------------------------");
        Get_biggestName(sale, qtRow);
        Get_youngest(sale, qtRow);
            
        

          
        while(1){
          printf("\n Digite (S ou s) para retornar ao menu principal ou (N ou n) "
                 "para encerrar o programa: ");
          input = inputDecisions_sanitized(&decision);
          if (input == 1)break;
        }
        if (decision == 'S' || decision == 's') {
          system("clear");
          break;
        } else {
          printf("Encerando o programa!\n");
          printf("See you later\n");
          sleep(2);
          system("clear");
          end = 0;
        }
        break;
      case 4:
        printf("Encerando o programa!\n");
        printf("See you later\n");
        sleep(2);
        system("clear");
        end = 0;
        break;
      default:
        system("clear");
        printf("Opção inválida!\nDigite novamente\n");
        sleep(2);
        system("clear");
        continue;    

    }
  }
 
  free(sale);


  return 0;
}

//====================================== Definição de funções ===============================
//====================================== inicio regex compiler ===============================
void regex_compiler(regex_t *exp){
  int feedback;
  char *namePattern = "^([a-zA-ZáàâãéêíóôõúçÁÀÂÃÉÊÍÓÔÕÚÇ]+){3,}( [a-zA-ZáàâãéêíóôõúçÁÀÂÃÉÊÍÓÔÕÚÇ]+)*$";
  feedback = regcomp(exp,namePattern,REG_EXTENDED);
  if(feedback){
    fprintf(stderr,"erro ao compilar regex");
  }  
}
//======================================inicio clear buffer ===============================
void clearBuffer(){
  int buffer;
  while((buffer = getchar()) != '\n' && buffer != EOF);

}
//======================================inicio input Decisions sanitized ===============================
int inputDecisions_sanitized(char *option){
  int userTyping;

    userTyping = scanf("%c",option);
    clearBuffer();
    if(userTyping != 1 || (*option != 'n' && *option != 'N' && *option != 's' && *option != 'S') ){
      printf("Opção inválida!\nDigite novamente\n");
      sleep(2);
      system("clear");
      return 0;
  }else{
      return 1;
  }
  
}

//======================================inicio input sanitized ===============================
int input_sanitized(venda *sale,float *floatQuery, fields field,int minRange, int maxRange){
  regex_t expression;
  int feedback;  
  char *string; 
  int userTyping;
  int registerQtSales; 
  regex_compiler(&expression);


  switch(field){
    case qt_Sales:
      userTyping = scanf("%d",&registerQtSales);
      clearBuffer();
      if(registerQtSales < minRange || userTyping != 1){
        printf("Entrada inválida!\n");
        printf("Por favor! Digite um valor válido acima de %d\n", minRange);
        sleep(2);
        system("clear");
        return 0;  
      }else{
        return registerQtSales;
      }
    case name:
      string = fgets(sale->customer.name,sizeof(sale->customer.name),stdin);
      sale->customer.name[strcspn(sale->customer.name,"\n")] = '\0';


      feedback = regexec(&expression,string,0,NULL,0);
      if(!feedback ){   
        regfree(&expression);
        return 1;
      }else if(feedback == REG_NOMATCH){       
        printf("Entrada inválida!\n");
        printf("Por favor! Digite um valor válido\n");
        if (strlen_utf8(sale->customer.name) < 3) {
          printf(" O campo nome deve ter no mínimo 3 letras.\n");
        }        
        sleep(2);
        system("clear");
        return 0;

      }else{
        fprintf(stderr,"Erro ao executar regex\n");
        regfree(&expression);
      }


      break;
    case gender:               
      userTyping = scanf("%c",&sale->customer.gender);
      clearBuffer();
      if(
         sale->customer.gender == 'M' ||  sale->customer.gender == 'm' ||
         sale->customer.gender == 'F' ||  sale->customer.gender == 'f' ||
         sale->customer.gender == 'N' ||  sale->customer.gender == 'n'){
         return 1;
      }else{
        printf("Opção inválida!\nDigite novamente\n");
        sleep(2);
        system("clear");
        return 0;  
      }
      break;
    case age:
      
      userTyping = scanf("%d",&sale->customer.age);
      clearBuffer();
      if((sale->customer.age < minRange || sale->customer.age > maxRange) || userTyping != 1 ){
        printf("Entrada inválida!\n");
        printf("Por favor! Digite um valor válido entre %d e %d\n", minRange,maxRange);
        sleep(2);
        system("clear");
        return 0;
      }else{
        return 1;

      }
      break;
    case qtItens:
      userTyping = scanf("%d",&sale->qtItens);
      clearBuffer();
      if((sale->qtItens < minRange || sale->qtItens > maxRange) || userTyping != 1){
        printf("Entrada inválida!\n");
        printf("Por favor! Digite um valor válido acima de %d\n", minRange);
        sleep(2);
        system("clear");
        return 0;        
      }else{
        return 1;
      }
      break;
    case store:
      userTyping = scanf("%c",&sale->store);
      clearBuffer();
      if(sale->store == 'A' || sale->store == 'a' ||
         sale->store == 'B' || sale->store == 'b' ||
         sale->store == 'C' || sale->store == 'c'){

         return 1;

      }else{
          printf("Opção inválida!\nDigite novamente\n");
          sleep(2);
          system("clear");
          return 0;
      }
      break;
    case price:
      userTyping = scanf("%f",&sale->price);
      clearBuffer();
      if(sale->price < minRange || userTyping != 1){
        printf("Entrada inválida!\n");
        printf("Por favor! Digite um valor válido acima de %d \n", minRange);
        sleep(2);
        system("clear");
        return 0;        
      }else{
        return 1;
      }
      break;
    case priceQuery:
      userTyping = scanf("%f",floatQuery);
      clearBuffer();
      if(*floatQuery < minRange || userTyping != 1){
        printf("Entrada inválida!\n");
        printf("Por favor! Digite um valor válido acima de %d \n", minRange);
        sleep(2);
        system("clear");
        return 0;
      }else{
        return 1;
      }
    default:
      printf("Erro fatal!!!");
      break; 

  }
  return 0;
}
//============================================ inicio register_sale=========================
void register_sale(venda **sale,int *qtRow){
  int count;
  int input = -1;
  char option = 's';
  int qtSales = 0;
  int realloc_amount = 0;
   int *newIndex = qtRow ;
  FILE *file;
  do{
    system("clear");
    printf("==========================CADASTRO DE VENDAS==========================\n");
    printf("\n");
    printf("Para cadastrar uma venda é necessário informar os seguintes dados:\n");
    while(1){
      printf("*Digite quantas vendas deseja cadastrar:\n");
      qtSales = input_sanitized(NULL,NULL,qt_Sales,1,0);
      system("clear");
      count = 1;
      if(qtSales != 0)break;
    }
    realloc_amount = *qtRow + qtSales;
    *sale = realloc(*sale,realloc_amount * sizeof(venda));
    if(sale == NULL){
      printf("Erro Fatal!!!\n");
      break;
    }
    
    for(; *newIndex < realloc_amount; (*newIndex)++){
      printf("==========================CADASTRO DE VENDAS==========================\n");
      for(int i = count; i <= qtSales; i++){
        printf("%c ",35);
      }
      printf("\nPROGRESSO TOTAL %d de %d\n",count,qtSales);
      printf("\n");
       

      while(1){
        
        printf("Informe o nome do cliente:\n");
        input = input_sanitized(&(*sale)[*newIndex],NULL,name,0,0);
         system("clear");
        if(input == 1)break;

      }

      while(1){
        printf("Informe o sexo do cliente: (M) para Masculino, (F) para feminino ou (N) para não declarar:\n");
        input = input_sanitized(&(*sale)[*newIndex],NULL,gender,0,0);
        system("clear");
        if(input == 1)break;

      }
      while(1){      
        printf("Informe a idade do cliente: \n");
        input = input_sanitized(&(*sale)[*newIndex],NULL,age,16,120); 
        system("clear");
        if(input == 1)break;


      }

      while(1){
        printf("Informe a quantidade de itens da venda: \n");
        input = input_sanitized(&(*sale)[*newIndex],NULL,qtItens,1,1000000000);
        system("clear");
         if(input == 1)break;
      }
      while(1){
        printf("Informe a unidade em que a venda ocorreu! Digite (A) para unidade A, (B) para unidade B, ou (C) pra unidade C:\n");
        input = input_sanitized(&(*sale)[*newIndex],NULL,store,0, 0);
        system("clear");
        if(input == 1)break;



      }
      while(1){
        printf("Informe o valor total da venda: \n");
        input = input_sanitized(&(*sale)[*newIndex],NULL,price,1, 0);
        system("clear");
        if(input == 1) break;
      }

      file = fopen("loja.txt", "a");
      if(file == NULL){
        printf("Erro ao carregar banco de dados!\n");
        printf("Erro ao carregar banco de dados!\n");
        printf("Erro ao carregar banco de dados!\n");
        break;
      }
      capitalized_case((*sale)[*newIndex].customer.name);
      capitalized_case(&(*sale)[*newIndex].customer.gender);
      capitalized_case(&(*sale)[*newIndex].store);

      fprintf(file, "%s/",(*sale)[*newIndex].customer.name);
      fprintf(file, "%c/",(*sale)[*newIndex].customer.gender);
      fprintf(file, "%d/",(*sale)[*newIndex].customer.age);
      fprintf(file, "%d/",(*sale)[*newIndex].qtItens);
      fprintf(file, "%c/",(*sale)[*newIndex].store);
      fprintf(file, "%.2f/\n",(*sale)[*newIndex].price);
      
      printf("Venda cadastrada com sucesso!\n");      
      sleep(1);
      count++;
      system("clear");
      fclose(file);    

    }   
    

   
    
    while(1){
      printf("Deseja cadastrar mais vendas?\nDigite (S) para sim ou (N) para voltar para o menu\n");       
      input = inputDecisions_sanitized(&option);   
      system("clear");  
      if(input == 1)break;
    }
    
  }while(option != 'N' &&  option != 'n');

}



//============================================ inicio sale_forName =========================
void sale_forName(venda *sale, int qtRow) {
  char name[30];
  float totalPrice = 0;
  char option = 's';
  int input= -1;
  int exists = 0;

  do {
    totalPrice = 0;
    exists = 0;
    
    printf("Informe o nome do cliente: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    capitalized_case(name);
    system("clear");

    printf("RESULTADOS DA PESQUISA:\n\n");
    

    for (int i = 0; i < qtRow; i++) {
      if (strcmp(name, sale[i].customer.name) == 0) {
        exists++;
        
        printf("================= %dº Resultado:========================\n",exists);     
        printf("------------------------------------\n");
        printf("\n------------------------------------\n");
        printf("|Nome: %s\n", sale[i].customer.name);
        printf("|Loja: %c\n", sale[i].store);      
        printf("|Número de itens: %d\n", sale[i].qtItens);
        printf("|Valor total da compraR$: %.2f Reais", sale[i].price);        
        printf("\n------------------------------------\n\n");
       
        totalPrice += sale[i].price;
       
      }
    }

    if (exists) {
      printf("O valor total comprado pelo cliente %s é R$: %.2f Reais\n", name,
             totalPrice);
    } else {
      printf("Nemhuma compra encontrada para o cliente %s\n", name);
    }
    while (1){
    printf("\nDeseja pesquisar mais vendas (S) para sim ou (N) para voltar para o menu:\n ");
    input = inputDecisions_sanitized(&option);
    sleep(1);
    system("clear"); 
    
    if(input == 1)break;      
    }


  }while(option != 'n' && option != 'N');
}

//============================================ inicio sales_lessThan =========================
void sales_lessThan(venda *sale, int qtRow) {
  
  float query = 0 ;
  int input = -1;
  int exists = 0;

  
  while(1){
    
   
    printf("Informe um valor para verificar a quantidade de vendas abaixo deste: \n");
    input = input_sanitized(NULL,&query, priceQuery, 1, 0);
    
    if(input == 1){
      for (int i = 0; i < qtRow; i++) {
        if (query > sale[i].price) {
          exists++;
        }
      }
      if (exists > 0) {
        printf("\n--------");                       
        printf("\n--------RELATÓRIO:----------------------------------------------------------------\n");
        printf("-------- \n\n");  
        printf("\nForam encontradas %d vendas abaixo de R$: %.2f Reais\n",exists,query);
        break;
      } else {
        printf("\nNão Foi encontrada nehuma venda abaixo de R$: %.2f Reais\n",query);
        break;
      }

      
    } 

  }   
  
}
//============================================ inicio sales_withThree_items =========================

void sales_withThree_items(venda *sale, int qtRow) {
  
  int exists = 0;

  for (int i = 0; i < qtRow; i++) {
    if (sale[i].qtItens == 3) {
      exists++;
    }
  }
  printf("\nForam encontradas %d vendas com 3 itens.\n", exists);
}
//============================================ inicio sales_in_B =========================
void sales_in_B(venda *sale, int qtRow) {
  int exists = 0;
  for (int i = 0; i < qtRow; i++) {
    if (sale[i].store == 'B' || sale[i].store == 'b') {
        exists++;
    }
  }
  printf("\nForam encontradas %d vendas na unidade B.\n", exists);
}
//============================================ inicio Get_men =========================
void Get_men(venda *sale, int qtRow) {
  int exists = 0;
  int reponse;
  for (int i = 0; i < qtRow; i++) {
    if (sale[i].customer.gender == 'M' || sale[i].customer.gender == 'm') {
        exists++;
    }
  }
  if (exists > 0) {
    reponse = exists == 1 ? printf("\nFoi encontrado apenas %d cliente homen.\n", exists) : printf("\nForam encontrados %d clientes homens.\n", exists);
  } else {
    printf("\nNão foi encontrado nenhum cliente homen.\n");
  }
}
//============================================ inicio sale_genderN =========================
void sale_genderN(venda *sale, int qtRow) {
  
  float contGenderN = 0;

  for (int i = 0; i < qtRow; i++) {
    if (sale[i].customer.gender == 'N' || sale[i].customer.gender == 'n') {
      contGenderN += sale[i].price;
    }
  }
  if (contGenderN > 0) {
    printf(
        "\nO valor total das vendas em que não declararam o sexo "
        "é R$: %.2f Reais\n",
        contGenderN);
  } else {
    printf("\nNão foi encontrado comprardor Que não declarou o sexo.\n");
  }
}

//============================================ inicio Get_itensTotal =========================

void Get_itensTotal(venda *sale, int qtRow) {
  
  int contQtItens = 0;

  for (int i = 0; i < qtRow; i++) {
    contQtItens += sale[i].qtItens;
  }
  if (contQtItens > 0) {
    printf("\nO total de itens vendidos é: %d itens\n", contQtItens);
  } else {
    printf("\nNenhum item foi encontrado.\n");
  }
}
//============================================ inicio Get_totalValue =========================
void Get_totalValue(venda *sale, int qtRow) {
  float totalValue = 0;

  for (int i = 0; i < qtRow; i++) {
    totalValue += sale[i].price;
    
  }
  printf("\nO valor total em vendas é de R$: %.2f Reais\n",totalValue);
  
}
//============================================ inicio sale_averageValue =========================
void sale_averageValue(venda *sale, int qtRow) {
  float totalValue = 0;
  float averageValue = 0;

  for (int i = 0; i < qtRow; i++){
    totalValue += sale[i].price;
  }
  averageValue = totalValue / qtRow;
  printf("\nO valor médio de uma venda é R$: %.2f Reais\n", averageValue);
}
//============================================ inicio sale_lowPrice_Women =========================
void sale_lowPrice_Women(venda *sale, int qtRow) {
  float lowPrice = 0;
  for (int i = 0; i < qtRow; i++) {
    if (sale[i].customer.gender == 'F' || sale[i].customer.gender == 'f') {
      if (sale[i].price < lowPrice || lowPrice == 0) {
        lowPrice = sale[i].price;
      }
    }
  }
  printf("\nA compra mais barata feita por uma mulher foi de R$: %.2f Reais\n",lowPrice);
}
//============================================ inicio get biggestName =========================

void Get_biggestName(venda *sale, int qtRow) {
  int maior = 0;
  int i = 0;
  

  for (int i = 0; i < qtRow; i++) {
    if( strlen_utf8(sale[i].customer.name) > maior){
      maior = strlen_utf8(sale[i].customer.name);
    }      
      
  }
  printf("\n--------                       --------");
  printf("\n--------CLIENTE COM MAIOR NOME:--------\n");
  printf("--------                       --------\n");
  for (int i = 0; i < qtRow; i++) {
    while (maior == strlen_utf8(sale[i].customer.name)) {

      printf("\n------------------------------------\n");

      
      printf("\n------------------------------------\n");
      printf("|Nome: %s\n", sale[i].customer.name);
      printf("|Sexo: %c\n", sale[i].customer.gender);
      printf("|Idade: %d\n", sale[i].customer.age);
      printf("|Quantidade de itens: %d\n", sale[i].qtItens);
      printf("|Loja: %c\n", sale[i].store);
      printf("|Preço: %.2f", sale[i].price);
      printf("\n------------------------------------\n");

      
      i++;
    }
  }
}

//============================================ inicio Get_youngest =========================
void Get_youngest(venda *sale, int qtRow) {

  int young;

  for (int i = 0; i < qtRow; i++) {
    if (sale[i].customer.age < young || i == 0) {
      young = sale[i].customer.age;
    }
  }

  printf("\n--------                       --------");
  printf("\n--------CLIENTE MAIS JOVEM:--------\n");
  printf("--------                       --------\n");
  for (int i = 0; i < qtRow; i++) {
    while (young == sale[i].customer.age) {
      
      printf("\n------------------------------------\n");


      printf("\n------------------------------------\n");
      printf("|Nome: %s\n", sale[i].customer.name);
      printf("|Sexo: %c\n", sale[i].customer.gender);
      printf("|Idade: %d\n", sale[i].customer.age);
      printf("|Quantidade de itens: %d\n", sale[i].qtItens);
      printf("|Loja: %c\n", sale[i].store);
      printf("|Preço: %.2f", sale[i].price);
      printf("\n------------------------------------\n");
      i++;
    }
  }
}


//============================================ inicio strlen_utf8 =========================
int strlen_utf8(char *str){
  int count = 0;
  while(*str){
    if((unsigned char)*str <= 0xBF && (unsigned char)*str != 0x20){
      count++;
    }
    str++;
  }
 return count; 
}
//============================================ inicio capitalized_case =========================
void capitalized_case(char *str){
  char *strPosition_zero = str;
  while(*str){
    if(strPosition_zero == str){
      if((unsigned char)*str >= 0x61 && (unsigned char)*str <= 0x7A){       
        *str = *str - 0x20;
      }else if((unsigned char)*str == 0xC3){
        ++str;
        if((unsigned char)*str >= 0xA0 && (unsigned char)*str <= 0xBA)
            *str = *str - 0x20;
        }
      }else if((unsigned char)*str>= 0x41 && (unsigned char)*str <= 0x5A){
      *str = *str + 0x20;

    }else if((unsigned char)*str == 0xC3){
      str++;
      if((unsigned char)*str >= 0x80 && (unsigned char)*str <= 0x9A)
        *str = *str + 0x20;


    }
    str++;
  }


}



