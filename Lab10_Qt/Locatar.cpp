#include "Locatar.h"
#include <assert.h>

bool cmp_nume(const Locatar& l1, const Locatar& l2) noexcept {
	return l1.get_nume() < l2.get_nume();
}

bool cmp_suprafata(const Locatar& l1, const Locatar& l2) noexcept {
	return l1.get_suprafata() < l2.get_suprafata();
}

bool cmp_tip_suprafata(const Locatar& l1, const Locatar& l2) noexcept {
	if (l1.get_tip() == l2.get_tip()) {
		return l1.get_suprafata() < l2.get_suprafata();
	}
	else
		return l1.get_tip() < l2.get_tip();
}

void test_create_locatar()
{
	Locatar l{ 1, "Pop Ion", 123, "garsoniera" };

	assert(l.get_ap() == 1);
	assert(l.get_nume() == "Pop Ion");
	assert(l.get_suprafata() == 123);
	assert(l.get_tip() == "garsoniera");
}
