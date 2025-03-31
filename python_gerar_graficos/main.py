import pandas as pd
import matplotlib.pyplot as plt
from fpdf import FPDF
import tempfile

# Ler o arquivo CSV
data = pd.read_csv("results.csv")
max_size = data["Size"].max()

# Criar o PDF
pdf = FPDF()
pdf.set_auto_page_break(auto=True, margin=15)

for start in range(1000, max_size + 1, 2000):  # Criar gráficos para cada 2000 elementos
    pdf.add_page()
    
    fig, axes = plt.subplots(2, 1, figsize=(5, 6))
    
    for i, limit in enumerate([start, start + 1000]):
        if limit > max_size:
            break
        
        subset = data[data["Size"] <= limit]
        if subset.empty:
            continue
        
        axes[i].plot(subset["Size"], subset["MergeSortTime"], linestyle='-', label='Merge Sort', color='b')
        axes[i].plot(subset["Size"], subset["InsertionSortTime"], linestyle='-', label='Insertion Sort', color='r')
        axes[i].set_title(f"Tempo de ordenação com {limit} elementos")
        axes[i].set_xlabel("Número de elementos")
        axes[i].set_ylabel("Tempo (s)")
        axes[i].grid(True)
        axes[i].legend()
    
    plt.tight_layout()
    
    with tempfile.NamedTemporaryFile(delete=False, suffix=".png") as tmpfile:
        plt.savefig(tmpfile.name, format='png')
        pdf.image(tmpfile.name, x=10, y=30, w=180)
    
    plt.close()

pdf.output("sorting_results.pdf")
print("PDF gerado com sucesso!")
