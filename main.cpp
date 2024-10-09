#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;


//Generate the fixtures for the teams in the league
void generateFixture(const vector<Team>& teams, vector<Match>& fixtures) {
    int weekend = 1;
    vector<Match>rivalry;
    size_t numTeams=teams.size();
    for (size_t a = 0; a < teams.size(); ++a) {
        for (size_t b = a + 1; b < teams.size(); ++b) {
            //First normal fixtures are to be generated
            if(teams[a].town !=teams[b].town){
                // First leg
                fixtures.push_back({teams[a].name, teams[b].name, teams[a].town, teams[a].stadium, 1, weekend});
                fixtures.push_back({teams[b].name, teams[a].name, teams[b].town, teams[b].stadium, 2, weekend});
                weekend++;
            }
            //Then the derbies/local rivalries take place
            else {
                rivalry.push_back({teams[a].name, teams[b].name, teams[a].town, teams[a].stadium, 1,weekend});
                rivalry.push_back({teams[b].name, teams[a].name, teams[b].town, teams[b].stadium, 2,weekend});
                }
            }
        }
        for(auto& rivals:rivalry) {
            rivals.weekend=weekend++;
            fixtures.push_back(rivals);
        }
   // To display the fixtures after being generated which is then saved to the fixtures file
void displayFixtures(const vector<Match>& fixtures, const string& outputFilename) {
    ofstream outfile(outputFilename);
    if (!outfile.is_open()) {
        cout << "File not found" << endl;
        return;
    }
    for (const auto& fixture : fixtures) {
        string output="| Weekend: " +to_string(fixture.weekend)+ " | Match: " +fixture.homeTeam + " vs " + fixture.awayTeam+ " at " + fixture.stadium + ", " + fixture.localTown+" (Leg " +to_string (fixture.leg) +")\n";
        cout<<output;
        outfile<<output;
    }

    cout<<"The fixtures have been stored in "<<outputFilename<<endl;

}
    //To prevent invalid matchups where only one team is available
    if(numTeams%2 !=0) {
        fixtures.push_back({"N/A",teams.back().name,"N/A","N/A",0,weekend});
    }
}
int main{
    string filename = "main.csv";

    // Read teams from the CSV file
    vector<Team> teams = readCSV(filename);

    // Display teams (This is for clarification to see if the matches have been set appropiately)
    for (const auto& team : teams) {
        cout << "Team: " << team.name << ", Town: " << team.town<<", Stadium: " << team.stadium << endl;
    }
// Generating fixtures then displaying it to the user
    vector<Match>fixtures;
    generateFixture(teams, fixtures);
    displayFixtures(fixtures);

    return 0;
