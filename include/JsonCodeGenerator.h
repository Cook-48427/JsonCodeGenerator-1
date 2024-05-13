
#pragma once

#include "json_fwd.hpp"
#include <fstream>

class Generator {
public:

	void Generate(std::istream& definitionfile, std::fstream& codefile);

private:

	void ClassBuilder(nlohmann::json doc, std::fstream& codefile, int indent);
	void EnumBuilder(nlohmann::json doc, std::fstream& codefile, int indent);

};