# Object Oriented Programing 2023 Section Tasks

### [Quiz #2]()
create new class that have the following:
- new class that is not (student or computer or laptop or pc)
- has up to 8 different attributes or more 
- has 5 different constructors or more 
- has 6 different methods
```c#
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
        public int Speed;
        public int Max_Fuel;
        public int Price;
        public int Guarantee_Duration;
        
        
                // Constructor
        public Car()
        {
            Console.WriteLine("Ojbect Created!");
        }
        
                //Actions or Methods
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
            CarOne.Speed = 155;
            CarOne.Max_Fuel = 22;
            CarOne.Price = 3000000;
            CarOne.Guarantee_Duration = 10;
            

            //objectName.attributeName
            Console.WriteLine("Model: {0}",CarOne.Model);
            Console.WriteLine("Manufacture Date: {0}",CarOne.Manufacture_Date);
            Console.WriteLine("Manufacturer: {0}",CarOne.Manufacturer);
            Console.WriteLine("Color: {0}",CarOne.Color);
            Console.WriteLine("Speed: {0} MPH",CarOne.Speed);
            Console.WriteLine("Max Fuel: {0} GAL",CarOne.Max_Fuel);
            Console.WriteLine("Price: {0}",CarOne.Price);
            Console.WriteLine("Guarantee: {0} Years",CarOne.Guarantee_Duration);
    
        }
    }
}
```
