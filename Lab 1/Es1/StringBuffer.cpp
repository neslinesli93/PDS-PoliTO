#include <stdlib.h>
#include <stdio.h>
#include "StringBuffer.h"

#define REASONABLE_BUFFER_SIZE 255

// Implementation of a basic strlen
size_t myStrlen(const char *s) {
	size_t i;
	for (i = 0; s[i] != '\0'; i++);

	return i;
}

// Implementation of a strncpy.
// It copies 'length' characters from string 'src' into 'dst',
// with the specified dst/src indexes.
void myStrncpy(char *dst, const char *src, size_t startingDstPos, size_t startingSrcPos, size_t length) {
	size_t i;

	for (i = startingDstPos; i < length; i++) {
		dst[startingSrcPos + i] = src[i];
	}
	dst[startingSrcPos + i] = '\0';
}

///////////////////////
// PRIVATE FUNCTIONS //
///////////////////////

// Utility function that, given a threshold, reallocs until
// this->maxSize is greater than the threshold
void StringBuffer::myRealloc(size_t threshold, size_t increment) {
	size_t newMaxLength;

	while (this->maxSize < (threshold)) {
		newMaxLength = this->maxSize + increment;

		this->string = (char *) realloc(this->string, newMaxLength);
		this->maxSize = newMaxLength;
	}
}

///////////////////////
// PUBLIC FUNCTIONS //
///////////////////////

// Build an object with a reasonable buffer size, and 0 used characters
StringBuffer::StringBuffer() {
	this->maxSize = REASONABLE_BUFFER_SIZE;
	this->length = 0;
	this->string = (char *) malloc(sizeof(char) * REASONABLE_BUFFER_SIZE);
};

// Build an object big enough to hold all the characters of the string s
// included \0. It should also remember the correct number of used chars.
StringBuffer::StringBuffer(const char *s) {
	size_t length = myStrlen(s);

	this->string = (char *) malloc(sizeof(char) * (length + 1));
	this->length = length;
	this->maxSize = length;

	myStrncpy(this->string, s, 0, 0, length);
}

// Build an object big enough to hold all the characters inside the object
// sb and initialize it with a copy of its characters
StringBuffer::StringBuffer(const StringBuffer& sb) {
	this->string = (char *) malloc(sizeof(char) * sb.maxSize);
	this->length = sb.length;
	this->maxSize = sb.maxSize;

	myStrncpy(this->string, sb.string, 0, 0, length);
}

// Return the number of characters used by the string inside the buffer
size_t StringBuffer::size() {
	return this->length;
}

// Return the total size of the buffer
size_t StringBuffer::bufsize() {
	return this->maxSize;
}

// Reset the number of used characters to 0
void StringBuffer::clear() {
	// I am not zero-ing the characters from 0 to this->length
	this->length = 0;
}

// Insert the string 's' inside the buffer at index 'pos'
// N.B: We are inserting, not replacing.
void StringBuffer::insert(const char *s, size_t pos) {
	size_t i;
	size_t length = myStrlen(s);
	char *stringBackup;

	// If we need to do padding with spaces, it's like
	// an append with a bunch of spaces.
	// Otherwise, we need to save the string after pos,
	// insert the new one, and copy the old one back.
	if (pos > this->size()) {
		// Considering only pos+length for the realloc threshold,
		// since pos is already an index and is > than this->size()
		this->myRealloc(pos + length + 1, REASONABLE_BUFFER_SIZE);

		// Add spaces
		for (i = this->size(); i < pos; i++) {
			(this->string)[i] = ' ';
		}

		// Copy the new string
		myStrncpy(this->string, s, 0, pos, length);

		// Increment the length by padding + length of string
		this->length += (pos - this->size()) + length;
	} else {
		// Considering length+this->size() for realloc threshold
		this->myRealloc(this->size() + length + 1, REASONABLE_BUFFER_SIZE);

		// Make a backup of this->string
		stringBackup = (char *) malloc(sizeof(char) * this->maxSize);
		myStrncpy(stringBackup, this->string, 0, 0, this->size());

		// Copy the new string, overwriting if necessary
		myStrncpy(this->string, s, 0, pos, length);

		// Copy the old string back
		myStrncpy(this->string, stringBackup, pos, length, this->size());

		// Increment the length by the length of the given string
		this->length += length;

		free(stringBackup);
	}
}

