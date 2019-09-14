using System;
using System.Collections.Generic;

namespace GradeBook
{
    class Program
    {
        static void Main(string[] args)
        {
            var book = new DiskBook("Scott's Grade Book");
            book.GradeAdded += OnGradeAdded;
            EnterGrades(book);

            var stat = book.GetStatistics();
            Console.WriteLine($"The book's category is {InMemoryBook.CATEGORY}");
            Console.WriteLine($"The book name is {book.Name}");
            Console.WriteLine($"The average grade is {stat.Average:N1}");
            Console.WriteLine($"The lowest grade is {stat.Low}");
            Console.WriteLine($"The highest grade is {stat.High}");
            Console.WriteLine($"The letter grade is {stat.Letter}");
        }

        private static void EnterGrades(IBook book)
        {
            while (true)
            {
                Console.WriteLine("Enter a grade or 'q' to quit");
                var input = Console.ReadLine();
                if (input == "q")
                {
                    break;
                }

                try
                {
                    var grade = double.Parse(input);
                    book.AddGrade(grade);
                }
                catch (ArgumentException ex)
                {
                    Console.WriteLine(ex.Message);
                }
                catch (FormatException ex)
                {
                    Console.WriteLine(ex.Message);
                }
                finally
                {
                    Console.WriteLine("**");
                }
            }
        }

        static void OnGradeAdded(object sender, EventArgs e)
        {
            Console.WriteLine("The grade is added");
        }
    }
}
