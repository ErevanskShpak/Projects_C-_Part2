#pragma once
#include "AccArray.h"
#include "StudArray.h"
#include "Sign.h"

class Menu {
	static void menuAdminAcc(AccArray&);
	static void menuAdminData(StudArray&);
	static void menuSort(StudArray&);
	static void menuSearch(StudArray&);

public:
	static void menuAdmin(AccArray&, StudArray&);
	static void menuUser(StudArray&);
};

