using System.Threading;
using ClassLibrary;

namespace lab7
{
    class Program
    {
        public static void Main()
        {
            Integral integral = new();
            integral.Progress += ProgressBar;
            integral.Result += PrintResult;
             
            Thread fastThread = new Thread(integral.Calculate);
            fastThread.Priority = ThreadPriority.Highest; 
            fastThread.Start();

            for (int i = 0; i < 1; i++)
            {
                Thread slowThread = new Thread(integral.Calculate);
                slowThread.Priority = ThreadPriority.Lowest;
                slowThread.Start();
            }
        }

        public static void ProgressBar(int threadId, double percent)
        {
            //return;

            int maxStripeSymbols = 30;
            string stripe = "";
            for (int i = 0; i < (int)(maxStripeSymbols * percent); i++)
            {
                stripe += "=";
            }
            stripe += ">";
            while (stripe.Length < maxStripeSymbols + 1)
            {
                stripe += " ";
            }

            Console.WriteLine($"Поток {threadId:00}: [{stripe}] {(int)(percent * 100)}%");

        }

        public static void PrintResult(int threadId, string priority, TimeSpan timeSpan, double answer)
        {
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                                                timeSpan.Hours, timeSpan.Minutes, timeSpan.Seconds,
                                                timeSpan.Milliseconds / 10);

            Console.WriteLine($"\nПоток {threadId} завершен\n" +
                $"Приоритет: {priority}\n" +
                $"Время: {elapsedTime}\n" +
                $"Ответ: {answer:f4}\n");
        }
        

    }
}