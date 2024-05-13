
#include "JsonCodeGenerator.h"
#include "json.hpp"

#define TAB "    "
#define INDENTATION(out, count) for (int i = 0; i < count; i++) {out << TAB;}

using namespace nlohmann;

void Generator::Generate(std::istream& definitionfile, std::fstream& codefile) {
	nlohmann::json document = json::parse(definitionfile);

	for (auto& obj : document.items()) {
		std::string key = obj.value().begin().key();
		if (key == "Class") {
			ClassBuilder(obj.value().begin().value(), codefile, 0);
		}
		else if(key == "Enum") {
			EnumBuilder(obj.value().begin().value(), codefile, 0);
		}
	}

}

void Generator::ClassBuilder(nlohmann::json doc, std::fstream& codefile, int indent) {
	json obname = doc.at("name");
	std::string name = obname.template get<std::string>();

	INDENTATION(codefile, indent)
	codefile << "class " << name << " {" << std::endl;

	json vars = doc.at("vars");
	for (auto& var : vars.items()) {
		std::string key = var.value().begin().key();
		if (key == "Class") {
			ClassBuilder(var.value().begin().value(), codefile, indent + 1);
		}
		else if (key == "Enum") {

		}
		else {
			std::string vartype = var.value().begin().value().at("name").template get<std::string>();

			INDENTATION(codefile, indent)
			codefile << "    " << vartype << " " << key << ";" << std::endl;
		}
	}

	INDENTATION(codefile, indent)
	codefile << "};" << std::endl;

}

void Generator::EnumBuilder(nlohmann::json doc, std::fstream& codefile, int indent) {
	json obname = doc.at("name");
	std::string name = obname.template get<std::string>();

	INDENTATION(codefile, indent)
	codefile << "enum class " << name << " unsigned char {" << std::endl;

	json vars = doc.at("vars");
	for (auto& val : vars.items()) {
		std::string key = val.value().begin().key();
		std::string value = val.value().begin().value();

		INDENTATION(codefile, indent)
		codefile << "    " << key << " = " << value << ";" << std::endl;
	}

	INDENTATION(codefile, indent)
	codefile << "};" << std::endl;

	INDENTATION(codefile, indent)
	codefile << "std::ostream& operator<<(std::ostream& out, " << name << "& value){" << std::endl;

	INDENTATION(codefile, indent + 1)
	codefile << "out";
	for (auto& val : vars.items()) {
		std::string key = val.value().begin().key();
		codefile << " << \"\\\"" << key << "\\\":\" << " << key;
	}
	codefile << ";" << std::endl;

	INDENTATION(codefile, indent)
	codefile << "};" << std::endl;
}
