#include <unordered_map>
#include "HelperFunctions.h"

static int IdCounter = 0;
class State
{
private:
	std::unordered_map<char, State> Delta;
	std::unordered_map<char, std::string> Lambda;
	std::string Psi;
	bool IsFinal;
public:
	const int Id;
	State();
	bool operator==(const State& Other) const;
	void AddDeltaTransition(char Letter, State& ToState);
	void AddLambdaTransition(char Letter, std::string Output);
	bool GetIsFinal() const;
	std::string GetPsi() const;
	//Pair of : <Letter , State Id> 
	std::vector<std::pair<char, int>> GetDeltaAsSortedVectorOfPairs() const;
	std::vector<std::pair<char, std::string>> GetLambdaAsSortedVectorOfPairs() const;
};

namespace std
{
	template<>
	struct hash<State>
	{
		std::size_t operator()(const State& HashedState) const
		{
			
			std::size_t HashCode(HashedState.GetIsFinal());
			HashCode += StringToIntHashing(HashedState.GetPsi());
			std::vector<std::pair<char, int>> SortedDeltaAsPairs(HashedState.GetDeltaAsSortedVectorOfPairs());
			std::vector<std::pair<char, std::string>> SortedLambdaPairs(HashedState.GetLambdaAsSortedVectorOfPairs());
			for (int i = 0; i < SortedDeltaAsPairs.size(); ++i)
			{
				HashCode += SortedDeltaAsPairs[i].first + SortedDeltaAsPairs[i].second;
			}
			for (int i = 0; i < SortedLambdaPairs.size(); ++i)
			{
				HashCode += SortedLambdaPairs[i].first + StringToIntHashing(SortedLambdaPairs[i].second);
			}

			return HashCode;
		}
	};
}
