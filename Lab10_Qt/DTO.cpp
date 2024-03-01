#include "DTO.h"
#include <iostream>


string DTO::get_tip() const {
	return this->tip;
}

int DTO::get_count() {
	return this->count;
}

void DTO::set_count(int new_count) {
	this->count = new_count;
}

void DTO::set_tip(string new_tip) {
	this->tip = new_tip;
}