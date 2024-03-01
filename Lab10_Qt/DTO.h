#pragma once

#include <iostream>

using std::string;

class DTO {
private:
	string tip;
	int count;

public:
	DTO() = default;

	DTO(string tip, int count) : tip{ tip }, count{ count } {};

	string get_tip() const;

	int get_count();

	void set_tip(string new_tip);

	void set_count(int new_count);

	~DTO() = default;

};