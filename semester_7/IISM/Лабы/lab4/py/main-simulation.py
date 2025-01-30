import tkinter as tk
import random
import time

class SMOSimulation:
    def __init__(self, master):
        self.master = master
        self.master.title("СМО Симуляция")
        self.master.geometry("800x600")

        # Параметры модели
        self.arrival_rate = 0.25  # Лямбда
        self.service_rate = 0.3  # Мю
        self.simulation_time = 600  # Время моделирования в секундах

        # Очередь и сервер
        self.queue = []
        self.server_busy = False

        # UI элементы
        self.canvas = tk.Canvas(self.master, width=600, height=400, bg="white")
        self.canvas.pack(pady=20)

        self.info_label = tk.Label(self.master, text="Начало симуляции", font=("Arial", 14))
        self.info_label.pack()

        self.start_button = tk.Button(self.master, text="Запустить симуляцию", command=self.start_simulation)
        self.start_button.pack(pady=10)

    def draw_queue(self):
        self.canvas.delete("all")
        x_start = 50
        y = 200
        for i, customer in enumerate(self.queue):
            self.canvas.create_oval(x_start + i * 30, y, x_start + i * 30 + 20, y + 20, fill="blue")
            self.canvas.create_text(x_start + i * 30 + 10, y - 10, text=f"{customer:.2f}")

        if self.server_busy:
            self.canvas.create_rectangle(500, 150, 550, 250, fill="red")
            self.canvas.create_text(525, 130, text="Обслуживание")
        else:
            self.canvas.create_rectangle(500, 150, 550, 250, fill="green")
            self.canvas.create_text(525, 130, text="Свободно")


    def generate_arrival_time(self):
        return random.expovariate(self.arrival_rate)

    def generate_service_time(self):
        return random.expovariate(self.service_rate)

    def start_simulation(self):
        self.queue = []
        self.server_busy = False
        current_time = 0
        next_arrival = self.generate_arrival_time()
        service_end_time = float("inf")

        while current_time < self.simulation_time:
            if next_arrival < service_end_time:
                # Обработка прибытия клиента
                current_time = next_arrival
                self.queue.append(current_time)
                self.info_label.config(text=f"Прибыл клиент в {current_time:.2f} сек")

                if not self.server_busy:
                    # Если сервер свободен, начинаем обслуживание
                    self.server_busy = True
                    service_time = self.generate_service_time()
                    service_end_time = current_time + service_time
                    self.info_label.config(
                        text=f"Обслуживание клиента началось в {current_time:.2f} сек, закончится в {service_end_time:.2f} сек"
                    )

                next_arrival += self.generate_arrival_time()
            else:
                # Обработка завершения обслуживания
                current_time = service_end_time
                self.server_busy = False
                self.queue.pop(0)
                self.info_label.config(text=f"Обслуживание клиента завершено в {current_time:.2f} сек")

                if self.queue:
                    # Если есть клиенты в очереди, начинаем обслуживание следующего
                    self.server_busy = True
                    service_time = self.generate_service_time()
                    service_end_time = current_time + service_time
                    self.info_label.config(
                        text=f"Обслуживание следующего клиента началось в {current_time:.2f} сек, закончится в {service_end_time:.2f} сек"
                    )
                else:
                    service_end_time = float("inf")

            self.draw_queue()
            self.master.update()
            time.sleep(1)

if __name__ == "__main__":
    root = tk.Tk()
    app = SMOSimulation(root)
    root.mainloop()