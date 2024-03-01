#pragma once
#include "Locatar.h"
#include "repo.h"
#include <vector>
#include <functional>

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	AbstractRepo& rep;

public:
	UndoAdauga(AbstractRepo& rep) : rep{ rep } {}
	void doUndo() override {
		rep.remove_repo(rep.get_all_locatari().size() - 1);
	}
};

class UndoSterge : public ActiuneUndo {
	Locatar l;
	int poz;
	AbstractRepo& rep;

public:
	UndoSterge(const Locatar l, const int poz, AbstractRepo& rep) : l{ l }, poz{ poz }, rep{ rep } {}
	void doUndo() override {
		//rep.store(l);
		rep.insert_repo(poz, l);
	}
};

class UndoModifica : public ActiuneUndo {
	Locatar l;
	int poz;
	AbstractRepo& rep;

public:
	UndoModifica(const Locatar l, const int poz, AbstractRepo& rep) : l{ l }, poz{ poz }, rep{ rep } {}
	void doUndo() override {
		rep.modify(poz, l);
	}
};
