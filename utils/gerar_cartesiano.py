import matplotlib.pyplot as plt
import numpy as np
import re
from collections import defaultdict

# Abrindo o arquivo para analisar seu conteúdo
file_path = "./resultado_tempo.out"

with open(file_path, "r", encoding="utf-8") as file:
    lines = file.readlines()

# Dicionário para armazenar os dados
data = defaultdict(list)

# Expressão regular para extrair os valores
pattern = re.compile(r"algoritmo: (\w+) instancia: (\d+) media: ([\d\.]+)")

# Processar cada linha do arquivo
for line in lines:
    match = pattern.search(line)
    if match:
        algoritmo, instancia, media = match.groups()
        instancia = int(instancia)
        media = float(media)
        data[algoritmo].append((instancia, media))

# Ordenar os dados por instância
for algoritmo in data:
    data[algoritmo].sort()

# Criar o gráfico
plt.figure(figsize=(10, 6))
for algoritmo, valores in data.items():
    instancias, medias = zip(*valores)
    plt.plot(instancias, medias, marker="o", label=algoritmo)

# Configurações do gráfico
plt.xlabel("Instância")
plt.ylabel("Tempo Médio (ms)")
# plt.title("Comparação de Tempo Médio por Algoritmo")
plt.legend()
plt.grid(True)

# Definir os valores específicos no eixo X
plt.xticks([0, 1, 20, 30, 40, 60, 80, 100])

# Mostrar o gráfico
plt.show()
