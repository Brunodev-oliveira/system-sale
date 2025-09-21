
# 📄 Documentação do Projeto

## 1. 🧾 Informações Gerais
- **Nome do Projeto:**  Sistema de Vendas - Fábrica de Salgadinhos 
- **Disciplina:** Programação de computadores 2 
- **Desenvolvedores:** Bruno oliveira, Caio Padilha, Débora Duque e Raul dos Santos
- **Instituição:** Universidade La Salle - Rio de Janeiro  
- **Professor:** Lauro Víctor Ramos Cavada
- **Data de Entrega:** 12/06/2025]  
- **Linguagem Utilizada:** C  


---

## 2. 🎯 Objetivo do Programa

Este projeto Acadêmico permite registrar e analisar vendas realizadas em uma Pseudo fábrica de salgadinhos. Ele lê, persiste e atualiza um arquivo de texto (`loja.txt`), além de fornecer relatórios como: número de vendas por determinados critérios, valores totais, média de vendas e estatísticas por gênero. Este projeto faz parte de uma atividade de avaliação de conhecimentos de prova final, em conjunto à avaliação de provas.

---

## 3. 🧱 Estrutura Geral do Programa

- **main()**  
  - Lê o arquivo `loja.txt`, conta registros e carrega-os dinamicamente em memória.  
  - Exibe menu interativo para: cadastrar novas vendas, buscar vendas por nome, gerar relatórios ou encerrar.  
  - Usa `switch()` para chamar funções associadas às opções do menu.

- **Funções auxiliares**:
  - **Validação e Entrada de Dados**  
    - `input_sanitized(...)` — valida vários tipos de entradas (nome, gênero, idade, quantidade, loja e preço). Tem por finalidade garantir a integridade das entradas de usuário,  assegurando os registros dos dados persistentes e protegendo o sistema de comportamentos indesejáveis e fatais.
    - `inputDecisions_sanitized(...)` — valida respostas  do tipo: ‘S’/‘N’.  
    - `clearBuffer()` — limpa o buffer do teclado corretamente para 'N' casos.  
    - `regex_compiler()` — compila expressão regular para validar entradas de usuário no cadastro de nomes, conforme regras específicas
    - obs: Na seção 4, explicações mais especificas. 

  - **Manipulação de Strings**  
    - `capitalized_case()` — Transforma qualquer strings para o formato “Capitalizado”.  
    - `strlen_utf8()` — calcula o tamanho real de caracteres em strings UTF‑8. A função Strlen da biblioteca strings.h, não é capaz de tratar corretamente. 

  - **Cadastro de Vendas**  
    - `register_sale()` — permite inserir novas vendas com validação, aumenta o vetor com `realloc` e salva no arquivo(loja.txt).

  - **Consultas e Relatórios**  
    - `sale_forName()` — busca vendas por nome, trazendo dados de compras pertinente a esse nome(se existir).  
    - `sales_lessThan()` — conta vendas abaixo de determinado valor.  
    - `sales_withThree_items()` — conta vendas com exatamente 3 itens.  
    - `sales_in_B()` — conta as vendas feitas na loja `B`.  
    - `Get_men()` — conta os clientes do gênero masculino.  
    - `sale_genderN()` — soma os valores de vendas de gênero ‘N’ (não declarado), se Existir.  
    - `Get_itensTotal()` — soma o total de itens vendidos.  
    - `Get_totalValue()` — soma o total dos valores das vendas.  
    - `sale_averageValue()` — calcula o valor médio de venda.  
    - `sale_lowPrice_Women()` — encontra a menor venda feita por mulheres.  
    - `Get_biggestName()` — exibe cliente com o nome mais longo.  
    - `Get_youngest()` — exibe o cliente mais jovem.

---

## 4. ⚙️ Considerações de funções

### `void capitalized_case(char *str)`

   Converte uma string para formato "Capitalizado" (primeira letra maiúscula, restantes minúsculas, considerando UTF‑8.Pt).

