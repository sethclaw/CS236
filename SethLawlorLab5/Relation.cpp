#include "Relation.h"

using namespace std;

Relation::Relation(string n){
	Name = n;
}
Relation::~Relation(){}

void Relation::select(vector<string> quer_params){
	map<string,vector<int>> paramMap;
	
	vector<Tuple> intersection;
	copy(tuples.begin(), tuples.end(), std::back_inserter(intersection));

	for(unsigned i = 0;i < quer_params.size();i++){
		paramMap[quer_params[i]].push_back(i);
	}
	for (auto pair: paramMap){
		if(isConstant(pair.first)){
			intersection = setIntersect(intersection,select(pair.first,pair.second));
		}
		else if(pair.second.size() > 1){
			intersection = setIntersect(intersection,select(pair.second));
		}
	}
	setTuples(intersection);
}
void Relation::setTuples(vector<Tuple>& tups){
	tuples.clear();
	for(auto tuple: tups){
		if (tuple.size() > 0)
			tuples.insert(tuple);
	}
}
vector<Tuple> Relation::select(vector<int>& variable_indices){
	vector<Tuple> temp_list;
	vector<Tuple> results;
	copy(tuples.begin(), tuples.end(), std::back_inserter(temp_list));
	for(auto tuple: temp_list){
		string value = tuple[variable_indices[0]];
		bool still_meets_req = true;
		for(auto index: variable_indices){
			if (tuple[index] != value)
				still_meets_req = false;
		}
		if (still_meets_req == true)
			results.push_back(tuple); 
	}
	return results;
}
vector<Tuple> Relation::select(string value,vector<int>& indices){
	//use this function to determine if any Tuples have value at all indicated indices
	vector<Tuple> results;
	vector<Tuple> temp_list;
	copy(tuples.begin(), tuples.end(), std::back_inserter(temp_list));
	bool still_meets_req;
	for (auto tuple: temp_list){
		still_meets_req = true;
		for(auto index: indices){
			if (tuple[index] != value)
				still_meets_req = false;
		}
		if (still_meets_req == true)
			results.push_back(tuple);
	}
	return results;
}

void Relation::project(vector<string> quer_params){
	map<string,int> paramMap;
	for(unsigned i = 0;i < quer_params.size();i++)
		paramMap[quer_params[i]] = i;
	for (auto pair: paramMap)
		if(!isConstant(pair.first))
			projectCols.push_back(pair.second);
		
	vector<Tuple> temp_list;
	sort (projectCols.begin(), projectCols.end());
	//project scheme as well
	projectScheme();

	//
	copy(tuples.begin(), tuples.end(), std::back_inserter(temp_list));
	tuples.clear();
	if(projectCols.size() > 0){
		for(Tuple tup: temp_list){
			Tuple temp_tup;
			for(int i: projectCols)
				temp_tup.push_back(tup[i]);
			tuples.insert(temp_tup);
		}
	}
}

void Relation::projectScheme(){
	Scheme new_scheme;
	for(int i: projectCols)
		new_scheme.push_back(schemes[i]);
	schemes = new_scheme;
}


void Relation::reduce(vector<string> quer_params){
	Scheme new_scheme;

	for(auto attrib: quer_params){
		for(int j = 0; j < int(schemes.size()); j++){
			if(attrib == schemes[j]){
				new_scheme.push_back(attrib);
				reduceCols.push_back(j);
			}
		}
	}
	vector<Tuple> temp_list;
	copy(tuples.begin(), tuples.end(), std::back_inserter(temp_list));
	tuples.clear();
	if(reduceCols.size() > 0){
		for(Tuple tup: temp_list){
			Tuple temp_tup;
			for(int i: reduceCols)
				temp_tup.push_back(tup[i]);
			tuples.insert(temp_tup);
		}
	}
	schemes = new_scheme;
}





