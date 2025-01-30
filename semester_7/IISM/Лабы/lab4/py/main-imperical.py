import tkinter as tk
from tkinter import messagebox
import random
import statistics

def run_experiment(arrival_rate, service_rate, simulation_time):
    # Временные точки событий
    arrivals = []
    departures = []
    queue_times = []  # Время ожидания в очереди
    system_times = []  # Время в системе (очередь + обслуживание)

    current_time = 0
    queue = []  # Очередь клиентов
    server_busy_until = 0  # Когда сервер освободится

    # Генерация событий прибытия
    while current_time < simulation_time:
        inter_arrival_time = random.expovariate(arrival_rate)
        current_time += inter_arrival_time
        if current_time > simulation_time:
            break
        arrivals.append(current_time)

    # Обработка событий
    for arrival_time in arrivals:
        # Если сервер занят, клиент становится в очередь
        if arrival_time < server_busy_until:
            queue.append(arrival_time)
        else:
            # Если сервер свободен, обслуживание начинается сразу
            service_time = random.expovariate(service_rate)
            departure_time = arrival_time + service_time
            server_busy_until = departure_time
            departures.append(departure_time)
            queue_times.append(0)
            system_times.append(service_time)

        # Обработка очереди
        while queue and queue[0] <= server_busy_until:
            start_service_time = max(server_busy_until, queue.pop(0))
            service_time = random.expovariate(service_rate)
            departure_time = start_service_time + service_time
            server_busy_until = departure_time
            departures.append(departure_time)
            queue_times.append(start_service_time - arrival_time)
            system_times.append(departure_time - arrival_time)

    # Вычисление характеристик
    avg_time_in_queue = statistics.mean(queue_times) if queue_times else 0
    avg_time_in_system = statistics.mean(system_times) if system_times else 0

    return {
        "Среднее время пребывания заявки в очереди (Tоч)": avg_time_in_queue,
        "Среднее время пребывания в СМО (Tсмо)": avg_time_in_system
    }

def calculate():
    try:
        arrival_rate = float(entry_arrival_rate.get())
        service_rate = float(entry_service_rate.get())
        simulation_time = int(entry_simulation_time.get())

        results = run_experiment(arrival_rate, service_rate, simulation_time)

        # Вывод результатов в текстовое поле
        result_text.delete(1.0, tk.END)
        result_text.insert(tk.END, "Эмпирические характеристики эффективности:\n")
        for key, value in results.items():
            result_text.insert(tk.END, f"{key}: {value:.2f}\n")

    except ValueError:
        messagebox.showerror("Ошибка ввода", "Пожалуйста, введите корректные числовые значения!")

# Создание интерфейса
root = tk.Tk()
root.title("Эмпирический расчёт СМО")
root.geometry("600x500")

# Поля ввода
tk.Label(root, text="Интенсивность прибытия (лямбда):").pack()
entry_arrival_rate = tk.Entry(root)
entry_arrival_rate.insert(0, "0.25")
entry_arrival_rate.pack()

tk.Label(root, text="Интенсивность обслуживания (мю):").pack()
entry_service_rate = tk.Entry(root)
entry_service_rate.insert(0, "0.3")
entry_service_rate.pack()

tk.Label(root, text="Время моделирования (минуты):").pack()
entry_simulation_time = tk.Entry(root)
entry_simulation_time.insert(0, "60")
entry_simulation_time.pack()

# Кнопка для запуска расчётов
tk.Button(root, text="Рассчитать", command=calculate).pack()

# Текстовое поле для вывода результата
result_text = tk.Text(root, width=70, height=15)
result_text.pack()

# Запуск программы
root.mainloop()
