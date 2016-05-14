#ifndef GNFA_H
#define GNFA_H

#include <iostream>
#include <set>
#include <vector>
#include <cassert>

class gnfa
{
	private:
		int num_states;
		std::vector< std::vector< std::set<std::string> > > rel;
		int num_pairs(int state);
		std::string cycling_local(int state);
	public:
		gnfa(int N);
		std::string regex();
		void add_regex(int u, int v, std::string reg);
};

#endif
