using lab1.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using lab1.Settings;
using System.Diagnostics;

namespace lab1.Services
{
    public class SQLiteService : IDbService
    {
        private SQLiteAsyncConnection _db;
        public async Task<IEnumerable<Musician>> GetAllMusicians()
        {
            await Init();
            return await _db.Table<Musician>().ToListAsync();
        }

        public async Task<IEnumerable<Song>> GetMusicianSongs(int musicianId)
        {
            await Init();
            return await _db.Table<Song>().Where(s => s.MusicianId == musicianId).ToListAsync();
        }

        public async Task Init()
        {
            if (_db != null)
            {
                return;
            }

            _db = new SQLiteAsyncConnection(DbConstants.DatabasePath, DbConstants.Flags);
            await _db.DropTableAsync<Musician>();
            await _db.DropTableAsync<Song>();
            await _db.CreateTableAsync<Musician>();
            await _db.CreateTableAsync<Song>();
            

            await _db.InsertAsync(new Musician() 
            { 
                Name = "Denis Konchik", 
                Country = "Belarus", 
                Subscribers = 2536230 
            }); 
            await _db.InsertAllAsync(new List<Song>()
            {
                new Song() { Title = "Cadillac", Listenings = 5358238, Likes = 35838, MusicianId = 1 },
                new Song() { Title = "DINERO", Listenings = 257325, Likes = 5735, MusicianId = 1 },
                new Song() { Title = "ICE", Listenings = 3523632, Likes = 52363, MusicianId = 1 },
                new Song() { Title = "Новый Мерин", Listenings = 3623623, Likes = 63623, MusicianId = 1 },
                new Song() { Title = "Cristal & МОЁТ", Listenings = 8676433, Likes = 67643, MusicianId = 1 },
                new Song() { Title = "ДУЛО", Listenings = 7736231, Likes = 37231, MusicianId = 1 },
                new Song() { Title = "NOMINALO", Listenings = 7533262, Likes = 53262, MusicianId = 1 },
                new Song() { Title = "SHOW", Listenings = 5634537, Likes = 34537, MusicianId = 1 },
                new Song() { Title = "ПОЧЕМУ?", Listenings = 5325742, Likes = 10542, MusicianId = 1 }
            });
   
            await _db.InsertAsync(new Musician()
            {
                Name = "Till Lindemann",
                Country = "Germany",
                Subscribers = 1004243
            });
            await _db.InsertAllAsync(new List<Song>()
            {
                new Song() { Title = "Du hast", Listenings = 73462352, Likes = 362352, MusicianId = 2 },
                new Song() { Title = "Ich Will", Listenings = 426264, Likes = 2264, MusicianId = 2 },
                new Song() { Title = "Deutschland", Listenings = 4364623, Likes = 36463, MusicianId = 2 },
                new Song() { Title = "Sonne", Listenings = 46363464, Likes = 436344, MusicianId = 2 },
                new Song() { Title = "Mein Herz brennt", Listenings = 634643623, Likes = 3464623, MusicianId = 2 },
                new Song() { Title = "Engel", Listenings = 90061623, Likes = 306123, MusicianId = 2 }
            });


            await _db.InsertAsync(new Musician()
            {
                Name = "Yaugen Kahnouski",
                Country = "China",
                Subscribers = 1954186
            });
            await _db.InsertAllAsync(new List<Song>()
            {
                new Song() { Title = "Лесник", Listenings = 87634234, Likes = 633934, MusicianId = 3 },
                new Song() { Title = "Кукла колдуна", Listenings = 7564342, Likes = 56432, MusicianId = 3 },
                new Song() { Title = "Ели мясо мужики", Listenings = 9784536, Likes = 78453, MusicianId = 3 },
                new Song() { Title = "Проклятый старый дом", Listenings = 1234576, Likes = 23456, MusicianId = 3 },
                new Song() { Title = "Охотник", Listenings = 34098652, Likes = 940862, MusicianId = 3 },
                new Song() { Title = "Ром", Listenings = 56682105, Likes = 682103, MusicianId = 3 },
                new Song() { Title = "Танец злобного гения", Listenings = 270542, Likes = 7052, MusicianId = 3 }
            });
        }


    }
}
