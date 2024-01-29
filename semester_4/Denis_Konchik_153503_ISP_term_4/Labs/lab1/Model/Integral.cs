using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab1.Model
{
    public class Integral
    {
        public async void CalculateAsync(CancellationToken cancellationToken)
        {
            await Task.Run(() =>
            {
                (double a, double b) = (0, 1);
                double step = 0.0000001;
                int iterations = (int)((b - a) / step);
                double sum = 0;

                for (int i = 1; i <= iterations; i++)
                {
                    if (cancellationToken.IsCancellationRequested)
                    {
                        ProgressChanged?.Invoke(0, false);
                        return;
                    }

                    if (i % (iterations / 10000) == 0)
                    {
                        double percent = (double)i / iterations * 100;
                        ProgressChanged?.Invoke(percent, false);
                    }

                    sum += Math.Sin(step * i + step / 2) * step;

                    // Extra actions.
                    for (int j = 0; j < 0; j++)
                    {
                        int m = j * 10;
                    }
                }

                ProgressChanged?.Invoke(sum, true);

            }, cancellationToken);
        }

        public event Action<double, bool> ProgressChanged;

    }
}
