#include "Member.h"
Member::Member(wstring id, wstring name, int age, bool gender, bool is_smoker, bool is_drinker) :id(id), name(name), age(age), gender(gender), is_smoker(is_smoker), is_drinker(is_drinker) {

}
wstring Member::GetId()const {
	return id;
}
wstring Member::GetName()const {
	return name;
}
int Member::GetAge()const {
	return age;
}
bool Member::GetGender()const {
	return gender;
}
bool Member::IsSmoker()const {
	return is_smoker;
}
bool Member::IsDrinker()const {
	return is_drinker;
}