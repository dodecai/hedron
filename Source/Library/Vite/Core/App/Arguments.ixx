export module Vite.App.Arguments;

import std;

export namespace Hedron {

///
/// @brief Container for passed command line arguments
/// @example
///   Arguments arguments({ argv + 1, argv + argc });
///
class Arguments {
    // Types
    using ArgumentList = std::vector<std::string>;
    using ArgumentMap = std::unordered_map<std::string, std::string>;

public:
    // Default
    Arguments() = default;
    Arguments(const ArgumentList& arguments) : mArgumentList(arguments) {
        MapArguments();
    }

    // Accessors
    bool Contains(const std::string& argument) const {
		return mArgumentMap.find(argument) != mArgumentMap.end();
	}

    // Operators
    std::string operator[](const std::string& argument) const {
        auto it = mArgumentMap.find(argument);
        if (it != mArgumentMap.end()) return it->second;
        return "";
	}

private:
    // Methods
    void MapArguments() {
        for (size_t i = 0; i < mArgumentList.size(); i++) {
			const auto &argument = mArgumentList[i];
            if (argument.starts_with("-") || argument.starts_with("/")) {
                if (i + 1 < mArgumentList.size()) {
					const auto &value = mArgumentList[i + 1];
                    if (!value.starts_with("-") && !value.starts_with("/")) {
						mArgumentMap[argument] = value;
						i++;
                    } else {
						mArgumentMap[argument] = "";
					}
                } else {
					mArgumentMap[argument] = "";
				}
            } else {
				mArgumentMap[argument] = "";
			}
		}
	}

private:
    // Properties
    ArgumentList mArgumentList = {};
    ArgumentMap mArgumentMap = {};
};

}
