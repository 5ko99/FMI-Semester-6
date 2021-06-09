#pragma once
#include "command.h"
#include "editor.h"
#include <string>

class processor
{
public:
	processor(const string& path);

	bool is_valid(command& cmd) const;
	void execute(command& cmd);

	inline void setPath(const string& path) { m_filePath = path; };

private:
	editor m_editor;
	string m_filePath;
};

