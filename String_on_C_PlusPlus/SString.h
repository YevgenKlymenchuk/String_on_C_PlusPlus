#pragma once
class SString
{
private:
	int _length;
	LPTSTR _buffer;
public:
	int getLegth() const throw() { return _length; }
	LPCTSTR getBuffer() const throw() { return _buffer; }
public:
	SString();
	SString(int nLength);
	SString(LPCTSTR stzBuffer);
	SString(const SString& copy);
	virtual ~SString();
public:
	SString& operator=(const SString& other);
	SString& operator=(LPCTSTR other);

#pragma region Object operators
	const SString operator+(const SString& other) const;
	const SString operator+(LPCTSTR other) const;
	SString& operator+=(const SString& other);
	SString& operator+=(LPCTSTR other);
	TCHAR& operator[](const int index);
#pragma endregion

#pragma region Friends operators
	friend const SString operator+(LPCTSTR other, const SString& str);
#if UNICODE
	friend std::wostream& operator<<(std::wostream& os, const SString& obj);
	friend std::wistream& operator >> (std::wistream& is, SString& obj);
#else
	friend std::ostream& operator<<(std::ostream& os, const SString& obj);
	friend std::istream& operator >> (std::istream& is, SString& obj);
#endif
#pragma endregion
public:
	__declspec(property(get = getLength)) int Length;
	__declspec(property(get = getBuffer)) LPCTSTR Buffer;
public:

};

