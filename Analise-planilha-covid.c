/*

Arthur Barbosa Jacintho Silva - 2020100750
Trabalho Final - Programacao II
Engenharia de Computacao - Primeiro Periodo

*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#define N 30
#define Tam 202363

struct Variaveis{
    char DataCadastro[N];
    char DataObito[N];
    char Classificacao[N];
    char Municipio[N];
    char IdadeNaDataNotificacao[N];
    char ComorbidadePulmao[N];
    char ComorbidadeCardio[N];
    char ComorbidadeRenal[N];
    char ComorbidadeDiabetes[N];
    char ComorbidadeTabagismo[N];
    char ComorbidadeObesidade[N];
    char FicouInternado[N];
    int CadastroFiltrado;       // Data cadastro transformado para quantidade de dias, para facilitar o manuseio
    int ObitoFiltrado;          // Data obito transformado para quantidade de dias, para facilitar o manuseio
    int IdadesEmAnos;           // Idade convertida de char para int
};
struct Variaveis Pessoas[Tam];  // Struct para armazenar os dados do arquivo csv

struct Cidades{
    char CidadesOrdenadas[N];
    int Casos;                  
};
struct Cidades CidadesAlfabeticas[80];          // Struct para armazenas todas os municipios do ES, em ordem alfabetica,
                                                // e quantidade de casos para cada municipio
struct city{
    char Cidades[N];
    int QntCasos;
};
struct city CidadesDecrescentes[80];            // Por ser uma variavel global, ela se altera dentro de um funcao, 
                                                // logo criamos outra struct e copiamos os municipios da CidadesAlfabeticas
                                                // para poder organiza-la de forma decrescentes de casos para poder
                                                // utilizar um top x de casos, utilizamos no Item 5

void leArquivo ();                              // Funcao responsavel por ler o arquivo csv, com o argumento sendo
                                                // a Struct Pessoas

int filtroData (int x, int y, int z);           // Funcao para filtrar as datas

void QuantCasos();                              // Item 3 - Quantidade de casos

void QntCasosDataUmDataDois();                  // Item 4 - Casos entre duas datas

void OrdemDecrescente();                        // Funcao para ordenar um vetor em ordem decrescente

void CidadesDecrescente();                      // Item 5 - Top x de quantidade de casos num intervalo 
                                                // entre duas datas

void estatisticasCidades();                     // Item 6 - Estatisticas sobre a tabela

void MediaDesvioPadrao();                       // Item 7 - Media e desvio padrao

char ehMinusculo (char c);                      // funcao para transformar letra minuscula em maiuscula

int main (){                                    // funcao main, principal                       
    
    setlocale(LC_ALL, "Portuguese");            // funcao para traduzir possiveis casos de acentuacao
    char DiretorioItem3[30], DiretorioItem4[30];
    char DiretorioItem5[30], DiretorioItem6[30];
    char DiretorioItem7[30], limpeza;

    scanf("%[^\n]*c", DiretorioItem3);          // Lendo uma string ate ter um enter(\n)
    scanf("%c", limpeza);                       // Lendo o enter (\n)

    mkdir(DiretorioItem3, 0777);                // Criando um diretorio usando a funcao mkdir

    strcpy(DiretorioItem4, DiretorioItem3);     // Copiamos a string DiretorioItem3 em outras variaveis, pois
                                                // se nao usassemos uma variavel para cada funcao, teriamos que 
    strcpy(DiretorioItem5, DiretorioItem3);     // concatenar e desconcatenar dentro de cada funcao, o que seria
                                                // mais trabalhoso
    strcpy(DiretorioItem6, DiretorioItem3);
                                                
    strcpy(DiretorioItem7, DiretorioItem3);

    leArquivo();                                // chamando a funcao de ler arquivo csv
    
    QuantCasos(DiretorioItem3);                 // chamando a funcao Quantidade de casos (item 3) com o Argumento sendo o DiretorioItem3
    
    QntCasosDataUmDataDois(DiretorioItem4);     // chamando a funcao Quantidade de casos entre duas datas (item 4) com o Argumento sendo o DiretorioItem4
    
    CidadesDecrescente(DiretorioItem5);         // chamando a funcao para informar as cidades com mais casos em ordem decrescente entre duas datas (item 5) com o Argumento sendo o DiretorioItem5
    
    estatisticasCidades(DiretorioItem6);        // chamando a funcao para informar as estatisticas da planilha de cada municipio, ou de todos, (item 6) com o Argumento sendo o DiretorioItem6  
    
    MediaDesvioPadrao(DiretorioItem7);          // chamando a funcao que calcula a media e o desvio padrao, alem da porcentagem de mortes sem comorbidades (item 7) com o Argumento sendo o DiretorioItem7
    

    return 0;

}                                               // Fim da funcao main

void leArquivo (){                                          // funcao de le arquivo
    
    char Limpeza, c[300];
   
    int i=0, Ano, Mes, Dia, Ano2, Mes2, Dia2;
    int Anos, Meses, Dias;

    FILE *Arquivo;                                          // declarando o ponteiro do Arquivo
    
    Arquivo = fopen("covid19ES.csv", "r");                  // abrindo o arquivo para leitura
    if (Arquivo == NULL){                                   // testando se abriu corretamente o arquivo
        printf("Deu Problema Ai!");
        exit(1);             
    }

    fscanf(Arquivo, "%[^\n]*c", c);                             // Lendo a linha toda ate chegar no enter (\n), a fim de ignorar o cabecalho e nao atrapalhar no manuseio da tabela
    fscanf(Arquivo, "%c", &Limpeza);                            // lendo o (\n) para n atrapalhar as leituras futuras
                                                                
    for (i=0; i<Tam; i++){                                      // esse for e para ler todas as linhas do arquivo
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].DataCadastro);    // esta lendo ate chegar numa virgula e associando a string de dataCadasto
        fscanf(Arquivo, "%c", &Limpeza);                        // esta lendo a virgula e armazenando na variavel limpeza
       
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].DataObito);       // esta lendo ate chegar numa virgula e associando a string de dataObito
        fscanf(Arquivo, "%c", &Limpeza);                        // esta lendo a virgula e armazenando na variavel limpeza
      
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].Classificacao);   // esta lendo ate chegar numa virgula e associando a string de Classificacao
        fscanf(Arquivo, "%c", &Limpeza);                        // esta lendo a virgula e armazenando na variavel limpeza
       
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].Municipio);       // esta lendo ate chegar numa virgula e associando a string de Municipio
        fscanf(Arquivo, "%c", &Limpeza);                        // esta lendo a virgula e armazenando na variavel limpeza
        fscanf(Arquivo, "%c", &Limpeza);                        // esta lendo a primeira " e armazenando na variavel limpeza
       
        fscanf(Arquivo, "%[^\"]*c", Pessoas[i].IdadeNaDataNotificacao);   // esta lendo ate chegar na segunda " e associando a string de IdadeDataNotificacao
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a segunda " e armazenando na variavel limpeza
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza

        fscanf(Arquivo, "%[^,]*c", Pessoas[i].ComorbidadePulmao);         // esta lendo ate chegar numa virgula e associando a string de ComorbidadePulmao
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
       
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].ComorbidadeCardio);         // esta lendo ate chegar numa virgula e associando a string de ComorbidadeCardio
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
       
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].ComorbidadeRenal);          // esta lendo ate chegar numa virgula e associando a string de ComorbidadeRenal
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
      
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].ComorbidadeDiabetes);       // esta lendo ate chegar numa virgula e associando a string de ComorbidadeDiabetes
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
        
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].ComorbidadeTabagismo);      // esta lendo ate chegar numa virgula e associando a string de ComorbidadeTabagismo
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
      
        fscanf(Arquivo, "%[^,]*c", Pessoas[i].ComorbidadeObesidade);      // esta lendo ate chegar numa virgula e associando a string de ComorbidadeObesidade
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
       
        fscanf(Arquivo, "%[^\n]*c", Pessoas[i].FicouInternado);           // esta lendo ate chegar numa virgula e associando a string de FicouInternado
        fscanf(Arquivo, "%c", &Limpeza);                                  // esta lendo a virgula e armazenando na variavel limpeza
        
        sscanf(Pessoas[i].DataCadastro,"%d-%d-%d", &Ano ,&Mes, &Dia);     // Esta lendo novamente a string dataCadastro so que de forma que o ano, mes e dia sejam inteiros
        sscanf(Pessoas[i].DataObito,"%d-%d-%d", &Ano2 ,&Mes2, &Dia2);     // Esta lendo novamente a string dataObito so que de forma que o ano, mes e dia sejam inteiros
        sscanf(Pessoas[i].IdadeNaDataNotificacao, "%d anos, %d meses, %d dias", &Anos, &Meses, &Dias);  // Lendo novamente a string da idade, e transformando para int
        
        Pessoas[i].CadastroFiltrado = filtroData(Ano, Mes, Dia);          // esta utilizando a funcao filtroData que transforma o mes e dia em diastotais e associando a variavel cadastroFiltrado
        Pessoas[i].ObitoFiltrado = filtroData(Ano2, Mes2, Dia2);          // esta utilizando a funcao filtroData que transforma o mes e dia em diastotais e associando a variavel obitoFiltrado
        Pessoas[i].IdadesEmAnos = Anos;                                   // Associando a idade transfomada para int na na variavel IdadeEmAnos dentro da struct Pessoas
    }
    fclose(Arquivo);                                                      // fechando o arquivo para leitura

}                                                                         // fim da funcao leArquivo

int filtroData (int x, int y, int z){               // funcao filtroData, que transforma o mes e dia para total de dias
    int TotalDia = 0;                               // variavel para total de dias
    
    if (x == 2020){                                 // se for ano de 2020, vai entrar no if, se nao o total de dias sera 0
        if (y == 1){                                // essa funcao basicamente usa o dia que foi dado e soma a quantidade de dias dos meses anteriores
            TotalDia = z;                           // por exemplo, se o mes informado foi 4, e o dia informado foi 15, vai somar-se o a quantidade de dias
        }else if(y == 2){                           // de janeiro, de fevereiro, de março com o dia informado, ou seja, 31+29+31+15 que sera igual ao total de dias
            TotalDia = 31 + z;                      // que sera entao, 106 dias
        }else if(y == 3){
            TotalDia = 31 + 29 + z;
        }else if(y == 4){
            TotalDia = 31*2 + 29 + z;
        }else if(y == 5){
            TotalDia = 31*2 + 29 + 30 + z;
        }else if(y == 6){
            TotalDia = 31*3 + 29 + 30 + z;
        }else if(y == 7){
            TotalDia = 31*3 + 29 + 30*2 + z;
        }else if(y == 8){
            TotalDia = 31*4 + 29 + 30*2 + z;
        }else if(y == 9){
            TotalDia = 31*5 + 29 + 30*2 + z;
        }else if(y == 10){
            TotalDia = 31*5 + 29 + 30*3 + z;
        }else if(y == 11){
            TotalDia = 31*6 + 29 + 30*3 + z;
        }else if(y == 12){
            TotalDia = 31*6 + 29 + 30*4 + z;
        }
    }
    return TotalDia;                                // como e uma funcao int, tera um retorno, e esse retorno sera o total de dias
}                                                   // fim da funcao de filtroData

void TodasCidades(){                                                        // funcao resposavel para armazenas todos os municipios em ordem alfabetica
    int i = 0;                                                              // na struct cidadesAlfabeticas
    int j = 0;
    strcpy(CidadesAlfabeticas[0].CidadesOrdenadas, "AFONSO CLAUDIO");       // essa funcao esta copiando o nome do municipio na string cidadesAlfabeticas.CidadesOrdenadas
    strcpy(CidadesAlfabeticas[1].CidadesOrdenadas, "AGUA DOCE DO NORTE");   // e se repete ate que copie todos os municipios
    strcpy(CidadesAlfabeticas[2].CidadesOrdenadas, "AGUIA BRANCA");
    strcpy(CidadesAlfabeticas[3].CidadesOrdenadas, "ALEGRE");
    strcpy(CidadesAlfabeticas[4].CidadesOrdenadas, "ALFREDO CHAVES");
    strcpy(CidadesAlfabeticas[5].CidadesOrdenadas, "ALTO RIO NOVO");
    strcpy(CidadesAlfabeticas[6].CidadesOrdenadas, "ANCHIETA");
    strcpy(CidadesAlfabeticas[7].CidadesOrdenadas, "APIACA");
    strcpy(CidadesAlfabeticas[8].CidadesOrdenadas, "ARACRUZ");
    strcpy(CidadesAlfabeticas[9].CidadesOrdenadas, "ATILIO VIVACQUA");
    strcpy(CidadesAlfabeticas[10].CidadesOrdenadas, "BAIXO GUANDU");
    strcpy(CidadesAlfabeticas[11].CidadesOrdenadas, "BARRA DE SAO FRANCISCO");
    strcpy(CidadesAlfabeticas[12].CidadesOrdenadas, "BOA ESPERANCA");
    strcpy(CidadesAlfabeticas[13].CidadesOrdenadas, "BOM JESUS DO NORTE");
    strcpy(CidadesAlfabeticas[14].CidadesOrdenadas, "BREJETUBA");
    strcpy(CidadesAlfabeticas[15].CidadesOrdenadas, "CACHOEIRO DE ITAPEMIRIM");
    strcpy(CidadesAlfabeticas[16].CidadesOrdenadas, "CARIACICA");
    strcpy(CidadesAlfabeticas[17].CidadesOrdenadas, "CASTELO");
    strcpy(CidadesAlfabeticas[18].CidadesOrdenadas, "COLATINA");
    strcpy(CidadesAlfabeticas[19].CidadesOrdenadas, "CONCEICAO DA BARRA");
    strcpy(CidadesAlfabeticas[20].CidadesOrdenadas, "CONCEICAO DO CASTELO");
    strcpy(CidadesAlfabeticas[21].CidadesOrdenadas, "DIVINO DE SAO LOURENCO");
    strcpy(CidadesAlfabeticas[22].CidadesOrdenadas, "DOMINGOS MARTINS");
    strcpy(CidadesAlfabeticas[23].CidadesOrdenadas, "DORES DO RIO PRETO");
    strcpy(CidadesAlfabeticas[24].CidadesOrdenadas, "ECOPORANGA");
    strcpy(CidadesAlfabeticas[25].CidadesOrdenadas, "FUNDAO");
    strcpy(CidadesAlfabeticas[26].CidadesOrdenadas, "GOVERNADOR LINDENBERG");
    strcpy(CidadesAlfabeticas[27].CidadesOrdenadas, "GUACUI");
    strcpy(CidadesAlfabeticas[28].CidadesOrdenadas, "GUARAPARI");
    strcpy(CidadesAlfabeticas[29].CidadesOrdenadas, "IBATIBA");
    strcpy(CidadesAlfabeticas[30].CidadesOrdenadas, "IBIRACU");
    strcpy(CidadesAlfabeticas[31].CidadesOrdenadas, "IBITIRAMA");
    strcpy(CidadesAlfabeticas[32].CidadesOrdenadas, "ICONHA");
    strcpy(CidadesAlfabeticas[33].CidadesOrdenadas, "IRUPI");
    strcpy(CidadesAlfabeticas[34].CidadesOrdenadas, "ITAGUACU");
    strcpy(CidadesAlfabeticas[35].CidadesOrdenadas, "ITAPEMIRIM");
    strcpy(CidadesAlfabeticas[36].CidadesOrdenadas, "ITARANA");
    strcpy(CidadesAlfabeticas[37].CidadesOrdenadas, "IUNA");
    strcpy(CidadesAlfabeticas[38].CidadesOrdenadas, "JAGUARE");
    strcpy(CidadesAlfabeticas[39].CidadesOrdenadas, "JERONIMO MONTEIRO");
    strcpy(CidadesAlfabeticas[40].CidadesOrdenadas, "JOAO NEIVA");
    strcpy(CidadesAlfabeticas[41].CidadesOrdenadas, "LARANJA DA TERRA");
    strcpy(CidadesAlfabeticas[42].CidadesOrdenadas, "LINHARES");
    strcpy(CidadesAlfabeticas[43].CidadesOrdenadas, "MANTENOPOLIS");
    strcpy(CidadesAlfabeticas[44].CidadesOrdenadas, "MARATAIZES");
    strcpy(CidadesAlfabeticas[45].CidadesOrdenadas, "MARECHAL FLORIANO");
    strcpy(CidadesAlfabeticas[46].CidadesOrdenadas, "MARILANDIA");
    strcpy(CidadesAlfabeticas[47].CidadesOrdenadas, "MIMOSO DO SUL");
    strcpy(CidadesAlfabeticas[48].CidadesOrdenadas, "MONTANHA");
    strcpy(CidadesAlfabeticas[49].CidadesOrdenadas, "MUCURICI");
    strcpy(CidadesAlfabeticas[50].CidadesOrdenadas, "MUNIZ FREIRE");
    strcpy(CidadesAlfabeticas[51].CidadesOrdenadas, "MUQUI");
    strcpy(CidadesAlfabeticas[52].CidadesOrdenadas, "NOVA VENECIA");
    strcpy(CidadesAlfabeticas[53].CidadesOrdenadas, "PANCAS");
    strcpy(CidadesAlfabeticas[54].CidadesOrdenadas, "PEDRO CANARIO");
    strcpy(CidadesAlfabeticas[55].CidadesOrdenadas, "PINHEIROS");
    strcpy(CidadesAlfabeticas[56].CidadesOrdenadas, "PIUMA");
    strcpy(CidadesAlfabeticas[57].CidadesOrdenadas, "PONTO BELO");
    strcpy(CidadesAlfabeticas[58].CidadesOrdenadas, "PRESIDENTE KENNEDY");
    strcpy(CidadesAlfabeticas[59].CidadesOrdenadas, "RIO BANANAL");
    strcpy(CidadesAlfabeticas[60].CidadesOrdenadas, "RIO NOVO DO SUL");
    strcpy(CidadesAlfabeticas[61].CidadesOrdenadas, "SANTA LEOPOLDINA");
    strcpy(CidadesAlfabeticas[62].CidadesOrdenadas, "SANTA MARIA DE JETIBA");
    strcpy(CidadesAlfabeticas[63].CidadesOrdenadas, "SANTA TERESA");
    strcpy(CidadesAlfabeticas[64].CidadesOrdenadas, "SAO DOMINGOS DO NORTE");
    strcpy(CidadesAlfabeticas[65].CidadesOrdenadas, "SAO GABRIEL DA PALHA");
    strcpy(CidadesAlfabeticas[66].CidadesOrdenadas, "SAO JOSE DO CALCADO");
    strcpy(CidadesAlfabeticas[67].CidadesOrdenadas, "SAO MATEUS");
    strcpy(CidadesAlfabeticas[68].CidadesOrdenadas, "SAO ROQUE DO CANAA");
    strcpy(CidadesAlfabeticas[69].CidadesOrdenadas, "SERRA");
    strcpy(CidadesAlfabeticas[70].CidadesOrdenadas, "SOORETAMA");
    strcpy(CidadesAlfabeticas[71].CidadesOrdenadas, "VARGEM ALTA");
    strcpy(CidadesAlfabeticas[72].CidadesOrdenadas, "VENDA NOVA DO IMIGRANTE");
    strcpy(CidadesAlfabeticas[73].CidadesOrdenadas, "VIANA");
    strcpy(CidadesAlfabeticas[74].CidadesOrdenadas, "VILA PAVAO");
    strcpy(CidadesAlfabeticas[75].CidadesOrdenadas, "VILA VALERIO");
    strcpy(CidadesAlfabeticas[76].CidadesOrdenadas, "VILA VELHA");
    strcpy(CidadesAlfabeticas[77].CidadesOrdenadas, "VITORIA");

    for (i = 0; i < 78; i++){                                                                   // esse for e responsavel para verificar se quando as strings da struct cidadesAlfabeticas
        for (j = 0; j < Tam; j++){                                                              // e a struct Pessoas.Municipio são identicas e se for identicas e a Pessoas.Cadastro foi igual
            if((strcmp(CidadesAlfabeticas[i].CidadesOrdenadas, Pessoas[j].Municipio)) == 0){    // a Confirmados, adiciona a quantidade de casos na struct cidadesAlfabeticas. Logo, ao final do for
                if (strcmp(Pessoas[j].Classificacao, "Confirmados") == 0){                      // a struct cidadesAlfabeticas.Casos terá a quantidade total de casos de cada cidade
                    CidadesAlfabeticas[i].Casos++;
                }
            }
        }            
    }


}                                                                                               // final da funcao TodasCidades

void QuantCasos(char diretorio[]){              // funcao responsavel para gerar um arquivo com as cidades com mais de x casos, sendo x um numero dado para o teste, tendo como argumento o char diretorio[]
    int i;
    
    TodasCidades();                             // estamos chamando a funcao de todas a cidades
    
    int QuantidadeCasos;    

    strcat(diretorio, "item3.txt");            // concatenamos o nome do diretorio presente no arquivo teste, com o nome do arquivo do item 3

    FILE *FuncaoTres;                           // ponteiro responsavel para manuseio do arquivo

    FuncaoTres = fopen (diretorio, "w");        // gerando um arquivo para escrita do item 3 no diretorio informado

    scanf("%d", &QuantidadeCasos);              // lendo a quantidade de casos para teste

           
    for (i = 0; i < 78; i++){                                                                                               // esse for e responsavel para analisar se a quantidade de casos de cada municipio for maior do que a quantidade de casos informado
        if(QuantidadeCasos < CidadesAlfabeticas[i].Casos){                                                                  // se for maior, vai imprimir o municipio e a quantidade de casos
            fprintf(FuncaoTres, "- %s: %d casos\n", CidadesAlfabeticas[i].CidadesOrdenadas, CidadesAlfabeticas[i].Casos);
        }
    }

    fclose(FuncaoTres);                                                                                                     // fechando o arquivo item 3
}                                                                                                                           // final da funcao

void QntCasosDataUmDataDois(char diretorio[]){                                              // funcao responsavel para ver a quantidade de casos entre duas datas
    
    int entAno, entMes, entDia;
    int entAno2,entMes2, entDia2;
    int DataUm, DataDois, i = 0;
    int TotalCasos = 0;
    
    strcat(diretorio, "item4.txt");                                                        // concatenamos o nome do diretorio presente no arquivo teste, com o nome do arquivo do item 4

    FILE *FuncaoQuatro;                                                                     // ponteiro responsavel para manuseio do arquivo
    
    FuncaoQuatro = fopen(diretorio, "w");                                                   // abrindo um arquivo para escrita item 4, no diretorio informado

    scanf("%d-%d-%d %d-%d-%d", &entAno, &entMes, &entDia, &entAno2, &entMes2, &entDia2);    // lendo as datas, um e dois e associando ao anoum, mesum, diaum, anodois, mesdois, diadois
                                                                                            // para poder usar no arguento da funcao filtroData
    DataUm = filtroData(entAno,entMes,entDia);                                              // convertendo a data um para quantidade de dias totais

    DataDois = filtroData(entAno2,entMes2,entDia2);                                         // convertendo a data dois para quantidade de dias totais
    
        for (i = 0; i < Tam; i++){                                                          // for responsavel por analisar se o casastrofiltrado esta entre a data um e a data dois, se for
            if(Pessoas[i].CadastroFiltrado >= DataUm){                                      // ira analisar se na mesma linha, na struct pessoas.classificacao está classificado como "confirmados"
                if (Pessoas[i].CadastroFiltrado <= DataDois){                               // se estiver como confirmados, ira incrementar mais um na variavel totalcasos, que inicialmente era 0
                    if(strcmp(Pessoas[i].Classificacao,"Confirmados") == 0){
                        TotalCasos++;
                    }
                }
            }
        }
   
    fprintf(FuncaoQuatro, "- Total de pessoas: %d",TotalCasos);                             // esta printando no arquivo item 4 o total de casos entre as duas datas

    fclose(FuncaoQuatro);                                                                   // fechando o arquivo
}                                                                                           // final da funcao QntCasosDataUmDataDois

void CidadesDecrescente(char diretorio[]){              // funcao responsavel por ver o top x de cidades em ordem decrescente de quantidade de casos, entre duas datas, com arugumento sendo o char diretorio[]
    
    int i = 0, j = 0;
    int NumeroCidades;
    int entAno, entMes, entDia;
    int entAno2,entMes2, entDia2;
    int dataUm, dataDois;
    
    strcat(diretorio, "item5.txt");                    // funcao para concatenar o diretorio com o nome do arquivo

    FILE *FuncaoCinco;                                  // ponteiro para poder manusear o arquivo

    FuncaoCinco = fopen (diretorio, "w");               // criando um arquivo para escrita item 5, no diretorio informado

    scanf("%d %d-%d-%d %d-%d-%d", &NumeroCidades, &entAno, &entMes, &entDia, &entAno2, &entMes2, &entDia2);         // lendo as entradas
    
    dataUm = filtroData(entAno,entMes,entDia);          // utilizando a funcao filtrodata para transformar os dias e meses em um total de dias
    dataDois = filtroData(entAno2,entMes2,entDia2);     // utilizando a funcao filtrodata para transformar os dias e meses em um total de dias

    for (i = 0; i < 78; i++){
        strcpy(CidadesDecrescentes[i].Cidades, CidadesAlfabeticas[i].CidadesOrdenadas);     // for responsavel por copiar as cidades de uma struct para outra, ou seja, de cidadesAlfabeticas para cidadesDecrescentes
    }

    
    for (i = 0; i < 78; i++){            // for responsavel por contar a quantidade de casos, entre duas datas, de cada municipio
        for (j = 0; j < Tam; j++){
            if(Pessoas[j].CadastroFiltrado >= dataUm){
                if(Pessoas[j].CadastroFiltrado <= dataDois){
                    if((strcmp(CidadesDecrescentes[i].Cidades, Pessoas[j].Municipio)) == 0){
                        if (strcmp(Pessoas[j].Classificacao, "Confirmados") == 0){
                            CidadesDecrescentes[i].QntCasos++;
                        }
                    }
                }
            }
        }            
    }

    OrdemDecrescente();                     // chamando a funcao de ordenar as cidades em ordem decrescente de quantidade de casos
    
    for (i = 0; i < NumeroCidades; i++){    // for responsavel por printar no no arquivo gerado
        fprintf(FuncaoCinco, "- %s: %d casos\n", CidadesDecrescentes[i].Cidades, CidadesDecrescentes[i].QntCasos);
    }

    fclose(FuncaoCinco);                    // fechando o arquivo
}                                           // fim da funcao cidadesDecrescente

void OrdemDecrescente(){                    // funcao responsavel por ordenar as cidades em relacao ao numero de casos, de forma decrescente
    int i = 0;
    int j = 0;
    int AuxUm;
    char AuxDois[N];


    for (i = 0; i < 78; i++){                                                           // for responsavel por ordenar de forma decrescente, utilizamos o metodo de "bubble sort", ou seja
        for (j = i; j < 78; j++){                                                       // o for compara uma cidade com todas as proximas, e a maior se torna a primeira cidade
            if (CidadesDecrescentes[i].QntCasos < CidadesDecrescentes[j].QntCasos){     // assim, precisamos modificar nao somente a quantidade de casos, mas tambem as cidades, logo
                AuxUm = CidadesDecrescentes[i].QntCasos;                                // trocamos tanto a quantidade de casos como as cidades
                CidadesDecrescentes[i].QntCasos = CidadesDecrescentes[j].QntCasos;
                CidadesDecrescentes[j].QntCasos = AuxUm;
                strcpy(AuxDois, CidadesDecrescentes[i].Cidades);
                strcpy(CidadesDecrescentes[i].Cidades, CidadesDecrescentes[j].Cidades);
                strcpy(CidadesDecrescentes[j].Cidades, AuxDois);
            }
        }
    }
}               // Fim da funcao responsavel por ordenar de forma decrescente

void estatisticasCidades(char diretorio[]){     // funcao reponsavel por informar as estatisticas de algum municipio, ou de todos
    
    strcat(diretorio, "item6.txt");            // funcao para concatenar o nome do arquivo com o diretorio informado

    FILE *FuncaoSeis;                           // ponteiro para possibilitar o manuseio do arquivo

    FuncaoSeis = fopen(diretorio, "w");         // criando um arquivo para escrita do item 6, no diretorio informado

    int i = 0;

    int tamanho;
    
    float PessoasConfirmadas = 0, PessoasInternadas = 0, PessoasMortasGeral = 0, PessoasMortasInternadas = 0;

    float EstConfirmadoInternado, EstPessoasMorreram, EstInternadoMorreram;

    char EntradaMunicipio[30];
   
    scanf("%s", EntradaMunicipio);                                                  // lendo a entrada, sendo todos ou algum municipio

    tamanho = strlen(EntradaMunicipio);                                             // calculando o tamanho da string de entrada

    for (i = 0; i < tamanho; i++){                                                  // for responsavel para transformar a string toda para maiusculo, utilizando a funcao ehMinusculo
        EntradaMunicipio[i] = ehMinusculo(EntradaMunicipio[i]);
    }
 

    if (strcmp(EntradaMunicipio, "TODAS") == 0){                        // if a entrada for TODAS, for responsavel por contar as pessoas confirmadas, internadas, mortas que ficaram internadas e mortas no geral
        for (i = 0; i < Tam; i++){                 
            if (strcmp(Pessoas[i].Classificacao, "Confirmados") == 0){
                PessoasConfirmadas++;
                if (strcmp(Pessoas[i].FicouInternado, "Sim") == 0){
                    PessoasInternadas++;
                    if (Pessoas[i].ObitoFiltrado != 0){
                        PessoasMortasInternadas++;
                    }
                }
                if (Pessoas[i].ObitoFiltrado != 0){
                    PessoasMortasGeral++;
                }
            }
        }
    }else {                                                             // else a entrada for algum municipio, for responsavel por contar as pessoas confirmadas, internadas, mortas que ficaram internadas e mortas no geral do municipio
        for (i = 0; i < Tam; i++){
            if (strcmp(EntradaMunicipio, Pessoas[i].Municipio) == 0){
                if (strcmp(Pessoas[i].Classificacao, "Confirmados") == 0){
                    PessoasConfirmadas++;
                    if (strcmp(Pessoas[i].FicouInternado, "Sim") == 0){
                        PessoasInternadas++;
                        if (Pessoas[i].ObitoFiltrado != 0){
                            PessoasMortasInternadas++;
                        }
                    }
                    if (Pessoas[i].ObitoFiltrado != 0){
                        PessoasMortasGeral++;
                    }
                }
            }
        }
    }
    

    EstConfirmadoInternado = (PessoasInternadas * 100) / PessoasConfirmadas;        // Calcular a porcentagem de pessoas que ficaram internadas, com covid
    
    EstPessoasMorreram = (PessoasMortasGeral * 100) / PessoasConfirmadas;           // Calcular a porcentagem de mortes de pessoas com covid
    
    EstInternadoMorreram = (PessoasMortasInternadas * 100) / PessoasMortasGeral;    // Calcular a porcentagem de pessoas mortas com covid, em relacao a pessoas mortas no geral


    fprintf(FuncaoSeis, "- Resultados para %s:\n", EntradaMunicipio);                                                   // printando o resultado para todas ou para algum municipio
   
    fprintf(FuncaoSeis, "- A %% de pessoas com Covid-19 que ficaram internadas: %.3f%%\n", EstConfirmadoInternado);     // printando a primeira estatistica
   
    fprintf(FuncaoSeis, "- A %% de pessoas com Covid-19 que morreram: %.3f%%\n", EstPessoasMorreram);                   // printando a segunda estatistica
   
    fprintf(FuncaoSeis, "- A %% de pessoas que ficaram internadas e morreram: %.3f%%", EstInternadoMorreram);           // printando a terceira estatistica
   
    fclose(FuncaoSeis);         // fechando o arquivo
}                               // fim da funcao responsavel por informar as estatisticas de todas os municipios ou de algum

void MediaDesvioPadrao(char diretorio[]){                                                                           // funcao responsavel por calcular a media, desvio padrao e a porcentagem de pessoas mortas sem comorbidade
    
    strcat(diretorio, "item7.txt");                                                                                // funcao para concatenar o nome do arquivo com o diretorio informado

    FILE *FuncaoSete;                                                                                               // ponteiro para possibilitar o manuseio do arquivo

    FuncaoSete = fopen(diretorio, "w");                                                                             // criando um arquivo para escrita do item 7, no diretorio informado

    int i = 0, DataUm, DataDois, LerAnoUm, LerMesUm, LerDiaUm, LerAnoDois, LerMesDois, LerDiaDois;

    float Media, SemComor, SomatorioIdades = 0, QntMortes = 0, DesvioPadrao = 0, SomatorioDP = 0, QntSemComor = 0;

    scanf("%d-%d-%d %d-%d-%d", &LerAnoUm, &LerMesUm, &LerDiaUm, &LerAnoDois, &LerMesDois, &LerDiaDois);             // lendo as entradas

    DataUm = filtroData(LerAnoUm, LerMesUm, LerDiaUm);                                                              // utilizando a funcao filtrodata para transformar os dias e meses em um total de dias

    DataDois = filtroData(LerAnoDois, LerMesDois, LerDiaDois);                                                      // utilizando a funcao filtrodata para transformar os dias e meses em um total de dias

    for (i = 0; i < Tam; i++){                                                                                      // for responsavel por calcular a quantidade de mortes, de mortes sem comorbidades e fazer um somatorio das idades
        if (Pessoas[i].CadastroFiltrado >= DataUm){                                                                 // em um intervalo de datas
            if (Pessoas[i].CadastroFiltrado <= DataDois){
                if (strcmp(Pessoas[i].Classificacao, "Confirmados") == 0){    
                    if (Pessoas[i].ObitoFiltrado != 0){                    
                        SomatorioIdades = SomatorioIdades + Pessoas[i].IdadesEmAnos;
                        QntMortes++;
                        if (strcmp(Pessoas[i].ComorbidadePulmao, "Sim") != 0){
                            if (strcmp(Pessoas[i].ComorbidadeCardio, "Sim") != 0){
                                if (strcmp(Pessoas[i].ComorbidadeRenal, "Sim") != 0){
                                    if (strcmp(Pessoas[i].ComorbidadeDiabetes, "Sim") != 0){
                                        if (strcmp(Pessoas[i].ComorbidadeTabagismo, "Sim") != 0){
                                            if (strcmp(Pessoas[i].ComorbidadeObesidade, "Sim") != 0){
                                                QntSemComor++;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                    }
                }
            }
        }
    }
    
    SemComor = (QntSemComor*100) / (QntMortes);                                                                     // calculando a porcentagem de pessoas que morreram sem comorbidade de covid
    Media = SomatorioIdades / (QntMortes);                                                                          // calculando a media das idades das pessoas que morreram com covid

    for (i = 0; i < Tam; i++){                                                                                      // for responsavel pelo somatorio das difenrencas, ao quadrado, das idades pela media das pessoas que morreram por covid
        if (Pessoas[i].CadastroFiltrado >= DataUm){
            if (Pessoas[i].CadastroFiltrado <= DataDois){
                if (strcmp(Pessoas[i].Classificacao, "Confirmados") == 0){    
                    if (Pessoas[i].ObitoFiltrado != 0){                     
                        SomatorioDP = ((Pessoas[i].IdadesEmAnos - Media) * (Pessoas[i].IdadesEmAnos - Media)) + SomatorioDP;
                    }
                }
            }
        }
    }
    
    DesvioPadrao = (SomatorioDP) / (QntMortes - 1);                                                                 // calculo da divisao do somatorio do desvio padrao pela quantidade de mortes - 1 (Sendo considerado o desvio padrao amostral, por isso divide pela quantidade de mortes - 1)
 
    DesvioPadrao = sqrt(DesvioPadrao);                                                                              // calculando a raiz quadrada da varianca amostral, para chegar no desvio padrao amostral

    fprintf(FuncaoSete, "A media e desvio padrao da idade: %.3f -- %.3f\nA %% de pessoas que morreram sem comorbidade: %.3f%%", Media, DesvioPadrao, SemComor);  // printando os valores da media, desvio padrao e a porcentagem de pessoas que morreram por covid sem comorbidades
    

    fclose(FuncaoSete);     // fechando o arquivo
}                           // fim da funcao que calcula a media, desvio padrao e porcentagem de pessoas que morreram por covid sem comorbidades

char ehMinusculo (char c){                  // funcao resposavel por transoformar o caractere minusculo em maiusculo
    
    if ((c >= 'a') && (c <= 'z')){          // se o caractere for minusculo, ira subtrair o caractere por 32, ou seja, mudando seu valor na tabela ascii, tornando-se maiusculo
        return c - 32;                      // pois 32 e o valor da diferenca entre o caractere maiusculo e minusculo
    }else if ((c >= 'A') && (c <= 'Z')){    // se o caractere ja for maiuculo ira retornar o mesmo caractere
        return c;
    }else{                                  // por fim, se nao for nem maiusculo nem minusculo, retornara o mesmo caractere
        return c;
    }

}                                           // fim da funcao ehMinusculo