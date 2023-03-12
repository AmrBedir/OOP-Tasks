using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_Tasks
{

    // class nameOfClass { Attributes & Actions }

    class Car {
        // accees modifer type variableName;
        public string Model;
        public int Manufacture_Date;
        public string Manufacturer;
        public string Color;
        public string Speed;
        public string Max_Fuel;
        public string Price;
        public string Guarantee;
        
        
                // Constructor
        public Car()
        {
            Console.WriteLine("Ojbect Created!");
        }
        
                //Actions 
                public void PrintObjectInfo()
        {
            Console.WriteLine("Model: {0} , Manufacturer: {1} ", Model, Manufacturer);
        }
    }

     class Program
    {
        static void Main(string[] args)
        {
            // className variableName = new className();
            Car CarOne = new Car();
            
            // array is object because of using new keyword
            int[] arr = new int[10];
            
            // write operation
            //objectName.attributeName = value;
            CarOne.Model = "BMW X7";
            CarOne.Manufacture_Date = 2018;
            CarOne.Manufacturer = "Bayerische Motoren Werke AG - BMW";
            CarOne.Color = "Black";
            CarOne.Speed = "155 mph";
            CarOne.Max_Fuel = "21.9 gal";
            CarOne.Price = "2,620,000";
            CarOne.Guarantee = "10 Years";
            

            //Read Operation
            //objectName.attributeName
            Console.WriteLine("Model: {0}",CarOne.Model);
            Console.WriteLine("Manufacture Date: {0}",CarOne.Manufacture_Date);
            Console.WriteLine("Manufacturer: {0}",CarOne.Manufacturer);
            Console.WriteLine("Color: {0}",CarOne.Color);
            Console.WriteLine("Speed: {0}",CarOne.Speed);
            Console.WriteLine("Max Fuel: {0}",CarOne.Max_Fuel);
            Console.WriteLine("Price: {0}",CarOne.Price);
            Console.WriteLine("Guarantee: {0}",CarOne.Guarantee);
    
        }
    }
}
