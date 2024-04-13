#pragma once
#include <string>

class IDatabase {
public:
	virtual bool open() = 0;
	virtual bool close() = 0;
	virtual int doesUserExist(const std::string& val) const = 0;
	virtual int doesPasswordMatch(const std::string& comparedValue, const std::string valueToComare) const = 0;
	virtual int addNewUser(const std::string& password, const std::string& userName, const std::string& mail);
};