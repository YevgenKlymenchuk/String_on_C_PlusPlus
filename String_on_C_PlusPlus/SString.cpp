#include "stdafx.h"
#include "SString.h"


SString::SString()
	:_buffer(NULL), _length(0)
{
}

SString::SString(int nLength)
	: _buffer(NULL), _length(nLength)
{
	_buffer = DBG_NEW TCHAR[_length + 1];
	ZeroMemory(_buffer, _length * sizeof(TCHAR));
}

SString::SString(LPCTSTR stzBuffer)
	: _buffer(NULL), _length(0)
{
	_length = _tcslen(stzBuffer);
	_buffer = DBG_NEW TCHAR[_length + 1];
	memcpy_s(&_buffer[0], _length * sizeof(TCHAR), stzBuffer, _length * sizeof(TCHAR));
	_buffer[_length] = _T('\0');
}

SString::SString(const SString& copy)
	: _buffer(NULL), _length(0)
{
	_length = copy._length;
	_buffer = DBG_NEW TCHAR[_length + 1];
	memcpy_s(&_buffer[0], _length * sizeof(TCHAR), copy._buffer, _length * sizeof(TCHAR));
	_buffer[_length] = _T('\0');
}

SString::~SString()
{
	if (_buffer != NULL)
		delete[] _buffer, _buffer = NULL;
	_length = 0x00;
}

#pragma region Operators

SString& SString::operator=(const SString& other)
{
	if (this == &other)
		return *this;

	if (_length < other._length)
	{
		_length = other._length;
		if (_buffer != NULL)
			delete[] _buffer, _buffer = NULL;
		_buffer = DBG_NEW TCHAR[_length + 1];
	}
	memcpy_s(&_buffer[0], _length * sizeof(TCHAR), other._buffer, _length * sizeof(TCHAR));
	_buffer[_length] = _T('\0');
	return *this;
}

SString& SString::operator=(LPCTSTR other)
{
	int otherLength = _tcslen(other);
	if (_length < otherLength)
	{
		_length = otherLength;
		if (_buffer != NULL)
			delete[] _buffer, _buffer = NULL;
		_buffer = DBG_NEW TCHAR[_length + 1];
	}
	memcpy_s(&_buffer[0], _length * sizeof(TCHAR), other, _length * sizeof(TCHAR));
	_buffer[_length] = _T('\0');
	return *this;
}

const SString SString::operator+(const SString& other) const
{
	return SString(*this) + other._buffer;
}

const SString SString::operator+(LPCTSTR other) const
{
	return SString(*this).operator+=(SString(other));
}

SString& SString::operator+=(const SString& other)
{
	return operator+=(other._buffer);
}

SString& SString::operator+=(LPCTSTR other)
{
	int newLen = _length + _tcslen(other);
	LPTSTR buff = DBG_NEW TCHAR[newLen + 1];
	memcpy_s(&buff[0], _length * sizeof(TCHAR), &_buffer[0], _length * sizeof(TCHAR));
	memcpy_s(&buff[_length], newLen * sizeof(TCHAR), &other[0], (newLen - _length) * sizeof(TCHAR));
	buff[newLen] = _T('\0');

	if (_buffer != NULL)
		delete[] _buffer, _buffer = NULL;

	_length = newLen;
	_buffer = DBG_NEW TCHAR[_length + 1];
	memcpy_s(&_buffer[0], _length * sizeof(TCHAR), &buff[0], _length * sizeof(TCHAR));
	_buffer[_length] = _T('\0');

	delete[] buff, buff = NULL;
	return *this;
}

TCHAR& SString::operator[](const int index)
{
	if (index >= 0 && index < _length)
		return _buffer[index];
	throw _T("Index out of range.");
}

const SString operator+(LPCTSTR other, const SString& str)
{
	return SString(other) + str;
}

#if UNICODE
std::wostream& operator<<(std::wostream& os, const SString& obj)
#else
std::ostream& operator<<(std::ostream& os, const SString& obj)
#endif
{
	os << obj._buffer;
	return os;
}

#if UNICODE
std::wistream& operator>>(std::wistream& is, SString& obj)
#else
std::istream& operator>>(std::istream& is, SString& obj)
#endif
{
	LPTSTR buff = DBG_NEW TCHAR[0xFFFF];
	ZeroMemory(buff, 0xFFFF * sizeof(TCHAR));
	is >> buff;
	long len = _tcslen(buff);

	if (obj._buffer == NULL || len > obj._length)
	{
		if (obj._buffer != NULL)
			delete[] obj._buffer, obj._buffer = NULL;

		obj._length = len;
		obj._buffer = DBG_NEW TCHAR[obj._length + 1];
	}


	memcpy_s(&obj._buffer[0], obj._length * sizeof(TCHAR), buff, len * sizeof(TCHAR));
	obj._buffer[obj._length] = _T('\0');

	delete[] buff, buff = NULL;
	
	return is;
}

#pragma endregion
