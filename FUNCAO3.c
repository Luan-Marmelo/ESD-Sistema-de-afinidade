/******************************************************************************
FUNÇÃO PARA O TOPICO 3, "BUSCAR PESSOA PELO NOME";
*******************************************************************************/
//PRECISA DAS LIBS STDIO.H E STRING.H NO TOPO DO CÓDIGO PRINCIPAL;
// CRIAR CONSTANTE "MAX_CARACTERES_NOME" NO TOPO DO CÓDIGO PRINCIPAL E DEFINI-LA COM O VALOR 25; 

int buscarPessoaPorNome(char nomeParaBuscar[], char nomes[MAX_PESSOAS][MAX_CARACTERES_NOME]){
    for(int i = 0; i<MAX_PESSOAS; i++){
        if(strcmp(nomeParaBuscar, nomes[i]) == 0)
            return i;
    }    
    
    printf("NOME: %s -  NÃO ENCONTRADO!", nomeParaBuscar);
    return -1;
}
