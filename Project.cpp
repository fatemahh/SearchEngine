#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Webpage.h"
#include "Webgraph.h"

using namespace std;

vector<string> SplitString(string a, char sep)
{
	vector<string> result;
	stringstream temp(a);
	string sub;
	while (getline(temp, sub, sep))
	{
		result.push_back(sub);
	}

	return result;
}

// to find if in a string here is more than 1 word
bool MoreWords(const string& str) {
	istringstream iss(str);
	string word;
	int count = 0;

	while (iss >> word) {
		count++;
		if (count > 1) {
			return true;
		}
	}

	return false;
}

void InsertionSortWebpages(vector<Webpage>& web)
{
	vector<Webpage> result;
	Webpage key;
	for (int i = 1; i < web.size(); i++)
	{
		key = web[i];
		int j = i - 1;

		while (j >= 0 && web[j].getScore() < key.getScore())
		{
			web[j + 1] = web[j];
			j = j - 1;
		}
		web[j + 1] = key;
	}
}

void Search(vector<Webpage>& web)
{
	string search;
	cout << "What are you searching? " << endl;
	cin.ignore(); // ignore any remaining input in the stream
	getline(cin, search);
	vector<string> usersearch;
	usersearch = SplitString(search, ' ');

	bool operation = 0; // 0 is OR, 1 is AND
	string current = "";
	bool found = false;
	for (int i = 0; i < usersearch.size(); i++) {
		for (auto character : usersearch[i])
		{
			if ((character == '\'' || character == '\"') && found == false) // first "
			{
				found = true;
				continue;
			}
			else if ((character == '\'' || character == '\"') && found == true) // ending "
			{
				// remove quotes
				current.erase(remove(current.begin(), current.end(), '\"'), current.end());
				current.erase(remove(current.begin(), current.end(), '\''), current.end());
				usersearch.push_back(current);
				current = ""; // reput string to empty
				found = false;
			}
			else { // keep adding the character until reaching end of quotation
				current = current + character;
			}
		}
		current = current + " ";
	}
	// remove words with quotation marks, since already added the complete words to the vector
	for (int i = usersearch.size() - 1; i >= 0; i--)
	{
		current = usersearch[i];
		if (current[0] == '\'' || current[0] == '\"') // first character
		{
			usersearch.erase(usersearch.begin() + i); // so we don't take it into account
		}
		if (current[current.size() - 1] == '\'' || current[current.size() - 1] == '\"')  // last character
		{
			usersearch.erase(usersearch.begin() + i); // so we don't take it into account
		}
	}
	
	for (int i = 0; i < usersearch.size(); i++)
	{
		current = usersearch[i];
		if (current == "AND" || current == "and")
		{
			operation = 1;
			usersearch.erase(usersearch.begin() + i); // so we don't take it into account
			break;
		}

		// for OR
		if (current == "OR" || current == "or")
		{
			operation = 0;
			usersearch.erase(usersearch.begin() + i); // so we don't take it into account
			break;
		}
		
	}

	int count = 0 ; // used to add +1 each time a word is found in keywords
	vector <Webpage> result;

	for (int i = 0; i < web.size(); i++)
	{
		count = 0;
		vector<string> searchwords = web[i].getKeywords();
		for (int  j= 0; j < usersearch.size(); j++)
		{
			for (int k = 0; k < searchwords.size(); k++)
			{
				if (usersearch[j] == searchwords[k])
					count++;
			}
		}

		if (operation == 1) { // for and
			if (count == usersearch.size())
				result.push_back(web[i]);
		}

		if (operation == 0) { // for or
			if (count != 0)
				result.push_back(web[i]);
		}

	}

	for (int i = 0; i < result.size(); i++)
	{
		for (int j = 0; j < web.size(); j++) {
			if (result[i].getID() == web[j].getID())
				web[j].IncrementImpressions();
		}

	}

	if (result.size() == 0) {
		cout << "No webpages match the keywords. \n";
		return;
	}

	else
	{
		cout << "Here are the corresponding results. \n";
		for (int i = 0; i < result.size(); i++)
		{
			cout << i + 1 << ". " << result[i].getURL() << endl;
		}
		int a;
		cout << "Which website would you like to visit? \n";
		cin >> a;

		if (a < 1 || a > result.size()) {
			cout << "Error. The number does not exist. \n";
			return;
		}


		for (int j = 0; j < web.size(); j++) {
			if (result[a - 1].getID() == web[j].getID()) {
				web[j].IncrementClicks();
				cout << "Here is the URL for the website: " << web[j].getURL() << endl;;
			}
		}

		return;
	}

}

