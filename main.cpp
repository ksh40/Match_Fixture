#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Structure for the teams info
struct Team {
    string name;
    string town;
    string stadium;
    Team(const string& name, const string& town,const string& stadium): name(name), town(town), stadium(stadium) {}
};

// Structure for the match info
struct Match {
    string homeTeam;
    string awayTeam;
    string localTown;
    string stadium;
    int leg;
    int weekend;
};

// To enable it to access and view the teams info
vector<Team> readCSV(const string& filename) {
    vector<Team> teams;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return teams;
    }

    string line;
    getline(file, line);  // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        string name, town, stadium;

        getline(ss, name, ',');
        getline(ss, town, ',');
        getline(ss, stadium, ',');
        if(name.empty()||town.empty()||stadium.empty()) {
            cout<<"Unavailable info"<<line<<endl;
            continue;
        }
        teams.push_back({name, town, stadium});
    }

    file.close();
    return teams;
}
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
    //To prevent invalid matchups where only one team is available
    if(numTeams%2 !=0) {
        fixtures.push_back({"N/A",teams.back().name,"N/A","N/A",0,weekend});
    }
}

// To display the fixtures after being generated
void displayFixtures(const vector<Match>& fixtures) {
    for (const auto& fixture : fixtures) {
        cout << "| Weekend: " << fixture.weekend<<" | Match: " << fixture.homeTeam << " vs " << fixture.awayTeam<<" at " << fixture.stadium << ", " << fixture.localTown<<" (Leg " << fixture.leg << ")" << endl;
    }
}
//Output of the teams info then the matches
int main() {
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
}