
namespace _153503_Konchik_lab5.Domain
{
    public interface ISerializer
    {
        IEnumerable<Computer> DeSerializeByLINQ(string fileName);
        IEnumerable<Computer> DeSerializeXML(string fileName);
        IEnumerable<Computer> DeSerializeJSON(string fileName);
        void SerializeByLINQ(IEnumerable<Computer> collection, string fileName);
        void SerializeXML(IEnumerable<Computer> collection, string fileName);
        void SerializeJSON(IEnumerable<Computer> collection, string fileName);
    }
}
