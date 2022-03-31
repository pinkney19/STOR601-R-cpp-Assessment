#include <Rcpp.h>
#include <unordered_map>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace Rcpp;


//conversion from Rcpp dataframe to unordered_map
std::unordered_map<std::string, std::vector<std::string>> convert_list_to_map(DataFrame input)
{
  // create empty unordered map for output
  std::unordered_map <std::string, std::vector<std::string>>  output;
  //get keys from named list 
  CharacterVector keys = input.names();
  //populate unordered map with entries from list of vectors
  for (int i=0; i<keys.size(); i++)
  {
    std::string key = as<std::string> (keys[i]);
    
    std::vector <std::string> values = input[key];
    
    output[key] = values;
  }
  return output;
}

// [[Rcpp::plugins(cpp17)]]
// [[Rcpp::export]]
CharacterVector fundamental_algorithm(DataFrame p1_init, DataFrame p2_init)
{
  
  //convert from R dataframe to unordered map
  auto p1 = convert_list_to_map(p1_init);
  auto p2 = convert_list_to_map(p2_init);
  
  //set-up list of males and females 
  std::vector<std::string> men = p2.begin()->second;
  std::vector<std::string> women = p1.begin()->second;
  
  // all women temporariliy engaged to the undesirable man
  //hence initial matchings are:
  std::unordered_map<std::string, std::string> m;
  
  for (const auto& i:women)
  {
    m[i] = "omega";
  }
  
  int k = 0;
  int n = p2.size();
  
  //add omega to end of list of preferences for each woman
  for (auto i : p2){
    p2.at(i.first).push_back("omega");
  }
  
  
  //while not all men have matches
  while (k<n){
    std::string X = men[k];
    while (X!="omega"){
      // X's list of preferences
      std::vector<std::string> preference_list = p1[X];
      
      //get best choice
      std::string x = preference_list[0];
      
      //currnet partner (fiance) of women x is:
      std::string h = m[x];
      
      //find index of current partner
      auto i = std::find(p2[x].begin(), p2[x].end(), h);
      int current_index = std::distance(p2[x].begin(),i);
      
      //find index of new potential partner
      i = std::find(p2[x].begin(), p2[x].end(), X);
      int potential_index = std::distance(p2[x].begin(),i);
      
      //if women prefers new man then engage them
      if (potential_index < current_index)
      {
        m[x]=X;
        // X becomes preceeding fiance of x
        X = h;
      }
      
      if (X != "omega")
      {
        //withdraw x from X's list
        p1[X].erase(p1[X].begin());
      }
    }
    k = k+1;
  }
  return wrap(m); //need to wrap so it spits it out in a format R likes
}


