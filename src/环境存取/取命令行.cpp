#include <string>
#include <vector>
#ifdef _WIN32
#include<windows.h>
KrnlnApi std::size_t 取命令行A(std::vector<std::string>& saryArgs)
{
	// Initialize the output vector.
	saryArgs = {};
	// Get the command-line arguments.
	const char* conmline = GetCommandLineA();
	if (!conmline)
	{
		return 0;
	}

	// Inline the SkipSpaces function.
	const char* ps = conmline;
	while (*ps != '\0')
	{
		if (!isspace(*ps))
			break;
		ps++;
	}

	// Set psCommand to the value of conmline.
	// This will ensure that the first command-line argument is not skipped.
	const char* psCommand = ps;

	// Skip the program name.
	char ch = ' ';
	if (*psCommand == '\"')
	{
		ch = '\"';
		psCommand++;
	}
	while (*psCommand != ch && *psCommand != '\0')
		psCommand++;

	if (*psCommand != '\0')
		psCommand++;

	// Do not skip the first space.
	// This will ensure that the first command-line argument is not skipped.
	// if (ch != ' ' && *psCommand == ' ')
	//     psCommand++;    // Skip the first space.

	// Extract the command-line arguments.
	while (*psCommand != '\0')
	{
		if (*psCommand == '\"')
		{
			psCommand++;

			const char* ps = psCommand;
			while (*ps != '\0' && *ps != '\"')
				ps++;

			saryArgs.push_back(std::string(psCommand, ps - psCommand));

			psCommand = ps;
			if (*psCommand != '\0')
				psCommand++;
		}
		else if (!isspace(*psCommand))
		{
			const char* ps = psCommand;
			while (*ps != '\0' && !isspace(*ps))
				ps++;

			saryArgs.push_back(std::string(psCommand, ps - psCommand));
			psCommand = ps;
		}
		else
		{
			psCommand++;
		}
	}

	return saryArgs.size();
}
KrnlnApi std::size_t 取命令行W(std::vector<std::wstring>& saryArgs)
{
	// Initialize the output vector.
	saryArgs = {};

	// Get the command-line arguments.
	const wchar_t* conmline = GetCommandLineW();

	//getenv("_")POSIX环境使用??
	if (!conmline)
	{
		return 0;
	}

	// Inline the SkipSpaces function.
	const wchar_t* ps = conmline;
	while (*ps != L'\0')
	{
		if (!iswspace(*ps))
			break;
		ps++;
	}

	// Set psCommand to the value of conmline.
	// This will ensure that the first command-line argument is not skipped.
	const wchar_t* psCommand = ps;

	// Skip the program name.
	wchar_t ch = L' ';
	if (*psCommand == L'\"')
	{
		ch = L'\"';
		psCommand++;
	}
	while (*psCommand != ch && *psCommand != L'\0')
		psCommand++;

	if (*psCommand != L'\0')
		psCommand++;

	// Do not skip the first space.
	// This will ensure that the first command-line argument is not skipped.
	// if (ch != L' ' && *psCommand == L' ')
	//     psCommand++;    // Skip the first space.

	// Extract the command-line arguments.
	while (*psCommand != L'\0')
	{
		if (*psCommand == L'\"')
		{
			psCommand++;

			const wchar_t* ps = psCommand;
			while (*ps != L'\0' && *ps != L'\"')
				ps++;

			saryArgs.push_back(std::wstring(psCommand, ps - psCommand));

			psCommand = ps;
			if (*psCommand != L'\0')
				psCommand++;
		}
		else if (!iswspace(*psCommand))
		{
			const wchar_t* ps = psCommand;
			while (*ps != L'\0' && !iswspace(*ps))
				ps++;

			saryArgs.push_back(std::wstring(psCommand, ps - psCommand));
			psCommand = ps;
		}
		else
		{
			psCommand++;
		}
	}

	return saryArgs.size();
}
KrnlnApi std::vector<std::string> 取命令行A()
{
	std::vector<std::string> saryArgs;
	// Initialize the output vector.
	saryArgs = {};
	// Get the command-line arguments.
	const char* conmline = GetCommandLineA();
	if (!conmline)
	{
		return saryArgs;
	}

	// Inline the SkipSpaces function.
	const char* ps = conmline;
	while (*ps != '\0')
	{
		if (!isspace(*ps))
			break;
		ps++;
	}

	// Set psCommand to the value of conmline.
	// This will ensure that the first command-line argument is not skipped.
	const char* psCommand = ps;

	// Skip the program name.
	char ch = ' ';
	if (*psCommand == '\"')
	{
		ch = '\"';
		psCommand++;
	}
	while (*psCommand != ch && *psCommand != '\0')
		psCommand++;

	if (*psCommand != '\0')
		psCommand++;

	// Do not skip the first space.
	// This will ensure that the first command-line argument is not skipped.
	// if (ch != ' ' && *psCommand == ' ')
	//     psCommand++;    // Skip the first space.

	// Extract the command-line arguments.
	while (*psCommand != '\0')
	{
		if (*psCommand == '\"')
		{
			psCommand++;

			const char* ps = psCommand;
			while (*ps != '\0' && *ps != '\"')
				ps++;

			saryArgs.push_back(std::string(psCommand, ps - psCommand));

			psCommand = ps;
			if (*psCommand != '\0')
				psCommand++;
		}
		else if (!isspace(*psCommand))
		{
			const char* ps = psCommand;
			while (*ps != '\0' && !isspace(*ps))
				ps++;

			saryArgs.push_back(std::string(psCommand, ps - psCommand));
			psCommand = ps;
		}
		else
		{
			psCommand++;
		}
	}

	return saryArgs;
}
KrnlnApi std::vector<std::wstring> 取命令行W()
{
	std::vector<std::wstring> saryArgs;
	// Initialize the output vector.
	saryArgs = {};

	// Get the command-line arguments.
	const wchar_t* conmline = GetCommandLineW();
	if (!conmline)
	{
		return saryArgs;
	}

	// Inline the SkipSpaces function.
	const wchar_t* ps = conmline;
	while (*ps != L'\0')
	{
		if (!iswspace(*ps))
			break;
		ps++;
	}

	// Set psCommand to the value of conmline.
	// This will ensure that the first command-line argument is not skipped.
	const wchar_t* psCommand = ps;

	// Skip the program name.
	wchar_t ch = L' ';
	if (*psCommand == L'\"')
	{
		ch = L'\"';
		psCommand++;
	}
	while (*psCommand != ch && *psCommand != L'\0')
		psCommand++;

	if (*psCommand != L'\0')
		psCommand++;

	// Do not skip the first space.
	// This will ensure that the first command-line argument is not skipped.
	// if (ch != L' ' && *psCommand == L' ')
	//     psCommand++;    // Skip the first space.

	// Extract the command-line arguments.
	while (*psCommand != L'\0')
	{
		if (*psCommand == L'\"')
		{
			psCommand++;

			const wchar_t* ps = psCommand;
			while (*ps != L'\0' && *ps != L'\"')
				ps++;

			saryArgs.push_back(std::wstring(psCommand, ps - psCommand));

			psCommand = ps;
			if (*psCommand != L'\0')
				psCommand++;
		}
		else if (!iswspace(*psCommand))
		{
			const wchar_t* ps = psCommand;
			while (*ps != L'\0' && !iswspace(*ps))
				ps++;

			saryArgs.push_back(std::wstring(psCommand, ps - psCommand));
			psCommand = ps;
		}
		else
		{
			psCommand++;
		}
	}

	return saryArgs;
}
#endif 

