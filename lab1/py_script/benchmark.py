import csv
import re
import subprocess
import matplotlib.pyplot as plt

n_values = [20000, 40000, 60000, 80000, 100000, 120000, 140000, 160000]
RUNS = 5
min_times = []
table_data = []

binary = r"..\cmake-build-debug\lab1.exe"

for n in n_values:
    runs = []
    for _ in range(RUNS):
        res = subprocess.run([binary, str(n)], capture_output=True, text=True, check=True)
        nums = re.findall(r"[-+]?\d*\.\d+|\d+", res.stdout)
        runs.append(float(nums[-1]))

    best = min(runs)
    min_times.append(best)
    table_data.append([n, best])
    print(f"N = {n:5d} | runs: {runs} | min = {best:.4f} s")

with open("statistics.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    writer.writerow(["n", "time_sec"])
    writer.writerows(table_data)

plt.figure(figsize=(9, 5))
plt.plot(n_values, min_times, marker='o', color='#1f77b4', linewidth=2, label='Эксперимент (Bubble Sort)')
plt.title('Зависимость времени выполнения от размера массива N', fontsize=12)
plt.xlabel('Размер массива N, элементов', fontsize=11)
plt.ylabel('Время выполнения t, с', fontsize=11)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()

plt.savefig('bubble_sort_chart.png', dpi=300)
plt.show()