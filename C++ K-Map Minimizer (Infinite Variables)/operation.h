#ifndef Operation_H
#define Operation_H

#include "compareKmapTerms.h"

/*
	class ConverteTerms is using to:
	Converte terms to ist equivalent ones

	class Combination is using to:
	provide all combination's possibilites

	class convSopToPos is using to:
	converte terms from some of product type
	to product of some type


*/


class  ConverteTerms 
{
	protected:	

	vector<int> termToPos (vector<char> term, int &type);
	vector <char> extract(vector<char> &terms, int &type);
	void compTerm(vector<char> &part,vector<char> &terms, int &type, int &pos);

};

//complete terms to be a full-minterm terms
void ConverteTerms :: compTerm(vector<char> &part,vector<char> &terms, int &type, int &pos)
	{
		
		int dashCount = 0 ;
		vector<char>copyPart;  //copying part for don't cares
		int temp;
		bool edited = 0; //check edditing in first phase

		pos -= part.size()-1; //return to main positiion
		terms.erase( terms.begin()+pos,terms.begin()+pos+part.size() );//return the part from total terms
		
		//first phase
		for( temp = 0; temp < part.size(); temp++)
		{
			if(part[temp] == '\'')dashCount ++;

			else if (part[temp] != 65 + temp - dashCount)
			{
				part.insert(part.begin()+temp,65+temp-dashCount); //insert letter
				copyPart = part;                                  //copy letter
				part.insert(part.begin()+temp+1,'\'');            //insert ' to the letter
				terms.insert(terms.begin()+pos,copyPart.begin(),copyPart.end()); //insert part without dash
				terms.insert(terms.begin()+pos,'+');                     //insert +
				terms.insert(terms.begin()+pos,part.begin(),part.end()); //insert the part with dash to be first
				edited = true; //this part has eddieted 
				break;

			}
		}
	
		//losing last digit
		if (edited == false &&part[part.size() -1] != 65+type)
		{
				part.insert(part.begin()+temp,65+temp-dashCount); //insert a letter
				copyPart = part;                                  //copy letter
				part.insert(part.begin()+temp+1,'\'');            //insert ' to the letter
				terms.insert(terms.begin()+pos,copyPart.begin(),copyPart.end()); //insert part without dash
				terms.insert(terms.begin()+pos,'+');                     //insert +
				terms.insert(terms.begin()+pos,part.begin(),part.end()); //insert the part with dash to be first
				
		}


	}//end edit part
/***Stretching terms by getting its full-minterm terms by:
*  1- getting comparelified terms
*  2- complete it with "compTerm" Function
*/
vector<char> ConverteTerms :: extract(vector<char> &terms, int &type)
	{
		int temp = 0;
		vector<char>part;  //part of expression
		int dashCount = 0;
		
		//save one term in part
		for(temp = 0; temp < terms.size(); temp++)
		{
			
			if( isalpha(terms[temp]) || terms[temp] == '\'' )
			{
				part.push_back(terms[temp]);
				if(terms[temp] == '\'') dashCount++;
			}	

			 if( (terms[temp] =='+' || temp == terms.size()-1  ) && part.size() - dashCount < type )
			 {
				 if(terms[temp] =='+')
						temp--; //return temp to last digit
				 compTerm(part,terms,type,temp); //complete term
				 temp--;//return temp to the digit before part
				 part.clear(); //clear edit to be used again
				 dashCount=0;
			 }
			 
			 else if (terms[temp] =='+' && part.size() - dashCount == type)
				 {
					 part.clear();  //clear part
					 dashCount=0;   //clear dash
				}

		}//end looping for
		return terms;
	}//end extr


vector<int> ConverteTerms :: termToPos (vector<char> term, int &type)
{
	vector<int>result; //for returning
	int weight = 0; //default case
	int pos = 0; //saving position
	
	term = extract(term, type); 

	//compute a full-minterm term positions
	for(int temp = term.size()-1; temp >=0 ; temp--)
	{
		if(term[temp] == '\'') //dashed digits
		{
			pos +=0;
			temp --; //going to the next minterm
		}
		else if ( isalpha(term[temp] ) ) //undashed digits
		{
			pos += pow(2.0, weight);
		}

		//seperators
		 if(term [temp] == '+' || temp == 0)
		{
			result.push_back(pos);
			pos = 0; //default case
			weight = 0; //default case
			continue;
		}
		weight++;
	}//end for

	for(int temp = 0; temp < result.size() - 1 ; temp++)
	{
		if(result[temp] == result[temp+1])
			result.erase(result.begin()+temp+1);

		else if (result[temp] > result[temp+1])
		{
			swap(result[temp], result[temp+1]);
		temp = -1;
		}
	}

	return result;
}//end term to pos

class Combination
{
	vector<int> people;
	vector<int> element;
	vector <vector<int>> result;
	int  size;
	 int count;

void saveResult(const vector<int>& v, int k, int &size)
{
 
  result.push_back(vector<int> () );
	for (int i = 0; i < v.size(); ++i) 
  {  
	  result[count].push_back(v[i]); 
	  if(result[count].size() == size)
		  count++;
	}

  
}//end save result

void go(int offset, int k) 
{

  if (k == 0) {
    saveResult(element, k, size);
    return;
  }
  for (int i = offset; i <= people.size() - k; ++i) {
    element.push_back(people[i]);
    go(i+1, k-1);
    element.pop_back();
  }
}//end go


public:
	vector<vector<int>> getCombination(int n, int k)
	{
	  size = k;
	people.clear();	
	result.clear();
	count = 0;
	for (int i = 0; i < n; ++i) { people.push_back(i); }
		go(0, k);

 	
  return result;
	}//end setComb

};

//converte from some of product to product ot sum
class SOPtoPOS
{
protected:
	void convSopToPos (vector<char> &result)
	{
		result.insert(result.begin(), '(');
		result.insert(result.end(), ')');

		for(int temp = 0; temp < result.size(); temp++)
		{
			if(result[temp] == '+')
			{
				result.erase(result.begin()+temp);
				result.insert(result.begin()+temp, ')');
				result.insert(result.begin()+temp+1, '.');
				result.insert(result.begin()+temp+2, '(');
				temp ++;
			}
			else if ( temp > 0 (isalpha(result[temp-1]) || result[temp-1] == '\'' ) && isalpha(result[temp] ) 
				&& result[temp-1] != '(' && result[temp-1] != '+' && result[temp] != ')')
			{
				result.insert(result.begin()+temp,'+');
			}
				
		}
	}//end convSopToPos

};

#endif