### `int strlen_utf8(char *str)`

   Retorna o número de caracteres visíveis, com suporte UTF‑8, ignorando espaços em branco. Decidimos por criar nossa própria função de comprimento de strings, que pudesse lidar com as especificidades da língua portuguesa, em caso de caracteres diacríticos. Deixando o Sistema amigável à escrita Brasileira e nos registros persistentes. 

   O Código ainda está em sua primeira versão e não garante segurança em todos os casos, ele garante entradas UTF-8 , para o uso do Português e das regras do sistema que é sítio dessa documentação. Para a construção dessa lógica, estivemos nos introduzindo aos fundamentos de baixo nível UTF-8, em artigos do IME(Instituo de matemática e estatística da USP) [confira clicando aqui](https://www.ime.usp.br/~pf/algoritmos/apend/unicode.html) que nos levaram aos entendimentos Basilares. Também fundamentamos a lógica, consultando o RFC-UTF8, que detalha as regras computacionais e de baixo nível da estrutura que valida o UTF-8 [clique para consultar a fonte aqui](https://datatracker.ietf.org/doc/html/rfc3629)

### `void regex_compiler(regex_t *exp)`

   Compila uma  regex que garante, pelo menos 3 letras em nome válido; biblioteca Regex.h. Foi utilizando um padrão de regex robusto, feito por nossa equipe, que valida entradas no cadastro 'nome' conforme regras a seguir: impede nome com espaços em branco no início, números em qualquer posição, impede que nomes compostos tenham mais que um espaço entre as palavras, garante que nomes não sejam cadastrados com menos de três caracteres, restringe símbolos especiais que não são utilizados em nomes reais e impede espaços em branco ao final de qualquer strings(nome).

### `void clearBuffer()`

Descarta caracteres restantes no buffer até `\n`. Notamos que alguns casos, devido a permissividade em funções C, que não validam entradas erradas e que podem gerar bugs indefinidos — por sobra de mais de um caractere no buffer — que acarretaram problemas em outros campos, principalmente em funções fgets() após scanf() com entradas inválidas. O getchar(), pega apenas um caractere. Em um exemplo rápido de um scanf(%d), com uma entrada de caracteres, sempre retornam um erro, Todavia a função não atualiza a variável, não trata o erro e passa a execução para frente, deixando os inputs sem receber valores, sendo assim, os caracteres que sobraram no buffer criaram comportamentos indefinidos em varias ocasiões.

### `int input_sanitized(..., fields field, int minRange, int maxRange)`

Valida entrada de acordo com o `field` , aplicando regras de range máximo e mínimos para diversos campos. Retorna o valor válido ou sinaliza erro. O parâmetro field é uma Enum que sinaliza à função qual input ela deve implementar e em qual campo da função de cadastro e da função de consulta específica deve tratar e validar, higienizando as entradas de usuário.

### `int inputDecisions_sanitized(char *option)`

Valida escolhas do tipo: ‘S’/’N’. Garantido entradas válidas se beneficiando de funções como clearBuffer( ).

### `void register_sale(venda **sale, int *qtRow)`

Solicita cadastro de vendas, expande vetor com `realloc`, grava no arquivo e atualiza a variável `qtRow`. Recebe um ponteiro de um ponteiro, que permite interagir com o cache de registros criado na inicialização do sistema, permitindo que o arquivo persistente se atualize, de modo que: também mantenha o cache representando o estado completo e atual do arquivo(loja.txt) com eficiência de recursos. 

O uso de ponteiro de ponteiro foi imprescindível, pois o aprendizado mostrou-nos: que realloc( ) feito por outro ponteiro influencia o ponteiro anterior, de modo que o ponteiro do cache fora da função perdia a referência, gerando erros.

### `void sale_forName(venda *sale, int qtRow)`

Busca por nome, exibe cada venda e soma os valores (as demais seguem lógica semelhante: `sales_lessThan()`, `Get_itensTotal()`, entre outas).


## 5. 🧾  Considerações sobre o aprendizado

O projeto nos deixou muito empolgados com diversos percalços que enfrentamos e que nos permitiu um conhecimento mais profundo sobre: fundamentos da computação, programação de baixo nível e como as diferentes formas de pensamento criam intempéries na equipe, devido a forma como cada um cria sua lógica. Gerando desafios para integrar o desenvolvimento de todos.

## 5. 📝💐  Agradecimentos: 

É deveras importante pra nós, expressar sincera gratidão ao Professor Mestre, Lauro Víctor Cavada, cujo apoio e orientação foram essenciais para a realização deste trabalho. Sua proposição de desafio nos ensinou muito — mesmo não sendo o mais complexo dos sistemas— E nos colocou na seara de conhecimentos e envolvimentos interpessoais de grande valia.








