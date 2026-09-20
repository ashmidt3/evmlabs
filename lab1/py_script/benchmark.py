import subprocess
import re
import matplotlib.pyplot as plt

RUNS = 5
N = 90000  # Размер массива
binary = r"..\cmake-build-debug\lab1.exe"

x_values = list(range(1, RUNS + 1))
y_values = []

print(f"Запуск программы {RUNS} раз для N = {N}...\n")

for i in x_values:
    res = subprocess.run([binary, str(N)], capture_output=True, text=True, check=True)

    # Обновленное регулярное выражение:
    # Захватывает время (группа 1) и число после слова Погрешность/Прогрешность (группа 2)
    match = re.search(r"Time taken:\s*([0-9.]+).*?(?:Прогрешность|Погрешность)\s*(\d+)", res.stdout)

    if match:
        time_sec = float(match.group(1))
        fault_nsec = int(match.group(2))
        y_values.append(time_sec)

        # Теперь выводим оба значения в консоль
        print(f"Измерение {i}: {time_sec:.4f} с | Погрешность таймера: {fault_nsec} нс")
    else:
        print(f"Ошибка парсинга вывода на шаге {i}: {res.stdout}")

# Построение графика
plt.figure(figsize=(9, 5))
plt.plot(x_values, y_values, marker='o', color='#ff7f0e', linewidth=2, label=f'Время работы (N={N})')

plt.title('Стабильность времени выполнения алгоритма', fontsize=12)
plt.xlabel('Счетчик измерения X (Номер запуска)', fontsize=11)
plt.ylabel('Время выполнения Y, с', fontsize=11)

plt.xticks(x_values)
plt.ylim(min(y_values) * 0.95, max(y_values) * 1.05)
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()
plt.tight_layout()

plt.savefig('measurements_chart.png', dpi=300)
plt.show()