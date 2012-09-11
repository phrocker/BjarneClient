/*
 * KeyExtent.h
 *
 *  Created on: Sep 10, 2012
 *      Author: marc
 */

#ifndef KEYEXTENT_H_
#define KEYEXTENT_H_

#include "../client/ClientException.h"
#include <string>
#include <iostream>

using namespace std;

namespace cclient {
namespace data {

using namespace cclient::impl;
class KeyExtent {
public:
	KeyExtent(string flattenedText, Value *prevEndRow) {
		decodeMetadataRow(flattenedText);

	}
	virtual ~KeyExtent() {

	}

	bool operator <(const KeyExtent &rhs) const {
		int result = tableId.compare(rhs.tableId);

		if (result < 0)
			return result;
		else if (result > 0)
			return false;

		result = endRow.compare(rhs.endRow);

		if (result < 0)
			return result;
		else if (result > 0)
			return false;

		result = prevEndRow.compare(rhs.prevEndRow);

		if (result < 0)
			return true;
		else
			return false;
	}

	bool operator ==(const KeyExtent &rhs) const {
		int result = tableId.compare(rhs.tableId);

		if (result != 0)
			return (result == 0);

		result = endRow.compare(rhs.endRow);

		if (result != 0)
			return (result == 0);

		result = prevEndRow.compare(rhs.prevEndRow);

		if (result != 0)
			return (result == 0);

		return true;
	}

protected:
	void setPrevEndRow(Value *prevEndRow) {
		std::pair<char *, size_t> valuePair = prevEndRow->getValue();

	}
	void setPrevEndRow(char *text, size_t text_len) {
		prevEndRow = text;
	}
	void decodeMetadataRow(string flattenedText) {
		int16_t semiPos = -1;
		int16_t ltPos = -1;

		if (flattenedText.at(flattenedText.size() - 1) == ';') {
			ltPos = flattenedText.size() - 1;
		} else {
			for (int i = 0; i < flattenedText.size(); i++) {
				if (flattenedText.at(i) == ';') {
					semiPos = i;
					break;
				}
			}
		}
		if (semiPos < 0 && ltPos < 0) {
			throw new ClientException("Metadata row does not contain ; or <");
		}

		if (semiPos < 0) {
			tableId = flattenedText.substr(0, flattenedText.size() - 1);
			endRow = "";
		} else {

			tableId = flattenedText.substr(0, semiPos);

			endRow = flattenedText.substr(0,
					flattenedText.size() - (semiPos + 1));
		}

	}
	string tableId;
	string endRow;
	string prevEndRow;
};

} /* namespace data */
} /* namespace cclient */
#endif /* KEYEXTENT_H_ */
