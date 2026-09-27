import subprocess
import re
import matplotlib.pyplot as plt

# Настройки бенчмарка
OPTIMIZATIONS = ["O0", "O1", "O2", "O3", "Os", "Ofast", "Og"]
N_VALUES = [20000, 40000, 60000, 80000, 100000]

results = {opt: [] for opt in OPTIMIZATIONS}

print(f"{'N':>8} | " + " | ".join([f"{opt:>8}" for opt in OPTIMIZATIONS]))
print("-" * (11 + 11 * len(OPTIMIZATIONS)))

for n in N_VALUES:
    row = [f"{n:8d}"]
    for opt in OPTIMIZATIONS:
        exe_name = f"./lab2_{opt}"
        
        try:
            # Запуск программы с передачей аргумента N
            proc = subprocess.run([exe_name, str(n)], capture_output=True, text=True, check=True)
            
            # Парсинг вывода: ищем "Min time taken: X.XXXXXX sec."
            match = re.search(r"Min time taken:\s*([0-9.]+)\s*sec", proc.stdout)
            if match:
                time_sec = float(match.group(1))
                results[opt].append(time_sec)
                row.append(f"{time_sec:8.4f}")
            else:
                results[opt].append(None)
                row.append(f"{'Error':>8}")
        except FileNotFoundError:
            print(f"Файл {exe_name} не найден. Запустите build.sh")
            exit(1)
            
    print(" | ".join(row))

# Построение графика
plt.figure(figsize=(10, 6))

colors = ['#1f77b4', '#ff7f0e', '#2ca02c', '#d62728', '#9467bd', '#8c564b', '#e377c2']
markers = ['o', 's', '^', 'D', 'v', '<', '>']

for (opt, color, marker) in zip(OPTIMIZATIONS, colors, markers):
    plt.plot(N_VALUES, results[opt], marker=marker, color=color, linewidth=2, label=f'-{opt}')

plt.title('Зависимость времени выполнения Bubble Sort от размера массива N при различных оптимизациях', fontsize=12)
plt.xlabel('Размер массива N, элементов', fontsize=11)
plt.ylabel('Минимальное время выполнения, с', fontsize=11)
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title="Уровень оптимизации")
plt.tight_layout()

# Сохранение графика для отчета
chart_filename = 'optimization_comparison_chart.png'
plt.savefig(chart_filename, dpi=300)
print(f"\nГрафик успешно сохранен в файл: {chart_filename}")
plt.show()