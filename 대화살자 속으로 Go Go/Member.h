#include<string>
using namespace std;
class Member {
	wstring id;
	wstring name;
	int age;
	bool gender;
	bool is_smoker;
	bool is_drinker;
public:
	Member(wstring id, wstring name, int age, bool gender = true, bool is_smoker = true, bool is_drinker = true);
	wstring GetId()const;
	wstring GetName()const;
	int GetAge()const;
	bool GetGender()const;
	bool IsSmoker()const;
	bool IsDrinker()const;

};