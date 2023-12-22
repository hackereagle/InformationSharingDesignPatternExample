// See https://aka.ms/new-console-template for more information
using System.Text;

Console.WriteLine("Hello, World!");
List<int> dataset = new List<int> {1, 5, 4, 3, 2, 8};
Context context = new Context(new SortAsending());
context.DoSomething(dataset);

Console.WriteLine("\n=====");
context.Strategy = new SortDesending();
context.DoSomething(dataset);
Console.ReadLine();

interface ISortStrategy
{
    void Sort(List<int> list);
}

class SortAsending : ISortStrategy
{
    public void Sort(List<int> list)
    {
        Console.WriteLine("Sorting list asending");
        list.Sort();
    }
}

class SortDesending : ISortStrategy
{
    public void Sort(List<int> list)
    {
        Console.WriteLine("Sorting list desending");
        list.Sort();
        list.Reverse();
    }
}

class  Context
{
    public Context(ISortStrategy strategy)
    {
        _strategy = strategy;
    }

    private ISortStrategy _strategy;
    public ISortStrategy Strategy { set => _strategy = value; }

    public void DoSomething(List<int> arr)
    {
        Console.WriteLine($"Do something before sorting, list: {ArrayToString(arr)}");
        _strategy.Sort(arr);
        Console.WriteLine($"Do something after sorting, list: {ArrayToString(arr)}");
    }
        
    private string ArrayToString(List<int> arr)
    {
        StringBuilder result = new StringBuilder();
        result.Append("[");
        foreach (var item in arr)
            result.Append($"{item} ");
        result.Append("]");
        return result.ToString();
    }
}
