using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;

namespace ClassLibrary
{
    public class StreamService<T>
    {
        private readonly Mutex mutexObj = new();

        public async Task WriteToStreamAsync(Stream stream, IEnumerable<T> data, 
            IProgress<string> progress)
        {
            progress.Report($"Начало WriteToStreamAsync в потоке: " +
                $"{Thread.CurrentThread.ManagedThreadId}");
            
            //await Task.Run(() => 
            //{
            mutexObj.WaitOne();
                
            await JsonSerializer.SerializeAsync(stream, data);


            //string? json = JsonSerializer.Serialize(data, 
            //    new JsonSerializerOptions { WriteIndented = true });
            //byte[] bytes = Encoding.UTF8.GetBytes(json);

            //stream.Flush();
            //stream.Write(bytes, 0, bytes.Length);
            
            mutexObj.ReleaseMutex();
            //});

            progress.Report($"Конец WriteToStreamAsync в потоке: " +
                $"{Thread.CurrentThread.ManagedThreadId}");
        }

        public async Task CopyFromStreamAsync(Stream stream, string fileName, 
            IProgress<string> progress)
        {
            progress.Report($"Начало CopyFromStreamAsync в потоке: " +
                $"{Thread.CurrentThread.ManagedThreadId}");

            await Task.Run(() => 
            {
                mutexObj.WaitOne();

                byte[] bytes = new byte[stream.Position];
                stream.Position = 0;
                stream.Read(bytes, 0, bytes.Length);

                using StreamWriter writer = new StreamWriter(fileName, false);
                writer.Write(Encoding.UTF8.GetString(bytes));

                mutexObj.ReleaseMutex();
            });

            progress.Report($"Конец CopyFromStreamAsync в потоке: " +
                $"{Thread.CurrentThread.ManagedThreadId}");
        }

        public async Task<int> GetStatisticsAsync(string fileName, Func<T, bool> filter)
        {
            int ans = 0;

            await Task.Run(() => 
            {
                using FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate);
                List<T>? items = JsonSerializer.Deserialize<List<T>>(fs);

                foreach (var item in items)
                {
                    if (filter(item))
                    {
                        ans++;
                    }
                }
            });
            
            return ans;
        }
    }
}