int main()
{
	vector<Webpage> Webpages;
	

	// INPUT KEYWORDS
	ifstream keywordcsv;
	string input1, input2, input3, input4;
	cout << "Input Keywords file name." << endl;
	cin >> input1;

	keywordcsv.open(input1);
	if (!keywordcsv.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}
	string line, url;
	vector<string> filekeywords;

	while (getline(keywordcsv, line) )
	{
		if (line.empty())
			continue;
		else {
			filekeywords = SplitString(line, ',');
			for (int i = 0; i < filekeywords.size(); i++) // remove tabs and space from each keyword string
			{
				if (!MoreWords(filekeywords[i])) { // to find if in the string there is more than 1 word
					filekeywords[i].erase(remove(filekeywords[i].begin(), filekeywords[i].end(), ' '), filekeywords[i].end());
					filekeywords[i].erase(remove(filekeywords[i].begin(), filekeywords[i].end(), '	'), filekeywords[i].end());
				}
			}
			url = filekeywords[0];
			filekeywords.erase(filekeywords.begin()); // we don't need the url in the keywords
			if (url.empty()) // if no url skip
				continue;
			Webpage temp;
			temp.setURL(url);
			temp.setKeywords(filekeywords);
			Webpages.push_back(temp); // add to our vector
		}


	}



	// INPUT IMPRESSIONS
	ifstream impressionscsv;
	cout << "Input Impressions file name." << endl;
	cin >> input2;
	impressionscsv.open(input2);
	if (!impressionscsv.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}

	string line2, url2;
	vector<string> fileimpressions;

	while (getline(impressionscsv, line2))
	{
		fileimpressions = SplitString(line2, ',');
		url2 = fileimpressions[0];
		for (int i = 0; i < Webpages.size(); i++) {
			if (Webpages[i].getURL() == url2)
				Webpages[i].setImpressions(stoi(fileimpressions[1]));
		}
	}

	// INPUT CLICKS
	ifstream clickscsv;
	cout << "Input Clicks file name." << endl;
	cin >> input3;
	clickscsv.open(input3);
	if (!clickscsv.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}

	string line3, url3;
	vector<string> fileclicks;

	while (getline(clickscsv, line3))
	{
		fileclicks = SplitString(line3, ',');
		url3 = fileclicks[0];
		for (int i = 0; i < Webpages.size(); i++) {
			if (Webpages[i].getURL() == url3)
				Webpages[i].setClicks(stoi(fileclicks[1]));
		}

	}
		
	// set id for each website for use in webgraph
	for (int i = 0; i < Webpages.size(); i++)
		Webpages[i].setID(i);

	// Webgraph
	int x = Webpages.size();
	Webgraph Graph1(x);
	ifstream PageRankcsv;
	cout << "Input Page Rank file name." << endl;
	cin >> input4;
	PageRankcsv.open(input4);
	if (!PageRankcsv.is_open()) {
		cout << "Error opening file" << endl;
		return 0;
	}
	string urlsource, urldest;
	string line4;
	vector<string> filePR;

	while (getline(PageRankcsv, line4))
	{
		filePR = SplitString(line4, ',');
		urlsource = filePR[0];
		urldest = filePR[1];
		int id1 = 0, id2 = 0;

		for (int i = 0; i < Webpages.size(); i++) {
			if (Webpages[i].getURL() == urlsource)
				id1 = Webpages[i].getID();
			if (Webpages[i].getURL() == urldest)
				id2 = Webpages[i].getID();
		}
		Graph1.addEdge(id1, id2);
	}


	// now we have to calculate final score then sort using InsertionSort

	// first we calculate PageRank

	double numpages = Graph1.getN();
	// array for each page rank
	vector<double> pagerank(numpages);
	for (int i = 0; i < pagerank.size(); i++) // calculate initial PageRank
	{
		pagerank[i] = 1.0 / numpages;
	}
	// like in the video, iteration 0 has equal pages ranks for all webpages with 1/number of webpages
	vector<double> finalpagerank(numpages, 1 / numpages);

	vector<vector<double>> ourgraph = Graph1.getGraph();

	vector<int> count(numpages, 0);

	// count is used to know how many edges are outgoing to use in formula
	for (int i = 0; i < numpages; i++) {
		for (int j = 0; j < numpages; j++)
		{
			if (ourgraph[i][j] == 1)
				count[i]++;
		}
	}

	double minloop = 0.001;
	// we repeat multiple iterations
	while (true)
	{
		for (int i = 0; i < numpages; i++)
		{
			finalpagerank[i] = 0;
			for (int j = 0; j < numpages; j++)
			{
				if (ourgraph[j][i] == 1)
					finalpagerank[i] += pagerank[j] / count[j];
			}
		}


		// calculate the difference between new page rank and old page rank to know when to stop iterations
		double diff = 0;
		for (int i = 0; i < numpages; i++) {
			diff += abs(finalpagerank[i] - pagerank[i]);
		}

		// check if the difference is less than our minimum number, if so, break out of the loop
		if (diff < minloop) {
			break;
		}

		// update page rank with new page rank to calculate new iteration
		pagerank = finalpagerank;
	}
	

	// now we get the normalized page rank dividing each page rank by sum of all page ranks
	double sum = 0;

	for (int i = 0; i < numpages; i++) {
		sum += pagerank[i];
	}

	// normalize the page rank values and put it the class Webgraph
	for (int i = 0; i < numpages; i++) {
		if (Webpages[i].getID() == i)
			Webpages[i].setPR(pagerank[i] / sum);
	}

	// fianlly get score
	for (int i = 0; i < Webpages.size(); i++)
	{
		Webpages[i].setScore();
	}

	// now we need to sort the webpages using insertion sort
	InsertionSortWebpages(Webpages);


	string choice;
	while (true)
	{
		cout << "Hello, would you like to: \n";
		cout << "1. Perform a new search \n";
		cout << "2. Exit program \n";
		cout << "Enter your choice \n";
		cin >> choice;

		if (choice == "1")
		{
			Search(Webpages);
		}
		else if (choice == "2")
		{
			cout << "The program will now exit. Goodbye. \n";
			return 0;
		}
		else {
			cout << "Please enter a valid number. \n";
			continue;
		}

		ofstream updateimpression;
		updateimpression.open(input2);
		for (int i = 0; i < Webpages.size(); i++)
		{
			updateimpression << Webpages[i].getURL() << "," << Webpages[i].getImpressions() << endl;
		}

		ofstream updateclick;
		updateclick.open(input3);
		for (int i = 0; i < Webpages.size(); i++)
		{
			updateclick << Webpages[i].getURL() << "," << Webpages[i].getClicks() << endl;
		}
	}

	return 0;
}