void Relation::join(Relation import){
	
	joinedSchema(import.schemes);
	vector<Tuple> local_tuples;
	copy(tuples.begin(), tuples.end(), std::back_inserter(local_tuples));
	vector<Tuple> import_tuples;
	copy(import.tuples.begin(), import.tuples.end(), std::back_inserter(import_tuples));

	for(auto local_tup: local_tuples){
		for(auto import_tup: import_tuples){
			vector<int> dups = joinable(local_tup, import_tup);
			
			if(join_pairs.size() == 0){
				Tuple joined_tuple = setJoin(local_tup,import_tup);
				join_tuples.insert(joined_tuple);
			}
			else if(dups.size() > 0){
				Tuple joined_tuple = setJoin(local_tup,import_tup,dups);
				join_tuples.insert(joined_tuple); 
			}
		}
	}
	tuples = join_tuples;
	join_tuples.clear();
	schemes = join_scheme;
	join_scheme.clear();
	join_pairs.clear();
	
}

Tuple Relation::setJoin(Tuple& v1,Tuple& v2){
	Tuple v3;
	for (auto value: v1)
		v3.push_back(value);
	for (unsigned j =0; j < v2.size(); j++)
		v3.push_back(v2[j]);
	return v3;	
}
string Relation::printTup(Tuple t){
	stringstream out;
	int count = 0;
	for(auto i: t){
		count++;
		out << i;
		if(count < int(t.size()))
			out << ",";
	}
	out << "\t";
	return out.str();
}

Tuple Relation::setJoin(Tuple& v1,Tuple& v2, vector<int>& dups){
	Tuple v3;
	for (auto value: v1)
		v3.push_back(value);
	for(int val: uniquecols)
		v3.push_back(v2[val]);
	return v3;
}

void Relation::joinedSchema(Scheme& imported_schemes){
	/*
	snap(S,n,A,P) |X| csg(c,S,G)
	S <0,1>
	n <1>
	A <2>
	P <3>
	c <0>
	G <2>
	new Relation Scheme  <S,n,A,P,c,G>
	return largest vector in size S: <0,1> <- this will be the one to join on.
	*/
	map<string,vector<int>> SchemeMap;
	int schemesize = 0;
	vector<int> joinable_indicies;
	uniquecols.clear();
	for(unsigned a = 0; a < schemes.size(); a++){//poplulate map from local schemes
		SchemeMap[schemes[a]].push_back(a);
		join_scheme.push_back(schemes[a]);
	}

	for(unsigned a = 0; a < imported_schemes.size(); a++){//poplulate map from imported schemes
		schemesize = int(SchemeMap.size());
		SchemeMap[imported_schemes[a]].push_back(a);
		if(schemesize != int(SchemeMap.size())){
			join_scheme.push_back(imported_schemes[a]);
			uniquecols.push_back(a);
		}
	}
	for(auto  pair: SchemeMap){	
		if(pair.second.size() == 2)
			join_pairs.push_back(pair.second); 
	}

}
vector<int> Relation::joinable(Tuple& t1, Tuple& t2){
	vector<int> dups;
	for(auto join_pair: join_pairs)
		if(t1[join_pair[0]] != t2[join_pair[1]]){
			dups.clear();
			return dups;
		}else{
			dups.push_back(join_pair[1]);
		} 

	return dups;
}
vector<Tuple> Relation::unionWith(Relation& importedRelation){
	vector<Tuple> new_tuples;
	int begin_size;
	for(auto tup: importedRelation.tuples){
		begin_size = int(tuples.size());
		tuples.insert(tup);
		if(int(tuples.size()) != begin_size)
			new_tuples.push_back(tup);
	}

	return new_tuples;
};


void Relation::rename(vector<string> quer_params){
	schemes.clear();
	for(int i: projectCols)
		schemes.push_back(quer_params[i]);
}

bool Relation::isConstant(string param){
	//return true if Parameter is constant
	if(string::npos != param.find_first_of("'"))
		return true;
	else return false;
}

vector<Tuple> Relation::setIntersect(vector<Tuple>& v1,vector<Tuple> v2){
	vector<Tuple> v3;
	set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
	return v3;
}



string Relation::print(){
	stringstream out;
	if(tuples.size() == 0) 
		return "";
	for(auto i: tuples){
		for (unsigned j = 0; j < i.size(); j++){
			if(j < 1)
				out << "  ";
			out << schemes[j] << "=" << i[j];
			if (j < i.size() - 1)
				out << " ";
		}
		out << endl;
				
	}
	return out.str();
}