#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define Cred "\e[0;31m"
#define Cgreen "\e[0;32m"
#define Cyellow "\e[0;33m"
#define Cblue "\e[0;34m"
#define Cpurple "\e[0;35m"
#define Ccyan "\e[0;36m"
#define Cwhite "\e[0;37m"

void opcaoMenu(), opcaoInvalida(),opcaoRelatorio(), infoCarro();

struct TCarro{
    char modelo[20];
char cor[20];
    int ano;
};

void flush_in(){
  int ch;
  while((ch = fgetc(stdin)) != EOF && ch != '\n'){}
}

int main(void){
 
  printf (Cgreen"\n\nPrograma feito por: Henrique Silva Pereira dos Santos\n\n");
  printf ("\n\nEste programa serve para gerenciar O POSTO DO CHAPA !!!!!!\n\n");
  printf ("\n\n"Cwhite);

  // Validação do preço do combusível
 float preco_combustivel = 0; 
 bool Validacao_PrecoCombustivel = false;
  while(Validacao_PrecoCombustivel == false){
    printf(Cwhite"Digite o preço do combustível, por favor utilizar ponto no lugar da virgula para numeros quebrados: \n");
    scanf("%f", &preco_combustivel);
     if(preco_combustivel > 0){
      Validacao_PrecoCombustivel = true;  
    }
    else{
      system("clear");
      printf(Cred "PREÇO DE COMBUSTÍVEL INVÁLIDO, POR FAVOR DIGITE UM VALOR MAIOR QUE 0\n\n");
    }
  }
// Validação fila
   int tamanho_fila,  fila_atual=0;  
  bool validacao_fila = false;
  
  while(validacao_fila == false){
    printf(Cwhite"\nInforme o tamanho máximo da fila que o posto suporta: \n");
    scanf("%d", &tamanho_fila);

    if(tamanho_fila > 0){
      validacao_fila = true;
    }
    else{
      system("clear");
      printf( Cred "\nTAMANHO DE FILA INVÁLIDO, POR FAVOR DIGITE UM VALOR MAIOR QUE 0\n\n" Cwhite); 
    }
  }
  
     printf ("\n");
  
   // mostrando a definição dos valores iniciais
   system("clear");
  printf(Cpurple "\n TODOS OS VALORES DOS DADOS INICIAIS FORAM DEFINIDOS\n\n");
  printf(Cgreen "\nO Preço da gasolina foi definido como: R$%.2f", preco_combustivel);
  printf(Cgreen "\nO número máximo da fila foi definido como: %d\n\n", tamanho_fila);


  // Criação dos dois vetores, Carros Na fila e Carros Atendidos.
  struct TCarro *carrosNAfila, *carrosAtendidos;
    carrosNAfila = (int*)malloc(tamanho_fila * sizeof(struct TCarro));
  carrosAtendidos = (int*)malloc(1 * sizeof(struct TCarro));
  
  int opcao = 7;
  int opcao_relatorio, restantes = 0;
  float valor_arrecadado = 0,tanque_atual=200,  litros_vendidos=0;
   int Totalcarros_atendidos = 0;
  while (opcao != 5){
    
    // Menu Principal
    opcaoMenu();
      scanf("%d",&opcao);
    if (opcao == 1 || opcao == 2 || opcao == 3 || opcao == 4 || opcao == 5){
       switch(opcao){
        case 1:
                  system("clear");
              flush_in();
            printf (Ccyan"\n[1] ADICIONAR UM CARRO NA FILA\n\n");
          if (tanque_atual>0){
                 if(fila_atual < tamanho_fila){
            printf("\n\nQual o modelo do carro ? \n");
          fgets(carrosNAfila[fila_atual].modelo,20,stdin);

           printf("\nInforme a cor do carro: \n ");
            fgets(carrosNAfila[fila_atual].cor,20,stdin);
           carrosNAfila[fila_atual].cor[strcspn(carrosNAfila[fila_atual].cor,"\n")] = 0;
           
          printf("\nQual o ano do carro?\n");
         scanf("%d"Cwhite, &carrosNAfila[fila_atual].ano);
            system("clear");
           fila_atual = fila_atual+1;
          printf(Cgreen"\nCarro adicionado na fila\n");
            }
        else{
          printf(Cred "TAMANHO MÁXIMO DA FILA FOI ATINGIDO\n");
        }
        }else{
            printf("NÃO E POSSÍVEL ADICIONAR CARRO, POIS NÃO TEMOS MAIS COMBUSTÍVEL");
          }
             
      break;
          
        case 2:
          system("clear");
          printf ("\n[2] ABASTECER UM VEÍCULO\n\n");
          if(fila_atual != 0){
            float abastecer_litros;
            if (tanque_atual <= 0) {
            printf(Cred"\nPESSOAL PEDIMOS DESCULPAS PELO TRANSTORNO, MAS ESTAMOS SEM COMBUSTÍVEL, VAMOS TIRAR TODOS OS CARROS DA FILA");
              fila_atual = 0;
              printf(Cblue"\n\nCarros na fila: %d", fila_atual);
              
              break;
            }   
              else {
                printf("Quantos litros deseja abastecer? \n");
                scanf("%f", &abastecer_litros);
                while (abastecer_litros > tanque_atual) {
                 printf("Puts chefia, não temos combustivel suficiente para atender ao seu pedido, temos apenas um total de %.2f L\n",tanque_atual);      
                printf ("\nVamos encher com o máximo que tem no taque %2.fL ? Ou vai ser uma quantia menor\n ", tanque_atual);
                  scanf("%f", &abastecer_litros);
                }
                printf(Cgreen"\nCarro abastecido.\n"Cwhite);
  
                
                tanque_atual = tanque_atual - abastecer_litros;
                litros_vendidos = litros_vendidos + abastecer_litros;
                valor_arrecadado = valor_arrecadado + (preco_combustivel * abastecer_litros); 
                carrosAtendidos = (int*)realloc(carrosAtendidos,(Totalcarros_atendidos + 1) * sizeof(struct TCarro));
                carrosAtendidos[Totalcarros_atendidos] = carrosNAfila[0];
               Totalcarros_atendidos = Totalcarros_atendidos+1;
                fila_atual = fila_atual - 1;

                for(int i = 0; i < tamanho_fila; i++) {
                  carrosNAfila[i] = carrosNAfila[i+1];
                }
                
              }         
          }
          else {
            printf(Cred "A FILA ESTÁ VAZIA, PRIMEIRO ADICIONE UM CARRO.");
            system("clear"); 
          }
          break;

        
        case 3:
        system("clear");
          restantes = fila_atual;
        printf (Cwhite "\n\n[3] FILA DE ESPERA\n\n");
        printf(Cwhite "Carros na fila:%d\n", restantes);
          for (int i = 0; restantes > i; i++) {
            printf(Cblue"\nCarro [%d] \n"Cyellow, i+1);
            infoCarro(carrosNAfila[i]);
          } 
         break;
        case 4:
          system("clear");
           opcao_relatorio = 7;
          while (opcao_relatorio != 6){ 
            // Opção Relatório
            opcaoRelatorio();
            scanf("%d",&opcao_relatorio);
             switch(opcao_relatorio){ 
              case 1:
               system("clear");
              printf ("OPÇÃO [A] MENU RELATÓRIO -- LITROS VENDIDOS\n\n");
              printf("A quantidade de litros vendida é de: %.2f L \n", litros_vendidos);
            break;

            case 2:
              system("clear");              
              printf ("OPÇÃO [B] MENU RELATÓRIO -- VALOR ARRECADADO\n\n");
              printf("O valor total arrecadado até o momento é de: R$%.2f \n", valor_arrecadado);
            break;
            case 3:
               system("clear");
                  printf ("OPÇÃO [C] MENU RELATÓRIO -- QUANTIDADE DE CARROS ATENDIDOS\n\n");
               for (int i = 0;  Totalcarros_atendidos > i; i++) {
                    printf(Cblue"\nCarro [%d]\n"Cwhite, i+1);
                    infoCarro(carrosAtendidos[i]);
                  }                   
                  printf(Cblue"\nQuantidade de carros atendidios: %d\n"Cwhite, Totalcarros_atendidos);
  
                  break;
            case 4:
             system("clear");
              printf ("OPÇÃO [D] MENU RELATÓRIO -- QUANTIDADE RESTANTE NO TANQUE\n\n");
              printf("Combustível restante no tanque: %.2f L \n", tanque_atual);
            break;
            case 5:
              system("clear");
              printf ("OPÇÃO [E] MENU RELATÓRIO -- ARQUIVO RELATÓRIO PARA IMPRESSÃO\n\n");
               FILE *arquivo;
  arquivo = fopen("ArquivoRelátorioImpressão.txt", "w");
  if (arquivo==NULL){
    printf("Não foi possível abrir o arquivo");
    exit (0);
  }
  fprintf (arquivo, "\n\n_______________ARQUIVO RELATÓRIO PARA IMPRESSÃO_______________\n\n");
  fprintf (arquivo, "\nQuantidade de litros vendida [%.2fL]\n", litros_vendidos);
  fprintf (arquivo, "\nValor arrecadado com as vendas [%.2fR$]\n", valor_arrecadado);
  fprintf(arquivo, "\nQuantidade de carros atendidios: [%d]\n", Totalcarros_atendidos);    
  for (int i = 0;  Totalcarros_atendidos > i; i++) {
    fprintf(arquivo, "\nCarro [%d]\n", i+1);
    fprintf(arquivo,"\nModelo do carro: %s", carrosAtendidos[i].modelo);
    fprintf(arquivo,"\n Cor do carro: %s\n", carrosAtendidos[i].cor);
    fprintf(arquivo, "\nAno de lançamento: %d\n", carrosAtendidos[i].ano);
  }
  fprintf (arquivo, "\nQuantidade de combustível restante [%.2fL]\n", tanque_atual);
  fclose (arquivo);
            break;
               case 6:
               system ("clear");
               printf ("OPÇÃO [F] MENU RELATÓRIO -- VOLTAR AO MENU PRINCIPAL\n\n");
               printf("Voltar para o menu principal"); 
               break;
                 default:
              system("clear");
              opcaoInvalida();
            break;
          }
        }
      break;
        
          case 5:
            system ("clear");
          printf(Ccyan"\n\n Programa encerrado, muito obrigado por utilizar esse programa meu Camarada !!!!!!!!!\n");
          break;  
       }
      }
      
    else {
      system ("clear");
    opcaoInvalida(); 
    }
      
    
  }
 return 0;

  }

  void opcaoMenu(){
    printf(Cyellow"\n\n_______________MENU PRINCIPAL_______________\n\n"Cwhite);
    printf(Cpurple"1 - Adicionar um carro na fila \n");
    printf("2 - Abastecimento \n");
    printf("3 - Exibir carros na fila de espera \n");
    printf("4 - Relatórios\n");
    printf("5 - Encerrar\n\n"Cwhite);
    printf ("Escolha uma opção de 1 a 4, ou clique 5 para encerrar o programa: \n");
  }
void opcaoInvalida(){
  printf(Cred "OPÇÃO INVÁLIDA, INFORME NOVAMENTE A OPÇÃO\n\n");
}

void opcaoRelatorio(){
  printf(Ccyan"\n\n_______________MENU RELATÓRIO_______________\n\n");
          printf("1 - Quantidade de litros vendida;\n");
          printf("2 - Valor total arrecadado com as vendas;\n");
          printf("3 - Quantidade de carros atendidos;\n");
          printf("4 - Quantidade de combustível restante no tanque;\n");
          printf("5 - Gerar arquivo para impressão (com todas as informações de A, B, C e D);\n");
          printf("6 - voltar ao menu anterior.\n"Cwhite); 
}
      void infoCarro(struct TCarro Carros) {
  printf("\nModelo do carro: %s", Carros.modelo);
  printf("\n Cor do carro: %s\n", Carros.cor);
  printf("\nAno de lançamento: %d\n", Carros.ano);
}