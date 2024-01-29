using _153503_Konchik_lab5.Domain;
using System.Xml.Linq;
using System.Xml.Serialization;
using System.Text.Json;
using System.Xml;

namespace _153503_Konchik_lab5.Serializer
{
    public class Serializer : ISerializer
    {
        public void SerializeByLINQ(IEnumerable<Computer> collection, string fileName)
        {
            // Документ
            var xDoc = new XDocument();

            // Корневой элемент
            var xComputers = new XElement("Computers");

            foreach (var computer in collection)
            {
                // Корневой элемент
                var xComputer = new XElement("Computer");

                // Винчестер
                var xWinchester = new XElement("Winchester");

                // Элементы винчестера
                xWinchester.Add(
                    new XElement("Manufacturer", computer.Winchester.Manufacturer), 
                    new XElement("Interface", computer.Winchester.Interface),
                    new XElement("FormFactor", computer.Winchester.FormFactor),
                    new XElement("RotationSpeed", computer.Winchester.RotationSpeed),
                    new XElement("DataTransferRate", computer.Winchester.DataTransferRate),
                    new XElement("BufferSize", computer.Winchester.BufferSize));

                xComputer.Add(xWinchester);
                xComputers.Add(xComputer);
            }
            xDoc.Add(xComputers);
            xDoc.Save(fileName);    
        }
        public IEnumerable<Computer> DeSerializeByLINQ(string fileName)
        {
            XDocument xDoc = XDocument.Load(fileName);

            var computers = xDoc.Element("Computers")?
                .Elements("Computer").Select(p => p.Element("Winchester"))
                .Select(p => new Computer(new Winchester() 
                {
                    Manufacturer = p?.Element("Manufacturer")?.Value ?? "",
                    Interface = p?.Element("Interface")?.Value ?? "",
                    FormFactor = Double.Parse(p?.Element("FormFactor")?.Value ?? "0"),
                    RotationSpeed = Double.Parse(p?.Element("RotationSpeed")?.Value ?? "0"),
                    DataTransferRate = Double.Parse(p?.Element("DataTransferRate")?.Value ?? "0"),
                    BufferSize = Double.Parse(p?.Element("BufferSize")?.Value ?? "0")
                }
                )) ?? new List<Computer>();

            return computers;
        }

        public void SerializeXML(IEnumerable<Computer> collection, string fileName)
        {
            XmlSerializer xmlSerializer = new XmlSerializer(collection.GetType());

            using (XmlWriter xmlWriter = XmlWriter.Create(fileName, 
                new XmlWriterSettings() { Indent = true }))
            {
                xmlSerializer.Serialize(xmlWriter, collection);
            }
        }

        public IEnumerable<Computer> DeSerializeXML(string fileName)
        {
            XmlSerializer xmlSerializer = new XmlSerializer(typeof(List<Computer>));

            List<Computer>? computers = null;

            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                computers = xmlSerializer.Deserialize(fs) as List<Computer>;
            };

            return computers ?? new List<Computer>();
        }

        public void SerializeJSON(IEnumerable<Computer> collection, string fileName)
        {
            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                JsonSerializer.Serialize(fs, collection, 
                    new JsonSerializerOptions() 
                    { 
                        WriteIndented = true 
                    });
            }
        }

        public IEnumerable<Computer> DeSerializeJSON(string fileName)
        {
            List<Computer>? computers = null;

            using (FileStream fs = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                computers = JsonSerializer.Deserialize<List<Computer>>(fs);
            }

            return computers ?? new List<Computer>();
        }
    }
}