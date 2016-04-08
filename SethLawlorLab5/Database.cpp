#include "Database.h"


using namespace std;

Database::Database(){};
Database::~Database(){};

void Database::populateDB(vector<Predicate> my_schemes, vector<Predicate> my_facts,vector<Rule> my_rules, vector<Predicate> my_queries){
	//cout << "########################################\n\n";
	Schemes = my_schemes;
	Facts = my_facts;
	Rules = my_rules;
	Queries = my_queries;
	evalSchemes();
	evalFacts();
	//evalRules();
	evalGraphRules();
	printFacts();
	evalQueries();
	//cout << "\n\n\n\n\n" << debug.str();
};
/*Schemes*/
void Database::evalSchemes(){
	output << "Scheme Evaluation" << "\n" << endl;
	for(auto i: Schemes)
		addScheme(i);
}
void Database::addScheme(Predicate& pred){
	// add an empty Relation to the Database
	Relation temp_relation = Relation(pred.getName());
	// the attribute list from the scheme as the scheme of the relation
	for(auto i: pred.getParameters())
		temp_relation.schemes.push_back(i);
	
	//add relation to relations map
	Relations.insert(pair<string,Relation>(pred.getName(),temp_relation));
}
/*Facts*/
void Database::evalFacts(){
	output << "Fact Evaluation" << "\n" << endl;
	//For each fact in the Datalog program,
	for(auto i: Facts){
		addFact(i);
	}
	for(auto j: Relations){
		output << j.second.Name << endl;
		output << j.second.print() << endl;	
	}
}
void Database::printFacts(){
	for(auto j: Relations){
		output << j.second.Name << endl;
		output << j.second.print() << endl;	
	}
}

void Database::addFact(Predicate& pred){
	// add a Tuple to a Relation
	Tuple temp_tup;
	
	for(unsigned int i = 0; i < pred.getParameters().size(); i++)
		temp_tup.push_back(pred.getParameters()[i]);
	Relations.at(pred.getName()).tuples.insert(temp_tup);
}

void Database::evalGraphRules(){
	cout << "rules";
	Graph my_graph(Rules);
	vector<int> postOrder = my_graph.getPO();
	map<int,set<int>> sccs = my_graph.getSCCs();
	map<int,vector<int>> SCCmap = mapSet2Vector(sccs);
	for(auto i: my_graph.getSCCs()){
		cout << i.first << " ";
		for(auto j: i.second)
			cout << " " << j;
		cout << endl;
	}
	//#########
	output << "Rule Evaluation" << endl;
	output << my_graph.printDepGraph();
	output << my_graph.printRevDepGraph();
	output << my_graph.printPoNum();
	output << my_graph.printSearchOrder();

	//#########
	for(auto index: postOrder){
		if(SCCmap[index].size() > 0){
			output << "\nSCC:";
			for(auto i: SCCmap[index])
			 	output << " R" << i;
			output << endl;
			
			if(SCCmap[index].size() == 1 && !my_graph.dependent(index)){
				evalRule(SCCmap[index][0]);
			}else{
				evalRule(SCCmap[index]);
			}
		}
	}
	output << "\nRule Evaluation Complete\n" << endl;
}



void Database::evalRule(int r){
// this function is called when there is only one SCC and it does not depend on itself
	vector<Relation> intermediate_results;
	vector<Tuple> diff;
	Rule rule = Rules[r];
	output << rule.getRule() << endl; 
	for(auto pred: rule.getValues()){
		//create relation for each on right side;
		//name relation
		string name = pred.getName();
		Relation temp_rel = Relations.at(name);
		//select
		temp_rel.select(pred.getParameters());
		//project
		temp_rel.project(pred.getParameters());
		//rename
		temp_rel.rename(pred.getParameters());
		//push back to list
		intermediate_results.push_back(temp_rel);
	}
	Relation result = intermediate_results[0];

	if(intermediate_results.size() >= 2)
		for(unsigned j = 1; j < intermediate_results.size(); j++)
			result.join(intermediate_results[j]);
	result.reduce(rule.getKey().getParameters());
	diff = Relations.at(rule.getKey().getName()).unionWith(result);
	printDiff(Relations.at(rule.getKey().getName()).schemes, diff);	
}
void Database::evalRule(vector<int> rules){
// when the scc depends on itself or on more than one
	vector<Tuple> diff;
	bool stop = false;
	//vector<Rules> subRules;
	while(!stop){
		stop = true;
		for(auto rule_index: rules){
			output << Rules[rule_index].getRule() << endl; 
			// list of intermediate results
			vector<Relation> intermediate_results;
			for(auto pred: Rules[rule_index].getValues()){
				//create relation for each on right side;
				//name relation
				string name = pred.getName();
				Relation temp_rel = Relations.at(name);
				//select
				temp_rel.select(pred.getParameters());
				//project
				temp_rel.project(pred.getParameters());
				//rename
				temp_rel.rename(pred.getParameters());
				//push back to list
				intermediate_results.push_back(temp_rel);
			}
			Relation result = intermediate_results[0];
			
			if(intermediate_results.size() >= 2)
				for(unsigned j = 1; j < intermediate_results.size(); j++)
					result.join(intermediate_results[j]);
			result.reduce(Rules[rule_index].getKey().getParameters());
			diff = Relations.at(Rules[rule_index].getKey().getName()).unionWith(result);
			if (diff.size() > 0){
				stop = false;
				printDiff(Relations.at(Rules[rule_index].getKey().getName()).schemes, diff);				
			}
			
		}
	}
}


/*Rules*/
void Database::evalRules(){

}

void Database::printDiff(vector<string>& scheme,vector<Tuple>& d){
	for(auto t: d){
		for(unsigned j = 0; j < t.size(); j++){
			if(j < 1)
				output << "  ";
			output << scheme[j] << "=" << t[j];
			if (j < t.size() - 1)
				output << " ";
		}
		output << endl;
	}
}

/*Queries*/
void Database::evalQueries(){
	output << "Query Evaluation" << endl;

	for(auto query: Queries){
		string name = query.getName();
		output << "\n" << query.getPredicate() << "? ";
		
		Relation solution = Relations.at(name);
		//select
		solution.select(query.getParameters());
		
		if(solution.tuples.size() < 1)
			output << "No" << endl;
		else{
			output << "Yes(" << solution.tuples.size() << ")" << endl;
			output << "select" << endl;
			output << solution.print();
			//project//
			solution.project(query.getParameters());
			output << "project" << endl;
			output << solution.print();
			//rename
			solution.rename(query.getParameters());
			output << "rename" << endl;
			output << solution.print();
		}
		
	}
}

map<int,vector<int>> Database::mapSet2Vector(map<int,set<int>> mof){
	map<int,vector<int>> SCCmap;
	for(auto pair: mof){
		vector<int> temp_list;	
		copy(pair.second.begin(), pair.second.end(), std::back_inserter(temp_list));
		SCCmap[pair.first] = temp_list;
	}
	return SCCmap;
}


void Database::print(ofstream& outFile){
	string result_string = output.str();
	outFile << result_string << endl;;
	cout << result_string;
}
