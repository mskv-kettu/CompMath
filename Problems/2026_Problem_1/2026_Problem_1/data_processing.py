import matplotlib.pyplot as plt
import numpy as np
from pathlib import Path

L = 20

dir_path = Path("upwind_data")
if not dir_path.is_dir():
        print(f"Ошибка: директория '{dir_path}' не существует.")
data_files = list(dir_path.glob("*.txt"))

for file_path in data_files:
    file = file_path.stem
    print(file)
    parts = file.split('_')
    CFL = float(parts[0])
    h = float(parts[1])
    t = float(parts[2])
    
    
    x, y = [], []
    data = np.loadtxt(file_path)
    x = data[:, 0]
    y = data[:, 1]


    y_th = (np.sin(4 * np.pi * (x-t) / L))

    # График
    fig, ax = plt.subplots(figsize=(12, 9))
    ax.grid()
    ax.plot(x, y, color='#1E90FF', label=f'Upwind')
    ax.plot(x, y_th, color="#E21C1C", label=f'Theoretical Value')

    ax.set_title(f"h= {h:.4f}, CFL = {CFL}", fontsize=12)

    ax.set_xlabel(r'x')
    ax.set_ylabel(r'U(T,x)')

    ax.legend()
    plt.savefig(f"upwind_plots/{file}.png")