#pragma once
#include <iostream>
#include <vector>
#include "Webpage.h"
using namespace std;

Webpage::Webpage()
{
    id = -1;
	URL = "";
	clicks = 0;
	impressions = 0;
	CTR = (clicks / impressions) * 100;
    PR = 0;
	score = 0;
}

Webpage::Webpage(string URLexample, double impressionsexample, vector <string> keywordsexample)
{
    id = -1;
	URL = URLexample;
	clicks = 0; // initially
	impressions = impressionsexample;
	CTR = (clicks / impressions) * 100;
    PR = 0; // initially
	score = 0; // initially
	keywords = keywordsexample;
}

// Setters

void Webpage::setID(int ids) {
    id = ids;
}

void Webpage::setURL(string urls) {
    URL = urls;
}

void Webpage::setClicks(double clickss) {
    clicks = clickss;
    CTR = (clicks / impressions) * 100; //update CTR
}

void Webpage::setImpressions(double impressionss) {
    impressions = impressionss;
    CTR = (clicks / impressions) * 100;//update CTR
}

void Webpage::setCTR() {
    CTR = (clicks / impressions) * 100; //update CTR
}

void Webpage::setPR(double prs) {
    PR = prs;
}

void Webpage::setScore() {
    score = 0.4 * PR + ((1 - (0.1 * impressions) / (1 + 0.1 * impressions)) * PR + (0.1 * impressions) / (1 + 0.1 * impressions) * CTR) * 0.6;
    // formula to calculate score
}

void Webpage::setKeywords(vector<string>& keywordss) {
    keywords.resize(keywordss.size());
    for (int i = 0; i < keywordss.size(); i++)
    {
        keywords[i] = keywordss[i];
    }
}

// Getters

int Webpage::getID() {
    return id;
}

string Webpage::getURL() {
    return URL;
}

double Webpage::getClicks() {
    return clicks;
}

double Webpage::getImpressions() {
    return impressions;
}

double Webpage::getCTR() {
    return CTR;
}

double Webpage::getPR() {
    return PR;
}

double Webpage::getScore() {
    return score;
}

vector<string> Webpage::getKeywords() {
    return keywords;
}


void Webpage::IncrementImpressions()
{   //used during search
    impressions += 1;
    CTR = (clicks / impressions) * 100; //update CTR
}
void Webpage::IncrementClicks()
{   //used during search
    clicks += 1;
    CTR = (clicks / impressions) * 100; //update CTR
}




