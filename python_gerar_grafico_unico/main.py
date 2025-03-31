import pandas as pd
import matplotlib.pyplot as plt

# Ler o arquivo CSV
data = pd.read_csv("results.csv")

# Filtrar os resultados até 100000 elementos
data = data[data["Size"] <= 100000]

# Criar o gráfico comparativo
plt.figure(figsize=(10, 6))
plt.plot(data["Size"], data["MergeSortTime"], linestyle='-', label='Merge Sort', color='b')
plt.plot(data["Size"], data["InsertionSortTime"], linestyle='-', label='Insertion Sort', color='r')

plt.title("Comparação entre Merge Sort e Insertion Sort")
plt.xlabel("Número de elementos")
plt.ylabel("Tempo (s)")
plt.legend()
plt.grid(True)

# Salvar o gráfico
plt.savefig("comparacao_sort.png")
plt.show()
