
#include "Graph.h"



Graph::Graph(){

}
Graph::~Graph(){}

Graph::Graph(vector<Rule> & r){
	Rules = r;
	buildGraphs();
	dfsForest();
	makeSCC();
}


void Graph::buildGraphs(){
	for(unsigned i = 0; i < Rules.size(); i++){
		for(auto pred: Rules[i].getValues()){
			for(unsigned j = 0; j < Rules.size(); j++){
				if(pred.getName() == Rules[j].getKey().getName()){
					depGraph[i].insertNode(j);
					revDepGraph[j].insertNode(i);
				}
			}
		}
	}
	confirmNodes();
}
void Graph::confirmNodes(){
	//ensure a pair was created for each Rule
	for(unsigned i = 0; i < Rules.size(); i++){
		if(depGraph.find(i) == depGraph.end())
			depGraph[i] = Node();
		if(revDepGraph.find(i) == revDepGraph.end())
			revDepGraph[i] = Node();
	}
}

void Graph::dfs(int key){
	Node& node = revDepGraph[key];
	node.markVisit();
	for(auto index: node.getNodes())
		if(!revDepGraph[index].getVisited())
			dfs(index);
	node.setPoNum(poNum);
	poNum++;
}

void Graph::dfsForest(){
	for(auto pair: revDepGraph)
		if(!pair.second.getVisited())//if not visited
			dfs(pair.first);
	getPostOrder();
}


void Graph::getPostOrder(){
	for(auto pair: revDepGraph)
		postOrder[revDepGraph.size() - pair.second.getPoNum()] = pair.first;
}

void Graph::makeSCC(){
	
	for(auto pair: postOrder){
		int rule_num = static_cast<int>(pair.second);
		postOrderVector.push_back(rule_num);
		set<int> sccomponent;
		if(!depGraph[rule_num].getVisited())
			sccDFS(rule_num,sccomponent);
		SCCs.insert(std::pair<int,std::set<int>>(rule_num, sccomponent));
	} 
}
map<int,set<int>> Graph::getSCCs(){
	return SCCs;
}

void Graph::sccDFS(int key,set<int>& sccomponent){
	Node& node = depGraph[key];
	node.markVisit();
	for(auto index: node.getNodes())
		if(!depGraph[index].getVisited())
			sccDFS(index, sccomponent);
	sccomponent.insert(key);
}

vector<int> Graph::getPO(){
	return postOrderVector;
}

bool Graph::dependent(int rule_index){
	vector<int> rule_to_check = depGraph[rule_index].getNodes();
	bool dep = false;
	for(auto i: rule_to_check)
		if(i == rule_index){
			dep = true;
			break;
		}
	return dep;
}


string Graph::printDepGraph(){
	stringstream out;
	out << "\nDependency Graph" << endl;
	for(auto pair: depGraph)
		out << "  R" << pair.first << ":" << pair.second.printNode() << endl;
	return out.str();
}

string Graph::printRevDepGraph(){
	stringstream out;
	out << "\nReverse Graph" << endl;
	for(auto pair: revDepGraph)
		out << "  R" << pair.first << ":" << pair.second.printNode() << endl;
	return out.str();
}

string Graph::printPoNum(){
	stringstream out;
	out << "\nPostorder Numbers" << endl;
	for(auto pair: revDepGraph)
		out << "  R" << pair.first << ": " << pair.second.getPoNum() << endl;
	return out.str();
}

string Graph::printSearchOrder(){
	stringstream out;
	out << "\nSCC Search Order" << endl;
	for(auto i: postOrderVector)
		out << "  R" << i << endl;
	return out.str();
}
