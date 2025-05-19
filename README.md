# TCC - Problema da Coleta de Azeite de Dendê nas Baianas de Acarajé

Esse github possui os códigos, instâncias de teste e resultados apresentados no TCC.

## Códigos principais (GRASP, Genético e Memético)

Na raiz do projeto podemos ver três códigos principais, grasp.cpp, genetic.cpp e memetic.cpp. Esses códigos são os que foram compilados e utilizados para rodar as instâncias de teste, neles teremos a leitura das instâncias como input e chamada para os algoritmos específicos passando os parâmetros escolhidos.

Todos eles vão usar arquivos .hpp que estão dentro de ./structs e ./algorithms.

Em ./structs temos algumas structs que representam algumas coisas abordadas no trabalho. O ./structs/limitations.hpp que representa a struct com as limitações do problema de máximo e mínimo de dendê e o limite de tempo. O ./structs/route_info.hpp representa uma aresta digrafo, tendo o originIndex e o destinationIndex como o par ordenado (v_i, v_j), a distância em metros e a duração em segundos para percorrer. O ./structs/cost.hpp será a representação de cada aresta na matriz de adjacência utilizada no problema, onde juntamos os valores que que estão na aresta e no vértice de destino para formar um custo apenas na aresta, como explicado na modelagem do problema, nele teremos a distanceInMeters, o durationInSeconds (aqui já está acumulado tanto a duração do caminho da rota quanto o tempo necessário para coleta), e o dendeInDeciliters, representando quanto de dendê será coletado ao passar por essa aresta.

Nos códigos iremos representar o digrafo como uma matriz de adjacência, mais especificamente um Vec<Vec<Cost>> ().

Em ./algorithms nós temos primeiro algumas funções auxiliares, como ./algorithms/calculate_total_cost.hpp, que recebe a matriz de adjacência e uma rota e retorna o custo daquela rota em um Cost acumulado. O ./algorithms/construct_adjacency_matrix.hpp que recebe os dados de input com as informações das baianas e das arestas e constrói a matriz de adjacência no formato antes citado.

Após esses nós temos as implementações dos algoritmos estudados de fato, como o ./algorithms/grasp.hpp implementando o GRASP. O ./algorithms/genetic.hpp implementando o genético e o memético (aqui temos um parâmetro booleano no input para definir se será memético ou genético). O ./algorithms/local_search.hpp que implementa o VND abordado no TCC. E o ./algorithms/make_random_route.hpp que é a função que gera uma rota aleatória, que respeite os limites do problema, utilizando um parâmetro epsilon para definir a aleatoriedade dessa rota.

## Instâncias

As instâncias de teste utilizadas estão em ./testes/instances. E terá o formato de input abordado no TCC.

## Resultados

Todos os resultados estão em ./testes/results/<algorithm>/instance<instance_number>/result<result_number>.out

Como mencionado no TCC, cada instância foi rodada 30 vezes para cada algoritmo, tendo 30 resultados para cada uma.

## Instruções

Para rodar os testes é preciso compilar os arquivos ./genetic.cpp, ./grasp.cpp e ./memetic.cpp. Alguns arquivos bash de exemplos estão em ./testes, como o ./testes/test_genetic.sh, ./testes/test_grasp.sh, ./testes/test_memetic.sh e ./testes/test_vnd.sh. Porém, esses arquivos provavelmente precisarão ser modificados a depender do ambiente de testes utilizados, no caso do TCC foi um Windows 11 pro.

## Extras

Alguns códigos extras podem ser vistos no TCC, como representações JSON do input, limitações, localizações etc. Eles foram feitos já integrando com a api do google Distance Matrix, e podemos ver códigos dessa implementação em ./input_generator e ./main.cpp. Onde o input_generator ele pega localizações dentro de locations.json e chama a API do google para formar o digrafo com dados reais, transformando essa resposta para o formato de input esperado nos nossos algoritmos e também colocando dentro de input.json. O arquivo limitations.json deve estar preenchido com as limitações do problema ao rodar o ./input_generator, assim irá gerar o input também com os limites.