// Insert the string of the object sb inside the buffer at index 'pos'
// N.B: We are inserting, not replacing.
void StringBuffer::insert(const StringBuffer& sb, size_t pos) {
	size_t i;
	size_t length = sb.length;
	char *stringBackup;

	// If we need to do padding with spaces, it's like
	// an append with a bunch of spaces.
	// Otherwise, we need to save the string after pos,
	// insert the new one, and copy the old one back.
	if (pos > this->size()) {
		// Considering only pos+length for the realloc threshold,
		// since pos is already an index and is > than this->size()
		this->myRealloc(pos + length + 1, REASONABLE_BUFFER_SIZE);

		// Add spaces
		for (i = this->size(); i < pos; i++) {
			(this->string)[i] = ' ';
		}

		// Copy the new string
		myStrncpy(this->string, sb.string, 0, pos, length);

		// Increment the length by padding + length of string
		this->length += (pos - this->size()) + length;
	} else {
		// Considering length+this->size() for realloc threshold
		this->myRealloc(this->size() + length + 1, REASONABLE_BUFFER_SIZE);

		// Make a backup of this->string
		stringBackup = (char *) malloc(sizeof(char) * this->maxSize);
		myStrncpy(stringBackup, this->string, 0, 0, this->size());

		// Copy the new string, overwriting if necessary
		myStrncpy(this->string, sb.string, 0, pos, length);

		// Copy the old string back
		myStrncpy(this->string, stringBackup, pos, length, this->size());

		// Increment the length by the length of the given string
		this->length += length;

		free(stringBackup);
	}
}

// Insert the string at the end of the buffer, reallocating if necessary
void StringBuffer::append(const char *s) {
	size_t length = myStrlen(s);

	// Threshold of the realloc is given by current size + length
	this->myRealloc(this->size() + length + 1, REASONABLE_BUFFER_SIZE);
	// Append the given string
	myStrncpy(this->string, s, 0, this->size(), length);

	// Increment the length by the length of the given string
	this->length += length;
}

// Insert the string inside the object 'sb' at the end of
// the buffer, reallocating if necessary
void StringBuffer::append(const StringBuffer& sb) {
	size_t length = sb.length;

	// Threshold of the realloc is given by current size + length
	this->myRealloc(this->size() + length + 1, REASONABLE_BUFFER_SIZE);
	// Append the given string
	myStrncpy(this->string, sb.string, 0, this->size(), length);

	// Increment the length by the length of the given string
	this->length += length;
}

const char* StringBuffer::c_str() {
	return this->string;
}

// Replace the string inside the buffer with the one
// provided, reallocating if necessary
void StringBuffer::set(const char *s) {
	size_t length = myStrlen(s);

	// Threshold of the realloc is given by the length of the new string
	this->myRealloc(length + 1, REASONABLE_BUFFER_SIZE);
	// Copy the new string
	myStrncpy(this->string, s, 0, 0, length);

	// Set new length property
	this->length = length;
}

// Replace the string inside the buffer with the one
// inside the provided object, reallocating if necessary
void StringBuffer::set(const StringBuffer& sb) {
	size_t length = sb.length;

	// Threshold of the realloc is given by the length of the new string
	this->myRealloc(length + 1, REASONABLE_BUFFER_SIZE);
	// Copy the new string
	myStrncpy(this->string, sb.string, 0, 0, length);

	// Set new length property
	this->length = length;
}

StringBuffer::~StringBuffer() {
	free(this->string);
}