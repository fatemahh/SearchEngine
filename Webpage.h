#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Webpage
{
private:
	int id;
	string URL;
	double clicks;
	double impressions;
	double CTR;
	double PR;
	double score;
	vector <string> keywords;

public:


	Webpage();
	Webpage(string URLexample, double impressionsexample, vector <string> keywordsexample);
	void setID(int ids);
	void setURL(string urls);
	void setClicks(double clickss);
	void setImpressions(double impressions);
	void setCTR();
	void setPR(double prs);
	void setScore();
	void setKeywords(vector<string>& keywordss);

	string getURL();
	int getID();
	double getClicks();
	double getImpressions();
	double getCTR();
	double getPR();
	double getScore();
	vector <string> getKeywords();

	void IncrementImpressions();
	void IncrementClicks();


};