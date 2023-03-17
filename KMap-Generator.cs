using System;
using System.Collections.Generic;

public class KMap_Generator {
  public static void Main(string[] args) {
    // Define K-Map
    bool[, ] kMap = new bool[4, 4];
    kMap[0, 0] = true;
    kMap[0, 1] = false;
    kMap[0, 2] = true;
    kMap[0, 3] = false;
    kMap[1, 0] = false;
    kMap[1, 1] = true;
    kMap[1, 2] = false;
    kMap[1, 3] = true;
    kMap[2, 0] = true;
    kMap[2, 1] = false;
    kMap[2, 2] = true;
    kMap[2, 3] = false;
    kMap[3, 0] = false;
    kMap[3, 1] = true;
    kMap[3, 2] = false;
    kMap[3, 3] = true;

    // Print K-Map
    Console.WriteLine("K-Map:");
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        Console.Write(Convert.ToInt32(kMap[i, j]) + " ");
      }
      Console.WriteLine();
    }

    // Find minterms and maxterms
    List < int > minterms = new List < int > ();
    List < int > maxterms = new List < int > ();
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        if (kMap[i, j]) {
          int minterm = (i * 4) + j;
          minterms.Add(minterm);
        } else {
          int maxterm = (i * 4) + j;
          maxterms.Add(maxterm);
        }
      }
    }

    // Print minterms and maxterms
    Console.WriteLine("MinTerms: " + string.Join(",", minterms));
    Console.WriteLine("MaxTerms: " + string.Join(",", maxterms));

    // Convert minterms and maxterms to expressions
    string mintermExpression = ConvertToExpression(minterms, "m");
    string maxtermExpression = ConvertToExpression(maxterms, "M");

    // Print the expressions
    Console.WriteLine("MinTerm Expression: " + mintermExpression);
    Console.WriteLine("MaxTerm Expression: " + maxtermExpression);

    Console.ReadLine();
  }

  public static string ConvertToExpression(List < int > terms, string prefix) {
    if (terms.Count == 0) {
      return "1";
    } else if (terms.Count == 16) {
      return "0";
    } else {
      List < string > expressionTerms = new List < string > ();
      foreach(int term in terms) {
        string termString = Convert.ToString(term, 2).PadLeft(4, '0');
        string expressionTerm = "";
        for (int i = 0; i < termString.Length; i++) {
          if (termString[i] == '0') {
            expressionTerm += prefix + (i + 1) + "'";
          } else {
            expressionTerm += prefix + (i + 1);
          }
        }
        expressionTerms.Add(expressionTerm);
      }
      return string.Join(" + ", expressionTerms);
    }
  }
}
