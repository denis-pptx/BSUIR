using ClassLibrary;
using LoremNET;

namespace lab8
{
    class Program
    {
        
        public static async Task Main(string[] args)
        {
            List<Musician> musicians = new List<Musician>();
            for (int i = 0; i < 1000; i++)
            {
                musicians.Add(new(i, Lorem.Words(1), (int)Lorem.Number(1, 100)));
            }

            var streamService = new StreamService<Musician>();
            var memoryStream = new MemoryStream();
            string? fileName = @"..\..\..\info.json";
            var progress = new Progress<string>(str => Console.WriteLine(str));
      

            var task1 = streamService.WriteToStreamAsync(memoryStream, musicians, progress);
            Thread.Sleep(150);
            var task2 = streamService.CopyFromStreamAsync(memoryStream, fileName, progress);
            Task.WaitAll(task1, task2);

            int statisticsParam = (int)Lorem.Number(1, 100);
            int ans = await streamService.GetStatisticsAsync(fileName, 
                musician => musician.NumberOfSongs > statisticsParam);
            Console.WriteLine($"Статистические данные (песен > {statisticsParam}): {ans}");
        }
    }
}
