import tkinter as tk
from tkinter import messagebox

def calculate():
    try:
        # Входные данные
        arrivals_A = float(entry_arrivals_A.get())
        print(f'{arrivals_A=}')
        time_A = float(entry_time_A.get())
        print(f'{time_A=}')

        arrivals_B = float(entry_arrivals_B.get())
        print(f'{arrivals_B=}')
        time_B = float(entry_time_B.get())
        print(f'{time_B=}')

        served_customers = float(entry_served_customers.get())
        print(f'{served_customers=}')
        service_time = float(entry_service_time.get())
        print(f'{service_time=}')

        num_states = int(entry_num_states.get())  
        print(f'{num_states=}')

        # Интенсивности входных потоков
        lambda_A = arrivals_A / time_A
        print(f'{lambda_A=}')
        lambda_B = arrivals_B / time_B
        print(f'{lambda_B=}')
        total_lambda = lambda_A + lambda_B
        print(f'{total_lambda=}')
        
        # Интенсивность обслуживания
        mu = served_customers / service_time
        print(f'{mu=}')

        # Проверка устойчивости
        rho = total_lambda / mu
        print(f'{rho=}')
        if rho >= 1:
            messagebox.showerror("Ошибка", "Система неустойчива, так как ρ >= 1!")
            return

        # Финальные вероятности состояний
        P = []
        for n in range(num_states):
            P_n = (1 - rho) * (rho ** n)
            P.append(f"P{n} = {P_n:.4f}")
        print(f'{P=}')

        # Характеристики эффективности
        Loch = (rho ** 2) / (1 - rho)
        print(f'{Loch=}')
        Lsmo = rho / (1 - rho)
        print(f'{Lsmo=}')
        Tsmo = Lsmo / total_lambda
        print(f'{Tsmo=}')
        Toch = Loch / total_lambda

        # Вывод результатов
        result_text.delete(1.0, tk.END)  
        result_text.insert(tk.END,
            f"Интенсивность потока A: {lambda_A}\n"
            f"Интенсивность потока B: {lambda_B}\n"
            f"Интенсивность потока общая (λ): {total_lambda:.4f}\n"
            f"Интенсивность обслуживания (μ): {mu:.4f}\n"
            f"Коэффициент загрузки системы (ρ = λ/μ): {rho:.4f}\n\n"
            f"Финальные вероятности состояний:\n"
            + "\n".join(P) + "\n\n"
            f"Характеристики эффективности:\n"
            f"Относительная пропускная способность (Q = pобс): 1\n"
            f"Абсолютная пропускная способность (А = λQ = λ): {total_lambda:.4f}\n"
            f"Среднее число заявок в очереди (Lоч): {Loch:.4f}\n"
            f"Среднее число обслуживаемых заявок (Lобс =ρ⋅Q=ρ ): {rho:.4f}\n"
            f"Среднее число заявок, находящихся в СМО (Lсмо = Lоч + Lобc): {Lsmo:.4f}\n"
            f"Среднее время пребывания в СМО (Tсмо): {Tsmo:.4f} мин\n"
            f"Среднее время пребывания заявки в очереди (Tоч): {Toch:.4f} мин"
        )

    except ValueError:
        messagebox.showerror("Ошибка ввода", "Пожалуйста, введите корректные числовые значения!")

# Создание интерфейса
root = tk.Tk()
root.title("Расчёт СМО с одним окном")
root.geometry("700x650")

# Поля ввода
tk.Label(root, text="Параметры потока пассажиров в пункт А").pack()
tk.Label(root, text="Количество пассажиров за время:").pack()
entry_arrivals_A = tk.Entry(root)
entry_arrivals_A.insert(0, "3") 
entry_arrivals_A.pack()

tk.Label(root, text="Время (минуты):").pack()
entry_time_A = tk.Entry(root)
entry_time_A.insert(0, "20") 
entry_time_A.pack()

tk.Label(root, text="Параметры потока пассажиров в пункт B").pack()
tk.Label(root, text="Количество пассажиров за время:").pack()
entry_arrivals_B = tk.Entry(root)
entry_arrivals_B.insert(0, "2") 
entry_arrivals_B.pack()

tk.Label(root, text="Время (минуты):").pack()
entry_time_B = tk.Entry(root)
entry_time_B.insert(0, "20")  
entry_time_B.pack()

tk.Label(root, text="Параметры обслуживания").pack()
tk.Label(root, text="Количество обслуживаемых пассажиров:").pack()
entry_served_customers = tk.Entry(root)
entry_served_customers.insert(0, "3")  
entry_served_customers.pack()

tk.Label(root, text="Время обслуживания (минуты):").pack()
entry_service_time = tk.Entry(root)
entry_service_time.insert(0, "10")  
entry_service_time.pack()

# Кнопка для запуска расчётов
tk.Button(root, text="Рассчитать", command=calculate).pack()

tk.Label(root, text="Количество состояний для расчёта:").pack()
entry_num_states = tk.Entry(root)
entry_num_states.insert(0, "3") 
entry_num_states.pack()


# Создание фрейма для прокручиваемого текста
frame = tk.Frame(root)
frame.pack(pady=10)

# Создание Text виджета для вывода результата
result_text = tk.Text(frame, width=70, height=15)
result_text.pack(side=tk.LEFT, fill=tk.Y)

# Добавление полосы прокрутки
scrollbar = tk.Scrollbar(frame, orient="vertical", command=result_text.yview)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
result_text.config(yscrollcommand=scrollbar.set)

# Запуск программы
root.mainloop()