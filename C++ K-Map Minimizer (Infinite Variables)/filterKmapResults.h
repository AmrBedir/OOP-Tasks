#ifndef FILTERKMAPRESULTS
#define FILTERKMAPRESULTS

#include "operation.h"

//this class is using for filtering results and giving
//all possibilites results
class FilterKmapTerms : public CompareKmapTerms, public ConverteTerms, public Combination 
{
protected:
		
	int	temp, temp1, temp2, temp3; //temprature variables
		
	vector<char> getTerm (vector<char> &result, int pos); //getting a term form an array
	int getMintermCount(vector<char> &term);
	int getLargestTermSize(vector<char> &result);
	vector <vector<char>> getFilterResult(vector<vector < char>> &results, vector<char> &essentialTerms);
	bool checkResult (vector<char> someResult, vector<int> ones );
	vector <vector<char>> filter (vector<char> &result, vector<int> ones);
	
};//end filterKmapTerms

/***
	The main function of the program that implement K-map by:
	1- prompting for k-map type by its variable's number
	2- prompting for one's position by getPos function
	3- prompting for don't care position by getPos function
	4- Minimizing and getting results
*/



//get a term from a vector of terms (result)
vector<char> FilterKmapTerms :: getTerm (vector<char> &result, int pos)
{
	int temp;
	vector<char> term;
	for(temp = pos; temp < result.size(); temp++)
	{
		if(result[temp] != '+')
			term.push_back(result[temp]);
		else
			break;
	}

	return term;
}//end getTerm


	//Determine the larget size of minterms
int FilterKmapTerms :: getLargestTermSize(vector<char> &result)
{
	int largestSize = 0;
	vector<char> term;

	for(int temp = 0; temp  <result.size(); temp += term.size() + 1)
	{
		term = getTerm(result, temp);
		
		if(getMintermCount(term) > largestSize) 
			largestSize = getMintermCount(term);
	
	}//end for

	return largestSize;
}//end get Largest Term size

	//return a term's minterms count
int FilterKmapTerms :: getMintermCount(vector<char> &term)
{
	int count = 0; //for return

	for(int temp = 0; temp < term.size(); temp++)
	{
		if(isalpha(term[temp]) ) //search for alphabets
			count++;
	}
	return count;
}//end get minterms count

vector<vector<char> > FilterKmapTerms :: filter (vector<char> &result, vector<int> ones)
{

	vector<char> term,    //reading all term alone
				essentialTerms; //result after filtering
	vector<vector<char>> filterResult;
	int LargestTermSize;
	vector<vector<char>>terms;
	

	//setting essentials
	LargestTermSize = getLargestTermSize(result);

	for(int temp = 0 ; temp < result.size(); temp ++)
	{
		term = getTerm(result, temp);

		//term is essential 
		if(LargestTermSize > getMintermCount(term) )
		{
			//add + for more than one term result
			if(essentialTerms.size() > 0 )
			{
				essentialTerms.push_back('+');
			}
			for(int temp1 = 0 ; temp1 < term.size(); temp1 ++)
			{
				essentialTerms.push_back(term[temp1]); //add term to filter result
				result.erase(result.begin()+temp);   //remove term form main result
			}

			if(result.size() > 0)//erase + for more than one term
				result.erase(result.begin()+temp);
			
			resultTerms--;  //decrement result terms
			temp--;
		}//end if of essential terms
		else
			temp += term.size();
	}//end result covering loop
	
	terms.push_back(vector<char> () );
	for(int temp = 0; temp < result.size(); temp++)
	{
		if(result[temp] == '+' && temp < result.size())
			terms.push_back(vector<char> () );
		else
		terms[terms.size()-1].push_back(result[temp]);
		
	}

	filterResult = getFilterResult(terms, essentialTerms);

	return filterResult;
}//end filter

/***
*   Getting terms position on k-map by:
*   1- Extracting comparelified terms and return it to 
*      it to its full-minterm terms
*   2- compute its positions by compute position of
*      each full-minterm terms
*/


bool FilterKmapTerms :: checkResult (vector<char> someResult, vector<int> ones)
{
	vector<int> resultPos; //saving someResult positions in k-map

	resultPos = termToPos(someResult,type);

	for(int temp = 0; temp < resultPos.size(); temp++)
	{
		for(int temp1= 0; temp1<ones.size(); temp1++)
		{
		if(ones[temp1] == resultPos[temp])  //searching for matching ones
			ones.erase(ones.begin()+temp1); //erase matching ones
		}
	}

	//results are covering all ones
	if(ones.size() == 0)
		return true;
	else//results don't cover all ones
		return false;

}//end check results

vector<vector<char>> FilterKmapTerms ::getFilterResult(vector<vector < char>> &results, vector<char> &essentialTerms)
{
	vector<vector<char>> filterResult; //return variable
	int filterResultCount = 0;  //count filter results
	int largestCombinationsCount = resultTerms;  //set largest combinations count
	vector<char> someResult;
	vector<vector<int> > possibilites;

	for(int temp = 1; temp <= largestCombinationsCount; temp++)
	{
		possibilites.clear();
		possibilites = getCombination(results.size(), temp);

		
		/* Adding other terms with combinational possibilites */

		//covering possibilites
		for(int temp1 = 0; temp1 < possibilites.size(); temp1++)
		{
			someResult.clear();
			//add essential terms
			for(int temp1 = 0; temp1 < essentialTerms.size(); temp1++)
			someResult.push_back(essentialTerms[temp1]);

			//covering all term alone
			for(int temp2 = 0; temp2 < possibilites[temp1].size(); temp2++)
			{
				
				if(someResult.size() > 0) someResult.push_back('+'); //adding + for separating terms
				for(int temp3 = 0; temp3 < results[ possibilites[temp1][temp2] ].size(); temp3++)
				{
					someResult.push_back(results[ possibilites[temp1][temp2] ] [temp3] );
				}
			
			}//end covering lonly terms

		if(checkResult(someResult,ones) )
		{
			filterResult.push_back( vector<char> () );

			for(int temp1 = 0; temp1 < someResult.size(); temp1++)
			{
				filterResult[filterResult.size() - 1].push_back(someResult[temp1]);
			}

			largestCombinationsCount = temp;
		}//end check result

		}//end covering possibilties

	}//general loop


	
	return filterResult;
}//end get Filter Result

#endif