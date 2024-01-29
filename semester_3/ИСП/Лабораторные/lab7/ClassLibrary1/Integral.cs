using System.Diagnostics;

namespace ClassLibrary
{
    public class Integral
    {
        private Semaphore sem = new(2, 2);

        public void Calculate()
        {
            Console.WriteLine($"Поток {Thread.CurrentThread.ManagedThreadId} ждет семафор\n");
            sem.WaitOne();
            Console.WriteLine($"Поток {Thread.CurrentThread.ManagedThreadId} взял семафор\n");
            


            double a = 0;
            double b = 1;
            double step = 0.00000001;
            int iterations = (int)((b - a) / step);
            double S = 0;

            int extraIterations = 10;

            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            
            Progress?.Invoke(Thread.CurrentThread.ManagedThreadId, 0);
            for (int i = 1; i <= iterations; i++)
            {
                if (i % (iterations / 100) == 0)
                {
                    Progress?.Invoke(Thread.CurrentThread.ManagedThreadId, (double)i / iterations);
                }

                S += Math.Sin(step * i + step / 2) * step;

                for (int j = 0; j < extraIterations; j++)
                {
                    int m = j * (extraIterations - j);
                }
            }

            stopWatch.Stop();
            
            Result?.Invoke(Thread.CurrentThread.ManagedThreadId, 
                Thread.CurrentThread.Priority.ToString(), stopWatch.Elapsed, S);



            sem.Release();
            Console.WriteLine($"Поток {Thread.CurrentThread.ManagedThreadId} освободил семафор\n");
        }
         
        public event Action<int, string, TimeSpan, double>? Result;
        public event Action<int, double>? Progress;
       
    }
}