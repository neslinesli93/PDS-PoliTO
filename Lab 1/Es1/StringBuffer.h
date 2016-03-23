#pragma once
#include <stdlib.h>

size_t myStrlen(const char *s);
void myStrncpy(char *dst, const char *src, size_t startingDstPos, size_t startingSrcPos, size_t length);

class StringBuffer {
private:
	char *string;
	size_t length;
	size_t maxSize;
	void myRealloc(size_t threshold, size_t increment);
public:
	StringBuffer();
	StringBuffer(const char *s);
	StringBuffer(const StringBuffer& sb);
	size_t size();
	size_t bufsize();
	void clear();
	void insert(const char *s, size_t pos);
	void insert(const StringBuffer& sb,	size_t pos);
	void append(const char *s);
	void append(const StringBuffer& sb);
	const char *c_str();
	void set(const char *s);
	void set(const StringBuffer& sb);
	~StringBuffer();
};