using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.Json;

namespace MyLib
{
    public class FileService<T> : lab6.IFileService<T> where T : class
    {
        public void SaveData(IEnumerable<T> data, string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                JsonSerializer.Serialize(fs, data,
                    new JsonSerializerOptions()
                    {
                        WriteIndented = true
                    });
            }
        }

        public IEnumerable<T> ReadFile(string fileName)
        {
            List<T>? data = null;

            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                data = JsonSerializer.Deserialize<List<T>>(fs);
            }

            return data ?? new List<T>();
        }
    }
}
