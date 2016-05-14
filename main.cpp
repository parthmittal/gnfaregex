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

int main()
{
}

gnfa::gnfa(int N)
{
	num_states = N;
	rel.resize(N);
	for (int i = 0; i < N; ++i)
		rel[i].resize(N);
}

int gnfa::num_pairs(int state)
{
	int leaving = 0, entering = 0;
	for (int i = 0; i < num_states; ++i)
		if (i != state) {
			entering += rel[i][state].size();
			leaving += rel[state][i].size();
		}
	return entering * leaving;
}

std::string gnfa::cycling_local(int state)
{
	if (rel[state][state].empty())
		return "";

	std::string reg = "(";
	for (auto &r : rel[state][state]) {
		if (reg != "")
			reg += 'U';
		reg += r;
	}
	reg += ")*";
	return reg;
}

void gnfa::add_regex(int u, int v, std::string reg)
{
	assert(u >= 0 && u < num_states);
	assert(v >= 0 && v < num_states);
	rel[u][v].insert(reg);
}

std::string gnfa::regex()
{
	std::vector<int> rem(num_states, 0);
	for (int i = 1; i <= num_states - 2; ++i) {
		int min_num_pairs = -1, index = -1;
		for (int j = 1; j < num_states - 1; ++j) {
			int curr_num_pairs;
			if (!rem[j]
					&& (min_num_pairs == -1 || (curr_num_pairs = num_pairs(j)) < min_num_pairs))
				index = j, min_num_pairs = curr_num_pairs;
		}
		assert(index != -1);
		std::string middle = cycling_local(index);
		for (int i = 0; i < num_states; ++i)
			if (i != index && !rem[i])
				for (int j = 0; j < num_states; ++j)
					if (j != index && ! rem[j])
						for (auto &pre : rel[i][index])
							for (auto &suff : rel[index][i])
								rel[i][j].insert(pre + middle + suff);
	}

	std::string reg = "";
	for (auto &r : rel[0][num_states - 1]) {
		if (reg != "")
			reg += 'U';
		reg += r;
	}
	return reg;
}
